/*
*  Shivam Choudhary : sc3973
*  Ayush Jain : aj2672
*/

#include "fbputchar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "usbkeyboard.h"
#include <pthread.h>

#define SERVER_HOST "192.168.1.1"
#define SERVER_PORT 42000

#define BUFFER_SIZE 128

/*
 * References:
 *
 * http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
 * http://www.thegeekstuff.com/2011/12/c-socket-programming/
 * 
 */

int sockfd; /* Socket file descriptor */
int row=1; //keeps track of the row on which the output is to be printed.

struct libusb_device_handle *keyboard;
uint8_t endpoint_address;

pthread_t network_thread;
void *network_thread_f(void *);
void printstring(char buffer[], int n);
int main()
{
  int err;

  struct sockaddr_in serv_addr;

  struct usb_keyboard_packet packet;
  int transferred;
  char keystate[12];

  if ((err = fbopen()) != 0) {
    fprintf(stderr, "Error: Could not open framebuffer: %d\n", err);
    exit(1);
  }

// Clears the screen in the beginning. The parameters define the from rows and to rows to be printed. 
clearscreen(0, 47);
 /* Open the keyboard */
  if ( (keyboard = openkeyboard(&endpoint_address)) == NULL ) {
    fprintf(stderr, "Did not find a keyboard\n");
    exit(1);
  }
    
  /* Create a TCP communications socket */
  if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
    fprintf(stderr, "Error: Could not create socket\n");
    exit(1);
  }

  /* Get the server address */
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERVER_PORT);
  if ( inet_pton(AF_INET, SERVER_HOST, &serv_addr.sin_addr) <= 0) {
    fprintf(stderr, "Error: Could not convert host IP \"%s\"\n", SERVER_HOST);
    exit(1);
  }

  /* Connect the socket to the server */
  if ( connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    fprintf(stderr, "Error: connect() failed.  Is the server running?\n");
    exit(1);
  }

  /* Start the network thread */
  pthread_create(&network_thread, NULL, network_thread_f, NULL);

char buffer[BUFFER_SIZE];
int i=0, numChars=0;
  memset(buffer, 0, BUFFER_SIZE);
  /* Look for and handle keypresses */
  for (;;) {
    libusb_interrupt_transfer(keyboard, endpoint_address,
			      (unsigned char *) &packet, sizeof(packet),
			      &transferred, 0);
    
    if (transferred == sizeof(packet)) {
      sprintf(keystate, "%02x %02x %02x", packet.modifiers, packet.keycode[0],
	      packet.keycode[1]);
      int input, curRow, curCol;
      bool shift; 
      input = packet.keycode[0];
      //boolean variable holds information of shift key(true if pressed else false).
      shift = (packet.modifiers==0x02 || packet.modifiers==0x20); 
      // Current cursor position in the input text area.
      curRow = i>127 ? 45 : 44;
      curCol = i>127 ? i-127: i;
      //Called after any key is released.
      if(input == 0){
      	// clear and re-print the data buffer.
	clearscreen(44, 46);
	fbputs(buffer, 44, 0);
	fbputchar('_', curRow, curCol); // Prints the cursor.
	continue;
      }
      // Backspace key.
      if(input == 0x2a){
	if(i>0){
	  if(i<numChars){
	    int j;
	    j = i-1;
	    while(j<numChars){
	      buffer[j] = buffer[j+1];
	      j++;
	    }
	    buffer[j]=0;
	  }else{
	    buffer[i-1]=0;
	  }
	  i--;
	  numChars--;
	}
	continue;
      }
      //left arrow key
      if(input == 0x50){
	if(i>0){
	  i--;
	}
	continue;
      }
      // right arrow key.
      if(input == 0x4f){
	if(i<numChars){
	  i++;
	}
	continue;
      }
      //checks if shift is pressed or not.
      //Accordingly, prints capital or lowercase letters.
      if(input != 40){
	if(shift)
	  input += 61;
	else
	  input += 93;
	buffer[i++] = (char)(input);
	numChars++;
	fbputs(buffer, 44, 0);
      }else{
 	int n;
	n = write(sockfd, buffer, BUFFER_SIZE);	
	if(n<0){	  
	    fprintf(stderr, "Error: write() failed.  Is the server running?\n");
	}
	printstring(buffer, i+1);
 	clearscreen(44, 46);	
	i=0;numChars=0;
	memset(buffer, 0, BUFFER_SIZE);
      }

	if (packet.keycode[0] == 0x29) { /* ESC pressed? */
	break;
      }
    }
  }

  /* Terminate the network thread */
  pthread_cancel(network_thread);

  /* Wait for the network thread to finish */
  pthread_join(network_thread, NULL);

  return 0;
}

void *network_thread_f(void *ignored)
{
  char recvBuf[BUFFER_SIZE];
  int n;
  /* Receive data */
  while ( (n = read(sockfd, &recvBuf, BUFFER_SIZE - 1)) > 0 ) {
    recvBuf[n] = '\0';
    printstring(recvBuf, n);
  }
  return NULL;
}

// To print a buffer text of a particular length.
// Takes care of the row where data is to be printed.
void printstring(char recvBuf[], int n){
    fbputs(recvBuf, row, 0);
    if((row+n/128+1)>42){
	clearscreen(0, 44);
	row = 1;
    }else{
	row += n%128 == 0 ? n/128 : n/128+1 ;
    }
}

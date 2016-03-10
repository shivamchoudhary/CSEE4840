/*
 * Userspace program that communicates with the led_vga device driver
 * primarily through ioctls
 *
 * Ayush Jain : aj2672
 * Shivam Choudhary : sc3973
 * Columbia University
 */

#include <stdio.h>
#include "vga_led.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int vga_led_fd;

/* Read and print the segment values */
void print_segment_info() {
  vga_led_arg_t vla;
  int i;

  for (i = 0 ; i < 4 ; i++) {
    vla.digit = i;
    if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
      perror("ioctl(VGA_LED_READ_DIGIT) failed");
      return;
    }
    printf("%02x ", vla.segments);
  }
  printf("\n");
}

/* Write the contents of the array to the display */
void write_segments(const unsigned char segs[4])
{
  vga_led_arg_t vla;
  int i;
  for (i = 0 ; i < 4 ; i++) {
    vla.digit = i;
    vla.segments = segs[i];
    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
      perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
      return;
    }
  }
}

int main()
{
  vga_led_arg_t vla;
  int i;
  static const char filename[] = "/dev/vga_led";

  static unsigned char message[4] = { 0x3f, 0x00, 0x3f, 0x00 };

  printf("VGA LED Userspace program started\n");

  if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
    fprintf(stderr, "could not open %s\n", filename);
    return -1;
  }

  printf("initial state: ");
  print_segment_info();

  write_segments(message);

  printf("current state: ");
  print_segment_info();

  int slope = -1, x = 0x3f, y = 0x3f;
  char direction = 'd';
  for(;;) {
    switch(direction){
        case('d'):{
	    x -= slope;
	    y += 1;
	    if( x<=0x3f || x>= (640-0x3f))
		slope *= -1;
	    if( y >= (480-0x3f) ){
		direction = 'u';
		slope *= -1;
	    }
	    break;
        }
	case('u'):{
	    x += slope;
	    y -= 1;
	    if( x <= 0x3f || x >= (640-0x3f))
		slope *= -1;
	    if( y <= (0x3f) ){
		direction = 'd';
		slope *= -1;
	    }
	    break;
	}
    }
    message[0] = x%256;
    message[1] = x/256;
    message[2] = y%256;
    message[3] = y/256;
    write_segments(message);
    usleep(4000);
  }
  
  printf("VGA LED Userspace program terminating\n");
  return 0;
}

// CSEE 4840 Lab1: Display and modify the contents of memory
//
// Spring 2014
//
// Ayush Jain: aj2672
// Shivam Choudhary: sc3973

module lab1(input logic       clk,
            input logic [3:0] KEY,
            output [7:0]      hex0, hex2, hex3);

   logic [3:0] 		      a;         // Address
   logic [7:0] 		      din, dout; // RAM data in and out
   logic 		      we;        // RAM write enable

   hex7seg h0( .a(a),         .y(hex0) ),
           h1( .a(dout[7:4]), .y(hex2) ),
           h2( .a(dout[3:0]), .y(hex3) );

   controller c( .* ); // Connect everything with matching names
   memory m( .* );
  
endmodule

module controller(input logic        clk,
		  input logic [3:0]  KEY,
		  input logic [7:0]  dout,
		  output logic [3:0] a,
		  output logic [7:0] din,
		  output logic 	     we);

   // Replace these with your code
		logic flag; //flag required to change only on input.
		logic [7:0] 			 mem [15:0];
		always_ff @(posedge clk)
			case (~KEY)
				4'b0001: if(flag ==1'b0) //KEY 0 Increments the value to be stored in Memory a
					begin
						din =dout+8'b00000001;
						flag=1'b1;
						we = 1'b1;
					end
				4'b0010: if(flag ==1'b0) //KEY 1 Decrements the value to be stored in Memory a
					begin
						din =dout-8'b00000001;
						flag=1'b1;
						we = 1'b1;
					end
				4'b0100: if(flag ==1'b0) //Key 2 Increments the memory address of a
					begin 
						a = a+4'b0001;
						flag =1'b1;
						we = 1'b0;
					end
				4'b1000: if(flag ==1'b0) //Key 3 Decrements the memory address of a
					begin 
						a = a-4'b0001;
						flag=1'b1;
						we = 1'b0;
					end
				4'b1100: if(flag ==1'b0)
					begin
						
					end
				default: flag=1'b0;// Default sets flag to Zero.
			endcase			
endmodule
		  
module hex7seg(input logic [3:0] a,
	       output logic [7:0] y);

  // Replace this with your code
	always_comb 
		case (~a)
			//7 Segment output codes. B and D are small because they resemble 8 and 0
			// respectively.
			4'd0: 	y = 8'b00111111; //0
			4'd1: 	y = 8'b00000110; //1
			4'd2: 	y = 8'b01011011; //2
			4'd3: 	y = 8'b01001111; //3
			4'd4: 	y = 8'b01100110; //4
			4'd5: 	y = 8'b01101101; //5
			4'd6: 	y = 8'b01111101; //6
			4'd7: 	y = 8'b00000111; //7  
			4'd8: 	y = 8'b01111111; //8
			4'd9: 	y = 8'b01100111; //9
			4'd10: 	y = 8'b01110111; //A
			4'd11: 	y = 8'b01111100; //b
			4'd12: 	y = 8'b00111001; //C
			4'd13: 	y = 8'b01011110; //d
			4'd14: 	y = 8'b01111001; //E
			4'd15: 	y = 8'b01110001; //F
			default: y = 8'b00000000;
		endcase
endmodule

// 16 X 8 synchronous RAM with old data read-during-write behavior
module memory(input logic        clk,
	      input logic [3:0]  a,
	      input logic [7:0]  din,
	      input logic 	 we,
	      output logic [7:0] dout);
   
   logic [7:0] 			 mem [15:0];

   always_ff @(posedge clk) begin
      if (we) mem[a] <= din;
      dout <= mem[a];
   end
        
endmodule


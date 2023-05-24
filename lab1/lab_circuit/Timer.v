module Timer(clk, reset, out_pos);
	input clk;
	input reset;
	output reg [28:0]out_pos;
	
	always @(posedge clk)
	begin
		if (reset == 0)
			out_pos = 0;
		else
			out_pos <= out_pos + 1'd1;
	end
endmodule
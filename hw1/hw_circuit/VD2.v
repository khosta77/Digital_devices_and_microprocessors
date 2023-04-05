module VD2(clk, out_pos);
	input clk;
	output reg [19:0]out_pos;
	
	always @(posedge clk)
	begin
		out_pos <= out_pos + 1'd1;
	end
endmodule
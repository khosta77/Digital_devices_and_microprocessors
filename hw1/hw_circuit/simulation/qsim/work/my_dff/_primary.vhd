library verilog;
use verilog.vl_types.all;
entity my_dff is
    port(
        O1              : out    vl_logic;
        C               : in     vl_logic;
        O0              : out    vl_logic;
        RESET           : out    vl_logic
    );
end my_dff;

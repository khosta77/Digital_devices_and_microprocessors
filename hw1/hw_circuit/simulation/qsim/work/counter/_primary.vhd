library verilog;
use verilog.vl_types.all;
entity counter is
    port(
        A               : out    vl_logic;
        START           : in     vl_logic;
        B               : out    vl_logic;
        C               : out    vl_logic;
        D               : out    vl_logic;
        E               : out    vl_logic;
        F               : out    vl_logic;
        G               : out    vl_logic
    );
end counter;

library verilog;
use verilog.vl_types.all;
entity two_circuit is
    port(
        A               : out    vl_logic;
        X3              : in     vl_logic;
        X2              : in     vl_logic;
        X1              : in     vl_logic;
        X0              : in     vl_logic;
        B               : out    vl_logic;
        C               : out    vl_logic;
        D               : out    vl_logic;
        E               : out    vl_logic;
        F               : out    vl_logic;
        G               : out    vl_logic
    );
end two_circuit;

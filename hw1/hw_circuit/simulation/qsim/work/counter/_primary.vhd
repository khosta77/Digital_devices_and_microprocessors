library verilog;
use verilog.vl_types.all;
entity counter is
    port(
        LED_A           : out    vl_logic;
        START           : in     vl_logic;
        LED_B           : out    vl_logic;
        LED_C           : out    vl_logic;
        LED_D           : out    vl_logic;
        LED_E           : out    vl_logic;
        LED_F           : out    vl_logic;
        LED_G           : out    vl_logic
    );
end counter;

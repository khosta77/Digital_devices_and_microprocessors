library verilog;
use verilog.vl_types.all;
entity counter_vlg_check_tst is
    port(
        LED_A           : in     vl_logic;
        LED_B           : in     vl_logic;
        LED_C           : in     vl_logic;
        LED_D           : in     vl_logic;
        LED_E           : in     vl_logic;
        LED_F           : in     vl_logic;
        LED_G           : in     vl_logic;
        sampler_rx      : in     vl_logic
    );
end counter_vlg_check_tst;

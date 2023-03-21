library verilog;
use verilog.vl_types.all;
entity my_dff_vlg_check_tst is
    port(
        O0              : in     vl_logic;
        O1              : in     vl_logic;
        RESET           : in     vl_logic;
        sampler_rx      : in     vl_logic
    );
end my_dff_vlg_check_tst;

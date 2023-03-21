library verilog;
use verilog.vl_types.all;
entity asynchronous_counter_vlg_check_tst is
    port(
        Q0              : in     vl_logic;
        Q1              : in     vl_logic;
        Q2              : in     vl_logic;
        RESET           : in     vl_logic;
        sampler_rx      : in     vl_logic
    );
end asynchronous_counter_vlg_check_tst;

library verilog;
use verilog.vl_types.all;
entity asynchronous_counter_vlg_sample_tst is
    port(
        C               : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end asynchronous_counter_vlg_sample_tst;

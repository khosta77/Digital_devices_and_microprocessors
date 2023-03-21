library verilog;
use verilog.vl_types.all;
entity counter_vlg_sample_tst is
    port(
        START           : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end counter_vlg_sample_tst;

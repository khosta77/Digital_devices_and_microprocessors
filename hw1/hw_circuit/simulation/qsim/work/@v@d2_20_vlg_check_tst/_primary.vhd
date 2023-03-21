library verilog;
use verilog.vl_types.all;
entity VD2_20_vlg_check_tst is
    port(
        OUT2            : in     vl_logic;
        OUT4            : in     vl_logic;
        OUT8            : in     vl_logic;
        OUT16           : in     vl_logic;
        OUT32           : in     vl_logic;
        OUT64           : in     vl_logic;
        OUT128          : in     vl_logic;
        OUT256          : in     vl_logic;
        OUT512          : in     vl_logic;
        OUT1024         : in     vl_logic;
        OUT2048         : in     vl_logic;
        OUT4096         : in     vl_logic;
        OUT8192         : in     vl_logic;
        OUT16384        : in     vl_logic;
        OUT32768        : in     vl_logic;
        OUT65536        : in     vl_logic;
        OUT131072       : in     vl_logic;
        OUT262144       : in     vl_logic;
        OUT524288       : in     vl_logic;
        OUT1048576      : in     vl_logic;
        sampler_rx      : in     vl_logic
    );
end VD2_20_vlg_check_tst;

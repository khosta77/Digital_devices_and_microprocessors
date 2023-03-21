library verilog;
use verilog.vl_types.all;
entity VD2_20 is
    port(
        OUT2            : out    vl_logic;
        START           : in     vl_logic;
        OUT4            : out    vl_logic;
        OUT8            : out    vl_logic;
        OUT16           : out    vl_logic;
        OUT32           : out    vl_logic;
        OUT64           : out    vl_logic;
        OUT128          : out    vl_logic;
        OUT256          : out    vl_logic;
        OUT512          : out    vl_logic;
        OUT1024         : out    vl_logic;
        OUT2048         : out    vl_logic;
        OUT4096         : out    vl_logic;
        OUT8192         : out    vl_logic;
        OUT16384        : out    vl_logic;
        OUT32768        : out    vl_logic;
        OUT65536        : out    vl_logic;
        OUT131072       : out    vl_logic;
        OUT262144       : out    vl_logic;
        OUT524288       : out    vl_logic;
        OUT1048576      : out    vl_logic
    );
end VD2_20;

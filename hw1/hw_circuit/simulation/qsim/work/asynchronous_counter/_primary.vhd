library verilog;
use verilog.vl_types.all;
entity asynchronous_counter is
    port(
        Q0              : out    vl_logic;
        C               : in     vl_logic;
        Q1              : out    vl_logic;
        Q2              : out    vl_logic;
        RESET           : out    vl_logic
    );
end asynchronous_counter;

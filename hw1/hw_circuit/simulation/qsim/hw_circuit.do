onerror {quit -f}
vlib work
vlog -work work hw_circuit.vo
vlog -work work hw_circuit.vt
vsim -novopt -c -t 1ps -L cycloneiv_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.counter_vlg_vec_tst
vcd file -direction hw_circuit.msim.vcd
vcd add -internal counter_vlg_vec_tst/*
vcd add -internal counter_vlg_vec_tst/i1/*
add wave /*
run -all

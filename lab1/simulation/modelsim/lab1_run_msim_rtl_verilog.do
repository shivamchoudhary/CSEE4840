transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+/home/user3/spring16/sc3973/CSEE4840/lab1 {/home/user3/spring16/sc3973/CSEE4840/lab1/VGA_LED_Emulator.sv}
vlog -sv -work work +incdir+/home/user3/spring16/sc3973/CSEE4840/lab1 {/home/user3/spring16/sc3973/CSEE4840/lab1/lab1.sv}
vlog -sv -work work +incdir+/home/user3/spring16/sc3973/CSEE4840/lab1 {/home/user3/spring16/sc3973/CSEE4840/lab1/SoCKit_Top.sv}


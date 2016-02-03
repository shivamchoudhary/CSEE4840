library verilog;
use verilog.vl_types.all;
entity memory is
    port(
        clk             : in     vl_logic;
        a               : in     vl_logic_vector(3 downto 0);
        din             : in     vl_logic_vector(7 downto 0);
        we              : in     vl_logic;
        dout            : out    vl_logic_vector(7 downto 0)
    );
end memory;

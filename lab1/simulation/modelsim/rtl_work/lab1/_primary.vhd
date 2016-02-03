library verilog;
use verilog.vl_types.all;
entity lab1 is
    port(
        clk             : in     vl_logic;
        KEY             : in     vl_logic_vector(3 downto 0);
        hex0            : out    vl_logic_vector(7 downto 0);
        hex2            : out    vl_logic_vector(7 downto 0);
        hex3            : out    vl_logic_vector(7 downto 0)
    );
end lab1;

library verilog;
use verilog.vl_types.all;
entity controller is
    port(
        clk             : in     vl_logic;
        KEY             : in     vl_logic_vector(3 downto 0);
        dout            : in     vl_logic_vector(7 downto 0);
        a               : out    vl_logic_vector(3 downto 0);
        din             : out    vl_logic_vector(7 downto 0);
        we              : out    vl_logic
    );
end controller;

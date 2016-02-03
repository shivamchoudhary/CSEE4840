library verilog;
use verilog.vl_types.all;
entity VGA_LED_Emulator is
    generic(
        HACTIVE         : vl_logic_vector(0 to 10) := (Hi1, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        HFRONT_PORCH    : vl_logic_vector(0 to 10) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        HSYNC           : vl_logic_vector(0 to 10) := (Hi0, Hi0, Hi0, Hi1, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        HBACK_PORCH     : vl_logic_vector(0 to 10) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        HTOTAL          : vl_notype;
        VACTIVE         : vl_logic_vector(0 to 9) := (Hi0, Hi1, Hi1, Hi1, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        VFRONT_PORCH    : vl_logic_vector(0 to 9) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0);
        VSYNC           : vl_logic_vector(0 to 9) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        VBACK_PORCH     : vl_logic_vector(0 to 9) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi1);
        VTOTAL          : vl_notype
    );
    port(
        clk50           : in     vl_logic;
        reset           : in     vl_logic;
        hex0            : in     vl_logic_vector(7 downto 0);
        hex1            : in     vl_logic_vector(7 downto 0);
        hex2            : in     vl_logic_vector(7 downto 0);
        hex3            : in     vl_logic_vector(7 downto 0);
        hex4            : in     vl_logic_vector(7 downto 0);
        hex5            : in     vl_logic_vector(7 downto 0);
        hex6            : in     vl_logic_vector(7 downto 0);
        hex7            : in     vl_logic_vector(7 downto 0);
        VGA_R           : out    vl_logic_vector(7 downto 0);
        VGA_G           : out    vl_logic_vector(7 downto 0);
        VGA_B           : out    vl_logic_vector(7 downto 0);
        VGA_CLK         : out    vl_logic;
        VGA_HS          : out    vl_logic;
        VGA_VS          : out    vl_logic;
        VGA_BLANK_n     : out    vl_logic;
        VGA_SYNC_n      : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of HACTIVE : constant is 1;
    attribute mti_svvh_generic_type of HFRONT_PORCH : constant is 1;
    attribute mti_svvh_generic_type of HSYNC : constant is 1;
    attribute mti_svvh_generic_type of HBACK_PORCH : constant is 1;
    attribute mti_svvh_generic_type of HTOTAL : constant is 3;
    attribute mti_svvh_generic_type of VACTIVE : constant is 1;
    attribute mti_svvh_generic_type of VFRONT_PORCH : constant is 1;
    attribute mti_svvh_generic_type of VSYNC : constant is 1;
    attribute mti_svvh_generic_type of VBACK_PORCH : constant is 1;
    attribute mti_svvh_generic_type of VTOTAL : constant is 3;
end VGA_LED_Emulator;

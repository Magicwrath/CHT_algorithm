library ieee;
use ieee.std_logic_1164.all;
use IEEE.NUMERIC_STD.ALL;

package pkg is

type arr_type is array (natural range <>) of signed(9 downto 0);

function init_sin_f return arr_type;

function init_cos_f return arr_type;

end;

package body pkg is

  function init_sin_f return arr_type is
    variable sin_samples_arr : arr_type(0 to 360);
    constant sin : arr_type := ("0000000000", "0000000001", "0000000010", "0000000011", "0000000100", "0000000101", "0000000110", "0000000111", "0000001000", "0000001010", "0000001011", "0000001100",
                                "0000001101", "0000001110", "0000001111", "0000010000", "0000010001", "0000010010", "0000010011", "0000010100", "0000010101", "0000010110", "0000010111", "0000011001",
                                "0000011010", "0000011011", "0000011100", "0000011101", "0000011110", "0000011111", "0000011111", "0000100000", "0000100001", "0000100010", "0000100011", "0000100100",
                                "0000100101", "0000100110", "0000100111", "0000101000", "0000101001", "0000101001", "0000101010", "0000101011", "0000101100", "0000101101", "0000101110", "0000101110",
                                "0000101111", "0000110000", "0000110001", "0000110001", "0000110010", "0000110011", "0000110011", "0000110100", "0000110101", "0000110101", "0000110110", "0000110110",
                                "0000110111", "0000110111", "0000111000", "0000111001", "0000111001", "0000111010", "0000111010", "0000111010", "0000111011", "0000111011", "0000111100", "0000111100",
                                "0000111100", "0000111101", "0000111101", "0000111101", "0000111110", "0000111110", "0000111110", "0000111110", "0000111111", "0000111111", "0000111111", "0000111111", 
                                "0000111111", "0000111111", "0000111111", "0000111111", "0000111111", "0000111111", "0001000000");
  begin
    for i in 0 to 360 loop 
      if (i > 90 and i < 181) then          --second quadrant
        sin_samples_arr(i) := sin(180 - i);
      elsif (i > 180 and i < 271) then      --third quadrant
        sin_samples_arr(i) := -sin(i - 180);
      elsif (i > 270 and i < 361) then      --forth quadrant
        sin_samples_arr(i) := -sin(360 - i);
      else                                  --first quadrant
        sin_samples_arr(i) := sin(i);
      end if;
    end loop;
    return sin_samples_arr;
  end;
  
  function init_cos_f return arr_type is
    variable cos_samples_arr : arr_type(0 to 360);
    constant cos : arr_type := ("0001000000", "0000111111", "0000111111", "0000111111", "0000111111", "0000111111", "0000111111", "0000111111", "0000111111", "0000111111", "0000111111", "0000111110",
                                "0000111110", "0000111110", "0000111110", "0000111101", "0000111101", "0000111101", "0000111100", "0000111100", "0000111100", "0000111011", "0000111011", "0000111010",
                                "0000111010", "0000111010", "0000111001", "0000111001", "0000111000", "0000110111", "0000110111", "0000110110", "0000110110", "0000110101", "0000110101", "0000110100",
                                "0000110011", "0000110011", "0000110010", "0000110001", "0000110001", "0000110000", "0000101111", "0000101110", "0000101110", "0000101101", "0000101100", "0000101011",
                                "0000101010", "0000101001", "0000101001", "0000101000", "0000100111", "0000100110", "0000100101", "0000100100", "0000100011", "0000100010", "0000100001", "0000100000",
                                "0000100000", "0000011111", "0000011110", "0000011101", "0000011100", "0000011011", "0000011010", "0000011001", "0000010111", "0000010110", "0000010101", "0000010100",
                                "0000010011", "0000010010", "0000010001", "0000010000", "0000001111", "0000001110", "0000001101", "0000001100", "0000001011", "0000001010", "0000001000", "0000000111",
                                "0000000110", "0000000101", "0000000100", "0000000011", "0000000010", "0000000001", "0000000000");
  begin
    for i in 0 to 360 loop 
      if (i > 90 and i < 181) then          --second quadrant
        cos_samples_arr(i) := -cos(180 - i);
      elsif (i > 180 and i < 271) then      --third quadrant
        cos_samples_arr(i) := -cos(i - 180);
      elsif (i > 270 and i < 361) then      --forth quadrant
        cos_samples_arr(i) := cos(360 - i);
      else                                  --first quadrant
        cos_samples_arr(i) := cos(i);
      end if;
    end loop;
    return cos_samples_arr;
  end;
end;

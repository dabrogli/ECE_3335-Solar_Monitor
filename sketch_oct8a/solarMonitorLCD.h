#include <LiquidCrystal.h>

using namespace std;


#define size_pow 4;

class solarMonitorLCD {
  public:
    LiquidCrystal* lcd;
    solarMonitorLCD(int rs, int e, int d4, int d5, int d6, int d7){
      lcd = new LiquidCrystal(rs, e, d4, d5, d6, d7);
      (*lcd).begin(16, 2);
      (*lcd).clear();
      startup();
    }
  

    void startup() {
      (*lcd).clear();

      (*lcd).setCursor(0, 0);
      (*lcd).print("P:");

      (*lcd).setCursor(7, 0);
      (*lcd).print("W|");

      
      (*lcd).setCursor(9, 0);
      (*lcd).print("E:");

      (*lcd).setCursor(15, 0);
      (*lcd).print("%");

      (*lcd).setCursor(0, 1);
      (*lcd).print("I:");

      (*lcd).setCursor(7, 1);
      (*lcd).print("U|");

      (*lcd).setCursor(9, 1);
      (*lcd).print("T:");

      (*lcd).setCursor(15, 1);
      (*lcd).print("C|");

    }

    void write_pow(double pow) {
      char str_pow[] = "__._";

      trim_input(pow, 20.0, sizeof(str_pow), str_pow);

      (*lcd).setCursor(2, 0);

      safe_print_char(str_pow, sizeof(str_pow));
    }

    void write_irrad(double irrad) {
      char str_irrad[] = "__._";

      trim_input(irrad, 20.0, sizeof(str_irrad), str_irrad);

      (*lcd).setCursor(2, 1);

      safe_print_char(str_irrad, sizeof(str_irrad));
    }

    void write_eff(double eff) {
      char str_eff[] = "_._";

      trim_input(eff, 100.0, sizeof(str_eff), str_eff);

      (*lcd).setCursor(11, 0);

      safe_print_char(str_eff, sizeof(str_eff));
    }

    void write_temp(double temp) {
      char str_temp[] = "_._";

      trim_input(temp, 20.0, sizeof(str_temp), str_temp);

      (*lcd).setCursor(11, 1);

      safe_print_char(str_temp, sizeof(str_temp));
    }

    void safe_print_char(char* lcd_out, int length) {
      length = length - 1;
      for (int x = 0; x < length; x++) (*lcd).print(lcd_out[x]);
    }

    void trim_input(double input, double input_max, int length, char* output) {

      double max_log = log10(input_max);
      double input_log = log10(input);

      int max_place = (int) max_log;
      int input_place = (int) input_log;

      length = length - 1;

      double used_num = input;

      int max_index = length;
      int min_index = -length;

      int number_place = input_place;

      if (number_place < 0) {
        number_place = 0; 
      }
      
      if (input_place > length - 1) {
        number_place = length - 1;
        used_num = 10 * pow(10, length - 1) - 1;

      } else if (input_place <= -length + 1 || used_num == 0) {
        number_place = 0;
        used_num = 0;
      }

      for (int x = 0; x < length; x++) {

        double scale = 0;
        int temp_num = 0;

      
        scale = pow(10, number_place);

        if (x >= length - 1) temp_num = (int) round(used_num / scale);
        else temp_num = (int) (used_num / scale);

        used_num = used_num - temp_num * scale;
        
        output[x] = '0' + temp_num;

        if (number_place == 0) {
          x++;
          output[x] = '.';
        }

        number_place--;
      }
    }
};
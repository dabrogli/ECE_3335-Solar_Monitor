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
      length = length - 1;

      double input_log = log10(input);

      int input_place = (int) (input_log);

      int number_place = 0;
      if (input_place >= 0) number_place = input_place;
      else number_place = input_place - 1;

      int scale_power = length - number_place;

      int snip_num, snip_pow;

      if (input_place > length - 1) {
        number_place = length - 1;
        snip_num = 10 * pow(10, length - 1) - 1;
        snip_pow =  (int) log10(snip_num);

        Serial.println("Too Big.");

      } else if (input_place <= -length + 2 || input == 0) {
        number_place = 0;
        snip_num = 0;
        snip_pow = 0;
        Serial.println("Too Small.");
      } else {
        snip_num = round(input * pow(10, scale_power));
        snip_pow =  (int) log10(snip_num);
      }
      Serial.print("input_log: ");
      Serial.println(input_log);
      Serial.print("input_place: ");
      Serial.println(input_place);


      Serial.print("snip_num: ");
      Serial.println(snip_num);
      Serial.print("snip_pow: ");
      Serial.println(snip_pow);

      Serial.print("number_place: ");
      Serial.println(number_place);

      for (int x = 0; x < length; x++) {
        double scale = pow(10, snip_pow);
        int temp_num = snip_num / scale;
        
        if (number_place == -1) {
          output[x] = '.';
          x++;
       }

        output[x] = '0' + temp_num;
        
        snip_num = (int) snip_num - temp_num * scale;

        number_place--;
        snip_pow--;
      }
    }
};
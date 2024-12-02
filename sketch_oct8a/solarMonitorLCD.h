#include <LiquidCrystal.h>

#define size_pow 4;

class solarMonitorLCD {
  public:
    LiquidCrystal* lcd;
    double power = 0, irrad = 0, eff = 0, temp = 0, volt = 0, curr = 0;

    solarMonitorLCD(int rs, int e, int d4, int d5, int d6, int d7){
      lcd = new LiquidCrystal(rs, e, d4, d5, d6, d7);
      (*lcd).begin(16, 2);
      (*lcd).clear();
      startup_1();
    }
  
    void startup_1() {
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
    
    void startup_2() {
      (*lcd).clear();

      (*lcd).setCursor(0, 0);
      (*lcd).print("V:");

      (*lcd).setCursor(7, 0);
      (*lcd).print("V|");

      (*lcd).setCursor(0, 1);
      (*lcd).print("C:");

      (*lcd).setCursor(7, 1);
      (*lcd).print("A|");
    }

    void update_screen_1() {
      write_pow(power);
      write_irrad(irrad);
      write_temp(temp);
      write_eff(eff);
    }

    void update_screen_2() {
      write_volt(volt);
      write_curr(curr);
    }

    void write_pow(double power) {
      char str_pow[5] = "__._";

      trim_input(power, sizeof(str_pow) - 1, str_pow);

      (*lcd).setCursor(2, 0);

      safe_print_char(str_pow, sizeof(str_pow));
    }

    void write_volt(double volt) {
      char str_volt[5] = "__._";

      trim_input(volt, sizeof(str_volt) - 1, str_volt);

      (*lcd).setCursor(2, 0);

      safe_print_char(str_volt, sizeof(str_volt));
    }

    void write_curr(double curr) {
      char str_curr[5] = "__._";

      trim_input(curr, sizeof(str_curr) - 1, str_curr);

      (*lcd).setCursor(2, 1);

      safe_print_char(str_curr, sizeof(str_curr));
    }

    void write_irrad(double irrad) {
      char str_irrad[5] = "__._";

      trim_input(irrad, sizeof(str_irrad) - 1, str_irrad);

      (*lcd).setCursor(2, 1);

      safe_print_char(str_irrad, sizeof(str_irrad));
    }

    void write_eff(double eff) {
      char str_eff[4] = "_._";

      trim_input(eff, sizeof(str_eff) - 1, str_eff);

      (*lcd).setCursor(11, 0);

      safe_print_char(str_eff, sizeof(str_eff));
    }

    void write_temp(double temp) {
      char str_temp[4] = "_._";

      trim_input(temp, sizeof(str_temp) - 1, str_temp);

      (*lcd).setCursor(11, 1);

      safe_print_char(str_temp, sizeof(str_temp));
    }

    void safe_print_char(char* lcd_out, int length) {
      length = length - 1;
      for (int x = 0; x < length; x++) (*lcd).print(lcd_out[x]);
    }

void trim_input(double number, int length, char * output) {
	int pos = 0;

	double limit = pow(10, length - 1);

	if (number >= limit) number = limit - 1;
	if (number < 0) number = 0;

	if (number < 1) {
		pos = -1;
	} else {
		pos = (int) log10(number);
		if (number < pow(10, pos)) pos--;
	}

	int scale_power = length - pos - 2;
	int snip_num = round(number * pow(10, scale_power));

	for(int pow_pos = length - 2, char_pos = 0; char_pos < length; char_pos++) {
		if (pos == -1) {
			output[char_pos] = '.';
			char_pos++;
		}
		if (char_pos >= length) continue;

		double scale = pow(10, pow_pos);
		
		int temp_number = (int) (snip_num / scale);
    
		snip_num = snip_num - (int) (temp_number * scale);

		output[char_pos] = '0' + temp_number;

		pos--;
		pow_pos--;
	}
	
	output[length] = '\0';
  
  //    Serial.println(output);
  }
};

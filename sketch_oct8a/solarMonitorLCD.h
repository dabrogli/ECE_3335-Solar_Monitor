#include <LiquidCrystal.h>

class solarMonitorLCD {
  public:
    LiquidCrystal* lcd;
    solarMonitorLCD(int rs, int e, int d4, int d5, int d6, int d7){
      lcd = new LiquidCrystal(rs, e, d4, d5, d6, d7);
      (*lcd).begin(16, 2);
      (*lcd).print("Pointer within object.");
      startup();
    }
  

    void startup() {
      (*lcd).clear();

      (*lcd).setCursor(0, 0);
      (*lcd).print("P:");

      (*lcd).setCursor(6, 0);
      (*lcd).print("W|");


      (*lcd).setCursor(0, 1);
      (*lcd).print("T:");

      (*lcd).setCursor(6, 1);
      (*lcd).print("C|");


      (*lcd).setCursor(8, 0);
      (*lcd).print("E:");

      (*lcd).setCursor(15, 0);
      (*lcd).print("%");
    }

    void write_power(double pow) {

    }

    void write_irrad(double irrad) {

    }

    void write_eff(double eff) {

    }

    void write_temp(int temp) {

    }
};
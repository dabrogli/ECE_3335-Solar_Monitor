#include <LiquidCrystal.h>

class solarMonitorLCD {
  public:
    LiquidCrystal* lcd;
    solarMonitorLCD(int rs, int e, int d4, int d5, int d6, int d7){
      lcd = new LiquidCrystal(rs, e, d4, d5, d6, d7);
    }
  
};
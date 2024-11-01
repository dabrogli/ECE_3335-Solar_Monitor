#include <LiquidCrystal.h>

double R_a = 303000;
double R_b = 99800;

double R_f = 402000;
double R_o = 99900;
double R_s = 1;

double stupid = (double)5.0/1024.0;

LiquidCrystal lcd(8, 13, 12, 11, 10, 9);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.write("Hello World.");
}

void loop() {
  // put your main code here, to run repeatedly:
  int analog_voltage = analogRead(A0);
  int analog_current = analogRead(A1);
  int analog_photodi = analogRead(A2);

  double voltage = stupid*(double)analog_voltage; //mV
  double current = stupid*(double)analog_current; //mV

  double Solar_Vmv = voltage*(1+(R_a/R_b));
  double Solar_Imv = current/(R_s*(1 + (R_f/R_o)));

  double Solar_V = Solar_Vmv;
  double Solar_I = Solar_Imv;



  delay(100);

    if (analog_voltage>= 512) {
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
    }
        if (analog_voltage< 512) {
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    }
        //Serial.println(Solar_I);
        //Serial.println(current);

        
        Serial.print(voltage);
        Serial.print(",");
        Serial.print(current);
        Serial.print(",");
        Serial.print (Solar_V);
        Serial.print (",");
        Serial.print (Solar_I);
        Serial.println(" ");
        

}

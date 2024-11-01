#define pin_light 6
#define pin_voltage_in A0
#define pin_current_in A1

#define R_curr_f 402000
#define R_curr_o 99900
#define R_curr_shunt 1

#define R_volt_a 303000
#define R_volt_b 99800

//#include <LiquidCrystalDisplay.h>

int raw_v_voltage = 0;
int raw_v_current = 0;

double adj_v_voltage = 0;
double adj_v_current = 0;

double volt_in = 0;
double curr_in = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(pin_light, OUTPUT);

  digitalWrite(pin_light, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  //delay(1000);
  //digitalWrite(pin_light, LOW);
  
  //delay(1000);
  //digitalWrite(pin_light, HIGH);
  
  //Serial.println(F("\n---===NEWLINE===---"));

  //raw_v_voltage = analogRead(pin_voltage_in);
  //raw_v_current = analogRead(pin_current_in);

  //adj_v_voltage = (double) raw_v_voltage*5.0/1024.0;
  //adj_v_current = (double) raw_v_current*5.0/1024.0;

  
  //adj_v_voltage = adj_v_voltage*1.018050685;
  //adj_v_current = adj_v_current*1.017622212;


  //volt_in = adj_v_voltage*(1 + R_volt_a/R_volt_b);
  //curr_in = adj_v_current/(R_curr_shunt*(1 + R_curr_f/R_curr_o));


  //Serial.print(F("V: "));
  //Serial.print(volt_in);
  //Serial.println(" V");

  //Serial.print(F("I: "));
  //Serial.print(curr_in);
  //Serial.println(" A");

  //Serial.print(volt_in);
  //Serial.print(",");
  //Serial.println(curr_in);
}

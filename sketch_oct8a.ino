double R_a = 303000;
double R_b = 99800;

double R_f = 402000;
double R_o = 99900;
double R_s = 1;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  int analog_voltage = analogRead(A0);
  int analog_current = analogRead(A1);

  double voltage = 4.88281*analog_voltage; //mV
  double current = 4.88281*analog_current; //mV

  double Solar_Vmv = voltage*(1+(R_a/R_b));
  double Solar_Imv = current/(R_s*(1 + (R_f/R_o)));

  double Solar_V = Solar_Vmv/1000;
  double Solar_I = Solar_Imv/1000;



  delay(1000);

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
        Serial.print (Solar_V);
        Serial.print (",");
        Serial.print (Solar_I);
        Serial.println(" ");

}

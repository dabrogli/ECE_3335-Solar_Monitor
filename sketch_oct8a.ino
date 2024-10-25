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
  int analog_photodiode = analogRead(A2);

  double voltage = 4.88281*analog_voltage; //mV
  double current = 4.88281*analog_current; //mV
  double photodiode = 4.88281*analog_photodiode; //mV

  double Solar_Vmv = voltage*(1+(R_a/R_b));
  double Solar_Imv = current/(R_s*(1 + (R_f/R_o)));
  double Photodiode_Imv = photodiode/1600;

  double Solar_V = Solar_Vmv/1000;
  double Solar_I = Solar_Imv/1000;
  double Photodiode_I = Photodiode_Imv/1000;

  double AVSolar_V = 0;
  for (int i=0; i < 1000; i++) {
  AVSolar_V = AVSolar_V + Solar_V;
   }
  AVSolar_V = AVSolar_V/1000;

  double AVSolar_I = 0;
  for (int i=0; i < 1000; i++) {
  AVSolar_I = AVSolar_I + Solar_I;
   }
  AVSolar_I = AVSolar_I/1000;


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
        Serial.print (AVSolar_V);
        Serial.print (",");
        Serial.print (AVSolar_I);
        Serial.print (",");
        Serial.print(Photodiode_Imv);
        Serial.println(" ");

}

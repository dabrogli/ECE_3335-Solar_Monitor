#include "solarMonitorLCD.h"
#include <DHT.h>

const double R_volt_a = 298000;
const double R_volt_b = 99600;

const double R_curr_f = 398000;
const double R_curr_o = 99900;
const double R_curr_s = 1.09;

const double R_phdi_f_1 = 1600;
const double R_phdi_f_2 = 1600;

#define average_points 1000

#define analog_volt_pin A3
#define analog_curr_pin A2
#define analog_phdi_1_pin A0
#define analog_phdi_2_pin A0

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define rs 3
#define e 4
#define d4 5
#define d5 6
#define d6 7
#define d7 8

#define button_1 9
#define button_2 10

solarMonitorLCD* smLCD;

const double analog_to_mV = 5000.0 / 1024.0;  // mV/points

const double area_solar_cells_cm2 = 460.8;

int countms = 0;

int button_push_1 = 0, button_push_2 = 0;

bool screen_1 = true;

void setup() {
  Serial.begin(9600);
  Serial.println("\n\n-----===Setup Begin===-----");

  smLCD = new solarMonitorLCD(rs, e, d4, d5, d6, d7);

  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  OCR2A = 249;
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS20) | (1 << CS21);

  TIMSK2 = (1 << OCIE2A);
  sei();

  Serial.println("-----===Setup Complete===-----");
}

void loop() {
  double analog_voltage = 0.0;
  double analog_current = 0.0;
  double analog_photodiode = 0.0;
  float temperature = 0.0;

  if (countms >= 1000) {

    for (int i = 0; i < average_points; i++) {
      analog_voltage = analog_voltage + analogRead(analog_volt_pin);
    }
    analog_voltage = analog_voltage / average_points;

    for (int i = 0; i < average_points; i++) {
      analog_current = analog_current + analogRead(analog_curr_pin);
    }
    analog_current = analog_current / average_points;

    for (int i = 0; i < average_points; i++) {
      analog_photodiode = analog_photodiode + analogRead(analog_phdi_1_pin);
    }
    analog_photodiode = analog_photodiode / average_points;

    double voltage_mV = analog_to_mV * analog_voltage;        // mV
    double current_mV = analog_to_mV * analog_current;        // mV
    double photodiode_mV = analog_to_mV * analog_photodiode;  // mV

    double Solar_V_mV = voltage_mV * (double)(1 + (R_volt_a / R_volt_b)) * 1.02;
    double Solar_I_mA = current_mV / (double)(R_curr_s * (1 + (R_curr_f / R_curr_o))) * 1.10;
    double Photodiode_I_mA = photodiode_mV / (double) R_phdi_f_1;

    double Solar_V = Solar_V_mV / 1000;
    double Solar_I = Solar_I_mA / 1000;

    double Photodiode_I = Photodiode_I_mA / 1000;
    double Photodiode_Irradiance = Photodiode_I * 31600;

    double PanelPower_Wmv = Photodiode_Irradiance * 460.8;  // mW
    double PanelPower_W = PanelPower_Wmv / 1000;            // Expected power in watts

    double Power = Solar_V * Solar_I;         // Determined power in watts
    double Eff = Power / PanelPower_W * 100;  // Determined power in watts over expected power in watts

    temperature = dht.readTemperature();  // Read temperature from DHT sensor

    (*smLCD).power = (Power);
    (*smLCD).irrad = (Photodiode_Irradiance);
    (*smLCD).temp = (temperature);
    (*smLCD).eff = (Eff);
    (*smLCD).volt = (Solar_V);
    (*smLCD).curr = (Solar_I);

    if (screen_1) (*smLCD).update_screen_1();
    else (*smLCD).update_screen_2();


    Serial.print("Temperature ->");
    Serial.print(temperature);
    Serial.print(" C , Irradiance ->");
    Serial.print(Photodiode_Irradiance);
    Serial.print(" mW/cm^2 , Irrad Power ->");
    Serial.print(PanelPower_W);
    Serial.print(" W, Panel Current ->");
    Serial.print(Solar_I);
    Serial.print(" A, Panel Voltage ->");
    Serial.print(Solar_V);
    Serial.print(" V, Panel Power ->");
    Serial.print(Power);
    Serial.print(" W, Efficiency ->");
    Serial.print(Eff);
    Serial.println(" %");

    countms = 0;
  }
}

void(* resetFunc) (void) = 0;

ISR(TIMER2_COMPA_vect) {

  int button_read_1 = digitalRead(button_1);
  int button_read_2 = digitalRead(button_2);

  if (button_read_2 == HIGH && button_push_2 == 0) button_push_2 = 1;
  else if (button_read_2 == LOW && button_push_2 == 1) {
    screen_1 = !screen_1;
    button_push_2 = 0;

    if (screen_1) (*smLCD).startup_1();
    else (*smLCD).startup_2();
  }
  
  if (button_read_1 == HIGH && button_push_1 == 0) button_push_1 = 1;
  else if (button_read_1 == LOW && button_push_1 == 1) {
    resetFunc();
  }
  
  countms++;
}


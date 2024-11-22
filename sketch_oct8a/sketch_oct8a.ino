#include "solarMonitorLCD.h"
#include <DHT.h>

#define R_volt_a 298000
#define R_volt_b 99600

#define R_curr_f 398000
#define R_curr_o 99900
const double R_curr_s = 1.09;

#define R_phdi_f_1 1600
#define R_phdi_f_2 1600

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

solarMonitorLCD* smLCD;

const double analog_to_mV = 5000.0 / 1024.0;  // mV/points

const double area_solar_cells_cm2 = 460.8;

int countms = 0;

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

  TIMSK2 = /*(1 << OCIE2B) |*/ (1 << OCIE2A);
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

    double Solar_V_mV = voltage_mV * (1 + (R_volt_a / R_volt_b));
    double Solar_I_mA = current_mV / (R_curr_s * (1 + (R_curr_f / R_curr_o)));
    double Photodiode_I_mA = photodiode_mV / R_phdi_f_1;

    double Solar_V = Solar_V_mV / 1000;
    double Solar_I = Solar_I_mA / 1000;

    double Photodiode_I = Photodiode_I_mA / 1000;
    double Photodiode_Irradiance = Photodiode_I * 31600;


    double PanelPower_Wmv = Photodiode_Irradiance * 460.8;  // mW
    double PanelPower_W = PanelPower_Wmv / 1000;            // Expected power in watts

    double Power = Solar_V * Solar_I;         // Determined power in watts
    double Eff = Power / PanelPower_W * 100;  // Determined power in watts over expected power in watts

    temperature = dht.readTemperature();  // Read temperature from DHT sensor

    (*smLCD).write_pow(Power);
    (*smLCD).write_irrad(Photodiode_Irradiance);
    (*smLCD).write_temp(temperature);
    (*smLCD).write_eff(Eff);


    Serial.print("Temperature ->");
    Serial.print(temperature);
    Serial.print(" C , Irradience ->");
    Serial.print(Photodiode_Irradiance);
    Serial.print(" mW/cm^2, Power ->");
    Serial.print(Power);
    Serial.print(" W, Efficiency ->");
    Serial.print(Eff);
    Serial.println(" %");

    countms = 0;
  }
}

ISR(TIMER2_COMPA_vect) {
  countms++;
}

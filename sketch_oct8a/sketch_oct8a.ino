#include "solarMonitorLCD.h"
#include <DHT.h>

#define R_volt_a 303000
#define R_volt_b 99800

#define R_curr_f 402000
#define R_curr_o 99900
#define R_curr_s 1

#define R_phdi_f 1600

#define average_points 1000

#define analog_volt_pin A0
#define analog_curr_pin A1
#define analog_phdi_1_pin A2
#define analog_phdi_2_pin A3

#define DHTPIN 2        
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

#define rs 8
#define e 13
#define d4 12
#define d5 11
#define d6 10
#define d7 9


// Initialize LCD with specified pins
solarMonitorLCD smLCD(rs, e, d4, d5, d6, d7);

const double analog_to_mV = 5000.0 / 1024.0; // mV/points

const double area_solar_cells_cm2 = 460.8;

void setup() {
  Serial.begin(9600);
  
  Serial.println("-----===Setup Begin===-----");


  smLCD.startup();
  delay(10000);
  
  Serial.println("-----===Setup Complete===-----\n");
}

void loop() {
  int analog_voltage = 0.0;
  int analog_current = 0.0;
  int analog_photodiode = 0.0;
  float temperature = 0.0;
  
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

  double voltage_mV = analog_to_mV * analog_voltage; // mV
  double current_mV = analog_to_mV * analog_current; // mV
  double photodiode_mV = analog_to_mV * analog_photodiode; // mV

  double Solar_V_mV = voltage_mV * (1 + (R_volt_a / R_volt_b));
  double Solar_I_mA = current_mV / (R_curr_s * (1 + (R_curr_f / R_curr_o)));
  double Photodiode_I_mA = photodiode_mV / R_phdi_f;

  double Solar_V = Solar_V_mV / 1000;
  double Solar_I = Solar_I_mA / 1000;

  double Photodiode_I = Photodiode_I_mA / 1000;
  double Photodiode_Irradiance = Photodiode_I * 31600;


  double PanelPower_Wmv = Photodiode_Irradiance * 460.8; // mW
  double PanelPower_W = PanelPower_Wmv / 1000; // Expected power in watts

  double Power = Solar_V * Solar_I; // Determined power in watts
  double Eff = Power / PanelPower_W; // Determined power in watts over expected power in watts


  temperature = dht.readTemperature(); // Read temperature from DHT sensor


  // Serial.println(Solar_I);
  // Serial.println(current);
  // Serial.println(temperature);


  Power = 0;
  Eff = 0;
  temperature = 0;
  Photodiode_Irradiance = 0;
/*
  smLCD.write_pow(Power);
  smLCD.write_irrad(Photodiode_Irradiance);
  smLCD.write_temp(temperature);
  smLCD.write_eff(Eff);
  */
  Serial.print ("Temperature ->");
  Serial.print (temperature);
  Serial.print ("C , Irradience ->");
  Serial.print(Photodiode_Irradiance);
  Serial.print (" mW/cm^2, Power ->");
  Serial.print(Power);
  Serial.print (" W, Efficiency ->");
  Serial.print(Eff);
  Serial.println("%");

  
  delay(1000);
}

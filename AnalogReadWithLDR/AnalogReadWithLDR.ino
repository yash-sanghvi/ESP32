const int LDR_PIN = 36;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogReadResolution(10); //default is 12. Can be set between 9-12.
}

void loop() {
  // put your main code here, to run repeatedly:
  // LDR Resistance: 90k ohms
  // Resistance in series: 150k ohms
  // Pinouts:
  // Vcc -> 3.3 (CONNECTED TO LDR FREE END)
  // Gnd -> Gnd (CONNECTED TO RESISTOR FREE END)
  // Analog Read -> Vp (36) - Intermediate between LDR and resistance. 
  int LDR_Reading = analogRead(LDR_PIN);
  float LDR_Voltage = ((float)LDR_Reading*3.3/1023);
  Serial.print("Reading: ");Serial.print(LDR_Reading); Serial.print("\t");Serial.print("Voltage: ");Serial.println(LDR_Voltage);
}

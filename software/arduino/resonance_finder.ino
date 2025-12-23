/*
 * Project Triinfinity: Resonance Finder v1.0
 * Purpose: Sweep frequencies to find the harmonic peak of the 
 * Magnetostrictive-Piezoelectric Transduction stack.
 */

const int coilPin = 9;      // Output to coil driver
const int sensorPin = A0;   // Input from PZT stack
int bestFreq = 0;
float maxVoltage = 0;

void setup() {
  Serial.begin(9600);
  pinMode(coilPin, OUTPUT);
  Serial.println("Starting Resonance Sweep...");
}

void loop() {
  for (int freq = 100; freq <= 5000; freq += 10) {
    tone(coilPin, freq);   // Send frequency to Triinfinity coils
    delay(100);            // Let the liquid metal settle
    
    float voltage = analogRead(sensorPin) * (5.0 / 1023.0);
    
    if (voltage > maxVoltage) {
      maxVoltage = voltage;
      bestFreq = freq;
    }
    
    Serial.print("Freq: "); Serial.print(freq);
    Serial.print(" | Voltage: "); Serial.println(voltage);
  }
  
  Serial.print("--- OPTIMAL RESONANCE FOUND: ");
  Serial.print(bestFreq); Serial.println(" Hz ---");
  noTone(coilPin);
  while(1); // Stop after one full sweep
}

// ======================================================
// VibeSense System - Real-Time Sound to Vibration
// Hardware:
// Arduino Nano
// MAX9814 Microphone Module
// Amplifier / Vibration Driver
// ======================================================

// ---------------- Pin Configuration ----------------
const int micPin = A0;     // MAX9814 microphone output
const int ampPin = 9;      // Amplifier / vibration motor control

// ---------------- System Parameters ----------------
const int threshold = 40;   // Sound detection threshold
const int sampleSize = 10;  // Number of samples for averaging

// ======================================================
// Setup Function
// ======================================================
void setup() {
  pinMode(micPin, INPUT);
  pinMode(ampPin, OUTPUT);

  digitalWrite(ampPin, LOW);

  Serial.begin(115200);
}

// ======================================================
// Main Loop
// ======================================================
void loop() {

  long total = 0;

  // Step 1: Read multiple samples to reduce noise
  for (int i = 0; i < sampleSize; i++) {
    int rawValue = analogRead(micPin);

    // Normalize signal around midpoint (512)
    int volume = abs(rawValue - 512);

    total += volume;

    delayMicroseconds(200);
  }

  // Step 2: Calculate average sound level
  int avgVolume = total / sampleSize;

  // Step 3: Threshold-based sound detection
  if (avgVolume > threshold) {

    // Strong sound detected → Generate vibration
    digitalWrite(ampPin, HIGH);

  } else {

    // No significant sound → Stop vibration
    digitalWrite(ampPin, LOW);
  }

  // ---------------- Serial Monitoring ----------------
  Serial.print("Sound Level: ");
  Serial.print(avgVolume);
  Serial.print(" | Threshold: ");
  Serial.println(threshold);

  // Small delay for stable processing
  delay(5);
}
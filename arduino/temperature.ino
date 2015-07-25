/*
 * Adapted from Vilros LED and temperature sample projects
 * Uses TMP36 sensor
 * Range: -50C to 125C
 * Output: 0V at -50C and 1.75V at 125C
 */
int temperaturePin = 0; // Analog pin connected to TMP36 output
int ledPins[] = {2, 3, 4, 5, 6, 7, 8}; // Digital pins

void setup () {
  Serial.begin(9600); // Start serial connection
  analogReference(EXTERNAL); // Connect 3.3V to reference pin for less noise

  // Configure LED pins for output
  for (int i = 0; i < (sizeof(ledPins) / sizeof(int)); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop()
{
  // Analog pin reads 0-1023, which needs to be converted back to
  // voltage to calculate temperature.
  int pinValue = analogRead(temperaturePin);
  float voltage = pinValue * (3.3 / 1024); // Using 3.3V
  
  // 10 mV per degree with 500 mV offset at 0 degrees Celsius
  // (Voltages under 500 mV indicate negative temperatures)
  // Subtract 500 mV and multiply by 100 to get temperature in Celsius
  float temperatureC = (voltage - 0.5) * 100;
  float temperatureF = temperatureC * 9 / 5 + 32;

  Serial.println(temperatureF); // Write temperature to serial port for recording
  
  // Illuminate LEDs to display temperature reading on breadboard
  // The value at each pin is (i + 1)^2 so the first time through the loop, the 1
  // pin is set. Then 2, 4, 8, etc. 7 LEDs can display a maximum of 127F.
  int dividend = temperatureF;
  for (int i = 0; i < (sizeof(ledPins) / sizeof(int)); i++) {
    if (dividend % 2 == 0) {
      digitalWrite(ledPins[i], LOW);
    } else {
      digitalWrite(ledPins[i], HIGH);
    }
    dividend /= 2;
  }
  delay(1000); // Pause 1 second
}

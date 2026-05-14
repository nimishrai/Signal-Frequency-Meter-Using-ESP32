/**
 * ESP32 Frequency Detector
 * 
 * This sketch measures the frequency of an incoming signal on GPIO 27 
 * and displays it on an I2C LCD. It also reproduces the frequency 
 * on GPIO 26 using PWM.
 * 
 * Hardware Connections:
 * - Signal Input:  GPIO 27
 * - Signal Output: GPIO 26
 * - LCD SDA:       GPIO 21
 * - LCD SCL:       GPIO 22
 * - LCD I2C Addr:  0x27
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- Pin Definitions ---
#define INPUT_PIN 27
#define OUTPUT_PIN 26

// --- Global Variables ---
// volatile is used for variables modified inside interrupts
volatile unsigned long pulseCount = 0;

// Initialize LCD: address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

/**
 * Interrupt Service Routine (ISR)
 * This function runs every time a "Rising Edge" is detected on INPUT_PIN.
 * It must be stored in IRAM for speed on the ESP32.
 */
void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  // Start Serial communication for debugging
  Serial.begin(115200);

  // Configure Input Pin
  pinMode(INPUT_PIN, INPUT);

  // Attach an interrupt to the input pin.
  // When the pin goes from LOW to HIGH (RISING), countPulse() is called.
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), countPulse, RISING);

  // --- PWM (LEDC) Setup ---
  // ESP32 uses the ledc library for generating PWM/Tones
  const int pwmChannel = 0;
  const int resolution = 8;
  const int freq = 1000;

  // Initialize the output pin with the PWM frequency
  ledcAttach(OUTPUT_PIN, freq, resolution);

  // --- LCD Setup ---
  lcd.init();
  lcd.backlight();

  // Welcome Screen
  lcd.setCursor(0, 0);
  lcd.print("Freq Detector");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1. Reset the counter
  // We wrap this in noInterrupts() to ensure pulseCount isn't updated 
  // while we are trying to clear it.
  noInterrupts();
  pulseCount = 0;
  interrupts();

  // 2. Wait for exactly 1 second
  // During this second, the interrupt will trigger in the background 
  // for every pulse detected.
  delay(1000);

  // 3. Capture the result
  // The number of pulses in 1 second = Frequency in Hz.
  noInterrupts();
  unsigned long frequency = pulseCount;
  interrupts();

  // 4. Output to Serial
  Serial.print("Frequency: ");
  Serial.print(frequency);
  Serial.println(" Hz");

  // 5. Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Frequency:");
  lcd.setCursor(0, 1);
  lcd.print(frequency);
  lcd.print(" Hz");

  // 6. Mirror the frequency to the output pin
  if (frequency > 0) {
    // Generate a tone at the detected frequency
    ledcWriteTone(OUTPUT_PIN, frequency);
    // Set duty cycle to 50% (128 out of 255 for 8-bit resolution)
    ledcWrite(OUTPUT_PIN, 128);
  }
}

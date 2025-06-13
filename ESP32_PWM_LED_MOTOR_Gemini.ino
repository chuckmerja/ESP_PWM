// Define the pins for the joystick and LED
const int JOYSTICK_X_PIN = 34; // ESP32 ADC1_CH6 (GPIO 34) for X-axis
const int JOYSTICK_Y_PIN = 35; // ESP32 ADC1_CH7 (GPIO 35) for Y-axis (optional for this example, but good to include)
const int LED_PIN = 2;         // ESP32 GPIO 2 (PWM capable pin)

// PWM settings for the LED
const int PWM_FREQUENCY = 5000; // 5000 Hz (a common choice for LEDs)
const int PWM_RESOLUTION = 8;   // 8-bit resolution (0-255 range for duty cycle)
const int PWM_CHANNEL = 0;      // Use PWM channel 0

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  Serial.println("ESP32 Joystick LED Control Starting...");

  // Configure the joystick pins as input (analog)
  // No explicit pinMode is needed for analogRead on ESP32, but it's good practice
  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(JOYSTICK_Y_PIN, INPUT); // Though not used for LED fading in this example

  // Configure LEDC (LED Control) peripheral for PWM
  // ledcSetup(channel, frequency, resolution_bits)
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);

  // Attach the LED pin to the configured PWM channel
  // ledcAttachPin(pin, channel)   
  ledcAttachPin(LED_PIN, PWM_CHANNEL);

  Serial.println("Setup complete. Ready to read joystick and control LED.");
}

void loop() {
  // Read the analog value from the joystick's X-axis
  // The ESP32 ADC has a resolution of 12 bits by default (0-4095)
  int joystickValueX = analogRead(JOYSTICK_X_PIN);

  // Map the joystick value (0-4095) to the PWM duty cycle range (0-255)
  // The map() function handles the linear scaling
  int pwmDutyCycle = map(joystickValueX, 0, 4095, 0, 255);

  // Write the calculated PWM duty cycle to the LED
  // This will change the brightness of the LED
  // ledcWrite(channel, duty_cycle)
  ledcWrite(PWM_CHANNEL, pwmDutyCycle);

  // Print the raw joystick value and the mapped PWM value to the Serial Monitor
  Serial.print("Joystick X-axis Value: ");
  Serial.print(joystickValueX);
  Serial.print(" -> PWM Duty Cycle: ");
  Serial.println(pwmDutyCycle);

  // Small delay to prevent too rapid readings and for better readability in Serial Monitor
  delay(20);
}

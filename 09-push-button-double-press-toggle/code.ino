int led = 12;
int pushButton = 8;

int lastButtonState = HIGH;
bool ledState = false;

unsigned long firstPressTime = 0;
const unsigned long doublePressInterval = 1000;

int pressCount = 0;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{
  int currentButtonState = digitalRead(pushButton);
  unsigned long currentTime = millis();

  // Detect button press: HIGH -> LOW
  if (lastButtonState == HIGH && currentButtonState == LOW)
  {
    pressCount++;
    Serial.println("Button pressed");

    if (pressCount == 1)
    {
      // First press
      firstPressTime = currentTime;

      Serial.println("First press");
    }
    else if (pressCount == 2)
    {
      // Second press
      if (currentTime - firstPressTime <= doublePressInterval)
      {
        // Double press detected
        ledState = !ledState;
        digitalWrite(led, ledState ? HIGH : LOW);

        Serial.println("DOUBLE PRESS");
        Serial.println(ledState ? "LED ON" : "LED OFF");

        pressCount = 0;
      }
      else
      {
        // First press was too long ago.
        // Treat this as a new first press.
        firstPressTime = currentTime;
      }
    }
  }

  // If the second press doesn't happen within the time limit,
  // reset the counter.
  if (pressCount == 2 &&
      currentTime - firstPressTime > doublePressInterval)
  {
    pressCount = 0;
    Serial.println("Double press timeout");
  }

  lastButtonState = currentButtonState;
}
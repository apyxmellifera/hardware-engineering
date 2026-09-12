
int led = 12;
int pushButton = 8;

int lastButtonState = HIGH;
int stableButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

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

  // Detect a change in the raw button reading
  if (currentButtonState != lastButtonState)
  {
    lastDebounceTime = currentTime;
  }

  // Confirm the reading after it has remained stable
  if (currentTime - lastDebounceTime >= debounceDelay)
  {
    if (currentButtonState != stableButtonState)
    {
      stableButtonState = currentButtonState;

      // Confirmed button press
      if (stableButtonState == LOW)
      {
        Serial.println("Valid button press");
        digitalWrite(led, HIGH);
      }

      // Confirmed button release
      else
      {
        Serial.println("Valid button release");
        digitalWrite(led, LOW);
      }
    }
  }

  lastButtonState = currentButtonState;
}


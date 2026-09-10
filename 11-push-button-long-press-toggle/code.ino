// 11-push-button-long-press-toggle

int led = 12;
int pushButton = 8;

int lastButtonState = HIGH;

bool ledState = false;
bool longPressHandled = false;

unsigned long firstPressTime = 0;
unsigned long elapseTime = 0;

const unsigned long longPressInterval = 1000;

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
    firstPressTime = currentTime;
    longPressHandled = false;

    Serial.println("Button pressed");
    Serial.println(firstPressTime);
  }

  // Button is being held
  if (currentButtonState == LOW)
  {
    elapseTime = currentTime - firstPressTime;

    // Detect long press once
    if (elapseTime >= longPressInterval && !longPressHandled)
    {
      ledState = !ledState;
      digitalWrite(led, ledState ? HIGH : LOW);

      longPressHandled = true;

      Serial.println("LONG PRESS");
      Serial.println(ledState ? "LED ON" : "LED OFF");
    }
  }

  // Button released
  if (currentButtonState == HIGH)
  {
    longPressHandled = false;
  }

  lastButtonState = currentButtonState;
}
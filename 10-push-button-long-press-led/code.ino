int led = 12;
int pushButton = 8;

int lastButtonState = HIGH;

bool ledState = false;

unsigned long pressStartTime = 0;
unsigned long elapsedTime = 0;

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
    Serial.println("Button pressed");

    // Start timer
    pressStartTime = currentTime;
    Serial.println(pressStartTime);
  }

  // Button is being held
  if (currentButtonState == LOW)
  {
    elapsedTime = currentTime - pressStartTime;

    // Turn LED on after 1 second of holding
    if (elapsedTime >= longPressInterval)
    {
      ledState = true;
      digitalWrite(led, HIGH);

      Serial.println("LONG PRESS");
      Serial.println("LED ON");
    }
  }

  // Button released
  if (currentButtonState == HIGH)
  {
    ledState = false;
    digitalWrite(led, LOW);
  }

  lastButtonState = currentButtonState;
}
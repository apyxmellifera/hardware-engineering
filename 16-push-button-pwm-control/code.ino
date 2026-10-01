// 16-push-button-pwm-control

int led = 9;
int pushButton = 11;

int lastButtonState = HIGH;
int brightness = 0;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  int currentButtonState = digitalRead(pushButton);

  if (lastButtonState == HIGH && currentButtonState == LOW)
  {
    brightness += 25;

    if (brightness > 100)
    {
      brightness = 0;
    }

    int pwmValue = map(brightness, 0, 100, 0, 255);

    analogWrite(led, pwmValue);

    Serial.print("Brightness: ");
    Serial.print(brightness);
    Serial.print("% | PWM: ");
    Serial.println(pwmValue);
  }

  lastButtonState = currentButtonState;
}
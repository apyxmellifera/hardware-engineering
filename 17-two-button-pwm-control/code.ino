// 17-two-button-pwm-control

int led = 9;
int pushButton1 = 10;
int pushButton2 = 11;

int lastButtonState1 = HIGH;
int lastButtonState2 = HIGH;
int brightness = 0;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(pushButton2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  int currentButtonState1 = digitalRead(pushButton1);
  int currentButtonState2 = digitalRead(pushButton2);

  if (lastButtonState1 == HIGH && currentButtonState1 == LOW)
  {
    brightness += 25;

    if (brightness > 100)
    {
      brightness = 100;
    }

    int pwmValue = map(brightness, 0, 100, 0, 255);

    analogWrite(led, pwmValue);

    Serial.print("Brightness: ");
    Serial.print(brightness);
    Serial.print("% | PWM: ");
    Serial.println(pwmValue);
  }

  if (lastButtonState2 == HIGH && currentButtonState2 == LOW)
  {
    if (brightness > 0)
    {
      brightness -= 25;
    }

    int pwmValue = map(brightness, 0, 100, 0, 255);

    analogWrite(led, pwmValue);

    Serial.print("Brightness: ");
    Serial.print(brightness);
    Serial.print("% | PWM: ");
    Serial.println(pwmValue);
  }

  lastButtonState1 = currentButtonState1;
  lastButtonState2 = currentButtonState2;
}
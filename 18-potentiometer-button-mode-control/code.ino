// 18-potentiometer-button-mode-control

int led = 9;
int pushButton1 = 10;
int pushButton2 = 11;
int pushButton3 = 12;
int pot = A0;

int lastButtonState1 = HIGH;
int lastButtonState2 = HIGH;
int lastButtonState3 = HIGH;

int brightness = 0;
int mode = 1;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(pushButton2, INPUT_PULLUP);
  pinMode(pushButton3, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  int currentButtonState1 = digitalRead(pushButton1);
  int currentButtonState2 = digitalRead(pushButton2);
  int currentButtonState3 = digitalRead(pushButton3);

  // Button 3: switch mode
  if (lastButtonState3 == HIGH && currentButtonState3 == LOW)
  {
    mode++;

    if (mode > 2)
    {
      mode = 1;
    }
  }

  // Button control mode
  if (mode == 1)
  {
    if (lastButtonState1 == HIGH && currentButtonState1 == LOW)
    {
      brightness += 25;

      if (brightness > 100)
      {
        brightness = 100;
      }

      int pwmValue = map(brightness, 0, 100, 0, 255);

      analogWrite(led, pwmValue);

      Serial.print("Button Mode | Brightness: ");
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

      Serial.print("Button Mode | Brightness: ");
      Serial.print(brightness);
      Serial.print("% | PWM: ");
      Serial.println(pwmValue);
    }
  }

  // Potentiometer control mode
  if (mode == 2)
  {
    int potValue = analogRead(pot);
    int pwmValue = map(potValue, 0, 1023, 0, 255);

    analogWrite(led, pwmValue);

    Serial.print("Potentiometer Mode | ADC: ");
    Serial.print(potValue);
    Serial.print(" | PWM: ");
    Serial.println(pwmValue);
  }

  lastButtonState1 = currentButtonState1;
  lastButtonState2 = currentButtonState2;
  lastButtonState3 = currentButtonState3;
}

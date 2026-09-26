// 15-potentiometer-pwm-brightness

int led = 9;
int pot = A0;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int potValue = analogRead(pot);
  int brightness = map(potValue, 0, 1023, 0, 255);

  analogWrite(led, brightness);

  Serial.print("ADC: ");
  Serial.print(potValue);
  Serial.print(" | PWM: ");
  Serial.println(brightness);
}
// 14-pwm-brightness

int led = 9;
int brightness = 128;  // ~50.2% duty cycle

void setup()
{
  pinMode(led, OUTPUT);
}

void loop()
{
  analogWrite(led, brightness);
}
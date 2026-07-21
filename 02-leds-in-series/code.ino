// C++ code

int leds = 5;
int delayTime = 1000; // Wait for 1000 millisecond(s)
void setup()
{
  pinMode(leds, OUTPUT);
}

void loop()
{
  digitalWrite(leds, HIGH);
  delay(delayTime);
  digitalWrite(leds, LOW);
  delay(delayTime); 
}
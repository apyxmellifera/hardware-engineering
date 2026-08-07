// 05-push-button-external-pull-down

int led = 12;
int pushButton = 8;
int delayTime = 1000; // Wait for 1000 millisecond(s)
void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pushButton, INPUT);
}

void loop()
{
  if(digitalRead(pushButton)== HIGH){
  digitalWrite(led, HIGH);
  delay(delayTime);
  digitalWrite(led, LOW);
  delay(delayTime);  
  }
}
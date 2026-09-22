// 13-potentiometer-led-threshold

int led = 12;
int pot = A0;


void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
 int potValue = analogRead(pot);
 float voltage = (potValue * 5.0)/ 1023.0;
 
  if( voltage >= 2.6){
    digitalWrite(led, HIGH);
    Serial.println("Led ON"); 
    Serial.println(voltage);
  }else{
	digitalWrite(led, LOW);
  	Serial.println("Led OFF");
  	Serial.println(voltage);
  }
  
  }

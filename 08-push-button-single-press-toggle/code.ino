// 08-push-button-single-press-toggle

int led = 12;
int pushButton = 8;

int lastButtonState = HIGH;
bool ledState = false;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  int currentButtonState = digitalRead(pushButton);
  if(lastButtonState == HIGH && currentButtonState == LOW){
   
    if(ledState == false) {
      digitalWrite(led, HIGH);
      ledState = true;
      Serial.println(ledState);
      Serial.println("---High---");
    }else{
      digitalWrite(led, LOW);
      ledState = false;
      Serial.println(ledState);
      Serial.println("--Low----");
    }
  }
  lastButtonState = currentButtonState;
}
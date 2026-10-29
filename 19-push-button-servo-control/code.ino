// 19-push-button-servo-control
#include <Servo.h>

Servo servo;
int pushButton= 12;
int servoPin = 9;
int angle = 0;
int lastButtonState = HIGH;

void setup()
{
  pinMode(pushButton, INPUT_PULLUP);
  servo.attach(servoPin);
  servo.write(angle);
  Serial.begin(9600);
}

void loop()
{
  int currentButtonState = digitalRead(pushButton);
  
  if(lastButtonState == HIGH && currentButtonState == LOW){
    
    if(angle == 0) {
      angle = 90;
      servo.write(angle);
      Serial.println("Servo Angle: 90");
    }else{
     angle = 0;
      servo.write(angle);
      Serial.println("Servo Angle: 0");
    }
  }
  lastButtonState = currentButtonState;
}

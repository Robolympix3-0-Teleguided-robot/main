#include <Ps3Controller.h>
#define Pin_Forward 2
#define Pin_Backward 4

void setup() {
  Serial.begin(115200);
  Ps3.begin("00:00:00:00:00:00");
  Serial.println("Waiting for PS3 Controller...");

  pinMode(Pin_Forward,OUTPUT);
  pinMode(Pin_Backward,OUTPUT);
  
}

int8_t var = 0;
void loop() {
  if (Ps3.isConnected()) {
    if (Ps3.data.button.cross) {
      Serial.println("Cross button pressed");
    }
    Serial.println("left x = " + String(Ps3.data.analog.stick.lx) + " y = " + String(Ps3.data.analog.stick.ly));
    Serial.println("right x = " + String(Ps3.data.analog.stick.rx) + " y = " + String(Ps3.data.analog.stick.ry));
    
    if(Ps3.data.analog.stick.ly & 0x80){

        analogWrite(Pin_Backward,0);
        if(Ps3.data.analog.stick.ly == -128){
            analogWrite(Pin_Forward,255);
        }
        else{
            analogWrite(Pin_Forward,-Ps3.data.analog.stick.ly * 2);
        }
    }
    else{
        analogWrite(Pin_Forward,0);
        analogWrite(Pin_Backward,Ps3.data.analog.stick.ly * 2 + 1);
    }

    
    //Ps3.setRumble((float)var,1);
    //delay(10);
  }
  else{
    Serial.println("PS3 Controller Not Connected!");
    delay(100);
  }
}
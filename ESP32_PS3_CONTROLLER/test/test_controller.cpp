#include <Ps3Controller.h>

void setup() {
  Serial.begin(115200);
  Ps3.begin("00:00:00:00:00:00");
  Serial.println("Waiting for PS3 Controller...");
}

uint8_t var = 0;
void loop() {
  if (Ps3.isConnected()) {
    if (Ps3.data.button.cross) {
      Serial.println("Cross button pressed");
    }
    Serial.println("left x = " + String(Ps3.data.analog.stick.lx) + " y = " + String(Ps3.data.analog.stick.ly));
    Serial.println("right x = " + String(Ps3.data.analog.stick.rx) + " y = " + String(Ps3.data.analog.stick.ry));
    
    var++;
    //Ps3.setRumble((float)var,1);
    delay(10);
  }
  else{
    Serial.println("PS3 Controller Not Connected!");
    delay(100);
  }
}
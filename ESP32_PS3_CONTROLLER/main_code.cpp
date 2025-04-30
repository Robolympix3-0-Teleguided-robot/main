#include <Arduino.h>
#include <Ps3Controller.h>


//Gloabal Variables 
uint32_t serial_time_ms;

//==============================================================================Motor Control=====================================================================================

// GPIOs: 13, 12, 14, 27, 26, 25, 33, 32
#define NB_MOTORS 8
const uint8_t motor_pins[NB_MOTORS] = {13, 12, 15, 18, 26, 25, 33, 32};

#define UL_MOTOR_F 0
#define UL_MOTOR_B 1
#define UR_MOTOR_F 2
#define UR_MOTOR_B 3
#define DL_MOTOR_F 4
#define DL_MOTOR_B 5
#define DR_MOTOR_F 6
#define DR_MOTOR_B 7

#define MOTOR_FREQ_HZ 20000
#define MOTOR_BIT_RES 8

void init_motors(){

    for(uint8_t i = 0; i < NB_MOTORS; i++){
        pinMode(motor_pins[i],OUTPUT);
        ledcSetup(i, MOTOR_FREQ_HZ, MOTOR_BIT_RES);
        ledcAttachPin(motor_pins[i], i);
        ledcWrite(i, 128);
    }

}
void run_all(uint8_t val){
    for(uint8_t i = 0; i < NB_MOTORS; i++){
        ledcWrite(i,val);
    }

}

void basic_single_motor_handler(){
    if(Ps3.data.analog.stick.ly & 0x80){
      ledcWrite(UL_MOTOR_B,0);
        if(Ps3.data.analog.stick.ly == -128){
          ledcWrite(UL_MOTOR_F,255);
        }
        else{
          ledcWrite(UL_MOTOR_F,-Ps3.data.analog.stick.ly * 2);
        }
    }
    else{
        ledcWrite(UL_MOTOR_F,0);
        ledcWrite(UL_MOTOR_B,Ps3.data.analog.stick.ly * 2 + 1);
    }
}



//=====================================================================Start Function==========================================================================

void setup(){
    init_motors();
    Serial.begin(115200);
    Ps3.begin("00:00:00:00:00:00");
    Serial.println("Waiting for PS3 Controller...");

    serial_time_ms = millis();
}
//=====================================================================Main Loop==========================================================================

#define SERIAL_PRINT_MS 1000
void loop(){

    if(Ps3.isConnected()){
        basic_single_motor_handler();


        if(millis() - serial_time_ms > SERIAL_PRINT_MS){
          Serial.println("jx = " + String(Ps3.data.analog.stick.lx) + " jy = " + String(Ps3.data.analog.stick.ly));
          serial_time_ms = millis();
      }
    }
    else{
    }   


}   
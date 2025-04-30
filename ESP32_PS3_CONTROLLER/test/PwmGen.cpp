#include <Arduino.h>


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

void setup(){
    init_motors();
    run_all(200);

}

void loop(){
    delay(100);
}   
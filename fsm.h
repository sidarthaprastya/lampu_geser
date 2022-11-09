#ifndef FSM_H
#define FSM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATE_1    0
#define STATE_2    1
#define STATE_3    2
#define STATE_4    3

void fsm(int *button, int *state, int *led, int *counter){
    if(counter > 2){
        switch (*state){
            case STATE_1:
            if(*button == 1){       // Tombol kanan
                *state = STATE_2;
                led[0] = 0;
                led[1] = 1;
                led[2] = 0;
                led[3] = 0;
                *button = 0;
                *counter = 0;

            }
            else if(*button == -1){ // tombol kiri
                *state = STATE_4;
                led[0] = 0;
                led[1] = 0;
                led[2] = 0;
                led[3] = 1;
                *button = 0;
                *counter = 0;
            }
            else{
                led[0] = 1;
                led[1] = 0;
                led[2] = 0;
                led[3] = 0;
            }
            break;
        
        case STATE_2:
            if(*button == 1){       // Tombol kanan
                *state = STATE_3;
                led[0] = 0;
                led[1] = 0;
                led[2] = 1;
                led[3] = 0;
                *button = 0;
                *counter = 0;

            }
            else if(*button == -1){ // tombol kiri
                *state = STATE_1;
                led[0] = 1;
                led[1] = 0;
                led[2] = 0;
                led[3] = 0;
                *button = 0;
                *counter = 0;
            }
            break;
        
        case STATE_3:
            if(*button == 1){       // Tombol kanan
                *state = STATE_4;
                led[0] = 0;
                led[1] = 0;
                led[2] = 0;
                led[3] = 1;
                *button = 0;
                *counter = 0;
            }
            else if(*button == -1){ // tombol kiri
                *state = STATE_2;
                led[0] = 0;
                led[1] = 1;
                led[2] = 0;
                led[3] = 0;
                *button = 0;
                *counter = 0;
            }
            break;

        case STATE_4:
            if(*button == 1){       // Tombol kanan
                *state = STATE_1;
                led[0] = 1;
                led[1] = 0;
                led[2] = 0;
                led[3] = 0;
                *button = 0;
                *counter = 0;
            }
            else if(*button == -1){ // tombol kiri
                *state = STATE_3;
                led[0] = 0;
                led[1] = 0;
                led[2] = 1;
                led[3] = 0;
                *button = 0;
                *counter = 0;
            }
            break;

        default:
            *state = STATE_1;
            led[0] = 1;
            led[1] = 0;
            led[2] = 0;
            led[3] = 0;
            *button = 0;
            *counter = 0;
            break;
        }
    }
    else{
        counter += 1;
        *button = 0;
    }
        

//        vTaskDelayUntil(&xLastWakeTime, 10/portTICK_PERIOD_MS);
        
    
}

#endif

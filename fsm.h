#ifndef FSM_H
#define FSM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATE_1    0
#define STATE_2    1
#define STATE_3    2
#define STATE_4    3

#define STATE_DETECT    4
#define STATE_HOLD      5
#define STATE_SEND      6


void lampu_geser(int *button_debouncer, int *state_geser, int *led){
    // if(counter > 2){
        switch (*state_geser){
            case STATE_1:
            if(*button_debouncer == 1){       // Tombol kanan
                *state_geser = STATE_2;
                led[0] = 0;
                led[1] = 1;
                led[2] = 0;
                led[3] = 0;
                *button_debouncer = 0;
                // *counter = 0;

            }
            else if(*button_debouncer == -1){ // tombol kiri
                *state_geser = STATE_4;
                led[0] = 0;
                led[1] = 0;
                led[2] = 0;
                led[3] = 1;
                *button_debouncer = 0;
                // *counter = 0;
            }
            else{
                led[0] = 1;
                led[1] = 0;
                led[2] = 0;
                led[3] = 0;
            }
            break;
        
        case STATE_2:
            if(*button_debouncer == 1){       // Tombol kanan
                *state_geser = STATE_3;
                led[0] = 0;
                led[1] = 0;
                led[2] = 1;
                led[3] = 0;
                *button_debouncer = 0;
                // *counter = 0;

            }
            else if(*button_debouncer == -1){ // tombol kiri
                *state_geser = STATE_1;
                led[0] = 1;
                led[1] = 0;
                led[2] = 0;
                led[3] = 0;
                *button_debouncer = 0;
                // *counter = 0;
            }
            break;
        
        case STATE_3:
            if(*button_debouncer == 1){       // Tombol kanan
                *state_geser = STATE_4;
                led[0] = 0;
                led[1] = 0;
                led[2] = 0;
                led[3] = 1;
                *button_debouncer = 0;
                // *counter = 0;
            }
            else if(*button_debouncer == -1){ // tombol kiri
                *state_geser = STATE_2;
                led[0] = 0;
                led[1] = 1;
                led[2] = 0;
                led[3] = 0;
                *button_debouncer = 0;
                // *counter = 0;
            }
            break;

        case STATE_4:
            if(*button_debouncer == 1){       // Tombol kanan
                *state_geser = STATE_1;
                led[0] = 1;
                led[1] = 0;
                led[2] = 0;
                led[3] = 0;
                *button_debouncer = 0;
                // *counter = 0;
            }
            else if(*button_debouncer == -1){ // tombol kiri
                *state_geser = STATE_3;
                led[0] = 0;
                led[1] = 0;
                led[2] = 1;
                led[3] = 0;
                *button_debouncer = 0;
                // *counter = 0;
            }
            break;

        default:
            *state_geser = STATE_1;
            led[0] = 1;
            led[1] = 0;
            led[2] = 0;
            led[3] = 0;
            *button_debouncer = 0;
            // *counter = 0;
            break;
        }
    // }
    // else{
    //     counter += 1;
    //     *button = 0;
    // }
        
}


void debouncer(int *button_in, int *counter, int *state_debounce, int *button_fsm){
    switch(*state_debounce){
        case STATE_DETECT:
            if(*button_in != 0){
                *state_debounce = STATE_HOLD;
                *button_fsm = *button_in;
                *button_in = 0;
                *counter = 0;
            }
            break;

        case STATE_HOLD:
            if(*counter > 2){
                *state_debounce = STATE_DETECT;
            }
            else{
                *button_fsm = 0;
                *counter += 1;
            }
            break;

        // case STATE_SEND:
        //     *button_in = 0;
        //     *state_debounce = STATE_DETECT;
        //     break;
        
        default:
            *button_in = 0;
            *state_debounce = STATE_DETECT;
            break;
    }
}

#endif

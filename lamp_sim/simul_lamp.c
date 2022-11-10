#include <stdio.h>
#include "./../fsm.h"

int main(){
    // Test case:
    int lamp_in[11] = {0, 1, 0, 1, 1, 1, -1, 0, -1, 0, -1};
    // ----------

    int led_out[4];
    int state = STATE_1;
    int prev;

    for (int i=0; i<11; i++){
        prev = lamp_in[i];
        lampu_geser(&lamp_in[i], &state, led_out);
        printf("INPUT %d : %d\t | OUT : %d %d %d %d\n", i, prev,
                led_out[0], led_out[1], led_out[2], led_out[3]);
    }
    
    return 0;
}
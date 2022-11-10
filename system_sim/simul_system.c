#include <stdio.h>
#include "./../fsm.h"

int main(){
    // Test case:
    int button_in_left[11] = {0, -1, 0, -1, 0, -1, 0, 0, 0, 0, 0};
    int button_in_right[11] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1};
    // ----------
    int debounce_out_left = 0, debounce_out_right = 0;
    int counter_left = 0, counter_right = 0;
    int lamp_in;
    int led_out[4];
    int state_lamp = STATE_1;
    int state_deb_left = STATE_DETECT, state_deb_right = STATE_DETECT;
    int prev;
    int i;

    printf("BUTTON LEFT\t: ");
    for (i=0; i<11; i++){
        printf("%d\t", button_in_left[i]);
    }
    printf("\n");
    printf("BUTTON RIGHT\t: ");
    for (i=0; i<11; i++){
        printf("%d\t", button_in_right[i]);
    }
    printf("\n");

    for (i=0; i<11; i++){
        // prev_left = button_in_left[i];
        // prev_right = button_in_right[i];
        debouncer(&button_in_left[i], &counter_left, &state_deb_left, &debounce_out_left);
        debouncer(&button_in_right[i], &counter_right, &state_deb_right, &debounce_out_right);

        lamp_in = debounce_out_left + debounce_out_right;
        prev = lamp_in;
        lampu_geser(&lamp_in, &state_lamp, led_out);
        printf("INPUT %d : %d\t | OUT : %d %d %d %d\n", i, prev,
                led_out[0], led_out[1], led_out[2], led_out[3]);
    }
    
    return 0;
}
#include <stdio.h>
#include "./../fsm.h"

int main(){
    // Test case:
    int button[15] = {1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1};
    // ----------

    int out;
    int counter = 0;
    int state = STATE_DETECT;
    printf("Test Case: ");
    for (int k=0; k<11; k++){
        printf("%d, ", button[k]);
    }
    printf("\n");
    for (int i=0; i<15; i++){
        int prev_button = button[i];
        int prev_state = state;
        debouncer(button[i], &counter, &state, &out);
        printf("INPUT %d : %d\t | STATE : %d\t | OUT : %d\n", (i+1), prev_button, prev_state, out);
    }
    
    return 0;
}
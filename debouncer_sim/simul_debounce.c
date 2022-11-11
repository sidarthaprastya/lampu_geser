#include <stdio.h>
#include "./../fsm.h"

int main(){
    // Test case:
    int button[10] = {1, 0, 1, 1, 1, 1, 0, 1, 0, 0};
    // ----------

    int out;
    int counter = 0;
    int state = STATE_DETECT;
    printf("Test Case: ");
    for (int k=0; k<11; k++){
        printf("%d, ", button[k]);
    }
    printf("\n");
    for (int i=0; i<10; i++){
        int prev = button[i];
        debouncer(&button[i], &counter, &state, &out);
        printf("INPUT %d : %d\t | OUT : %d\n", (i+1), prev, out);
    }
    
    return 0;
}
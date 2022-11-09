#include <stdio.h>
#include "driver/gpio.h"
#include "driver/timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "fsm.h"

#define GPIO_OUTPUT_A    GPIO_NUM_4
#define GPIO_OUTPUT_B    GPIO_NUM_5
#define GPIO_OUTPUT_C    GPIO_NUM_18
#define GPIO_OUTPUT_D    GPIO_NUM_19
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_A) |(1ULL<<GPIO_OUTPUT_B) | (1ULL<<GPIO_OUTPUT_C)|(1ULL<<GPIO_OUTPUT_D))

#define GPIO_INPUT_PB1    GPIO_NUM_15
#define GPIO_INPUT_PB2    GPIO_NUM_2
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_PB1) | (1ULL<<GPIO_INPUT_PB2))

#define TIMER_USED            0     // HardwareTimer 0
#define TIMER_DIVIDER         16 
#define TIMER_SCALE           (TIMER_BASE_CLK /TIMER_DIVIDER)  
#define DELAY_S               (0.2)

int led_array[8] = {4,5,18,19};
int state = STATE_1; // Initial STATE
int led_out[4];
int button = 0, counter = 0;

void IRAM_ATTR timer_group_isr(void* para) {

    timer_spinlock_take(TIMER_USED); // TIMERG0
    int timer_idx = (int)para;
    uint32_t timer_intr = timer_group_get_intr_status_in_isr(TIMER_USED);

    if (timer_intr & TIMER_INTR_T0) {
        timer_group_clr_intr_status_in_isr(TIMER_USED, TIMER_0);
    } else if (timer_intr & TIMER_INTR_T1) {
        timer_group_clr_intr_status_in_isr(TIMER_USED, TIMER_1);
    }
    // ---------------------------------------------------------------
    // ------------------Main procedures for ISR----------------------
    // FSM Processed
    fsm(&button, &state, led_out, &counter);
    
    // Turn on desired LED 
    for(int i=0; i < 4; i++){
        gpio_set_level(led_array[i], led_out[i]);
    }

    // ---------------------------------------------------------------
    // ---------------------------------------------------------------

    timer_group_enable_alarm_in_isr(TIMER_USED, timer_idx);
    timer_spinlock_give(TIMER_USED);
}

void app_main(void) {
    // ---------------------------------------------------------------
    // ---------------GPIO CONFIGURATION------------------------------
    // OUTPUT LED
    gpio_config_t io_conf;
    io_conf.intr_type = 0;
    io_conf.mode = GPIO_MODE_DEF_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // ---------------------------------------------------------------
    // INPUT BUTTON
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_DEF_INPUT;
    io_conf.intr_type = 0; // Falling Edge
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE; // enable interrupt
    io_conf.pull_down_en = 0;
    gpio_config(&io_conf);
    // ---------------------------------------------------------------
    // ----------------TIMER CONFIGURATION----------------------------
    timer_config_t config = {
        .divider = TIMER_DIVIDER,
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_START,
        .alarm_en = TIMER_ALARM_EN,
        .auto_reload = TIMER_AUTORELOAD_EN,
    };
    timer_init(TIMER_USED, TIMER_USED, &config);
    timer_set_counter_value(TIMER_USED, TIMER_USED, 0x00000000ULL);
    timer_set_alarm_value(TIMER_USED, TIMER_USED, DELAY_S * TIMER_SCALE);
    timer_enable_intr(TIMER_USED, TIMER_USED);

    // ----------------TIMER ISR--------------------------------------
    timer_isr_register(TIMER_USED, TIMER_USED, timer_group_isr, (void*)TIMER_USED, ESP_INTR_FLAG_IRAM, NULL);
    timer_start(TIMER_USED, TIMER_USED);
    // ---------------------------------------------------------------
    // ---------------------------------------------------------------


    while (1) {
        // Check Button (0 if pressed)
        // Button value will back to 0 after FSM finished
        if (gpio_get_level(GPIO_INPUT_PB1) == 0) {
            button = 1;
        }
        else if(gpio_get_level(GPIO_INPUT_PB2) == 0){
            button = -1;
        }
        vTaskDelay(1);
    };
}
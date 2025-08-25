#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
int RED  = 0x02;  // PF1 - Red LED
int BLUE = 0x04;  // PF2 - Blue LED
int SW1  = 0x10;  // PF4 - Switch 1
int SW2  = 0x01;  // PF0 - Switch 2

int main(void) {
    SYSCTL_RCGCGPIO_R = 0x20;         // Enable clock for Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // Unlock PF0 for changes
    GPIO_PORTF_CR_R = 0x1F;           // Allow  PF0-PF4
    GPIO_PORTF_DIR_R = 0x06;          // Set PF1, PF2 as outputs
    GPIO_PORTF_PUR_R = 0x11;          // Enable pull-up on PF0, PF4
    GPIO_PORTF_DEN_R = 0x1F;          // Enable digital function

    while (1) {

        int sw1_pressed = !(GPIO_PORTF_DATA_R & SW1);
        int sw2_pressed = !(GPIO_PORTF_DATA_R & SW2);

        if (sw1_pressed && sw2_pressed) {
            GPIO_PORTF_DATA_R = RED | BLUE;
        }
        else if (sw1_pressed) {
            GPIO_PORTF_DATA_R = RED;
        }
        else if (sw2_pressed) {
            GPIO_PORTF_DATA_R = BLUE;
        }
        else {
            GPIO_PORTF_DATA_R = 0x00;
        }
    }
}

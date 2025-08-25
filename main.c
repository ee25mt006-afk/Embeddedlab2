#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
void delay(void){
    int i;
    for(i=0; i<50000; i++);  // Adjust count
}

int main(void){

    SYSCTL_RCGCGPIO_R = 0x20;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x1F;  // Enable digital function for PF0-PF4
    GPIO_PORTF_PUR_R = 0x10;  // Pull-up resistor
    unsigned char leds[3] = {0x02, 0x08, 0x04}; // Red, Green, Blue
    int i = 0;  // Start with Red

    while(1){

        if(!(GPIO_PORTF_DATA_R & 0x10)){
            delay();
            GPIO_PORTF_DATA_R = leds[i];    // Turn on current LED
            i = (i+1) % 3;                  // Move to next color


            while(!(GPIO_PORTF_DATA_R & 0x10));
            delay();
        }
    }
}

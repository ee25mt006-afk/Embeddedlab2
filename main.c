#include <stdint.h>
#include <stdbool.h>

// Definition of PortF base Address
#define SYSCTL_RCGCGPIO_R   (*((volatile uint32_t *)0x400FE608))
#define GPIO_PORTF_LOCK_R   (*((volatile uint32_t *)0x40025520))
#define GPIO_PORTF_CR_R     (*((volatile uint32_t *)0x40025524))
#define GPIO_PORTF_DIR_R    (*((volatile uint32_t *)0x40025400))
#define GPIO_PORTF_PUR_R    (*((volatile uint32_t *)0x40025510))
#define GPIO_PORTF_DEN_R    (*((volatile uint32_t *)0x4002551C))
#define GPIO_PORTF_DATA_R   (*((volatile uint32_t *)0x400253FC))


// definition of PortF Pins
#define RED     (1 << 1)   // PF1
#define BLUE    (1 << 2)   // PF2
#define SW1     (1 << 4)   // PF4
#define SW2     (1 << 0)   // PF0



   int main(void) {
    SYSCTL_RCGCGPIO_R = 0x20;         // Enable clock for Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // Unlock PF0
    GPIO_PORTF_CR_R = 0x1F;           // Allow PF0-PF4
    GPIO_PORTF_DIR_R = 0x06;          // PF1, PF2 output
    GPIO_PORTF_PUR_R = 0x11;          // Pull-up PF0, PF4
    GPIO_PORTF_DEN_R = 0x1F;          // Digital enable PF0-PF4

  while (1) {
        int sw1_pressed = !(GPIO_PORTF_DATA_R & SW1);
        int sw2_pressed = !(GPIO_PORTF_DATA_R & SW2);

        if (sw1_pressed && sw2_pressed) {
                   GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~(RED | BLUE)) | (RED | BLUE);
               }
               else if (sw1_pressed) {
                   GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~(RED | BLUE)) | RED;
               }
               else if (sw2_pressed) {
                   GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~(RED | BLUE)) | BLUE;
               }
               else {
                   GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~(RED | BLUE));
               }
    }
}


   

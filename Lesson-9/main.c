#include "lm4f120h5qr.h"
#include "delay.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

int main() {
  SYSCTL_RCGCGPIO_R      |= (1U << 5); //Enable and provide a clock to GPIO Port F in Run mode
  SYSCTL_GPIOHBCTL_R     |= (1U << 5); // Enable AHB for GPIOF
  GPIO_PORTF_AHB_DIR_R   |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIO_PORTF_AHB_DEN_R   |= (LED_RED | LED_BLUE | LED_GREEN);
  
  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
  while(1) {
  GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; //Uses the Store (STR) instruction sequence instead of Read, Modify, Write sequence
  delay();
  GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
  delay();
  }
  return 0;
}

#include "main.h"

/**
 * Main program.
 */
int main(void) {
  // Initialize global variables.
  led_on = 0;

  // Enable the SYSCFG peripheral.
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  // Enable the GPIOB peripheral.
  #ifdef VVC_F0
    RCC->AHBENR   |= RCC_AHBENR_GPIOBEN;
  #elif  VVC_L0
    RCC->IOPENR   |= RCC_IOPENR_IOPBEN;
  #endif
  // Initialize the GPIOB pins.
  // Reset all options, because the L0 lines reset to 0xFFFFFFFF.
  // B0-1 should be set to 'input' mode with pull-up.
  GPIOB->MODER  &= ~(0x3 << (BUTTON_PIN*2));
  GPIOB->PUPDR  &= ~(0x3 << (BUTTON_PIN*2));
  GPIOB->PUPDR  |=  (0x1 << (BUTTON_PIN*2));
  GPIOB->MODER  &= ~(0x3 << (ROTARY_PIN_B*2));
  GPIOB->PUPDR  &= ~(0x3 << (ROTARY_PIN_B*2));
  GPIOB->PUPDR  |=  (0x1 << (ROTARY_PIN_B*2));
  // B3 is connected to an LED on the 'Nucleo' board.
  //    It should be set to push-pull low-speed output.
  GPIOB->MODER  &= ~(0x3 << (LED_PIN*2));
  GPIOB->MODER  |=  (0x1 << (LED_PIN*2));
  GPIOB->OTYPER &= ~(0x1 << LED_PIN);
  GPIOB->PUPDR  &= ~(0x3 << (LED_PIN*2));

  // Set SYSCFG to connect the button EXTI line to GPIOB.
  SYSCFG->EXTICR[(BUTTON_PIN/4)] &= ~(0xF << ((BUTTON_PIN % 4) * 4));
  SYSCFG->EXTICR[(BUTTON_PIN/4)] |=  (0x1 << ((BUTTON_PIN % 4) * 4));
  // (Or, if you don't feel like using pin macros:)
  //SYSCFG->EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI1_Msk);
  //SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PB;
  // Setup EXTI interrupts for falling input on the button pin.
  EXTI->IMR |= (1 << BUTTON_PIN);
  // Disable the 'rising edge' trigger (button release).
  EXTI->RTSR &= ~(1 << BUTTON_PIN);
  // Enable the 'falling edge' trigger (button press).
  EXTI->FTSR |= (1 << BUTTON_PIN);
  // Enable the NVIC interrupt at minimum priority.
  NVIC_SetPriority(EXTI0_1_IRQn, 0x03);
  NVIC_EnableIRQ(EXTI0_1_IRQn);

  // Light the button only if it should be on.
  while (1) {
    if (led_on) {
      GPIOB->ODR |= (1 << LED_PIN);
    }
    else {
      GPIOB->ODR &= ~(1 << LED_PIN);
    }
  }
}

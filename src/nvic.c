#include "nvic.h"

void EXTI0_1_IRQ_handler(void) {
  // Check that EXTI7 is the line that triggered.
  if (EXTI->PR & (1 << BUTTON_PIN)) {
    // If it was, clear the interrupt flag.
    EXTI->PR |= (1 << BUTTON_PIN);

    // If you are using a button, toggle the LED state:
    //led_on = !led_on;

    // If you are using a rotary encoder, turn the
    // LED on or off depending on the direction.
    // (Comment this out if using a single button)
    if (GPIOB->IDR & (1 << ROTARY_PIN_B)) {
      // Turn the LED on.
      led_on = 1;
    }
    else {
      // Turn the LED off.
      led_on = 0;
    }
  }
}

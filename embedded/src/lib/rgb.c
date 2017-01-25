/* Library to control rgb LED on board */

#include "lib/include/rgb.h"

void rgb_blink(uint8_t color, uint8_t n) {

  // If the RGB is busy, yield task and then try again
  while (xSemaphoreTake(rgb_mutex, 0) == pdFALSE) {
    taskYIELD();
  }


  uint8_t i = 0;
  TickType_t ticktime = xTaskGetTickCount();

  while ( i < n ) {
    ROM_GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|GREEN_LED|BLUE_LED, color);
    //ROM_SysCtlDelay(5000000);
    vTaskDelayUntil(&ticktime, BLINK_RATE / portTICK_RATE_MS);

    ROM_GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|GREEN_LED|BLUE_LED, 0);
    //ROM_SysCtlDelay(5000000);
    vTaskDelayUntil(&ticktime, BLINK_RATE / portTICK_RATE_MS);
    i++;
  }

  xSemaphoreGive(rgb_mutex);
}

void rgb_on(uint8_t color) {

  // If the RGB is busy, yield task and then try again
  while (xSemaphoreTake(rgb_mutex, 0) == pdFALSE) {
    taskYIELD();
  }

  // Turn on the RGB with color
  ROM_GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|GREEN_LED|BLUE_LED, color);

  xSemaphoreGive(rgb_mutex);
}

void rgb_off(uint8_t color) {
  // If the RGB is busy, yield task and then try again
  while (xSemaphoreTake(rgb_mutex, 0) == pdFALSE ) {
    taskYIELD();
  }

  // Turn off the RGB with color
  ROM_GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|GREEN_LED|BLUE_LED, 0);

  xSemaphoreGive(rgb_mutex);
}
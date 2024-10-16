#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "reboot/bootsel-reboot.h"
#include "ads1015/ads1015.h"

#define uint unsigned int 

PICO_ADS1015 ads;

uint getPicoInput(uint input) {
    adc_select_input(input);

    const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result = adc_read(); 

    float voltage = result * conversion_factor;
    float resistance = 10000 * (voltage / 3.3f);

    // printf("%u,%fV,%fOhms\n", result, voltage, resistance);

    return (uint)(result / 4);
}

uint getAds1015Input(uint input)
{
    return (uint)ads.readADC_SingleEnded((ADSX_AINX_e)input);
}

void initAds() {
  ads.setGain(ADSXGain_ONE);
  
  if (!ads.beginADSX(ADSX_ADDRESS_GND, i2c0, 100, 4, 5)) {
    printf("Failed to initialize ADS.\n");
  }
}

void init() {
    stdio_init_all();
    arm_watchdog();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    adc_init();

    initAds();

    adc_gpio_init(28);
    adc_gpio_init(27);
}

void loop() {
    while (true) {
        uint input0 = getPicoInput(2);
        uint input1 = getPicoInput(1);

        // uint input1 = (uint)(getAds1015Input(0) / 1623.0f * 1023.0f);
        uint input2 = (uint)(getAds1015Input(1) / 1644.0f * 1023.0f);
        uint input3 = (uint)(getAds1015Input(2) / 1644.0f * 1023.0f);
        uint input4 = (uint)(getAds1015Input(3) / 1644.0f * 1023.0f);

        printf("%u|%u|%u|%u|%u\n", input2, input3, input4, input1, input0);

        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(50);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        sleep_ms(50);
        check_bootsel_button();
    }
}

int main() {
    init();
    loop();

    return 0;
}

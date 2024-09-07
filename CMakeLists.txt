cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(test_project C CXX ASM)

pico_sdk_init()

add_executable(test 
    main.cpp
    reboot/bootsel-reboot.cpp
    ads1015/ads1015.cpp)

pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 0)
pico_add_extra_outputs(test)

target_link_libraries(test pico_stdlib hardware_pwm hardware_spi hardware_interp hardware_pio hardware_i2c hardware_adc)
################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\sloeber.ino.cpp 

LINK_OBJ += \
.\sloeber.ino.cpp.o 

CPP_DEPS += \
.\sloeber.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
sloeber.ino.cpp.o: ..\sloeber.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\SCE\Sloeber\arduinoPlugin\packages\esp32\tools\xtensa-esp32-elf-gcc\1.22.0-80-g6c4433a-5.2.0/bin/xtensa-esp32-elf-g++" -DESP_PLATFORM "-DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\"" -DHAVE_CONFIG_H -DGCC_NOT_5_2_0=0 -DWITH_POSIX "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/config" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/app_trace" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/app_update" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/asio" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/bootloader_support" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/bt" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/coap" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/console" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/driver" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp-tls" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp32" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_adc_cal" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_event" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_http_client" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_http_server" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_https_ota" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_ringbuf" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/ethernet" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/expat" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/fatfs" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/freemodbus" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/freertos" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/heap" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/idf_test" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/jsmn" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/json" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/libsodium" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/log" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/lwip" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/mbedtls" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/mdns" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/micro-ecc" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/mqtt" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/newlib" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/nghttp" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/nvs_flash" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/openssl" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/protobuf-c" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/protocomm" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/pthread" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/sdmmc" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/smartconfig_ack" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/soc" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/spi_flash" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/spiffs" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/tcp_transport" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/tcpip_adapter" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/ulp" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/vfs" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/wear_levelling" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/wifi_provisioning" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/wpa_supplicant" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/xtensa-debug-module" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp-face" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp32-camera" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp-face" "-ID:\SCE\Sloeber\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/fb_gfx" -std=gnu++11 -Os -g3 -Wpointer-arith -fexceptions -fstack-protector -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -mlongcalls -nostdlib -Wall -Werror=all -Wextra -Wno-error=maybe-uninitialized -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wno-unused-parameter -Wno-unused-but-set-parameter -Wno-missing-field-initializers -Wno-sign-compare -fno-rtti -MMD -c -DF_CPU=240000000L -DARDUINO=10812 -DARDUINO_ESP32_DEV -DARDUINO_ARCH_ESP32 "-DARDUINO_BOARD=\"ESP32_DEV\"" -DARDUINO_VARIANT="esp32"  -DESP32 -DCORE_DEBUG_LEVEL=5    -I"D:\SCE\Sloeber\arduinoPlugin\packages\esp32\hardware\esp32\1.0.4\cores\esp32" -I"D:\SCE\Sloeber\arduinoPlugin\packages\esp32\hardware\esp32\1.0.4\variants\esp32" -I"D:\SCE\Sloeber\arduinoPlugin\libraries\can_common-master\src" -I"D:\SCE\Sloeber\arduinoPlugin\libraries\esp32_can-master\src" -I"D:\SCE\Sloeber\arduinoPlugin\packages\esp32\hardware\esp32\1.0.4\libraries\SPI\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"

	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ..\makefile.init

RM := -del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include core\core\libb64\subdir.mk
-include core\core\subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ..\makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
C:\DEV\workspace_sloeber\test4\Release\arduino.ar \

ELF += \
test4.elf \

HEX += \
test4.hex \


# All Target
all:
	$(MAKE) --no-print-directory pre-build
	$(MAKE) --no-print-directory main-build

# Main-build Target
main-build: test4

# Tool invocations
test4: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:\DEV\Sloeber\/arduinoPlugin/packages/ESP32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-size" -A "C:\DEV\workspace_sloeber\test4\Release/test4.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:\DEV\workspace_sloeber\test4\Release\arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:\DEV\Sloeber\/arduinoPlugin/packages/ESP32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-ar" cru     C:\DEV\workspace_sloeber\test4\Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

test4.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:\DEV\Sloeber\/arduinoPlugin/packages/ESP32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc" -nostdlib "-LC:\DEV\Sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/lib" "-LC:\DEV\Sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/ld" -T esp32_out.ld -T esp32.project.ld -T esp32.rom.ld -T esp32.peripherals.ld -T esp32.rom.libgcc.ld -T esp32.rom.spiram_incompatible_fns.ld -u ld_include_panic_highint_hdl -u call_user_start_cpu0 -Wl,--gc-sections -Wl,-static -Wl,--undefined=uxTopUsedPriority  -u __cxa_guard_dummy -u __cxx_fatal_exception  -Wl,--start-group   $(LINK_OBJ)   C:\DEV\workspace_sloeber\test4\Release/arduino.ar  -lgcc -lfreertos -lmesh -lod -lwear_levelling -lfb_gfx -lesp_adc_cal -lc_nano -lesp32 -ldriver -lhal -ljsmn -lsmartconfig -lesp_http_server -lprotocomm -lface_recognition -lespnow -ltcpip_adapter -lface_detection -lunity -lc -llibsodium -lesp_http_client -lapp_update -lnewlib -lcxx -ltcp_transport -lm -lefuse -lopenssl -lwifi_provisioning -lespcoredump -llog -lmbedtls -lesp_ringbuf -lwps -lnet80211 -lmqtt -lesp_https_server -lapp_trace -lesp_event -lesp32-camera -lsoc -lheap -llwip -lwpa -lrtc -lxtensa-debug-module -lspi_flash -lphy -lfr -lconsole -lcoap -lbtdm_app -lsdmmc -lfd -lmicro-ecc -ljson -lcore -lprotobuf-c -lethernet -lspiffs -lnvs_flash -lwpa_supplicant -lvfs -lasio -lwpa2 -lpp -lbootloader_support -limage_util -ldl_lib -lulp -lnghttp -lpthread -lfreemodbus -lexpat -lfatfs -lsmartconfig_ack -lmdns -lcoexist -lesp-tls -lesp_https_ota -lbt  -lstdc++ -Wl,--end-group -Wl,-EL -o "C:\DEV\workspace_sloeber\test4\Release/test4.elf"
	@echo 'Finished building: $@'
	@echo ' '

test4.hex: $(ELF)
	@echo 'Do all objcopy commands'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

pre-build:
	-${A.RECIPE.HOOKS.PREBUILD.1.PATTERN}
	${A.RECIPE.HOOKS.PREBUILD.2.PATTERN}
	-@echo ' '

.PHONY: all clean dependents main-build pre-build

-include ..\makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ccstheia141/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/CCSworkspace_v12/C_MSPM0G3507/3507_AD_DA" -I"D:/CCSworkspace_v12/C_MSPM0G3507/3507_AD_DA/Debug" -I"D:/ti/mspm0_sdk_1_30_00_03/source/third_party/CMSIS/Core/Include" -I"D:/ti/mspm0_sdk_1_30_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1227476575: ../3507_AD_DA.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/ccstheia141/ccs/utils/sysconfig_1.20.0/sysconfig_cli.bat" --script "D:/CCSworkspace_v12/C_MSPM0G3507/3507_AD_DA/3507_AD_DA.syscfg" -o "." -s "D:/ti/mspm0_sdk_1_30_00_03/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1227476575 ../3507_AD_DA.syscfg
device.opt: build-1227476575
device.cmd.genlibs: build-1227476575
ti_msp_dl_config.c: build-1227476575
ti_msp_dl_config.h: build-1227476575
Event.dot: build-1227476575

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ccstheia141/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/CCSworkspace_v12/C_MSPM0G3507/3507_AD_DA" -I"D:/CCSworkspace_v12/C_MSPM0G3507/3507_AD_DA/Debug" -I"D:/ti/mspm0_sdk_1_30_00_03/source/third_party/CMSIS/Core/Include" -I"D:/ti/mspm0_sdk_1_30_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: D:/ti/mspm0_sdk_1_30_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ccstheia141/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/CCSworkspace_v12/C_MSPM0G3507/3507_AD_DA" -I"D:/CCSworkspace_v12/C_MSPM0G3507/3507_AD_DA/Debug" -I"D:/ti/mspm0_sdk_1_30_00_03/source/third_party/CMSIS/Core/Include" -I"D:/ti/mspm0_sdk_1_30_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



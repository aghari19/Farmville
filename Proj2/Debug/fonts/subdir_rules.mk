################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
fonts/%.obj: ../fonts/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/abarh/Desktop/ECE 2534/ccsv8/tools/compiler/ti-cgt-arm_18.1.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/devices/msp432p4xx" --include_path="C:/Users/abarh/git/project2-aghari19/Proj2" --include_path="C:/Users/abarh/Desktop/ECE 2534/ccsv8/tools/compiler/ti-cgt-arm_18.1.5.LTS/include" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/Users/abarh/Desktop/ECE 2534/ccsv8/ccs_base/arm/include" --include_path="C:/Users/abarh/Desktop/ECE 2534/ccsv8/ccs_base/arm/include/CMSIS" --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="fonts/$(basename $(<F)).d_raw" --obj_directory="fonts" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



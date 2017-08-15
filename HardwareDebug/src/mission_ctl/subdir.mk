################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/mission_ctl/mission_ctl.c 

C_DEPS += \
./src/mission_ctl/mission_ctl.d 

OBJS += \
./src/mission_ctl/mission_ctl.obj 


# Each subdirectory must supply rules for building sources it contributes
src/mission_ctl/%.obj: ../src/mission_ctl/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c   -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv2 -optimize=0 -fpu -nologo  -define=__RX=1   "$<"
	ccrx -lang=c -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv2 -optimize=0 -fpu -nologo  -define=__RX=1   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.


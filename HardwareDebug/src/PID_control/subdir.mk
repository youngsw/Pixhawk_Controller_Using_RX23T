################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/PID_control/PID_control.c 

C_DEPS += \
./src/PID_control/PID_control.d 

OBJS += \
./src/PID_control/PID_control.obj 


# Each subdirectory must supply rules for building sources it contributes
src/PID_control/%.obj: ../src/PID_control/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c   -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv2 -optimize=0 -fpu -nologo  -define=__RX=1   "$<"
	ccrx -lang=c -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv2 -optimize=0 -fpu -nologo  -define=__RX=1   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/ppm_encoder/ppm_encoder.c 

C_DEPS += \
./src/ppm_encoder/ppm_encoder.d 

OBJS += \
./src/ppm_encoder/ppm_encoder.obj 


# Each subdirectory must supply rules for building sources it contributes
src/ppm_encoder/%.obj: ../src/ppm_encoder/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c   -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv2 -optimize=0 -fpu -nologo  -define=__RX=1   "$<"
	ccrx -lang=c -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv2 -optimize=0 -fpu -nologo  -define=__RX=1   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.


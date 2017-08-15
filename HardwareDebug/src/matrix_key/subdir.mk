################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/matrix_key/matrix_key.c 

C_DEPS += \
./src/matrix_key/matrix_key.d 

OBJS += \
./src/matrix_key/matrix_key.obj 


# Each subdirectory must supply rules for building sources it contributes
src/matrix_key/%.obj: ../src/matrix_key/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c   -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv2 -optimize=0 -fpu -nologo  -define=__RX=1   "$<"
	ccrx -lang=c -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv2 -optimize=0 -fpu -nologo  -define=__RX=1   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.


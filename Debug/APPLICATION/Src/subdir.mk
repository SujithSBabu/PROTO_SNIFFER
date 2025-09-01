################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APPLICATION/Src/circular_buffer.c \
../APPLICATION/Src/i2c_gyro_data_handle.c \
../APPLICATION/Src/log_data.c \
../APPLICATION/Src/spi_frame_simulate.c \
../APPLICATION/Src/spi_loopback_feature.c 

OBJS += \
./APPLICATION/Src/circular_buffer.o \
./APPLICATION/Src/i2c_gyro_data_handle.o \
./APPLICATION/Src/log_data.o \
./APPLICATION/Src/spi_frame_simulate.o \
./APPLICATION/Src/spi_loopback_feature.o 

C_DEPS += \
./APPLICATION/Src/circular_buffer.d \
./APPLICATION/Src/i2c_gyro_data_handle.d \
./APPLICATION/Src/log_data.d \
./APPLICATION/Src/spi_frame_simulate.d \
./APPLICATION/Src/spi_loopback_feature.d 


# Each subdirectory must supply rules for building sources it contributes
APPLICATION/Src/%.o APPLICATION/Src/%.su APPLICATION/Src/%.cyclo: ../APPLICATION/Src/%.c APPLICATION/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"E:/Embedded_Engineer_Projects/Protocol_Sniffer/proto_sniffer/APPLICATION/Inc" -I"E:/Embedded_Engineer_Projects/Protocol_Sniffer/proto_sniffer/ECUAL/Inc" -I"E:/Embedded_Engineer_Projects/Protocol_Sniffer/proto_sniffer/MCAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-APPLICATION-2f-Src

clean-APPLICATION-2f-Src:
	-$(RM) ./APPLICATION/Src/circular_buffer.cyclo ./APPLICATION/Src/circular_buffer.d ./APPLICATION/Src/circular_buffer.o ./APPLICATION/Src/circular_buffer.su ./APPLICATION/Src/i2c_gyro_data_handle.cyclo ./APPLICATION/Src/i2c_gyro_data_handle.d ./APPLICATION/Src/i2c_gyro_data_handle.o ./APPLICATION/Src/i2c_gyro_data_handle.su ./APPLICATION/Src/log_data.cyclo ./APPLICATION/Src/log_data.d ./APPLICATION/Src/log_data.o ./APPLICATION/Src/log_data.su ./APPLICATION/Src/spi_frame_simulate.cyclo ./APPLICATION/Src/spi_frame_simulate.d ./APPLICATION/Src/spi_frame_simulate.o ./APPLICATION/Src/spi_frame_simulate.su ./APPLICATION/Src/spi_loopback_feature.cyclo ./APPLICATION/Src/spi_loopback_feature.d ./APPLICATION/Src/spi_loopback_feature.o ./APPLICATION/Src/spi_loopback_feature.su

.PHONY: clean-APPLICATION-2f-Src


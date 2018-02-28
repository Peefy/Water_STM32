#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <stdbool.h>   

#include "stm32f10x.h"
#include "stm32f10x_it.h"

#include "stm32f10x_usart.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_spi.h"

#include "misc.h"

#include "GPIOLIKE51.h"
#include "init.h"
#include "delay.h"
#include "oled.h"
#include "uart.h"
#include "pwm.h"
#include "ad.h"
#include "slavecomputer.h"
//#include "nrf24l01.h"
#include "iwdg.h"
#include "sensor.h"
#include "pose.h"
#include "flash.h"
#include "servo.h"
#include "Motor.h"
#include "control.h"
#include "analysis.h"
#include "Sound.h"
#include "GUI.h"
#include "Key.h"

#include "SystemCore.h"
#include "Queue.h"
#include "CString.h"

extern PIDType SerPD;

#define LED PCout(13) //1代表亮，0代表灭。
#define FMQ_ON_onetime	kaiji_fmq(), delay_ms(100)

#endif

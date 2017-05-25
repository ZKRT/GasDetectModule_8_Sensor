#include <string.h>
#include <stdio.h>
#include "rs485.h"
#include "can.h"
#include "led.h"
#include "delay.h"
#include "poison.h"
#include "timer.h"
#include "usart.h"

uint16_t sen_val_buff[NO_OF_SENSOR]; //save all sersor value
//uint16_t sen_val_buff[NO_OF_SENSOR] ={1,2,3,4,5,6,7,8};

int main(void )
{
//	int i;
//	RCC_Configuration();  //使用外部晶振，屏蔽此调用
	SysTick_Init();
	RS485_Init(9600);
	usart_init();
	TIM3_Int_Init();
	CAN_Mode_Init(CAN_Mode_Normal);
	LED_Init();
	delay_ms(15000);//上电一定时间之后，才能去读传感器是否存在，不然会出错，故此处需加一个延时  //zkrt_debug
	//CheckSensorType(&sensor_type);  //not need
	while (1)
	{
		if(loop_flag)   //1000ms
		{
//			GPIO_ResetBits(GPIOA, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);  //just test //zkrt_debug
			ReadAllVal_V2(sen_val_buff);//上电约23秒之后才能开始读到CO2的数据
			zkrt_read_posion_ack();
//			for(i=0; i<NO_OF_SENSOR; i++)
//			{
//				printf("[%d] %d, ", i,sen_val_buff[i]);
//			}
//			printf("\n");			
			loop_flag=0;
		}
	}
}

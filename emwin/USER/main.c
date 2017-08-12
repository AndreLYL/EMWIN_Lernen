#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "ILI93x.h"
#include "key.h"  
#include "sram.h"   
#include "malloc.h" 
#include "GUI.h"

//ALIENTEK 探索者STM32F407开发板 实验37
//内存管理实验-库函数版本 
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
 
 

int main(void)
{        
	u8 key;		 
 	u8 i=0;	    
	u8 *p=0;
	u8 *tp=0;
	u8 paddr[18];				//存放P Addr:+p地址的ASCII值
	u8 sramx=0;					//默认为内部sram

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	LED_Init();					//初始化LED 
 	TFTLCD_Init();					//LCD初始化  
 	KEY_Init();					//按键初始化 
 	FSMC_SRAM_Init();			//初始化外部SRAM  
	
	my_mem_init(SRAMIN);		//初始化内部内存池
	my_mem_init(SRAMEX);		//初始化外部内存池
	my_mem_init(SRAMCCM);		//初始化CCM内存池
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//开启CRC时钟
	GUI_Init();
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_RED);
	GUI_Clear();
	GUI_SetFont(&GUI_Font24_ASCII);
//	GUI_DispStringAt("Hello World!!!",0,0);
	GUI_DispString("Hello World!!!");


}



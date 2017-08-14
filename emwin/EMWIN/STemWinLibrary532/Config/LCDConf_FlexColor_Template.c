/*********************************************************************
*          Portions COPYRIGHT 2016 STMicroelectronics                *
*          Portions SEGGER Microcontroller GmbH & Co. KG             *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_FlexColor_Template.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "ILI93x.h"

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/


//与触摸屏有关定义，根据实际情况填写
#define TOUCH_AD_TOP		160  	//按下触摸屏的顶部，写下 Y 轴模拟输入值。
#define TOUCH_AD_BOTTOM		3990 	//按下触摸屏的底部，写下 Y 轴模拟输入值。
#define TOUCH_AD_LEFT 		160		//按下触摸屏的左侧，写下 X 轴模拟输入值。
#define TOUCH_AD_RIGHT		3990	//按下触摸屏的右侧，写下 X 轴模拟输入值。



#define VXSIZE_PHYS	240 
#define VYSIZE_PHYS 320



//
// Physical display size
//
#define XSIZE_PHYS  240 // To be adapted to x-screen size
#define YSIZE_PHYS  320 // To be adapted to y-screen size

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
//配置程序,用于创建显示驱动器件,设置颜色转换程序和显示尺寸
void LCD_X_Config(void) {
	GUI_DEVICE_CreateAndLink(&GUIDRV_Template_API, GUICC_M565, 0, 0); //创建显示驱动器件
	LCD_SetSizeEx    (0, lcddev.width, lcddev.height);
	LCD_SetVSizeEx   (0, lcddev.width, lcddev.height);
	if(lcddev.id == 0X5510) //0X5510为4.3寸 800x480的屏
	{
		if(lcddev.dir == 0) //竖屏  // 2001:3520 6352
			{					    // 9147:3832 6288
			GUI_TOUCH_Calibrate(GUI_COORD_X,0,480,0,479);
			GUI_TOUCH_Calibrate(GUI_COORD_Y,0,800,0,799);
		}else //横屏
		{
			//GUI_TOUCH_SetOrientation(GUI_SWAP_XY|GUI_MIRROR_Y); 
			GUI_TOUCH_Calibrate(GUI_COORD_X,0,480,0,479); 		
			GUI_TOUCH_Calibrate(GUI_COORD_Y,0,800,0,799);
		}
	}else if(lcddev.id == 0X1963)//1963为7寸屏 800*480 
	{
		if(lcddev.dir == 0) //竖屏
		{					// 6368 3816
			//GUI_TOUCH_SetOrientation(GUI_SWAP_XY|GUI_MIRROR_Y); 
			GUI_TOUCH_Calibrate(GUI_COORD_X,0,800,0,799); 		
			GUI_TOUCH_Calibrate(GUI_COORD_Y,0,480,0,479);
		}else //横屏
		{
			GUI_TOUCH_Calibrate(GUI_COORD_X,0,800,0,799); 		
			GUI_TOUCH_Calibrate(GUI_COORD_Y,0,480,0,479);
		}
	}else if(lcddev.id == 0X5310 || lcddev.id == 0X6804) //0X5510 0X6804为3.5寸 320x480
	{
		if(lcddev.dir == 0) //竖屏 	
		{							
			GUI_TOUCH_Calibrate(GUI_COORD_X,0,320,3931,226);
			GUI_TOUCH_Calibrate(GUI_COORD_Y,0,480,3812,196);
		}else //横屏
		{
			GUI_TOUCH_SetOrientation(GUI_SWAP_XY|GUI_MIRROR_Y); 
			GUI_TOUCH_Calibrate(GUI_COORD_X,0,320,3931,226);
			GUI_TOUCH_Calibrate(GUI_COORD_Y,0,480,3812,196); 	
		}
	}
	else             //其他屏幕全部默认为2.8寸 320X240
	{
		if(lcddev.dir == 0) //竖屏
		{					
			GUI_TOUCH_Calibrate(GUI_COORD_X,0,lcddev.width,155,3903);
			GUI_TOUCH_Calibrate(GUI_COORD_Y,0,lcddev.height,188,3935);
		}else //横屏
		{
			GUI_TOUCH_SetOrientation(GUI_SWAP_XY|GUI_MIRROR_Y); 
			GUI_TOUCH_Calibrate(GUI_COORD_X,0,240,155,3903); 	
			GUI_TOUCH_Calibrate(GUI_COORD_Y,0,320,188,3935);
		}
	}
}

//显示器驱动的回调函数
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
	//当初始化的时候被调用,主要是设置显示控制器,如果显示控制器在外部初始化则需要用户初始化
		
	//	TFTLCD_Init(); //初始化LCD 已经在开始初始化了,所以此处不需要初始化。
    return 0;
  }
		default:
    r = -1;
	}
  return r;
}

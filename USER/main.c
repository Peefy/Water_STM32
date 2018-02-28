
#include "include.h"     //包含所有的头文件

int main(void)
{
		SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
		All_Init();	         // HardWare Init
		while (1)
		{
				Gui();	             			//交互界面显示
				AutoAngle();	       			//姿态获取	
				ComWithHC();			        //与上位机收发通信
				PowerOnStart_Main(); 			//上电延时启动辅助函数	
				FeedDog();					 			//喂看门狗
				UiThreadDelay(UiDelayMS);	//UI刷新延时		
    }
}



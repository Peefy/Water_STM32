
#include "include.h"     //�������е�ͷ�ļ�

int main(void)
{
		SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
		All_Init();	         // HardWare Init
		while (1)
		{
				Gui();	             //����������ʾ
				AutoAngle();	       //��̬��ȡ	
				ComWithHC();			
				PowerOnStart_Main(); //�ϵ���ʱ������������	
				FeedDog();			
				UiThreadDelay(UiDelayMS);			
    }
}








#include "include.h"     //�������е�ͷ�ļ�

int main(void)
{
		SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
		All_Init();	         // HardWare Init
		while (1)
		{
				Gui();	             			//����������ʾ
				AutoAngle();	       			//��̬��ȡ	
				ComWithHC();			        //����λ���շ�ͨ��
				PowerOnStart_Main(); 			//�ϵ���ʱ������������	
				FeedDog();					 			//ι���Ź�
				UiThreadDelay(UiDelayMS);	//UIˢ����ʱ		
    }
}



/************************* (C) COPYRIGHT 2013 DZXH ************************
* ��  ��  ��      : KEY_EVENT.C
* ��      ��      : DZXH@Dream Creater
* ��      ��      ��DZXH ������V2.1/V1.0��
* ��  ��  ��      : http://shop102062100.taobao.com/
* ��      ��      : V1.0
* ��      ��      : 2015/2/1
* ��  ��  MCU     : STM32F103VET6
* ��  ��  ��      : Keil ARM 4.54
* ��      ��      : �����¼�����
**************************************************************************/
#include "key.h"
#include "GUI.h"

/************************************************************************
* ��  ��  ��  : deal_key_event
* ��      ��  : �����¼�����
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void deal_key_event()
{
    KEY_MSG_t keymsg;

    while(get_key_msg(& keymsg))     //��ð����ͽ��д���
    {     	
        if(keymsg.status == KEY_DOWN)
        {
//////////������д�Լ����¼�����       
            switch(keymsg.key)
            {
            case KEY_0:
				break;

            case KEY_1:
				break;

            case KEY_2:
				break;

            case KEY_3:
				break;

            case KEY_4:
				break;            
            case KEY_UPP:
            	if(ActProgramSate == Saved)
           		{
              		ActChangeState=Once;
					ActCommand=SelectUp;//PageUp;
           		}
				else if(ActProgramSate == Changing)
           		{
              		ActChangeState=Once;
              		ActCommand=Add;
           		}
				else if(CMDstate == ActProgramSate)
				{
              		ActChangeState=Once;
					ActCommand=SelectUp;
				}
            
            	ActCommandState=Begin;
				#ifdef KeySound
				up_fmq();
				#endif
                break;

            case KEY_DOWNN:
            	if(ActProgramSate == Saved)
           		{
              		ActChangeState=Once;
					ActCommand=SelectDown;//PageDown;
           		}
				else if(ActProgramSate == Changing)
           		{
              		ActChangeState=Once;
              		ActCommand=Minus;
           		}
				else if(CMDstate == ActProgramSate)
				{
              		ActChangeState=Once;
					ActCommand=SelectDown;
				}
            
            	ActCommandState=Begin;
								#ifdef KeySound
				down_fmq();
				#endif
                break;

            case KEY_L:
    		 	if(ActProgramSate == Saved | CMDstate == ActProgramSate)
    		 	{    		 		  
           	  		ActCommand=PageUp;
              		ActCommandState=Begin;
    		 	}
									#ifdef KeySound
					left_fmq();
				#endif
				break;

            case KEY_R:
        		if(ActProgramSate == Saved | CMDstate == ActProgramSate)
    		 	{	  
           	  		ActCommand=PageDown;
              		ActCommandState=Begin;
    		 	}
									#ifdef KeySound
					right_fmq();
				#endif
				break;

            case KEY_OK:
				if(ActProgramSate == Changing)
					ActCommand=Save;
				else if(ActProgramSate == Saved)
					ActCommand=Select;
				else if(ActProgramSate == CMDstate)
					ActCommand = DoCmd;
				ActCommandState=Begin;		
				
				#ifdef KeySound
				ok_fmq();
				#endif
				
				break;

            default:
				break;
            }
//            down_fmq();
        }
        else if(keymsg.status == KEY_HOLD)
        {
         
            switch(keymsg.key)
            {
            case KEY_0:
                break;
            case KEY_1:
				break;
            case KEY_2:
				break;
            case KEY_3:     
				break;
            case KEY_4:	
				break;            
            case KEY_UPP:
	           if(ActProgramSate == Saved)
	           {
	              ActChangeState=Continue;
							  ActCommand=PageUp;
	           }else if(ActProgramSate == Changing)
	           {
	              ActChangeState=Continue;
	              ActCommand=Add;
	           }
	            
	            ActCommandState=Begin;
				break;
				
            case KEY_DOWNN:
				if(ActProgramSate == Saved)
		        {
		        	ActChangeState=Continue;
					ActCommand=PageDown;
		        }
				else if(ActProgramSate == Changing)
		        {
		        	ActChangeState=Continue;
		            ActCommand=Minus;
		        }
		        ActCommandState=Begin;
                break;

            case KEY_L:
				ActCommand = ModeUp;
				ActCommandState = Begin;
                break;

            case KEY_R:
				ActCommand = ModeDown;
				ActCommandState = Begin;
				break;

            case KEY_OK:
				ActCommandState = Finished;
				break;

            default:
				break;
		
            }
						
        }
    }
}

extern void GUI_showOnePage(void);
extern void GUI_ShowCMDOnePage(void);

void GUI_RefreshCmdUI(void)
{
		//LCD_CLEAR();
		GUI_ShowCMDOnePage();
}

void GUI_RefreshDataUI(void)
{
		//LCD_CLEAR();
		GUI_showOnePage();
}



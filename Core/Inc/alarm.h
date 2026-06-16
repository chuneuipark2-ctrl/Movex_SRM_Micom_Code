#ifndef __ALARM_H
#define __ALARM_H

#include "type.h"
#include "User_Define.h"

extern void		MCU_Output_Control(INT08U nPort, INT08U nFlag);


extern void		Graph_Update(void);
void			Graph_Update_Mode(void);
extern void		clearGraph(void);
void			Graph_Setup_Init();
void			Graph_Setup(INT08U nGraphType, INT08U nInterval, INT32U nStart_Postion);
void			add_alarm_log(INT08U MainCode, INT08U SubCode, INT08U Value);
extern void		save_error_code(INT08U main_error_code, INT08U sub_error_code, INT16U error_reason);
void			save_error_code_Invertor(INT08U main_error_code, INT08U sub_error_code, INT16U error_reason);
void Event_Warning_Code(INT08U main_error_code, INT08U sub_error_code, INT16U error_reason);
extern void           add_event_log(INT08U MainCode, INT08U SubCode, INT08U Value);
extern INT08U         get_event_log(INT08U last_inx, INT32U* systime, INT08U* time_bin, INT08U* main_code, INT08U* sub_code, INT08U* value);
extern void           controlCpuReset(void);
extern void			Set_MCU_Input_FilterTime(void);
extern void           get_main_controller_di(void);
extern void           get_main_controller_Mode_SW(void);
void Delete_ForkMoveInfo(INT08U nNum);
void Save_ForkMove_OrderStatus(INT08U num, INT08U st);
void Save_ForkMove_OrderProcess(INT08U num, INT08U st);
void Delete_ForkWorkInfo(INT08U nNum);
extern void           Save_ForkWork_OrderStatus(INT08U num, INT08U st);
extern void           Save_ForkWork_OrderProcess(INT08U num, INT08U st);
extern void           Save_ForkWork_Information(INT08U num, INT08U OrderStatus, INT08U OrderProcess);

extern void           getSystemDateTime(void);
extern void           DIManager(void);
extern void           runningLED(void);
extern void           FNDManager(void);
extern void           AlarmManager(void);

extern void Set_TestStatus(INT32S nIndex, INT32S nData);
extern void Clear_TestStatus(INT32S nIndex);
extern void All_Clear_TestStatus();
extern void Set_TestControl(INT32S nIndex, INT32S nData);
extern void Clear_TestControl(INT32S nIndex);
extern void All_Clear_TestControl();

extern void SetTimer1ms(INT32U*);
extern void SetTimer100us(INT32U*);

extern INT32U getCalcTimer100us(INT32U);
extern INT32U getCalcTimer1ms(INT32U);

extern void wait100us(INT32U);
extern void wait1ms(INT32U);
extern void wait1ms_no_wd(INT32U);
extern void uSleep_ms(INT32U time);


#endif

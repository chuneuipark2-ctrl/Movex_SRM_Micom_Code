/*
 * SRM_Parameter.h
 *
 *  Created on: 2022. 10. 26.
 *      Author: ARTWARE
 */

#ifndef SRC_SRM_PARAMETER_H_
#define SRC_SRM_PARAMETER_H_

#include "type.h"
#include "User_Define.h"

void BackUp_Device_Parameter(DeviceSetting* pSet);
extern INT08U Set_Device_Parameter(DeviceSetting* pSet);
extern void Device_Setting_Init();

//extern void Set_Machine_Parameter(SRM_Machine_Type* pSet);
//extern INT08U Set_Machine_Parameter(SRM_Machine_Type* pSet);
extern INT08U Set_Machine_Parameter(SRM_Machine_STR* pSet);
extern INT08U Set_DSP_Parameter(MX_DSP_Setting* pSet);
extern void Machine_Type_Setting_Init();

extern INT08U Check_DIO_SetParameter();
extern void Set_DIO_Parameter(DIO_SetSTR* pDIO_Set);
extern void DIO_Setting_Init();

extern INT08U Check_RackEnv_Config();
extern void Set_Rack_Config(RackConfigSTR* pSetting);
extern void Clear_Rack_Config(void);
extern void Rack_Config_Init();

extern INT08U Check_CellEnv_Config();
extern void Set_Cell_Config(CellConfigSTR* pSetting);
void Set_Cell_Config_1(CellConfigSTR* pSetting, INT08U nDir);
extern void Clear_Cell_Config();
extern void Cell_Config_Init();

extern INT08U Check_StationEnv_Config();
extern void Set_Station_Config(StationSetupSTR* pSetting);
extern void Clear_Station_Config();
extern void Station_Config_Init();

extern INT08U Check_ProhibitRack_Config();
extern void Clear_ProhibitRack_Config();
extern INT08U Check_InhibitRack_Data(InhibitRackSet_t* nData);
extern void Set_ProhibitRack_Config(ProhibitRackSTR* pSetting);
extern void ProhibitRack_Config_Init();

extern INT08U Check_SpecialRack_Config();
extern void Clear_SpecialRack_Config();
extern INT08U Check_SpecialRack_Data(SpecialRackSet_t* nData);
extern void Set_SpecialRack_Config(SpecialRackSTR* pSetting);
extern void SpecialRack_Config_Init();

extern void Write_CellOffset_InitCode();
extern INT08U Check_Cell_Offset_Config();
extern void Clear_Cell_Offset_UseFlag(INT16U nStart);
extern void Clear_Cell_Offset_UseFlagAll();
extern void Clear_CellOffset_Config();
extern void CellOffset_Config_Init();

//extern CellOffsetSTR Read_CellOffset(INT08U nBay, INT08U nLv);

extern INT08U Read_CellOffset_Bay_Lv(INT08U nBay, INT08U nLv, CellOffsetSTR* pReadBuf);
extern void Read_CellOffset_Addr(INT16U nIndex, CellOffsetSTR* pReadBuf);

extern INT08U Write_CellOffset(CellOffsetSTR* pBuf);
//extern INT08U Write_CellOffset_1(INT16U nIndex, CellOffsetSTR* pBuf);
//extern INT08U Write_CellOffset_2(INT16U nIndex, INT08U* pBuf, INT16U nLen);
extern INT08U Read_CellOffset_Block(INT16U nBlockNo, INT08U* pBuf);
extern INT08U Write_CellOffset_Block(INT16U nBlockNo, INT08U* pBuf);

extern INT08U Check_CellOffset_BlockNo(CellOffsetSTR* pBuf);
extern void Check_CellOffset_UseFlag(CellOffsetSTR* pBuf, INT08U* pUseFlag);
extern INT16U Scan_CellOffset_UseCount();
extern void Read_CellOffset_Data(INT16U nPage);
extern void Read_CellOffset_Data_1(INT16U nReadPage);

extern INT08U Set_SafetyPlug_Type(ParamControlSTR* pSetting);
extern INT08U Set_DoorSensor_UseFlag(ParamControlSTR* pSetting);
extern INT08U Set_DoorSensor_AlarmFlag(ParamControlSTR* pSetting);
extern INT08U Set_LaserModem_AlarmFlag(ParamControlSTR* pSetting);
extern INT08U Set_AutoChange_Mode(ParamControlSTR* pSetting);
extern INT08U Set_TravLift_OperTime_SyncFlag(ParamControlSTR* pSetting);
extern INT08U Set_Cargo_Adnormal_HomeReturn_UseFlag(ParamControlSTR* pSetting);
extern INT08U Set_Forking_Sensor_AlarmFlag(ParamControlSTR* pSetting);
extern INT08U Set_OutputStation_DoubleEntry_AlarmFlag(ParamControlSTR* pSetting);
extern INT08U Set_Forking_Interlock_AlarmFlag(ParamControlSTR* pSetting);
extern INT08U Set_Forking_Interlock_CheckFlag(ParamControlSTR* pSetting);
extern INT08U Set_Forking_lift_BrakeOn_UseFlag(ParamControlSTR* pSetting);
extern void Set_Forking_Origin_OperCount(ParamControlSTR* pSetting);
extern void Set_RetryInPositon(ParamControlSTR* pSetting);
extern void Set_Loading_DelayTime(ParamControlSTR* pSetting);
extern void Set_Unloading_DelayTime(ParamControlSTR* pSetting);
extern void Set_Fork_Origin_DelayTime(ParamControlSTR* pSetting);
extern void Set_Setup_TimeOut(ParamControlSTR* pSetting);
extern void Set_Drive_Timeout(ParamControlSTR* pSetting);
extern void Set_Auto_Timeout(ParamControlSTR* pSetting);
extern void Set_ForceMode_ReleaseTime(ParamControlSTR* pSetting);
extern INT08U Set_Fan_Control(ParamControlSTR* pSetting);
extern void Set_Buzzer_Control(ParamControlSTR* pSetting);
extern void Set_UpperBrakeSetup(ParamControlSTR* pSetting);

extern INT08U Set_AutoFork_PositionSensor_Alarm(ParamControlSTR* pSetting);
INT08U Set_Carriage_Stabilzation_Time(ParamControlSTR* pSetting);
extern void Save_Control_Param(ParamControlSTR* pSetting);
extern void Control_Param_Init();

extern void Set_Trav_Velocity(INT08U nType, UnitVelocitySTR* pVelocity);
extern void Set_Trav_Velocity_1(INT08U nType, UnitVelocitySTR* pSrcVel, UnitVelocitySTR* pWrVel);
extern void Set_Trav_InPostion_Tolerance(ParamTravelDriveSTR* pSetting);
extern void Set_Trav_InPostion_Tolerance_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);
extern void Set_Trav_InPostion_Hysteresis(ParamTravelDriveSTR* pSetting);
extern void Set_Trav_InPostion_Hysteresis_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);
extern void Set_Trav_Manual_Drive(ParamTravelDriveSTR* pSetting);
extern void Set_Trav_Manual_Drive_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);
extern void Set_Trav_BrakeOn_DelayTime(ParamTravelDriveSTR* pSetting);
extern void Set_Trav_BrakeOn_DelayTime_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);
extern void Set_Trav_Origin_Position(ParamTravelDriveSTR* pSetting);
extern void Set_Trav_Origin_Position_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);

extern INT32S Set_Trav_Home_StationNo(INT32S nSetValue);
extern INT32S Set_Trav_Home_BayNo(INT32S nSetValue);
extern INT08U Set_Trav_Home_Position(ParamTravelDriveSTR* pSetting);
extern INT08U Set_Trav_Home_Position_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);

extern INT32S Set_Trav_Maintenance_mm(INT32S nSetValue);
extern INT08U Set_Trav_Maintenance_Position(ParamTravelDriveSTR* pSetting);
extern INT08U Set_Trav_Maintenance_Position_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);

extern INT08U Set_Trav_DecelationRange_Mode(ParamTravelDriveSTR* pSetting);
extern INT08U Set_Trav_DecelationRange_Mode_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);

extern INT08U Set_Trav_SoftLimit_Error(ParamTravelDriveSTR* pSetting);
extern INT08U Set_Trav_SoftLimit_Error_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);
extern INT08U Set_Trav_SoftDecelation_Error(ParamTravelDriveSTR* pSetting);
extern INT08U Set_Trav_SoftDecelation_Error_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);

extern INT08U Set_Trav_OriginDog_Postion_Error(ParamTravelDriveSTR* pSetting);
extern INT08U Set_Trav_OriginDog_Postion_Error_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);

extern INT08U Set_Trav_DecelDog_Position_Error(ParamTravelDriveSTR* pSetting);
extern INT08U Set_Trav_DecelDog_Postion_Error_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);

extern void Set_Trav_Invertor_Param(ParamTravelDriveSTR* pSetting);
extern void Set_Trav_Invertor_Param_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf);

extern void Save_Travel_Drive_Param(ParamTravelDriveSTR* pSetting);
extern void Travel_Drive_Param_Init();

extern INT08U Check_Available_Trav_InPostion_Tolerance();
extern INT08U Check_Available_Trav_InPostion_Hysteresis();

extern void Set_Lift_Velocity(INT08U nType, UnitVelocitySTR* pVelocity);
extern void Set_Lift_Velocity_1(INT08U nType, UnitVelocitySTR* pSrcVel, UnitVelocitySTR* pWrVel);
extern void Set_Lift_InPostion_Tolerance(ParamLiftDriveSTR* pSetting);
extern void Set_Lift_InPostion_Tolerance_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern void Set_Lift_InPostion_Hysteresis(ParamLiftDriveSTR* pSetting);
extern void Set_Lift_InPostion_Hysteresis_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern void Set_Lift_Manual_Drive(ParamLiftDriveSTR* pSetting);
extern void Set_Lift_Manual_Drive_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern void Set_Lift_BrakeOn_DelayTime(ParamLiftDriveSTR* pSetting);
extern void Set_Lift_BrakeOn_DelayTime_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern void Set_Lift_Origin_Position(ParamLiftDriveSTR* pSetting);
extern void Set_Lift_Origin_Position_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern INT08U Set_Lift_Home_Position(ParamLiftDriveSTR* pSetting);
extern INT08U Set_Lift_Home_Position_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern INT08U Set_Lift_Maintanance_Position(ParamLiftDriveSTR* pSetting);
extern INT08U Set_Lift_Maintanance_Position_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern INT08U Set_Lift_DecelationRange_Mode(ParamLiftDriveSTR* pSetting);
extern INT08U Set_Lift_DecelationRange_Mode_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern INT08U Set_Lift_SoftLimit_Error(ParamLiftDriveSTR* pSetting);
extern INT08U Set_Lift_SoftLimit_Error_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern INT08U Set_Lift_SoftDecelation_Error(ParamLiftDriveSTR* pSetting);
extern INT08U Set_Lift_SoftDecelation_Error_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern INT08U Set_Lift_OriginDog_Postion_Error(ParamLiftDriveSTR* pSetting);
extern INT08U Set_Lift_OriginDog_Postion_Error_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern INT08U Set_Lift_DecelDog_Postion_Error(ParamLiftDriveSTR* pSetting);
extern INT08U Set_Lift_DecelDog_Postion_Error_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern INT08U Set_Lift_ForkOut_Jerk_Set(ParamLiftDriveSTR* pSetting);
extern INT08U Set_Lift_ForkOut_Jerk_Set_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrbuf);

extern void Set_Lift_Invertor_Param(ParamLiftDriveSTR* pSetting);
extern void Set_Lift_Invertor_Param_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);

extern void Set_Lift_LevelUpOffset(ParamLiftDriveSTR* pSetting);
extern void Set_Lift_LevelUpOffset_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern void Set_Lift_LevelDnOffset(ParamLiftDriveSTR* pSetting);
extern void Set_Lift_LevelDnOffset_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern void Set_Lift_Veriant_LT_Offset(ParamLiftDriveSTR* pSetting);
extern void Set_Lift_Veriant_LT_Offset_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf);
extern void Save_Lift_Drive_Param(ParamLiftDriveSTR* pSetting);
extern void Lift_Drive_Param_Init();

extern INT08U Check_Available_Lift_InPostion_Tolerance();
extern INT08U Check_Available_Lift_InPostion_Hysteresis();

extern void Set_Fork_Velocity(INT08U nType, UnitVelocitySTR* pVelocity);
extern void Set_Fork_Velocity_1(INT08U nType, UnitVelocitySTR* pVelocity, UnitVelocitySTR* pWrbuf);
extern void Set_Fork_InPostion_Tolerance(ParamForkDriveSTR* pSetting);
extern void Set_Fork_InPostion_Tolerance_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern void Set_Fork_InPostion_Hysteresis(ParamForkDriveSTR* pSetting);
extern void Set_Fork_InPostion_Hysteresis_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern void Set_Fork_Manual_Drive(ParamForkDriveSTR* pSetting);
extern void Set_Fork_Manual_Drive_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern INT08U Set_Fork_Encoder_Setup(ParamForkDriveSTR* pSetting);
extern INT08U Set_Fork_Encoder_Setup_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern void Set_Fork_Origin_Offset(ParamForkDriveSTR* pSetting);
extern void Set_Fork_Origin_Offset_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern void Set_Fork_LagError_Offset(ParamForkDriveSTR* pSetting);
extern void Set_Fork_LagError_Offset_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern void Set_Fork_P_Gain(ParamForkDriveSTR* pSetting);
extern void Set_Fork_P_Gain_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern INT08U Set_Fork_Decelation_Control(ParamForkDriveSTR* pSetting);
extern INT08U Set_Fork_Decelation_Control_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern void Set_Fork_TwinFork_Setup(ParamForkDriveSTR* pSetting);
extern void Set_Fork_TwinFork_Setup_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern INT08U Set_Fork_Position_UseFlag(ParamForkDriveSTR* pSetting);
extern INT08U Set_Fork_Position_UseFlag_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern void Set_Fork_Position_Depth(ParamForkDriveSTR* pSetting);
extern void Set_Fork_Position_Depth_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);
extern void Set_Fork_Invertor_Param(ParamForkDriveSTR* pSetting);
extern void Set_Fork_Invertor_Param_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf);

extern void Save_Fork_Drive_Param(ParamForkDriveSTR* pSetting);
extern void Fork_Drive_Param_Init();

extern INT08U Check_Available_Fork_InPostion_Tolerance();
extern INT08U Check_Available_Fork_InPostion_Hysteresis();

extern INT08U Check_Available_Fork_Origin_Offset();

#endif /* SRC_SRM_PARAMETER_H_ */

/*
 * com_dsp.h
 *
 *  Created on: 2023. 1. 3.
 *      Author: ARTWARE
 */

#ifndef INC_COM_DSP_H_
#define INC_COM_DSP_H_

#include "type.h"

#define DEF_DSP_SLAVE_CNT	(2)

struct __attribute__((__packed__)) tagDspStatus
{
	INT08U			ProtocolVer;
	INT08U			PgmVer[4];
	INT08U			Reserved1[4];

	INT08U			LinkStatus;
	INT08U			DeviceID;
	INT08U			ModeSw;
	INT08U			TestMode;
	INT08U			Reserved2[5];

	INT08U			Key1;
	INT08U			Key2;
	INT08U			Key3;

	INT08U			BuzzerTest;
	INT08U			Reserved3[10];
};
typedef struct tagDspStatus	DspStatusSTR;

struct __attribute__((__packed__)) tagDspColor
{
	INT08U			Code : 4;
	INT08U			Reserved_0 : 1;
	INT08U			Reserved_1 : 1;
	INT08U			Reserved_2 : 1;
	INT08U			Full : 1;
};
typedef struct tagDspColor		DspColor_t;

struct __attribute__((__packed__)) tagDspData		//C2 데이터 표시
{
	INT08U			Status1[6];
	INT08U			Reserved1;
	INT08U			Status2[6];
	DspColor_t		Color;
	INT08U			ToggleTime;			//단위 : ms, 100~
	INT08U			Buzzer;
	INT08U			BuzzerTime;			//단위 : 10ms, 설정범위 : 0.01~2.55초 -> 1~255, 값이 0이면 ON
	INT08U			Reserved2[10];
};
typedef struct tagDspData		DspDataSTR;

struct __attribute__((__packed__)) tagRecvDspData		//C2 데이터 표시
{
	INT08U			ProtocolVer;
	INT08U			PgmVer[4];
	INT08U			RemoconKey[3];
	INT08U			Reserved[10];
};
typedef struct tagRecvDspData		RecvDspData;

enum enumDSP_COLOR {
	DSP_COLOR_NONE = 0,
	DSP_COLOR_RED,
	DSP_COLOR_GREEN,
	DSP_COLOR_YELLOW,
	DSP_COLOR_BLUE,
	DSP_COLOR_PURPLE,
	DSP_COLOR_JADE,
	DSP_COLOR_WHITE,
};

extern DspStatusSTR		m_DspStatus[DEF_DSP_SLAVE_CNT];
//extern DspDataSTR		m_DspData;
extern RecvDspData		m_RecvDspData[DEF_DSP_SLAVE_CNT];

extern INT08U			m_Recv_DSP_ID;

void DSP_ComManager(void);

#endif /* INC_COM_DSP_H_ */

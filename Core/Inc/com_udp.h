/*
 * com_udp.h
 *
 *  Created on: Jun 15, 2022
 *      Author: ARTWARE
 */

#ifndef SRC_COM_UDP_H_
#define SRC_COM_UDP_H_

#include "ip4_addr.h"

#include "type.h"
#include "User_Define.h"

//#define UDP_SERVER_PORT    9506   /* define the UDP local connection port */

#define UPLINK_UDP_SERVER_PORT		11000   /* define the UDP local connection port */
//#define UPLINK_UDP_SERVER_PORT		9000 
#define DSP_UDP_SERVER_PORT			10000   /* define the UDP local connection port */

//#define UDP_CLIENT_PORT    5002   /* define the UDP remote connection port */
#define UDP_CLIENT_PORT    8000   /* define the UDP remote connection port */

struct __attribute__((__packed__)) tagUDPCom
{
	INT08U        Syn[4];
	ComHeaderSTR  Header;
	INT08U        Data[FRAME_MAX_DATA_LEN];
};
typedef struct tagUDPCom  UDPComSTR;
typedef struct tagUDPCom* UDPComPTR;

void udp_com_init(void);
void udp_com_init_DSP();

INT08U checkUdpServerDataFrame(UDPComSTR* pCom);

void udp_SendBuf();
void udp_SendBuf_DSP(INT32U* IPaddr, INT16U RemotePort);

void udp_Set_Fw_Download_IP_Info();

/* ============================================================
 * 설정값 - 서버 환경에 맞게 수정
 * ============================================================ */
#define TCP_SERVER_IP0              192
#define TCP_SERVER_IP1              168
#define TCP_SERVER_IP2              10
#define TCP_SERVER_IP3              30

#define TCP_MODBUS_PORT          502   // Local / Remote 공통

 /* 재연결 대기 시간 (ms) - getCalcTimer1ms 기준 */
#define TCP_RECONNECT_TIMEOUT_MS    5000

/* TCP 수신 버퍼 크기 */
#define TCP_RX_BUF_SIZE             1500

/* ============================================================
 * getFpgaTcpSocketState() 반환값과 1:1 매핑
 * 기존 HMI_UpLink_ModbusTCP_Manager() s_now_SSR 비교값 유지
 * ============================================================ */
#define TCP_SOCKET_STATE_IDLE        0   /* 미연결 (기존 FPGA: 0) */
#define TCP_SOCKET_STATE_SYN_WAIT    1   /* 연결 시도 중 (기존 FPGA: 1 TCP_SYN_ACK_WAIT) */
#define TCP_SOCKET_STATE_ESTABLISHED 2   /* 연결 완료 (기존 FPGA: 2 TCP_ESTABLISHED) */
#define TCP_SOCKET_STATE_ERROR       3   /* 에러 / 끊김 */

/* ============================================================
 * TCP 연결 상태
 * ============================================================ */
typedef enum {
    TCP_CLI_STATE_IDLE = 0,
    TCP_CLI_STATE_CONNECTING = 1,
    TCP_CLI_STATE_CONNECTED = 2,
    TCP_CLI_STATE_DISCONNECTED = 3,
    TCP_CLI_STATE_ERROR = 4,
} TCP_CLI_STATE;

/* ============================================================
 * Public API
 * ============================================================ */

 /**
  * @brief  TCP 클라이언트 초기화
  *         EtherNetManager() case 3: udp_com_init() 바로 다음에 호출
  */
void tcp_client_init(void);

/**
 * @brief  TCP 데이터 전송 (udp_SendBuf() 와 동일한 사용 방식)
 * @param  pData  전송 데이터 포인터
 * @param  nLen   전송 길이
 * @return 0: 성공, 1: 실패(미연결 or 버퍼 부족)
 */
INT08U tcp_client_SendBuf(INT08U* pData, INT16U nLen);

/**
 * @brief  현재 TCP 연결 상태 반환
 */
TCP_CLI_STATE tcp_client_GetState(void);

/**
 * @brief  TCP 연결 여부 (1: 연결됨, 0: 미연결)
 */
INT08U tcp_client_IsConnected(void);

/**
 * @brief  getFpgaTcpSocketState() 대체 함수
 *         기존 HMI_UpLink_ModbusTCP_Manager() 의 s_now_SSR 에 그대로 사용
 * @retval 0: IDLE, 1: SYN_WAIT(연결중), 2: ESTABLISHED(연결완료), 3: ERROR
 */
INT08U  tcp_client_GetSocketState(void);

void tcp_client_Connect(INT08U* pServerIp, INT16U localPort, INT16U remotePort);
void EtherNetManager(void);

#endif /* SRC_COM_UDP_H_ */

/**
  ******************************************************************************
  * @file            : com_udp.c
  * @version         :
  * @author          :
  * @brief           : This file implements UDP Communication
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "main.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "type.h"
#include "User_Define.h"
#include "uart.h"
#include "com_tml.h"
#include "lwip.h"
#include "alarm.h"
#include "com_udp.h"
#include "dev_SRM.h"

 /* Private typedef -----------------------------------------------------------*/
 /* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static struct udp_pcb m_upcb_Uplink;
static struct udp_pcb m_upcb_Dsplink;

static ip_addr_t m_Recv_IPAddr;
static INT16U m_RecvRemotePort = 0;

static ip_addr_t m_udp_IPAddr_FW_Download;
static INT16U m_UdpPort_FW_Download = 0;

/* Private function prototypes -----------------------------------------------*/
void udp_Process_echo(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port);
void udp_RecvProcess(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port);

void udp_RecvProcess_1(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port);

void udp_SendBuf();

static struct tcp_pcb* m_pTcpPcb = NULL;
static TCP_CLI_STATE    m_TcpState = TCP_CLI_STATE_IDLE;
static INT32U           m_ReconnectTimer = 0;
static ip4_addr_t       m_ServerIp;


static err_t  tcp_cb_connected(void* arg, struct tcp_pcb* pcb, err_t err);
static err_t  tcp_cb_recv(void* arg, struct tcp_pcb* pcb, struct pbuf* p, err_t err);
static err_t  tcp_cb_sent(void* arg, struct tcp_pcb* pcb, u16_t len);
static void   tcp_cb_err(void* arg, err_t err);
static err_t  tcp_cb_poll(void* arg, struct tcp_pcb* pcb);

/**
  * @brief  Initialize the server application.
  * @param  None
  * @retval None
  */
void udp_com_init(void)
{
	struct udp_pcb* upcb;
	err_t err;

	/* Create a new UDP control block  */
	upcb = udp_new();

	if (upcb)
	{
		/* Bind the upcb to the UDP_PORT port */
		/* Using IP_ADDR_ANY allow the upcb to be used by any local interface */
		err = udp_bind(upcb, IP_ADDR_ANY, UPLINK_UDP_SERVER_PORT);

		if (err == ERR_OK)
		{
			/* Set a receive callback for the upcb */
			udp_recv(upcb, udp_RecvProcess, NULL);

			memcpy(&m_upcb_Uplink, upcb, sizeof(struct udp_pcb));
		}
	}
}

/**
  * @brief  Initialize the server application.
  * @param  None
  * @retval None
  */
void udp_com_init_DSP()
{
	struct udp_pcb* upcb;
	err_t err;

	/* Create a new UDP control block  */
	upcb = udp_new();

	if (upcb)
	{
		/* Bind the upcb to the UDP_PORT port */
		/* Using IP_ADDR_ANY allow the upcb to be used by any local interface */
		err = udp_bind(upcb, IP_ADDR_ANY, DSP_UDP_SERVER_PORT);

		if (err == ERR_OK)
		{
			/* Set a receive callback for the upcb */
			udp_recv(upcb, udp_RecvProcess_1, NULL);

			memcpy(&m_upcb_Dsplink, upcb, sizeof(struct udp_pcb));
		}
	}
}

INT08U udp_Check_Fw_Download_IP_Info(const ip_addr_t* pAddr, INT16U nRemotePort)
{
	if (memcmp(pAddr, &m_udp_IPAddr_FW_Download, sizeof(ip_addr_t)))
	{
		return 0;
	}

	if (nRemotePort != m_UdpPort_FW_Download)
	{
		return 0;
	}

	return 1;
}

/**
  * @brief	udp_Set_Fw_Download_IP_Info
  * @param
  * @retval void
  */
void udp_Set_Fw_Download_IP_Info()
{
	memcpy(&m_udp_IPAddr_FW_Download, &m_Recv_IPAddr, sizeof(ip_addr_t));
	m_UdpPort_FW_Download = m_RecvRemotePort;
}


/* Private functions ---------------------------------------------------------*/

/**
  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */
void udp_Process_echo(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port)
{
	/* Connect to the remote client */
	udp_connect(upcb, addr, port);

	/* Tell the client that we have accepted it */
	udp_send(upcb, p);

	/* free the UDP connection, so we can accept new clients */
	udp_disconnect(upcb);

	/* Free the p buffer */
	pbuf_free(p);

}

/**
  * @brief  Check Vexi Protocol Frame
  * @param  UDP Dataram
  * @retval Result Check Frame
  */
INT08U checkUdpServerDataFrame(UDPComSTR* pCom)
{
	INT08U i, result = 0x00;

	for (i = 0; i < 4; i++) {
		if (pCom->Syn[i] != 0x16)   result |= 0x01;
	}

	if (!result) {
		if (pCom->Header.Len > 1492)	result |= 0x02;
	}

	if (!result) {
		if (pCom->Data[(pCom->Header.Len + 2) - 1] != 0xF5)	result |= 0x04;
	}

	if (!result) {
		if (crcInitStrCalc(0x0000, (INT08U*)&pCom->Header, (pCom->Header.Len - 1) + FRAME_HEADER_SIZE + FRAME_CRC_SIZE))
			result |= 0x08;
	}

	return result;
}


/**
  * @brief This function is called when an UDP datagram has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */
void udp_RecvProcess(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port)
{
	//INT08U	ret = 0, rxSt = 0;
	INT08U rxSt = 0;
	UDPComSTR pCom;

	static INT32U s_MassageIndex;

#if DEBUG_UPLINK_MSG
	printf("[UDP] Receive Massage Index : %ld IP:%d.%d.%d.%d Port : %d\r\n", s_MassageIndex,
		((INT08U)(addr->addr) & 0xFF), ((INT08U)(addr->addr >> 8) & 0xFF), \
		((INT08U)(addr->addr >> 16) & 0xFF), ((INT08U)(addr->addr >> 24) & 0xFF), port);
	/*
	printf("[UDP] Receive tot_len:%d len : %d\r\n", p->tot_len, p->len);

	printf("[UDP] Receive Data");
	for (INT16U i = 0; i < p->len; i++)
	{
		if ((i % 20) == 0)	printf("\r\n");
		printf("[%02x]", *((INT08U*)p->payload + i));
	}
	printf("\r\n");
	*/
#endif
	++s_MassageIndex;

	memcpy((INT08U*)&pCom, (INT08U*)p->payload, sizeof(INT08U) * p->len);
	rxSt = checkUdpServerDataFrame(&pCom);

	//++m_TestStatus.Ctrl[DEBUG_CTR_1];
	//m_TestStatus.Ctrl[DEBUG_CTR_2] = rxSt;

	if (rxSt)
	{
#if DEBUG_UPLINK_MSG
		printf("[UDP] RxIdx : %ld, Error Vexi Frame : %d\r\n", s_MassageIndex, rxSt);
#endif
	}
	else
	{
#if DEBUG_UPLINK_MSG
		printf("[UDP] RxIdx : %ld, Receive Vexi Frame : %d\r\n", s_MassageIndex, rxSt);
#endif
		if (m_pgmEnv.downloadMode)
		{
			if (udp_Check_Fw_Download_IP_Info(addr, port))
			{
				memcpy(&m_Recv_IPAddr, addr, sizeof(ip_addr_t));
				m_RecvRemotePort = port;

				rxDataAnalysis(rsETHUDPPort_Uplink, (TMLComSTR*)&pCom.Header);
			}
		}
		else
		{
			memcpy(&m_Recv_IPAddr, addr, sizeof(ip_addr_t));
			m_RecvRemotePort = port;

			rxDataAnalysis(rsETHUDPPort_Uplink, (TMLComSTR*)&pCom.Header);
		}
		

		m_pgmEnv.UDPConnect = 1;
		m_pgmEnv.UDPConnectTimer = m_pgmEnv.timer1ms;
	}

	/* Free the p buffer */
	pbuf_free(p);
}

/**
  * @brief This function is called when an UDP datagram has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */
void udp_RecvProcess_1(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port)
{
	//INT08U	ret = 0, rxSt = 0;
	INT08U rxSt = 0;
	UDPComSTR pCom;

	static INT32U s_MassageIndex;

#if DEBUG_DSP_UDP_MSG
	printf("[UDP_DSP] Receive Massage Index : %ld IP:%d.%d.%d.%d Port : %d\r\n", s_MassageIndex,
		((INT08U)(addr->addr) & 0xFF), ((INT08U)(addr->addr >> 8) & 0xFF), \
		((INT08U)(addr->addr >> 16) & 0xFF), ((INT08U)(addr->addr >> 24) & 0xFF), port);
	/*
	printf("[UDP] Receive tot_len:%d len : %d\r\n", p->tot_len, p->len);

	printf("[UDP] Receive Data");
	for (INT16U i = 0; i < p->len; i++)
	{
		if ((i % 20) == 0)	printf("\r\n");
		printf("[%02x]", *((INT08U*)p->payload + i));
	}
	printf("\r\n");
	*/
#endif
	++s_MassageIndex;

	memcpy((INT08U*)&pCom, (INT08U*)p->payload, sizeof(INT08U) * p->len);
	rxSt = checkUdpServerDataFrame(&pCom);

	if (rxSt)
	{
#if DEBUG_DSP_UDP_MSG
		printf("[UDP_DSP] RxIdx : %ld, Error Frame : %d\r\n", s_MassageIndex, rxSt);
#endif
	}
	else
	{
#if DEBUG_DSP_UDP_MSG
		printf("[UDP_DSP] RxIdx : %ld, Receive Frame : %d\r\n", s_MassageIndex, rxSt);
#endif
		rxDataAnalysis(rsDSP_UDP_Port, (TMLComSTR*)&pCom.Header);

		m_pgmEnv.DSP_Connect = 1;
		m_pgmEnv.DSP_ConnectTimer = m_pgmEnv.timer1ms;
	}

	/* Free the p buffer */
	pbuf_free(p);
}

/**
  * @brief  Send udp data
  * @param  None
  * @retval None
  */
void udp_SendBuf()
{
	struct pbuf* p;
	ip_addr_t* addr;
	u16_t port = 0;
	err_t err;
	INT08U i, nConnectFlag = 0;

	addr = &m_Recv_IPAddr;
	port = m_RecvRemotePort;

	p = pbuf_alloc(PBUF_TRANSPORT, m_pgmEnv.txEthUdpComLen, PBUF_RAM);
	p->payload = m_pgmEnv.txEthUdpComBuffer;

	/* Connect to the remote client */
	for (i = 0; i < 5; i++)
	{
		err = ERR_OK;
		err = udp_connect(&m_upcb_Uplink, addr, port);
		if (err != ERR_OK)
		{
#if DEBUG_UPLINK_MSG
			printf("[UDP] udp_connect error : %d, retry:%d\r\n", err, i);
#endif
		}
		else
		{
			nConnectFlag = 1;
			break;
		}
	}

	if (nConnectFlag)
	{
#if DEBUG_UPLINK_MSG
		printf("[UDP] Send udp data nConnectFlag:%d, retry:%d\r\n", nConnectFlag, i);
#endif
		/* Tell the client that we have accepted it */
		udp_send(&m_upcb_Uplink, p);

		/* free the UDP connection, so we can accept new clients */
		udp_disconnect(&m_upcb_Uplink);
	}

	pbuf_free(p);

	//asm volatile("NOP");
}

/**
  * @brief  Send udp data
  * @param  None
  * @retval None
  */
void udp_SendBuf_DSP(INT32U* IPaddr, INT16U RemotePort)
{
	struct pbuf* p;
	ip_addr_t* addr;
	u16_t port = 0;
	err_t err;
	INT08U i, nConnectFlag = 0;

	addr = (ip_addr_t*)IPaddr;
	port = RemotePort;

	p = pbuf_alloc(PBUF_TRANSPORT, m_pgmEnv.txDSPComLen, PBUF_RAM);
	p->payload = m_pgmEnv.txDSPComBuffer;

	/* Connect to the remote client */
	for (i = 0; i < 5; i++)
	{
		err = ERR_OK;
		err = udp_connect(&m_upcb_Dsplink, addr, port);
		if (err != ERR_OK)
		{
#if DEBUG_DSP_UDP_MSG
			printf("[UDP_DSP] udp_connect error : %d, retry:%d\r\n", err, i);
#endif
		}
		else
		{
			nConnectFlag = 1;
			break;
		}
	}

	if (nConnectFlag)
	{
#if DEBUG_DSP_UDP_MSG
		printf("[UDP_DSP] Send udp data nConnectFlag:%d, retry:%d\r\n", nConnectFlag, i);
#endif
		/* Tell the client that we have accepted it */
		udp_send(&m_upcb_Dsplink, p);

		/* free the UDP connection, so we can accept new clients */
		udp_disconnect(&m_upcb_Dsplink);
	}

	pbuf_free(p);

	//asm volatile("NOP");
}

/**
  * @brief  PCB 완전 해제 (에러/재연결 시 공통 사용)
  * @param  None
  * @retval None
  */
static void tcp_client_close(void)
{
    if (m_pTcpPcb != NULL)
    {
        /* 콜백 모두 NULL 처리 후 abort (에러 콜백 중복 방지) */
        tcp_arg(m_pTcpPcb, NULL);
        tcp_recv(m_pTcpPcb, NULL);
        tcp_sent(m_pTcpPcb, NULL);
        tcp_err(m_pTcpPcb, NULL);
        tcp_poll(m_pTcpPcb, NULL, 0);
        tcp_abort(m_pTcpPcb);
        m_pTcpPcb = NULL;
    }
}

/* Callback functions --------------------------------------------------------*/

/**
  * @brief  TCP 연결 완료 콜백
  */
static err_t tcp_cb_connected(void* arg, struct tcp_pcb* pcb, err_t err)
{
    if (err != ERR_OK)
    {
#if DEBUG_TCP_MSG
        printf("[TCP] Connect failed, err : %d\r\n", err);
#endif
        m_TcpState = TCP_CLI_STATE_ERROR;
        return err;
    }

    m_TcpState = TCP_CLI_STATE_CONNECTED;
    m_pgmEnv.TCPConnect = 1;
    m_pgmEnv.TCPConnectTimer = m_pgmEnv.timer1ms;

#if DEBUG_TCP_MSG
    printf("[TCP] Connected to server %d.%d.%d.%d:%d\r\n",
        TCP_SERVER_IP0, TCP_SERVER_IP1,
        TCP_SERVER_IP2, TCP_SERVER_IP3,
        TCP_MODBUS_PORT);
#endif

    return ERR_OK;
}

/**
  * @brief  TCP 데이터 수신 콜백
  *
  *  [처리 흐름]
  *   pbuf 수신 → 조립 버퍼 누적 → MBAP Length 기준 프레임 완성 확인
  *   → RxModbusTcpData_Uplink() 호출 (기존 함수 그대로 재사용)
  *
  *  [단편화 대응]
  *   TCP 스트림 특성상 1프레임이 여러 콜백으로 나뉘어 올 수 있음
  *   → m_TcpRxAssemBuf 에 누적 후 완성된 프레임만 전달
  *
  *  p == NULL : 서버 측 연결 종료 (FIN)
  */
static err_t tcp_cb_recv(void* arg, struct tcp_pcb* pcb,
    struct pbuf* p, err_t err)
{
    static INT08U  s_AssemBuf[TCP_RX_BUF_SIZE];  /* 프레임 조립 버퍼      */
    static INT16U  s_AssemLen = 0;               /* 현재 누적 바이트 수   */
    static INT32U  s_RecvMsgIndex = 0;

    /* ── 서버 연결 종료 (FIN) ─────────────────────────────── */
    if (p == NULL)
    {
#if DEBUG_TCP_MSG
        printf("[TCP] Server closed connection\r\n");
#endif
        s_AssemLen = 0;   /* 조립 버퍼 리셋 */
        m_TcpState = TCP_CLI_STATE_DISCONNECTED;
        return ERR_OK;
    }

    if (err != ERR_OK)
    {
        pbuf_free(p);
        return err;
    }

    /* ── pbuf 체인 전체를 조립 버퍼에 누적 ───────────────── */
    struct pbuf* q = p;
    while (q != NULL)
    {
        if ((s_AssemLen + q->len) > sizeof(s_AssemBuf))
        {
            /* 버퍼 오버플로우 → 조립 버퍼 리셋 */
#if DEBUG_TCP_MSG
            printf("[TCP] AssemBuf overflow, reset. (assem:%d + new:%d)\r\n",
                s_AssemLen, q->len);
#endif
            s_AssemLen = 0;
            break;
        }
        memcpy(s_AssemBuf + s_AssemLen, q->payload, q->len);
        s_AssemLen += (INT16U)q->len;
        q = q->next;
    }

    /* ★ 수신 윈도우 갱신 - 반드시 호출 */
    tcp_recved(pcb, p->tot_len);
    pbuf_free(p);

    /* ── 조립 버퍼에서 완성된 ModbusTCP 프레임 반복 추출 ─── */
    while (s_AssemLen >= 6)   /* MBAP 최소 6바이트(TransID+ProtoID+LenField) */
    {
        /* MBAP Length 필드 (offset 4~5, Big-Endian)
         * Length = UnitID(1) + FunctionCode(1) + Data(N)
         * 전체 프레임 크기 = 6 + Length                    */
        INT16U mbap_length = ((INT16U)s_AssemBuf[4] << 8) | s_AssemBuf[5];
        INT16U frame_total = 6 + mbap_length;

        /* 프레임 크기 유효성 검사 */
        if (mbap_length < 2 || frame_total > sizeof(s_AssemBuf))
        {
#if DEBUG_TCP_MSG
            printf("[TCP] Invalid MBAP Length:%d, reset AssemBuf\r\n", mbap_length);
#endif
            s_AssemLen = 0;
            break;
        }

        /* 전체 프레임이 아직 덜 도착 → 다음 콜백 대기 */
        if (s_AssemLen < frame_total)
        {
#if DEBUG_TCP_MSG
            printf("[TCP] Partial frame: assem:%d / need:%d\r\n",
                s_AssemLen, frame_total);
#endif
            break;
        }

        /* ── 프레임 1개 완성 → 기존 수신 처리 함수 직접 호출 ── */
        ++s_RecvMsgIndex;

#if DEBUG_TCP_MSG
        printf("[TCP] Frame complete MsgIdx:%ld, frame_total:%d\r\n",
            s_RecvMsgIndex, frame_total);
#endif

        /* 기존 RxModbusTcpData_Uplink() 그대로 재사용 */
        RxModbusTcpData(1, s_AssemBuf, frame_total);

        /* ── 처리된 프레임 제거, 남은 데이터 앞으로 이동 ── */
        INT16U remain = s_AssemLen - frame_total;
        if (remain > 0)
        {
            memmove(s_AssemBuf, s_AssemBuf + frame_total, remain);
        }
        s_AssemLen = remain;
    }

    m_pgmEnv.TCPConnect = 1;
    m_pgmEnv.TCPConnectTimer = m_pgmEnv.timer1ms;

    return ERR_OK;
}

/**
  * @brief  TCP 전송 완료 콜백 (ACK 수신)
  */
static err_t tcp_cb_sent(void* arg, struct tcp_pcb* pcb, u16_t len)
{
#if DEBUG_TCP_MSG
    printf("[TCP] Sent ACK %d bytes\r\n", len);
#endif
    return ERR_OK;
}

/**
  * @brief  TCP 에러 콜백
  *         ※ 이 콜백 진입 시 PCB는 LwIP이 이미 해제 → tcp_abort() 호출 금지
  *
  *  주요 에러 코드:
  *   ERR_RST  (-14) : 서버가 RST 전송 → Local Port TIME_WAIT 충돌 또는 서버 거부
  *   ERR_ABRT (-13) : 연결 강제 중단
  *   ERR_CONN  (-11) : 연결 실패 (서버 없음 / 방화벽)
  *   ERR_TIMEOUT(-3) : 연결 타임아웃
  */
static void tcp_cb_err(void* arg, err_t err)
{
#if DEBUG_TCP_MSG
    const char* errStr = "UNKNOWN";
    switch (err)
    {
    case -14: errStr = "ERR_RST(서버RST/포트충돌)";  break;
    case -13: errStr = "ERR_ABRT(강제중단)";          break;
    case -11: errStr = "ERR_CONN(연결실패)";          break;
    case  -3: errStr = "ERR_TIMEOUT(타임아웃)";       break;
    case  -8: errStr = "ERR_USE(포트사용중)";         break;
    default:  break;
    }
    printf("[TCP] Error callback : %d (%s)\r\n", err, errStr);
#endif

    /* PCB는 LwIP 내부에서 이미 해제됨 → NULL만 처리 */
    m_pTcpPcb = NULL;
    m_TcpState = TCP_CLI_STATE_ERROR;
    m_pgmEnv.TCPConnect = 0;
}

/**
  * @brief  TCP Poll 콜백 (주기적 keepalive / heartbeat 용)
  *         tcp_poll() 등록 시 interval(x500ms) 마다 자동 호출
  */
static err_t tcp_cb_poll(void* arg, struct tcp_pcb* pcb)
{
    /* 필요 시 heartbeat 전송 */
    /* 예: tcp_client_SendBuf((INT08U*)"HB", 2); */
    return ERR_OK;
}

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  TCP 클라이언트 초기화 - EtherNetManager() case 3 에서 1회만 호출
  *         변수 초기화만 담당, tcp_client_connect() 는 호출하지 않음
  *         연결 시작은 HMI_UpLink_ModbusTCP_Manager() case 1 에서 담당
  */
void tcp_client_init(void)
{
    m_pTcpPcb = NULL;
    m_TcpState = TCP_CLI_STATE_IDLE;
    m_pgmEnv.TCPConnect = 0;

#if DEBUG_TCP_MSG
    printf("[TCP] Client Init. Server:%d.%d.%d.%d:%d\r\n",
        TCP_SERVER_IP0, TCP_SERVER_IP1,
        TCP_SERVER_IP2, TCP_SERVER_IP3,
        TCP_MODBUS_PORT);
#endif
    /* ★ tcp_client_connect() 호출하지 않음
     *   HMI_UpLink_ModbusTCP_Manager() case 1 에서 명시적으로 호출 */
}

/**
  * @brief  TCP 클라이언트 상태머신 처리
  *         EtherNetManager() case 4: MX_LWIP_Process(); 다음에 호출
  *
  *  [연결 시작 권한]
  *   IDLE 상태에서 자동 connect 하지 않음.
  *   tcp_client_connect() 호출 권한은 호출자(HMI_UpLink_ModbusTCP_Manager 등)에게 있음.
  *   → 이중 connect / tcp_bind() ERR_USE 충돌 방지
  * @param  None
  * @retval None
  */
void tcp_client_process(void)
{
    switch (m_TcpState)
    {
    case TCP_CLI_STATE_IDLE:
        /* ★ 자동 connect 제거 - 외부에서 tcp_client_connect() 명시적 호출 */
        break;

    case TCP_CLI_STATE_CONNECTING:
        /* LwIP Raw API 콜백(tcp_cb_connected)에서 상태 전이 처리됨 */
        break;

    case TCP_CLI_STATE_CONNECTED:
        /* 연결 유지 타임아웃 감시 (옵션) */
        if (getCalcTimer1ms(m_pgmEnv.TCPConnectTimer) > 10000)
        {
            m_pgmEnv.TCPConnect = 0;
        }
        break;

    case TCP_CLI_STATE_DISCONNECTED:
    case TCP_CLI_STATE_ERROR:
        /* ★ 자동 재연결 제거 - 호출자 상태머신(case 9 → case 1)이 재연결 타이밍 관리 */
        m_pgmEnv.TCPConnect = 0;
        break;

    default:
        break;
    }
}

/**
  * @brief  TCP 데이터 전송 (udp_SendBuf 와 동일한 방식으로 사용)
  * @param  pData : 전송할 데이터 포인터
  * @param  nLen  : 전송 길이 (바이트)
  * @retval 0: 성공, 1: 실패
  */
INT08U tcp_client_SendBuf(INT08U* pData, INT16U nLen)
{
    err_t err;

    if (m_TcpState != TCP_CLI_STATE_CONNECTED || m_pTcpPcb == NULL)
    {
#if DEBUG_TCP_MSG
        printf("[TCP] SendBuf failed: not connected (state:%d)\r\n", m_TcpState);
#endif
        return 1;
    }

    /* 송신 버퍼 여유 공간 확인 */
    if (tcp_sndbuf(m_pTcpPcb) < nLen)
    {
#if DEBUG_TCP_MSG
        printf("[TCP] SendBuf failed: sndbuf %d < %d\r\n",
            tcp_sndbuf(m_pTcpPcb), nLen);
#endif
        return 1;
    }

    /* 데이터를 LwIP 내부 송신 큐에 적재 */
    err = tcp_write(m_pTcpPcb, pData, nLen, TCP_WRITE_FLAG_COPY);
    if (err != ERR_OK)
    {
#if DEBUG_TCP_MSG
        printf("[TCP] tcp_write() error : %d\r\n", err);
#endif
        m_TcpState = TCP_CLI_STATE_ERROR;
        SetTimer1ms(&m_ReconnectTimer);
        return 1;
    }

    /* ★ 폴링 모드에서는 반드시 tcp_output() 호출해야 즉시 전송됨 */
    err = tcp_output(m_pTcpPcb);
    if (err != ERR_OK)
    {
#if DEBUG_TCP_MSG
        printf("[TCP] tcp_output() error : %d\r\n", err);
#endif
        return 1;
    }

#if DEBUG_TCP_MSG
    printf("[TCP] SendBuf %d bytes\r\n", nLen);
#endif

    return 0;
}

/**
  * @brief  현재 TCP 연결 상태 반환
  * @retval TCP_CLI_STATE
  */
TCP_CLI_STATE tcp_client_GetState(void)
{
    return m_TcpState;
}

/**
  * @brief  TCP 연결 여부 반환
  * @retval 1: 연결됨, 0: 미연결
  */
INT08U tcp_client_IsConnected(void)
{
    return (m_TcpState == TCP_CLI_STATE_CONNECTED) ? 1 : 0;
}

/**
  * @brief  getFpgaTcpSocketState() 대체 함수
  *         기존 HMI_UpLink_ModbusTCP_Manager() 의 s_now_SSR 값과 1:1 매핑
  *           FPGA 0(IDLE)      → TCP_SOCKET_STATE_IDLE        (0)
  *           FPGA 1(SYN_WAIT)  → TCP_SOCKET_STATE_SYN_WAIT    (1)
  *           FPGA 2(ESTABLISH) → TCP_SOCKET_STATE_ESTABLISHED  (2)
  *           에러/끊김         → TCP_SOCKET_STATE_ERROR        (3)
  * @retval INT08U 소켓 상태값
  */
INT08U tcp_client_GetSocketState(void)
{
    switch (m_TcpState)
    {
    case TCP_CLI_STATE_IDLE:
        return TCP_SOCKET_STATE_IDLE;

    case TCP_CLI_STATE_CONNECTING:
        return TCP_SOCKET_STATE_SYN_WAIT;       /* 기존 FPGA: 1 (TCP_SYN_ACK_WAIT) */

    case TCP_CLI_STATE_CONNECTED:
        return TCP_SOCKET_STATE_ESTABLISHED;    /* 기존 FPGA: 2 (TCP_ESTABLISHED)  */

    case TCP_CLI_STATE_DISCONNECTED:
    case TCP_CLI_STATE_ERROR:
    default:
        return TCP_SOCKET_STATE_ERROR;
    }
}

/**
  * @brief  TCP 서버 연결 시도 (Public)
  *         HMI_UpLink_ModbusTCP_Manager() case 1 에서 명시적으로 호출
  *         com_tcp.h 의 TCP_SERVER_IP*, TCP_MODBUS_PORT 고정값 사용
  * @param  None
  * @retval None
  */
void tcp_client_connect(void)
{
    err_t err;

    tcp_client_close();  /* 기존 PCB 정리 */

    m_pTcpPcb = tcp_new_ip_type(IPADDR_TYPE_V4);
    if (m_pTcpPcb == NULL)
    {
#if DEBUG_TCP_MSG
        printf("[TCP] tcp_new() failed\r\n");
#endif
        m_TcpState = TCP_CLI_STATE_ERROR;
        return;
    }

    tcp_arg(m_pTcpPcb, NULL);
    tcp_recv(m_pTcpPcb, tcp_cb_recv);
    tcp_sent(m_pTcpPcb, tcp_cb_sent);
    tcp_err(m_pTcpPcb, tcp_cb_err);
    tcp_poll(m_pTcpPcb, tcp_cb_poll, 8);  /* 8 x 500ms = 4s */

    /* Local Port 0: 자동할당
     * - NO_SYS=1 환경에서 고정 포트 재사용 시 TIME_WAIT PCB 충돌 발생
     * - ModbusTCP 클라이언트는 Local Port 고정 불필요 (Remote 502만 고정) */
    err = tcp_bind(m_pTcpPcb, IP4_ADDR_ANY, 0);
    if (err != ERR_OK)
    {
#if DEBUG_TCP_MSG
        printf("[TCP] tcp_bind() error:%d\r\n", err);
#endif
        tcp_client_close();
        m_TcpState = TCP_CLI_STATE_ERROR;
        return;
    }

    IP4_ADDR(&m_ServerIp,
        TCP_SERVER_IP0, TCP_SERVER_IP1,
        TCP_SERVER_IP2, TCP_SERVER_IP3);

    /* Remote Port 502 (ModbusTCP 서버 표준 포트) */
    err = tcp_connect(m_pTcpPcb, &m_ServerIp,
        TCP_MODBUS_PORT, tcp_cb_connected);
    if (err != ERR_OK)
    {
#if DEBUG_TCP_MSG
        printf("[TCP] tcp_connect() error:%d\r\n", err);
#endif
        tcp_client_close();
        m_TcpState = TCP_CLI_STATE_ERROR;
        return;
    }

    m_TcpState = TCP_CLI_STATE_CONNECTING;

#if DEBUG_TCP_MSG
    printf("[TCP] Connecting local:auto -> %d.%d.%d.%d:%d\r\n",
        TCP_SERVER_IP0, TCP_SERVER_IP1,
        TCP_SERVER_IP2, TCP_SERVER_IP3,
        TCP_MODBUS_PORT);
#endif
}

/**
  * @brief  Connector LAN1 - Ethernet Process
  * @param  None
  * @retval None
  */
void EtherNetManager(void)
{
	static INT08U s_Step;
	static INT32U s_StepTimer;
	static INT32U s_LinkTimer;

	if (getCalcTimer1ms(s_LinkTimer) > 10)
	{
		HAL_GPIO_ReadPin(ETH_LINK_IN_GPIO_Port, ETH_LINK_IN_Pin) ? \
			(m_pgmEnv.UPLink = 0) : (m_pgmEnv.UPLink = 1);

		SetTimer1ms(&s_LinkTimer);
	}

	switch (s_Step)
	{
	case 0:		
		/* DP83838 power enable */
		HAL_GPIO_WritePin(ETH_PWR_DOWN_GPIO_Port, ETH_PWR_DOWN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ETH_RESET_GPIO_Port, ETH_RESET_Pin, GPIO_PIN_RESET);

		SetTimer1ms(&s_StepTimer);
		s_Step = 1;
		break;

	case 1:
		if (getCalcTimer1ms(s_StepTimer) > 2)
		{
			/* DP83838 reset disable */
			HAL_GPIO_WritePin(ETH_RESET_GPIO_Port, ETH_RESET_Pin, GPIO_PIN_SET);

			SetTimer1ms(&s_StepTimer);
			s_Step = 2;
		}
		break;

	case 2:
		if (getCalcTimer1ms(s_StepTimer) > 10)
		{
			s_Step = 3;
		}
		break;

	case 3:
		if (getCalcTimer1ms(s_StepTimer) > 10)
		{
			if (m_pgmEnv.UPLink)
			{
#if DEBUG_MSG
				printf("[DEBUG_APP] Connect EtherNET LAN1. UDP Socket Init.\r\n");
#endif	
				MX_LWIP_Init();
				udp_com_init();
				tcp_client_init();

				m_pgmEnv.UPLinkInitFlag = 1;

				SetTimer1ms(&s_StepTimer);
				s_Step = 4;
			}
		}
		break;

	case 4:
		MX_LWIP_Process();
		tcp_client_process();

		if (getCalcTimer1ms(m_pgmEnv.UDPConnectTimer) > 1000)
		{
			m_pgmEnv.UDPConnect = 0;
		}
		break;

	default:
		break;
	}
}

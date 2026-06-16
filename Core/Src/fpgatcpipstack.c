
#include "tcpipstack.h"

#include "type.h"
#include "User_Define.h"
#include "Alarm.h"
#include "fpga.h"
#include "com_tml.h"
#include "com_udp.h"
#include "dev_SRM.h"

static void ip_send(void);

void send_tcp_ack(INT08U s);

#define MAX_UDP_SOCKET_COUNT       4
#define MAX_TCP_SOCKET_COUNT       4

static EthSendQueueSTR  EthSendQ[MAX_ETH_SEND_QUEUE];
static INT16U           EthSendQCnt = 0;

//static udpip_connSTR *udpip_conn;
static udpip_connSTR udpip_conns[MAX_UDP_SOCKET_COUNT];
static tcpip_connSTR tcpip_conns[MAX_TCP_SOCKET_COUNT];

static arp_entrySTR   arp_table[ARP_TBL_SIZE];

static INT08U  EthData[MAX_ETH_DATA_SIZE];
static INT16S  EthLen;
static INT16U  EthHdrLen = MAC_ETH_HDR_LEN;

static INT16U ipid;

volatile static INT08U* ip_appdata;    // The uip_appdata pointer points to application data.
//volatile static INT08U* ip_sappdata;   // The uip_appdata pointer points to the application data which is to be sent.
volatile static INT08U ip_flags;
volatile static INT16U ip_slen;

static INT32U  HostIPAddr;
static INT32U  GatewayIPAddr;
static INT32U  SubnetMask;
static INT08U  HostMacAddr[6];

/*
volatile eth_hdrSTR     *ETHBUF;
volatile arp_hdrSTR     *ARPBUF;
volatile ip_hdrSTR      *IPBUF;
volatile tcpip_hdrSTR   *TCPBUF;
volatile icmpip_hdrSTR  *ICMPBUF;
volatile udpip_hdrSTR   *UDPBUF;
*/
static eth_hdrSTR* ETHBUF;
static arp_hdrSTR* ARPBUF;
static ip_hdrSTR* IPBUF;
static tcpip_hdrSTR* TCPBUF;
static icmpip_hdrSTR* ICMPBUF;
static udpip_hdrSTR* UDPBUF;

static void setEthernetBuffer(void)
{
	EthHdrLen = MAC_ETH_HDR_LEN;

	ETHBUF = ((eth_hdrSTR*)&EthData[0]);
	ARPBUF = ((arp_hdrSTR*)&EthData[0]);
	IPBUF = ((ip_hdrSTR*)&EthData[EthHdrLen]);
	TCPBUF = ((tcpip_hdrSTR*)&EthData[EthHdrLen]);
	ICMPBUF = ((icmpip_hdrSTR*)&EthData[EthHdrLen]);
	UDPBUF = ((udpip_hdrSTR*)&EthData[EthHdrLen]);
}

static void setStackHostIPAddr(INT08U* val)
{
	memcpy((INT08U*)&HostIPAddr, (INT08U*)val, 4);
}

static void setStackGatewayIPAddr(INT08U* val)
{
	memcpy((INT08U*)&GatewayIPAddr, (INT08U*)val, 4);
}

static void setStackSubnetMask(INT08U* val)
{
	memcpy((INT08U*)&SubnetMask, (INT08U*)val, 4);
}

static void setStackHostMacAddr(INT08U* val)
{
	memcpy((INT08U*)HostMacAddr, (INT08U*)val, 6);
}

static void open_udp_socket(INT08U s, INT32U ipaddr, INT16U lport, INT16U rport, INT08U chkipaddr, INT08U chkrport)
{
	if (s < MAX_UDP_SOCKET_COUNT)
	{
		udpip_conns[s].IPAddr = ipaddr;
		udpip_conns[s].LocalPort = HTONS(lport);
		udpip_conns[s].RemotePort = HTONS(rport);
		udpip_conns[s].chkIPAddr = chkipaddr;
		udpip_conns[s].chkRemotePort = chkrport;
	}
}

static void initTcpipSocket(void)
{
	EthSendQCnt = 0;
	memset((INT08U*)&EthSendQ, 0x00, sizeof(EthSendQueueSTR) * MAX_ETH_SEND_QUEUE);

	open_udp_socket(0, 0, 9000, 0, 0, 0);             // socket, ipaddr, localport, remoteport, chkipaddr, chkremoteport
	open_udp_socket(1, 0, 9001, 0, 0, 0);             // socket, ipaddr, localport, remoteport, chkipaddr, chkremoteport
	open_udp_socket(2, 0, UPLINK_UDP_SERVER_PORT, 0, 0, 0);             // socket, ipaddr, localport, remoteport, chkipaddr, chkremoteport
}

/////////////////////////////////////////////////////////////////////////////////////////////

static void arp_init(void)
{
	INT16U i;

	for (i = 0; i < ARP_TBL_SIZE; i++)
	{
		arp_table[i].IPAddr = 0;
	}
}

static void arp_timer(void)
{
	INT16U i;

	for (i = 0; i < ARP_TBL_SIZE; i++)
	{
		if (arp_table[i].IPAddr && (getCalcTimer1ms(arp_table[i].Time) >= ARP_MAX_AGE))
		{
			arp_table[i].IPAddr = 0;
		}
	}
}

static void arp_update(INT32U IPAddr, INT08U* MacAddr)
{
	INT32U maxTime = 0, time;
	INT16U i, pos = 0;

	for (i = 0; i < ARP_TBL_SIZE; i++)
	{
		if (arp_table[i].IPAddr == IPAddr)
		{
			arp_table[i].Time = m_pgmEnv.timer1ms;
			memcpy(arp_table[i].MacAddr, MacAddr, 6);
			return;
		}
	}

	for (i = 0; i < ARP_TBL_SIZE; i++)
	{
		if (arp_table[i].IPAddr == 0)  break;
	}

	if (i == ARP_TBL_SIZE)
	{
		for (i = 0; i < ARP_TBL_SIZE; i++)
		{
			time = getCalcTimer1ms(arp_table[i].Time);
			if (time > maxTime)
			{
				maxTime = time;
				pos = i;
			}
		}
		i = pos;
	}

	arp_table[i].IPAddr = IPAddr;
	arp_table[i].Time = m_pgmEnv.timer1ms;
	memcpy(arp_table[i].MacAddr, MacAddr, 6);
}

static void arp_ipin(void)
{
	//  if( (IPBUF->SrcIPAddr & SubnetMask) == (HostIPAddr & SubnetMask) ) 
	{
		arp_update(IPBUF->SrcIPAddr, (INT08U*)ETHBUF->SrcMacAddr);
	}
}

static void arp_arpin(void)
{
	if (EthLen < sizeof(arp_hdrSTR))
	{
		EthLen = 0;
		return;
	}

	EthLen = 0;

	switch (ARPBUF->OpCode)
	{
	case HTONS(ARP_REQUEST):
		if (ARPBUF->TargetIPAddr == HostIPAddr)
		{
			arp_update(ARPBUF->SenderIPAddr, (INT08U*)ARPBUF->EthHdr.SrcMacAddr);

			ARPBUF->OpCode = HTONS(ARP_REPLY);

			memcpy((INT08U*)ARPBUF->EthHdr.DstMacAddr, (INT08U*)ARPBUF->EthHdr.SrcMacAddr, 6);
			memcpy((INT08U*)ARPBUF->EthHdr.SrcMacAddr, (INT08U*)HostMacAddr, 6);
			memcpy((INT08U*)ARPBUF->SenderMacAddr, (INT08U*)HostMacAddr, 6);
			memcpy((INT08U*)ARPBUF->TargetMacAddr, (INT08U*)ARPBUF->EthHdr.DstMacAddr, 6);

			ARPBUF->TargetIPAddr = ARPBUF->SenderIPAddr;
			ARPBUF->SenderIPAddr = HostIPAddr;

			ARPBUF->EthHdr.EthType = HTONS(ETHTYPE_ARP);
			EthLen = sizeof(arp_hdrSTR);
		}
		break;
	case HTONS(ARP_REPLY):
		if (ARPBUF->TargetIPAddr == HostIPAddr)
		{
			arp_update(ARPBUF->SenderIPAddr, (INT08U*)ARPBUF->SenderMacAddr);
		}
		break;
	}
}

static void makeArpPacket(INT32U dstIpAddr)
{
	memset((INT08U*)ARPBUF->EthHdr.DstMacAddr, 0xFF, 6);
	memset((INT08U*)ARPBUF->TargetMacAddr, 0x00, 6);
	memcpy((INT08U*)ARPBUF->EthHdr.SrcMacAddr, (INT08U*)HostMacAddr, 6);
	memcpy((INT08U*)ARPBUF->SenderMacAddr, (INT08U*)HostMacAddr, 6);

	ARPBUF->TargetIPAddr = dstIpAddr;
	ARPBUF->SenderIPAddr = HostIPAddr;
	ARPBUF->OpCode = HTONS(ARP_REQUEST);
	ARPBUF->HwType = HTONS(ARP_HWTYPE_ETH);
	ARPBUF->Protocol = HTONS(ETHTYPE_IP);
	ARPBUF->HwLen = 6;
	ARPBUF->ProtocoLen = 4;
	ARPBUF->EthHdr.EthType = HTONS(ETHTYPE_ARP);
}

static void arp_out(void)
{
	INT32U ipaddr;
	INT16U i;
	INT16U j;

	if (HostIPAddr == GatewayIPAddr)                                     ipaddr = IPBUF->DstIPAddr;
	else if ((IPBUF->DstIPAddr & SubnetMask) != (HostIPAddr & SubnetMask))   ipaddr = GatewayIPAddr;
	else                                                                  ipaddr = IPBUF->DstIPAddr;

	if ((IPBUF->DstIPAddr & 0xFF000000) == 0xFF000000)
	{
		memset((INT08U*)ETHBUF->DstMacAddr, 0xFF, 6);
		memcpy((INT08U*)ETHBUF->SrcMacAddr, (INT08U*)HostMacAddr, 6);
		ETHBUF->EthType = HTONS(ETHTYPE_IP);

		EthLen += sizeof(eth_hdrSTR);
	}
	else
	{
		for (i = 0; i < ARP_TBL_SIZE; i++)
		{
			if (ipaddr == arp_table[i].IPAddr)  break;
		}

		if (i == ARP_TBL_SIZE)
		{
			for (j = 0; j < MAX_ETH_SEND_QUEUE; j++)
			{
				if (EthSendQ[j].Len == 0)
				{
					memcpy((INT08U*)&EthSendQ[j].Data[0], (INT08U*)&EthData, EthLen);
					EthSendQ[j].IPAddr = IPBUF->DstIPAddr;
					EthSendQ[j].Timer = m_pgmEnv.timer1ms;
					EthSendQ[j].Len = EthLen;
					EthSendQCnt++;
					break;
				}
			}

			makeArpPacket(ipaddr);
			EthLen = sizeof(arp_hdrSTR);
		}
		else
		{
			memcpy((INT08U*)ETHBUF->DstMacAddr, (INT08U*)arp_table[i].MacAddr, 6);
			memcpy((INT08U*)ETHBUF->SrcMacAddr, (INT08U*)HostMacAddr, 6);
			ETHBUF->EthType = HTONS(ETHTYPE_IP);

			EthLen += sizeof(eth_hdrSTR);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////

static INT16U ip_sum_calc(INT08U* buff, INT16U len)
{
	INT16U word16;
	INT32U sum = 0;
	INT16U i;

	for (i = 0; i < len; i += 2)
	{
		word16 = (((INT16U)buff[i] << 8) & 0xFF00) + ((INT16U)buff[i + 1] & 0xFF);
		sum += (INT32U)word16;
	}

	while (sum >> 16)  sum = (sum & 0xFFFF) + (sum >> 16);
	sum = ~sum;                                        // one's complement the result

	return ((INT16U)sum);
}

static INT16U tcpudpicmp_sum_calc(INT08U* buff, INT16U len)
{
	INT16U i, word16, padd = 0;
	INT32U sum = 0;

	if (len % 2)
	{
		padd = 1;
		buff[len] = 0;
	}

	for (i = 0; i < len + padd; i += 2)
	{
		word16 = (((INT16U)buff[i] << 8) & 0xFF00) + ((INT16U)buff[i + 1] & 0xFF);
		sum += (INT32U)word16;
	}

	sum += HTONS(((IPBUF->SrcIPAddr >> 16) & 0xFFFF));
	sum += HTONS(((IPBUF->SrcIPAddr) & 0xFFFF));
	sum += HTONS(((IPBUF->DstIPAddr >> 16) & 0xFFFF));
	sum += HTONS(((IPBUF->DstIPAddr) & 0xFFFF));
	sum += IPBUF->Protocol;
	sum += len;

	while (sum >> 16)  sum = (sum & 0xFFFF) + (sum >> 16);
	sum = ~sum;   // one's complement the result

	return ((INT16U)sum);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ICMP_ECHO_REQUEST    8
#define ICMP_ECHO_REPLY      0

//static INT16U icmp_cnt=0;

static void icmp_process(void)
{
	INT32U ipaddr;

	if (ICMPBUF->Type != ICMP_ECHO_REQUEST)
	{
		EthLen = 0;
		return;
	}

	ICMPBUF->Type = ICMP_ECHO_REPLY;
	//  ICMPBUF->IcmpCheckSum = 0;
	if (ICMPBUF->IcmpCheckSum >= HTONS(0xFFFF - (ICMP_ECHO_REQUEST << 8)))   ICMPBUF->IcmpCheckSum += HTONS(ICMP_ECHO_REQUEST << 8) + 1;
	else                                                                   ICMPBUF->IcmpCheckSum += HTONS(ICMP_ECHO_REQUEST << 8);
	ipaddr = ICMPBUF->SrcIPAddr;
	ICMPBUF->SrcIPAddr = ICMPBUF->DstIPAddr;
	ICMPBUF->DstIPAddr = ipaddr;
}

#define TCP_IDLE           0
#define TCP_SYN_ACK_WAIT   1
#define TCP_ESTABLISHED    2
#define TCP_FIN_ACK_WAIT   3

static void tcp_process(void)
{
	INT16U len;
	INT16U hdrlen;

	INT08U i = 0;

	for (i = 0; i < 2; i++)
	{
		if (tcpip_conns[i].appstate != 0)
		{
			if (tcpip_conns[i].IPAddr == TCPBUF->SrcIPAddr)
			{
				if ((tcpip_conns[i].RemotePort == HTONS(TCPBUF->SrcPort)) && (tcpip_conns[i].LocalPort == HTONS(TCPBUF->DstPort)))
				{
					if (TCPBUF->Code == 0x04)  // RST
					{
						tcpip_conns[i].appstate = TCP_IDLE;
					}
					else if (TCPBUF->Code == 0x14)  // RST+ACK
					{
						tcpip_conns[i].appstate = TCP_IDLE;
					}
					else if (TCPBUF->Code == 0x12) // SYN+ACK
					{
						if (tcpip_conns[i].appstate == TCP_SYN_ACK_WAIT)
						{
							tcpip_conns[i].appstate = TCP_ESTABLISHED;
							tcpip_conns[i].RcvSeqNum = HTONL(TCPBUF->SeqNum) + 1;
							tcpip_conns[i].SndSeqNum = HTONL(TCPBUF->AckNum);
							send_tcp_ack(i);
						}
						else
						{
							tcpip_conns[i].appstate = TCP_IDLE;
						}
					}
					else if (TCPBUF->Code == 0x10) // ACK
					{
						if (tcpip_conns[i].appstate == TCP_ESTABLISHED)
						{
							tcpip_conns[i].RcvSeqNum = HTONL(TCPBUF->SeqNum);
							tcpip_conns[i].SndSeqNum = HTONL(TCPBUF->AckNum);
						}
						else if (tcpip_conns[i].appstate == TCP_SYN_ACK_WAIT)
						{
							tcpip_conns[i].appstate = TCP_ESTABLISHED;
							tcpip_conns[i].RcvSeqNum = HTONL(TCPBUF->SeqNum);
							tcpip_conns[i].SndSeqNum = HTONL(TCPBUF->AckNum);
						}
					}
					else if (TCPBUF->Code == 0x18) // PSH+ACK
					{
						if (tcpip_conns[i].appstate == TCP_ESTABLISHED)
						{
							hdrlen = ((TCPBUF->VHL & 0x0F) * 4) + (((TCPBUF->HdrLen >> 4) & 0x0F) * 4);
							len = HTONS(TCPBUF->IpLen) - hdrlen;

							tcpip_conns[i].RcvSeqNum = HTONL(TCPBUF->SeqNum) + len;
							tcpip_conns[i].SndSeqNum = HTONL(TCPBUF->AckNum);

							RxModbusTcpData(i, (INT08U*)&EthData[EthHdrLen + hdrlen], len);

							send_tcp_ack(i);
						}
					}
					else
					{

					}

					tcpip_conns[i].Len = 0;
				}
			}
		}
	}

	EthLen = 0;
}

static void ip_send(void)
{
	++ipid;

	IPBUF->VHL = 0x45;
	IPBUF->TOS = 0;
	IPBUF->FlagOffset = 0;
	IPBUF->TTL = 128;
	IPBUF->IpId = HTONS(ipid);

	IPBUF->CheckSum = 0;
	IPBUF->CheckSum = HTONS(ip_sum_calc((INT08U*)&IPBUF->VHL, 20));
}

static void put_tcpip_ethernet_packet(INT08U* buf, INT16S len)
{
	putFPGAEthernet((INT08U*)buf, len);
}

static INT16U get_tcpip_ethernet_packet(INT08U* buf, INT16S len)
{
	return getFPGAEthernet((INT08U*)buf, len);
}

static void FpgatransferEthData(void)
{
	if (EthLen > 0)
	{
		arp_out();
		put_tcpip_ethernet_packet((INT08U*)&EthData, EthLen);
		EthLen = 0;
	}
}

void Fpga_tcp_send(INT08U s, INT08U* data, INT16U length)
{
	INT16U chksum;

	if ((tcpip_conns[s].appstate == TCP_ESTABLISHED) && length)
	{
		EthLen = 40 + length;
		memcpy((INT08U*)&EthData[EthHdrLen + 40], (INT08U*)data, length);

		TCPBUF->IpLen = HTONS(EthLen);
		TCPBUF->Protocol = IP_PROTO_TCP;
		TCPBUF->SrcIPAddr = HostIPAddr;
		TCPBUF->DstIPAddr = tcpip_conns[s].IPAddr;

		TCPBUF->SrcPort = HTONS(tcpip_conns[s].LocalPort);
		TCPBUF->DstPort = HTONS(tcpip_conns[s].RemotePort);
		TCPBUF->SeqNum = HTONL(tcpip_conns[s].SndSeqNum);
		TCPBUF->AckNum = HTONL(tcpip_conns[s].RcvSeqNum);
		TCPBUF->HdrLen = 0x50;
		TCPBUF->Code = 0x18;
		TCPBUF->WindowSize = HTONS(8190);
		TCPBUF->TcpCheckSum = 0;
		TCPBUF->UrgPointer = 0;

		// Calculate UDP checksum. 
		chksum = tcpudpicmp_sum_calc((INT08U*)&TCPBUF->SrcPort, EthLen - 20);
		TCPBUF->TcpCheckSum = HTONS(chksum);
		if (TCPBUF->TcpCheckSum == 0)  TCPBUF->TcpCheckSum = 0xFFFF;

		ip_send();
		FpgatransferEthData();

		tcpip_conns[s].Len = length;
	}
}

void send_tcp_ack(INT08U s)
{
	INT16U chksum;

	EthLen = 40;

	TCPBUF->IpLen = HTONS(EthLen);
	TCPBUF->Protocol = IP_PROTO_TCP;
	TCPBUF->SrcIPAddr = HostIPAddr;
	TCPBUF->DstIPAddr = tcpip_conns[s].IPAddr;

	TCPBUF->SrcPort = HTONS(tcpip_conns[s].LocalPort);
	TCPBUF->DstPort = HTONS(tcpip_conns[s].RemotePort);
	TCPBUF->SeqNum = HTONL(tcpip_conns[s].SndSeqNum);
	TCPBUF->AckNum = HTONL(tcpip_conns[s].RcvSeqNum);
	TCPBUF->HdrLen = 0x50;
	TCPBUF->Code = 0x10;
	TCPBUF->WindowSize = HTONS(8190);
	TCPBUF->TcpCheckSum = 0;
	TCPBUF->UrgPointer = 0;

	// Calculate UDP checksum. 
	chksum = tcpudpicmp_sum_calc((INT08U*)&TCPBUF->SrcPort, EthLen - 20);
	TCPBUF->TcpCheckSum = HTONS(chksum);
	if (TCPBUF->TcpCheckSum == 0)  TCPBUF->TcpCheckSum = 0xFFFF;

	ip_send();
	FpgatransferEthData();
}

void Fpga_udp_send(INT32U ipAddr, INT16U rport, INT16U lport)
{
	INT16U chksum;

	if (m_pgmEnv.txInvUdpComLen == 0)
	{
		EthLen = 0;
		return;
	}

	EthLen = m_pgmEnv.txInvUdpComLen + 28;
	memcpy((INT08U*)&EthData[EthHdrLen + 28], (INT08U*)&m_pgmEnv.txInvUdpComBuffer[0], m_pgmEnv.txInvUdpComLen);

	UDPBUF->IpLen = HTONS(EthLen);
	UDPBUF->Protocol = IP_PROTO_UDP;

	UDPBUF->UdpLen = HTONS(m_pgmEnv.txInvUdpComLen + 8);
	UDPBUF->UdpCheckSum = 0;
	//  UDPBUF->UdpCheckSum = HTONS(0);

	UDPBUF->SrcPort = HTONS(lport);
	UDPBUF->DstPort = HTONS(rport);
	UDPBUF->SrcIPAddr = HostIPAddr;
	UDPBUF->DstIPAddr = ipAddr;

	// Calculate UDP checksum. 
	chksum = tcpudpicmp_sum_calc((INT08U*)&UDPBUF->SrcPort, EthLen - 20);
	UDPBUF->UdpCheckSum = HTONS(chksum);
	if (UDPBUF->UdpCheckSum == 0)  UDPBUF->UdpCheckSum = 0xFFFF;

	ip_send();
	FpgatransferEthData();

	m_pgmEnv.txInvUdpComLen = 0;
}

static INT32U IPAddr = 0;
static INT16U LocalPort = 0;
static INT16U RemotePort = 0;

void sendUdpTxBuf_Downlink()
{
	if (IPAddr && RemotePort && LocalPort)
	{
		Fpga_udp_send(IPAddr, RemotePort, LocalPort);
	}
	m_pgmEnv.txInvUdpComLen = 0;
}
/*
void save_setup_func_ip_port(void)
{
	m_pgmEnv.SetupFuncDstIP = IPAddr;
	m_pgmEnv.SetupFuncDstPort = RemotePort;
}
*/

static INT32U linkTimer = 0;

static INT32U ServerIpAddr = 0;  // 0x0464A8C0;
static INT16U ServerPort = 0;  // 10000;
//static INT16U DevicePort = 9000;

INT08U AnalysisUDP(INT08U* data, INT16U len, INT32U ipAddr, INT16U lport, INT16U rport)
{
	INT08U      ret = 0, rxSt = 0;
	UDPComSTR* pCom;

	switch (lport)
	{
	case UPLINK_UDP_SERVER_PORT:
		pCom = (UDPComSTR*)data;
		rxSt = checkUdpServerDataFrame(pCom);

		//m_TestStatus.Ctrl[DEBUG_CTR_10] = rxSt;
		if (rxSt)  
		{
			// Error
			asm volatile("NOP");
		}
		else
		{
			IPAddr = ipAddr;
			LocalPort = lport;
			RemotePort = rport;

			if (pCom->Header.SrcID.Type == COM_ID_GCP)
			{
				ServerIpAddr = ipAddr;
				ServerPort = rport;
			}

			rxDataAnalysis(rsETHUDPPort_DwLink, (TMLComSTR*)&pCom->Header);
		}

		linkTimer = m_pgmEnv.timer1ms;
		ret = 0;
		break;

	default:
		break;
	}

	return ret;
}

static void udp_process(void)
{
	INT16U i;
	//INT16U chksum;

	//  chksum = tcpudpicmp_sum_calc( (INT08U *)&UDPBUF->SrcPort, EthLen-20 );
	//  if( chksum == 0x0000 )
	{
		for (i = 0; i < MAX_UDP_SOCKET_COUNT; i++)
		{
			if ((udpip_conns[i].chkIPAddr == 0) || (UDPBUF->SrcIPAddr == udpip_conns[i].IPAddr))
			{
				if ((udpip_conns[i].chkRemotePort == 0) || (UDPBUF->SrcPort == udpip_conns[i].RemotePort))
				{
					if ((udpip_conns[i].LocalPort != 0) && (UDPBUF->DstPort == udpip_conns[i].LocalPort))
					{
						EthLen -= 28;
						ip_appdata = &EthData[EthHdrLen + 28];
						ip_flags = IP_NEWDATA;
						ip_slen = 0;

						AnalysisUDP((INT08U*)&EthData[EthHdrLen + 28], EthLen, UDPBUF->SrcIPAddr, HTONS(UDPBUF->DstPort), HTONS(UDPBUF->SrcPort));
						break;
					}
				}
			}
		}
	}

	EthLen = 0;
}

static void ip_process(void)
{
	EthLen = 0;

	if ((IPBUF->DstIPAddr != HostIPAddr) && (IPBUF->DstIPAddr != 0xFFFFFFFF))
	{
		return;
	}

	if (IPBUF->VHL != 0x45)                                                      return;
	//  if( IPBUF->FlagOffset & 0x3FFF )                                             return;
	//  if( ip_sum_calc( (INT08U *)&IPBUF->VHL, 20 ) != 0x0000 )                     return;

	EthLen = HTONS(IPBUF->IpLen);

	switch (IPBUF->Protocol)
	{
	case IP_PROTO_ICMP: icmp_process();   break;
	case IP_PROTO_TCP: tcp_process();    break;
	case IP_PROTO_UDP: udp_process();    break;
	default: EthLen = 0;         break;
	}
}

/////////////////////////////////////////////////////////////////////
/*
static void checkGatewayMAC(void)
{
	INT16U i, isReqGateMAC = 1;

	if (HostIPAddr != GatewayIPAddr)
	{
		for (i = 0; i < ARP_TBL_SIZE; i++)
		{
			if (arp_table[i].IPAddr == GatewayIPAddr)
			{
				if (getCalcTimer1ms(arp_table[i].Time) > 6000)  isReqGateMAC = 0;
				break;
			}
		}

		if (isReqGateMAC)
		{
			makeArpPacket(GatewayIPAddr);
			put_tcpip_ethernet_packet((INT08U*)&EthData, sizeof(arp_hdrSTR));
		}
	}
}
*/

////////////////////////////////////////////////////////////////////


INT08U getFpgaTcpSocketState(INT08U s)
{
	return tcpip_conns[s].appstate;
}

INT08U getFpgaTcpSocketState_1(INT08U s)
{
	if (s < MAX_TCP_SOCKET_COUNT)
	{
		return tcpip_conns[s].appstate;
	}
	else
	{
		return 0;
	}
}

void send_tcp_connect_request(INT08U s)
{
	INT16U chksum;

	EthLen = 40;  // 44

	TCPBUF->IpLen = HTONS(EthLen);
	TCPBUF->Protocol = IP_PROTO_TCP;
	TCPBUF->SrcIPAddr = HostIPAddr;
	TCPBUF->DstIPAddr = tcpip_conns[s].IPAddr;

	TCPBUF->SrcPort = HTONS(tcpip_conns[s].LocalPort);
	TCPBUF->DstPort = HTONS(tcpip_conns[s].RemotePort);
	TCPBUF->SeqNum = HTONL(tcpip_conns[s].SndSeqNum);
	TCPBUF->AckNum = HTONL(tcpip_conns[s].RcvSeqNum);
	TCPBUF->HdrLen = 0x50;  // 0x60
	TCPBUF->Code = 0x02;
	TCPBUF->WindowSize = HTONS(8190);
	TCPBUF->TcpCheckSum = 0;
	TCPBUF->UrgPointer = 0;
	TCPBUF->OptData[0] = 0x02;
	TCPBUF->OptData[1] = 0x04;
	TCPBUF->OptData[2] = 0x05;
	TCPBUF->OptData[3] = 0xb4;

	// Calculate UDP checksum. 
	chksum = tcpudpicmp_sum_calc((INT08U*)&TCPBUF->SrcPort, EthLen - 20);
	TCPBUF->TcpCheckSum = HTONS(chksum);
	if (TCPBUF->TcpCheckSum == 0)  TCPBUF->TcpCheckSum = 0xFFFF;

	ip_send();
	FpgatransferEthData();

	tcpip_conns[s].Len = 1;
}

void connectFpgaTcp(INT08U* remote_ip, INT16U remote_port, INT16U local_port)
{
	memset((INT08U*)&tcpip_conns[0], 0x00, sizeof(tcpip_connSTR));

	memcpy((INT08U*)&tcpip_conns[0].IPAddr, (INT08U*)remote_ip, 4);
	tcpip_conns[0].RemotePort = remote_port;
	tcpip_conns[0].LocalPort = local_port;
	tcpip_conns[0].timer = m_pgmEnv.timer1ms;
	tcpip_conns[0].nrtx = 1;
	tcpip_conns[0].appstate = TCP_SYN_ACK_WAIT;

	send_tcp_connect_request(0);
}

void connectFpgaTcp_1(INT08U nSocket, INT08U* remote_ip, INT16U remote_port, INT16U local_port)
{
	memset((INT08U*)&tcpip_conns[nSocket], 0x00, sizeof(tcpip_connSTR));

	memcpy((INT08U*)&tcpip_conns[nSocket].IPAddr, (INT08U*)remote_ip, 4);
	tcpip_conns[nSocket].RemotePort = remote_port;
	tcpip_conns[nSocket].LocalPort = local_port;
	tcpip_conns[nSocket].timer = m_pgmEnv.timer1ms;
	tcpip_conns[nSocket].nrtx = 1;
	tcpip_conns[nSocket].appstate = TCP_SYN_ACK_WAIT;

	send_tcp_connect_request(nSocket);
}

void setFpgaTcpIpStackNetworkParameter(NetworkInfo_t* net_info)   // GatewayIP. SubnetMask, MyIP
{
	setStackHostIPAddr((INT08U*)net_info->MyIP);
	setStackGatewayIPAddr((INT08U*)net_info->GatewayIP);
	setStackSubnetMask((INT08U*)net_info->SubnetMask);
}

void setFpgaTcpIpStackMyMACAddrress(INT08U* mac_addr)
{
	setStackHostMacAddr((INT08U*)mac_addr);
}

void FpgaTcpIpStackInit(void)
{
	setEthernetBuffer();
	arp_init();
	initTcpipSocket();

	/*
	setStackHostIPAddr   ( (INT08U *)m_DevStatus.NetworkInfo_1.MyIP );
	setStackGatewayIPAddr( (INT08U *)m_DevStatus.NetworkInfo_1.GatewayIP );
	setStackSubnetMask   ( (INT08U *)m_DevStatus.NetworkInfo_1.SubnetMask );
	setStackHostMacAddr  ( (INT08U *)m_DevStatus.MyMACAddr_1);
	*/
}

void FpgaTcpIpStackProcess(void)
{
	static INT32U arpTimer = 0;
	INT16U i, j;

	EthLen = get_tcpip_ethernet_packet((INT08U*)EthData, MAX_ETH_DATA_SIZE);
	if (EthLen > 0)
	{
		switch (HTONS(ETHBUF->EthType))
		{
		case ETHTYPE_ARP:
			arp_arpin();
			if (EthLen)
			{
				put_tcpip_ethernet_packet((INT08U*)&EthData, EthLen);
			}
			break;
		case ETHTYPE_IP:
			if ((IPBUF->Protocol == IP_PROTO_ICMP) || (IPBUF->Protocol == IP_PROTO_TCP) || (IPBUF->Protocol == IP_PROTO_UDP))
			{
				arp_ipin();     // add the source to the ARP cache
			}

			ip_process();
			if (EthLen > 0)
			{
				arp_out();
				put_tcpip_ethernet_packet((INT08U*)&EthData, EthLen);
			}
			break;

		default:
			break;
		}

		EthLen = 0;
	}

	if (getCalcTimer1ms(arpTimer) > 5000) // 5 Second
	{
		arp_timer();
		arpTimer = m_pgmEnv.timer1ms;

		//checkGatewayMAC();
	}

	if (EthSendQCnt)
	{
		for (i = 0; i < MAX_ETH_SEND_QUEUE; i++)
		{
			if (EthSendQ[i].Len)
			{
				if (EthSendQ[i].Len < MAX_ETH_DATA_SIZE)
				{
					if (getCalcTimer1ms(EthSendQ[i].Timer) > 2000)
					{
						EthSendQ[i].Len = 0;
						EthSendQCnt--;
					}
					else
					{
						for (j = 0; j < ARP_TBL_SIZE; j++)
						{
							if (EthSendQ[i].IPAddr == arp_table[j].IPAddr)
							{
								memcpy((INT08U*)&EthData, (INT08U*)&EthSendQ[i].Data[0], EthSendQ[i].Len);
								EthLen = EthSendQ[i].Len;

								EthSendQ[i].Len = 0;
								EthSendQCnt--;
								FpgatransferEthData();
								break;
							}
						}
					}
				}
				else
				{
					EthSendQ[i].Len = 0;
					EthSendQCnt--;
				}

				if (EthSendQCnt == 0) break;
			}
		}
	}

// 	m_TestStatus.St[DEBUG_STR_29] = tcpip_conns[0].appstate;
// 	m_TestStatus.St[DEBUG_STR_30] = tcpip_conns[1].appstate;
}

/*
 * Dev_SRM.h
 *
 *  Created on: Jul 12, 2022
 *      Author: ARTWARE
 */

#ifndef INC_TCPIPSTACK_H_
#define INC_TCPIPSTACK_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "type.h"
#include "User_Define.h"

#define HTONS(n)  ((((INT16U)((n)&0x00ff))<<8) | (((n)&0xff00)>>8))
#define HTONL(n)  ((((INT32U)((n)&0x000000ff))<<24) | (((INT32U)((n)&0x0000ff00))<<8) | (((INT32U)((n)&0x00ff0000))>>8) | (((n)&0xff000000)>>24))

struct __attribute__((__packed__)) eth_hdr_User
{
	INT08U DstMacAddr[6];
	INT08U SrcMacAddr[6];
	INT16U EthType;        // IP : 0x08 0x00    ARP : 0x08 0x06     RARP : 0x80 0x35
};
typedef struct eth_hdr_User  eth_hdrSTR;

struct __attribute__((__packed__)) arp_hdr_User
{
	eth_hdrSTR  EthHdr;

	INT16U   HwType;            // 0x00 0x01   Ethernet�� 
	INT16U   Protocol;          // 0x08 0x00   Internet��
	INT08U   HwLen;             // 0x06        Ethernet��   MAC Address ����
	INT08U   ProtocoLen;        // 0x04        Internet��   IP  Address ����
	INT16U   OpCode;            // Request : 0x00 0x01      Reply : 0x00 0x02
	INT08U   SenderMacAddr[6];
	INT32U   SenderIPAddr;
	INT08U   TargetMacAddr[6];
	INT32U   TargetIPAddr;
};
typedef struct arp_hdr_User  arp_hdrSTR;

struct __attribute__((__packed__)) ip_hdr_User
{
	// IP header
	INT08U   VHL;
	INT08U   TOS;
	INT16U   IpLen;
	INT16U   IpId;
	INT16U   FlagOffset;
	INT08U   TTL;
	INT08U   Protocol;        // 1:ICMP, 6:TCP, 17:UDP
	INT16U   CheckSum;
	INT32U   SrcIPAddr;
	INT32U   DstIPAddr;
};
typedef struct ip_hdr_User  ip_hdrSTR;

// The TCP and IP headers
struct __attribute__((__packed__)) tcpip_hdr
{
	// IP header
	INT08U   VHL;
	INT08U   TOS;
	INT16U   IpLen;
	INT16U   IpId;
	INT16U   FlagOffset;
	INT08U   TTL;
	INT08U   Protocol;        // 1:ICMP, 6:TCP, 17:UDP
	INT16U   CheckSum;  // IpCheckSum;
	INT32U   SrcIPAddr;
	INT32U   DstIPAddr;

	// TCP header
	INT16U   SrcPort;
	INT16U   DstPort;
	INT32U   SeqNum;
	INT32U   AckNum;
	INT08U   HdrLen;
	INT08U   Code;
	INT16U   WindowSize;
	INT16U   TcpCheckSum;
	INT16U   UrgPointer;
	INT08U   OptData[4];
};
typedef struct tcpip_hdr  tcpip_hdrSTR;

// The ICMP and IP headers
struct __attribute__((__packed__)) icmpip_hdr
{
	// IP header
	INT08U   VHL;
	INT08U   TOS;
	INT16U   IpLen;
	INT16U   IpId;
	INT16U   FlagOffset;
	INT08U   TTL;
	INT08U   Protocol;        // 1:ICMP, 6:TCP, 17:UDP
	INT16U   IpCheckSum;
	INT32U   SrcIPAddr;
	INT32U   DstIPAddr;

	// ICMP (echo) header
	INT08U   Type;            // Echo Request : 0x80      Echo Reply : 0x00
	INT08U   Code;            // Echo Request : 0x00      Echo Reply : 0x00
	INT16U   IcmpCheckSum;
	INT16U   Id;
	INT16U   SeqNum;
};
typedef struct icmpip_hdr  icmpip_hdrSTR;

// The UDP and IP headers
struct __attribute__((__packed__)) udpip_hdr
{
	// IP header
	INT08U   VHL;
	INT08U   TOS;
	INT16U   IpLen;
	INT16U   IpId;
	INT16U   FlagOffset;
	INT08U   TTL;
	INT08U   Protocol;        // 1:ICMP, 6:TCP, 17:UDP
	INT16U   IpCheckSum;
	INT32U   SrcIPAddr;
	INT32U   DstIPAddr;

	// UDP header
	INT16U   SrcPort;
	INT16U   DstPort;
	INT16U   UdpLen;
	INT16U   UdpCheckSum;
};
typedef struct udpip_hdr  udpip_hdrSTR;


#define IP_PROTO_ICMP     1
#define IP_PROTO_TCP      6
#define IP_PROTO_UDP     17

#define UIP_APPSTATE_SIZE 1


struct __attribute__((__packed__)) tcpip_conn
{
	INT32U IPAddr;        // The IP address of the remote host. 

	INT16U LocalPort;     // The local TCP port, in network byte order. 
	INT16U RemotePort;    // The local remote TCP port, in network byte order. 

	INT32U RcvSeqNum;     // The sequence number that we expect to receive next. 
	INT32U SndSeqNum;     // The sequence number that was last sent by us. 
	INT16U Len;           // Length of the data that was previously sent. 
	INT16U MSS;           // Current maximum segment size for the connection. 
	INT16U InitialMSS;    // Initial maximum segment size for the connection.  
	INT08U sa;            // Retransmission time-out calculation state variable. 
	INT08U sv;            // Retransmission time-out calculation state variable. 
	INT08U rto;           // Retransmission time-out. 
	INT08U tcpstateflags; // TCP state and flags. 
	INT32U timer;         // The retransmission timer. 
	INT08U nrtx;          // The number of retransmissions for the last segment sent. 

	INT08U appstate;   // The application state. 
};
typedef struct tcpip_conn  tcpip_connSTR;

struct __attribute__((__packed__)) udpip_conn
{
	INT32U IPAddr;       // The IP address of the remote peer
	INT16U LocalPort;    // The local port number in network byte order
	INT16U RemotePort;   // The remote port number in network byte order

	INT08U chkIPAddr;
	INT08U chkRemotePort;
};
typedef struct udpip_conn  udpip_connSTR;


#define ARP_TBL_SIZE        256
#define ARP_MAX_AGE      180000   // 3 Minute

struct __attribute__((__packed__)) arp_entry
{
	INT32U IPAddr;
	INT08U MacAddr[6];
	INT32U Time;
};
typedef struct arp_entry  arp_entrySTR;

#define ARP_REQUEST    1
#define ARP_REPLY      2

#define ARP_HWTYPE_ETH 1


#define ETHTYPE_ARP   0x0806
#define ETHTYPE_IP    0x0800

#define MAX_ETH_DATA_SIZE    1600

#define MAC_ETH_HDR_LEN     14


#define IP_ACKDATA     0x01     // Signifies that the outstanding data was acked and the application should send out new data instead of retransmitting the last data.
#define IP_NEWDATA     0x02     // Flags the fact that the peer has sent us new data.
#define IP_REXMIT      0x04     // Tells the application to retransmit the data that was last sent.
#define IP_POLL        0x08     // Used for polling the application, to check if the application has data that it wants to send.
#define IP_CLOSE       0x10     // The remote host has closed the connection, thus the connection has gone away. Or the application signals that it wants to close the connection.
#define IP_ABORT       0x20     // The remote host has aborted the connection, thus the connection has gone away. Or the application signals that it wants to abort the connection.
#define IP_CONNECTED   0x40     // We have got a connection from a remote host and have set up a new connection for it, or an active connection has been successfully established. 
#define IP_TIMEDOUT    0x80     // The connection has been aborted due to too many retransmissions. 

#define MAX_ETH_SEND_QUEUE   30

struct __attribute__((__packed__)) tagEthSendQueue
{
	INT16U Len;
	INT32U Timer;
	INT32U IPAddr;
	INT08U Data[MAX_ETH_DATA_SIZE];
};
typedef struct tagEthSendQueue  EthSendQueueSTR;

//extern void FpgatransferEthData(void);
extern void Fpga_tcp_send(INT08U s, INT08U* data, INT16U length);
extern void Fpga_udp_send(INT32U ipAddr, INT16U rport, INT16U lport);
extern INT08U getFpgaTcpSocketState(INT08U s);
INT08U getFpgaTcpSocketState_1(INT08U s);

extern void connectFpgaTcp(INT08U* remote_ip, INT16U remote_port, INT16U local_port);
void connectFpgaTcp_1(INT08U nSocket, INT08U* remote_ip, INT16U remote_port, INT16U local_port);

extern void setFpgaTcpIpStackNetworkParameter(NetworkInfo_t* net_info);   // GatewayIP. SubnetMask, MyIP
extern void setFpgaTcpIpStackMyMACAddrress(INT08U* mac_addr);
extern void FpgaTcpIpStackInit(void);
extern void FpgaTcpIpStackProcess(void);

#endif /* INC_TCPIPSTACK_H_ */

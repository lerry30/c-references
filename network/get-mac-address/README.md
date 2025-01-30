### Simple program for querying MAC address ###

In this program requires to input the interface name(eth0, wlan0), 
in order for interface req(struct ifreq) to be configured properly
or select the specific interface.

```c
int sock;
```

Declared socket variable(sock) as int for containing socket id.

```c
struct ifreq ifr;
```

Delared interface structure for network interface details.

Creating socket and its required parameters(3)
1. The first one used to defined the address family:
  - AF_INET - ipv4
  - AF_INET6 - ipv6
  - AF_PACKET - used for raw socket communication. This bypasses
        higher-level protocols(TCP/UDP), giving access to the
        ethernet frames
2. Second parameter defines the protocol used for processing data
    to communicate properly like TCP which is really strict on
    sequence or arrangement of data received or sent since it waits
    missing packets in order.

  - SOCK_RAW - specifies that the socket will send/received raw
        packets without any protocol-specific processing.
  - SOCK_DGRAM - used UDP to send datagram or actually it didn't
        send anything in this case.

3. The third parameter is I'm not really familiar with so just
    passed zero.

Next thing is by setting the interface name, it's just a placehoder
or container which requires by ioctl() in order to communicate to 
kernel with NIC.

ioctl() is the actual thing that communicates to kernel with NIC,
it is able to used system calls. So socket is for sending and
receiving, while struct ifreq is for storing interface name so it
could be used by ioctl to identify which INC needed.

ioctl() requirements:
  - socket id
  - flag
    - SIOCGIFINDEX
    - SIOCGIFADDR(IPv4)
    - SIOCGIFHWADDR(MAC)
  - address of struct ifreq(&ifr)

If no issue arise in this section the connection between the program
kernel and INC is now established.

```c
unsigned char* mac = (unsigned char*)ifr.ifr_hwaddr.sa_data;
```

cast to unsigned char and assigned to a pointer. This kind of info
(MAC) resides on struct ifreq ifr.

### Simple Program to get the IPv4 ###

Here's a way of getting your IPv4 in C. 

```c
int sock;
struct ifreq ifr;
```

Declare necessary variables. The purpose of sock is for 
storing socket id. The struct ifreq ifr is a structure
used to save interface name to help the ioctl() to identify
the interface needed to get the info and save back to ifr 
like MAC, ipv4, etc.

```c
sock = socket(AF_INET, SOCK_DGRAM, 0);
```

Create a socket. It required:
1. address family
  - AF_INET(IPv4)
  - AF_INET6(IPv6)
  - AF_PACKET - raw packets bypassing higher level protocols
    (TCP/UDP), by allowing custom packet creation.
2. protocol
  - SOCK_DGRAM - datagram(UDP)
3. leaved it as zero for this instance

```c
memset(&ifr, 0, sizeof(ifr));
strncpy(ifr.if_name, iface, IFNAMSIZ-1);
```

Prepare struct ifreq by first initialized it to zero to avoid
garbage data. The strncpy will copy the value of iface(WLAN0)
which contains the interface name passed by user to ifr.ifr_name
so later ioctl() will used it to identify interface needed.

```c
if(ioctl(sock, SIOCGIFADDR, &ifr) == -1)
```

Would return -1 if something wrong about the ifr or socket.
1. First parameter is the socket id.
2. Flag needed for operation of what data it retieves from NIC.
3. struct ifreq ifr to identify the interface it will interacts
    on.

```c
struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
print("%s", inet_ntoa(ipaddr->sin_addr));
```

The sockaddr_in is a structure containing properties:
  - sin_family - specify address family(AF_INET)
  - sin_addr - where ipv4 resides.
  - sin_port - saved port number(used in socket programming).
Thereby ifr ipv4 will be properly gets through this type of struct
pointer in ifreq struct.

inet_ntoa() - parses the sin_addr to probably string format

```c
close(sock);
```

Finally closed the soket.

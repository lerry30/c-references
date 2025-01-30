### Getting the size of Maximum Transmission Unit ###

Probably I'm going to dive into explaining what the MTU does, and why it is important.
This small program will give you that MTU in bytes so what it is? It is just the size
of a packet that NIC can recieved and sent over the network. The importance of it is just
to help us as developers to know when to break it it into smaller packets(fragmentation),
so default program of kernel will never do that for performance reason, because letting
the kernel handling such things might caused some overhead. So since I'm using the ioclt()
which is a system calls and it needs to communicate to kernel before the actual hardware
which in this case is the NIC.

```c
int sock = socket(AF_INET, SOCK_DGRAM, 0);
```

It creates a new socket with address family of AF_INET(IPv4). The second parameter is the
protocol it uses to communicate SOCK_DGRAM is datagram(UDP). Let the third parameter as 0.

```c
struct ifreq ifr;
strncpy(ifr.ifr_name, iface, IFNAMSIZ-1);
```

Now the struct ifreq ifr is a structure used to set the interface name and eventually stored
all the necessary inforamation that the INC provided from the specific request made by the
ioctl(). The strncpy() is going to copy the iface into the ifr(struct ifreq) to save the
interface name which in this instance the iface is the string holding it, it would be "eth0",
"wlan0".

```c
if(ioctl(sock, SIOCGIFMTU, &ifr) == 0) {
    printf("MTU of %s is %d bytes\n", iface, ifr.ifr_mtu);
}
```

The ioctl() will tries to interact with the kernel to NIC. The SIOCGIFMTU is the flag used to
identify the request the ioctl() will made to retrieve data.

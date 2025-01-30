#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

void getIPv4(const char* iface) {
    int sock;
    struct ifreq ifr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("Socket creation failed");
        return;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, iface, IFNAMSIZ-1);

    if(ioctl(sock, SIOCGIFADDR, &ifr) == -1) {
        perror("ioctl failed");
        close(sock);
        return;
    }

    struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
    printf("The IPv4 address of %s: %s\n", iface, inet_ntoa(ipaddr->sin_addr));

    close(sock);
}

int main() {
    char iface[IFNAMSIZ];
    printf("Enter interface name(eth0, wlan0): ");
    scanf("%s", iface);

    getIPv4(iface);
    
    return 0;
}

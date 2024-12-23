#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

void getMacAddress(const char* iface) {
    int sock;
    struct ifreq ifr;

    // create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("Socket creation failed.");
        return;
    }

    // prepare struct ifreq
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);

    if(ioctl(sock, SIOCGIFHWADDR, &ifr) == -1) {
        perror("ioctl failed");
        close(sock);
        return;
    }

    unsigned char* mac = (unsigned char*)ifr.ifr_hwaddr.sa_data;
    printf("MAC address of %s: %02x:%02x:%02x:%02x:%02x:%02x\n", 
            iface, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    close(sock);
}

int main() {
    char iface[IFNAMSIZ];
    printf("Enter the interface name(eth0, wlan0): ");
    scanf("%s", iface);

    getMacAddress(iface);

    return 0;
}

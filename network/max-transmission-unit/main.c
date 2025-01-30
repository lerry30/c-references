#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

void getMTU(const char* iface) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("Socket creation failed");
        return;
    }

    struct ifreq ifr;
    strncpy(ifr.ifr_name, iface, IFNAMSIZ-1);
    ifr.ifr_name[IFNAMSIZ-1] = '\0';

    if(ioctl(sock, SIOCGIFMTU, &ifr) == 0) {
        printf("MTU of %s: %d bytes", iface, ifr.ifr_mtu);
    } else {
        perror("ioctl failed.");
    }

    close(sock);
}

int main() {
    char iface[IFNAMSIZ];
    printf("Enter the interface name(eth0, wlan0): ");
    scanf("%s", iface);

    getMTU(iface);

    return 0;
}

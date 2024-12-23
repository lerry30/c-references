#include <stdio.h>
#include <string.h>

void formatIPv6(const char* raw, char* formatted) {
    // Add colons every 4 characters
    for(int i = 0, j = 0; i < 32; i++) {
        formatted[j++] = raw[i];
        if((i+1)%4 == 0 && i != 31) {
            formatted[j++] = ':';
        }
    }
    formatted[39] = '\0'; // Null-terminate the string
}

void getIPv6Address(const char* iface) {
    FILE* file = fopen("/proc/net/if_inet6", "r");
    if(!file) {
        perror("Failed to open /proc/net/if_inet6");
        return;
    }

    char buf[128];
    while(fgets(buf, sizeof(buf), file)) {
        char raw_ipv6[31], devname[20];
        sscanf(buf, "%32s %*02x %*02x %*02x %*02x %19s", raw_ipv6, devname);

        if(strcmp(devname, iface) == 0) {
            char formatted_ipv6[40];
            formatIPv6(raw_ipv6, formatted_ipv6);

            printf("IPv6 address of %s: %s\n", iface, formatted_ipv6);
            fclose(file);
            return;
        }
    }

    printf("No IPv6 address found for interface %s\n", iface);
    fclose(file);
}

int main() {
    char iface[20];
    printf("Enter network interface name(eth0, wlan0): ");
    scanf("%s", iface);

    getIPv6Address(iface);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <unistd.h>

// Calculate checksum for IP and TCP headers
unsigned short checksum(void* b, int len) {
    unsigned short* buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2) sum += *buf++;
    if (len == 1) sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

void sendPacketToPhone(const char* phone_ip) {
    char packet[4096];
    memset(packet, 0, sizeof(packet));

    struct iphdr* iph = (struct iphdr*)packet;
    struct tcphdr* tcph = (struct tcphdr*)(packet + sizeof(struct iphdr));

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(80); // HTTP port (example)
    dest.sin_addr.s_addr = inet_addr(phone_ip);

    // Fill IP header
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = htons(sizeof(struct iphdr) + sizeof(struct tcphdr));
    iph->id = htonl(54321);
    iph->frag_off = htons(0x4000); // DF flag set
    iph->ttl = 64;
    iph->protocol = IPPROTO_TCP;
    iph->check = 0; // Will calculate later
    iph->saddr = inet_addr("192.168.0.104"); // Replace with your machine's IP
    iph->daddr = dest.sin_addr.s_addr;

    // Fill TCP header
    tcph->source = htons(12345);
    tcph->dest = htons(80);
    tcph->seq = htonl(1);
    tcph->ack_seq = 0;
    tcph->doff = 5;
    tcph->syn = 1;  // SYN flag set
    tcph->window = htons(5840);
    tcph->check = 0;
    tcph->urg_ptr = 0;

    // Calculate checksums
    iph->check = checksum((unsigned short*)packet, iph->tot_len);
    tcph->check = checksum((unsigned short*)tcph, sizeof(struct tcphdr));

    // Create raw socket
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Send packet
    if (sendto(sock, packet, ntohs(iph->tot_len), 0, (struct sockaddr*)&dest, sizeof(dest)) < 0) {
        perror("Send failed");
    } else {
        printf("Packet sent to %s!\n", phone_ip);
    }

    close(sock);
}

int main() {
    const char* phone_ip = "192.168.0.101";
    sendPacketToPhone(phone_ip);
    return 0;
}

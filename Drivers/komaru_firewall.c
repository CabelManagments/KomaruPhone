#include "komaru_firewall.h"
#include <stdio.h>
#include <stdlib.h>

int komaru_firewall_init(void) {
    system("iptables -F");
    return 0;
}

void komaru_firewall_block_all(void) {
    system("iptables -P INPUT DROP");
    system("iptables -P FORWARD DROP");
    system("iptables -P OUTPUT DROP");
}

void komaru_firewall_allow_all(void) {
    system("iptables -P INPUT ACCEPT");
    system("iptables -P FORWARD ACCEPT");
    system("iptables -P OUTPUT ACCEPT");
}

void komaru_firewall_allow_port(int port, const char *proto) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "iptables -A INPUT -p %s --dport %d -j ACCEPT", proto, port);
    system(cmd);
}

void komaru_firewall_block_port(int port, const char *proto) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "iptables -A INPUT -p %s --dport %d -j DROP", proto, port);
    system(cmd);
}

void komaru_firewall_allow_ip(const char *ip) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "iptables -A INPUT -s %s -j ACCEPT", ip);
    system(cmd);
}

void komaru_firewall_block_ip(const char *ip) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "iptables -A INPUT -s %s -j DROP", ip);
    system(cmd);
}

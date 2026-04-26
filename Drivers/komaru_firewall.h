#ifndef KOMARU_FIREWALL_H
#define KOMARU_FIREWALL_H

int komaru_firewall_init(void);
void komaru_firewall_block_all(void);
void komaru_firewall_allow_all(void);
void komaru_firewall_allow_port(int port, const char *proto);
void komaru_firewall_block_port(int port, const char *proto);
void komaru_firewall_allow_ip(const char *ip);
void komaru_firewall_block_ip(const char *ip);

#endif

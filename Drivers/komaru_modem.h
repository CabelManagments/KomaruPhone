#ifndef KOMARU_MODEM_H
#define KOMARU_MODEM_H

int komaru_modem_init(void);
int komaru_modem_call(const char *number);
int komaru_modem_sms(const char *number, const char *message);
int komaru_modem_read_response(char *buffer, int size);

#endif /* KOMARU_MODEM_H */

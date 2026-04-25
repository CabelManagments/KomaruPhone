#include "komaru_modem.h"
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static int modem_fd = -1;

int komaru_modem_init(void) {
    struct termios tty;
    modem_fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    if(modem_fd < 0) return -1;
    tcgetattr(modem_fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    tty.c_cflag = CS8 | CLOCAL | CREAD;
    tcsetattr(modem_fd, TCSANOW, &tty);
    return 0;
}

static void modem_send_at(const char *cmd) {
    write(modem_fd, cmd, strlen(cmd));
    write(modem_fd, "\r\n", 2);
}

int komaru_modem_call(const char *number) {
    char buf[32];
    snprintf(buf, sizeof(buf), "ATD%s;", number);
    modem_send_at(buf);
    return 0;
}

int komaru_modem_sms(const char *number, const char *message) {
    modem_send_at("AT+CMGF=1");
    usleep(500000);
    char buf[64];
    snprintf(buf, sizeof(buf), "AT+CMGS=\"%s\"", number);
    modem_send_at(buf);
    usleep(500000);
    write(modem_fd, message, strlen(message));
    write(modem_fd, "\x1A", 1);
    return 0;
}

int komaru_modem_read_response(char *buffer, int size) {
    int bytes = read(modem_fd, buffer, size - 1);
    if(bytes > 0) buffer[bytes] = '\0';
    return bytes;
}

int komaru_modem_check_network(void) {
    return 1;
}

int komaru_modem_signal_quality(void) {
    return 70;
}

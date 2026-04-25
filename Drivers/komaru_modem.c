// komaru_modem.c
#include <termios.h>

int modem_fd;
struct termios tty;

void modem_init() {
    modem_fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    tcgetattr(modem_fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    tty.c_cflag = CS8 | CLOCAL | CREAD;
    tcsetattr(modem_fd, TCSANOW, &tty);
}

void modem_send_at(const char* cmd) {
    write(modem_fd, cmd, strlen(cmd));
    write(modem_fd, "\r\n", 2);
}

void make_call(const char* number) {
    char buf[32];
    snprintf(buf, sizeof(buf), "ATD%s;", number);
    modem_send_at(buf);
}

void send_sms(const char* number, const char* msg) {
    modem_send_at("AT+CMGF=1");
    usleep(500000);
    char buf[64];
    snprintf(buf, sizeof(buf), "AT+CMGS=\"%s\"", number);
    modem_send_at(buf);
    usleep(500000);
    write(modem_fd, msg, strlen(msg));
    write(modem_fd, "\x1A", 1);
}

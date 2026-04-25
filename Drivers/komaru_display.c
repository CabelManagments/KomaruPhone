// komaru_display.c
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define OLED_ADDR 0x3C
#define I2C_BUS "/dev/i2c-1"

void oled_write_cmd(int fd, uint8_t cmd) {
    uint8_t buf[2] = {0x00, cmd};
    write(fd, buf, 2);
}

void oled_init() {
    int fd = open(I2C_BUS, O_RDWR);
    ioctl(fd, I2C_SLAVE, OLED_ADDR);
    
    oled_write_cmd(fd, 0xAE); // display off
    oled_write_cmd(fd, 0xD5); // clock divider
    oled_write_cmd(fd, 0x80);
    oled_write_cmd(fd, 0xA8); // multiplex
    oled_write_cmd(fd, 0x3F);
    oled_write_cmd(fd, 0xD3); // offset
    oled_write_cmd(fd, 0x00);
    oled_write_cmd(fd, 0x40); // start line
    oled_write_cmd(fd, 0x8D); // charge pump
    oled_write_cmd(fd, 0x14);
    oled_write_cmd(fd, 0xAF); // display on
}

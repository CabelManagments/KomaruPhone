// komaru_devtool.c
#include <linux/ioctl.h>

#define KOMARU_IOC_MAGIC 'k'
#define KOMARU_RESET_SYSTEM _IO(KOMARU_IOC_MAGIC, 1)
#define KOMARU_FLASH_MODEM _IO(KOMARU_IOC_MAGIC, 2)

long komaru_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch(cmd) {
        case KOMARU_RESET_SYSTEM:
            kernel_restart(NULL);
            break;
        case KOMARU_FLASH_MODEM:
            // перепрошивка модема через UART
            flash_modem_firmware();
            break;
    }
    return 0;
}

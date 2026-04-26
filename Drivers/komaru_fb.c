#include "komaru_fb.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <stdio.h>
#include <string.h>

static int fbfd = -1;
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
static char *fbp = NULL;

int komaru_fb_init(void) {
    fbfd = open("/dev/fb0", O_RDWR);
    if(fbfd < 0) return -1;
    
    ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo);
    ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
    
    fbp = mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    return (fbp != MAP_FAILED) ? 0 : -1;
}

void komaru_fb_clear(void) {
    memset(fbp, 0, finfo.smem_len);
}

void komaru_fb_pixel(int x, int y, int r, int g, int b) {
    if(x >= vinfo.xres || y >= vinfo.yres) return;
    long location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) +
                    (y + vinfo.yoffset) * finfo.line_length;
    *(fbp + location) = b;
    *(fbp + location + 1) = g;
    *(fbp + location + 2) = r;
}

int komaru_fb_width(void) { return vinfo.xres; }
int komaru_fb_height(void) { return vinfo.yres; }

void komaru_fb_close(void) {
    munmap(fbp, finfo.smem_len);
    close(fbfd);
}

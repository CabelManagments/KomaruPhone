#include <sys/time.h>
#include <signal.h>
#include <stdio.h>

static void (*frame_callback)(void) = NULL;

void timer_handler(int sig) {
    if(frame_callback) frame_callback();
}

void komaru_timer_init(void (*callback)(void)) {
    frame_callback = callback;
    
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 16667;  // 60 fps = 16.667 ms
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 16667;
    
    signal(SIGALRM, timer_handler);
    setitimer(ITIMER_REAL, &timer, NULL);
}

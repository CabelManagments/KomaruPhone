# KomaruPhone Makefile
CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -Wextra -Os -static -I./Drivers
LDFLAGS = -lm

DRIVERS = $(wildcard Drivers/*.c)
APPS = $(wildcard Apps/*.c)
OBJ = $(DRIVERS:.c=.o)

all: komaru_init komaru_devtool

komaru_init: init/komaru_init.c $(DRIVERS)
$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

komaru_devtool: devtool/komaru_devtool.c
$(CC) $(CFLAGS) -o $@ $^

# Для отладки на ПК (через SDL)
pc: CFLAGS += -DPC_BUILD -I/usr/include/SDL2
pc: LDFLAGS += -lSDL2
pc: komaru_init.c $(DRIVERS)
gcc $(CFLAGS) -o komaru_pc $^ $(LDFLAGS)

clean:
rm -f komaru_init komaru_devtool komaru_pc $(OBJ)

.PHONY: all clean pc

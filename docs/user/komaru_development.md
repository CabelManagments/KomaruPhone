# Разработка под KomaruOS

## Написание своего приложения

```c
#include "komaru_display.h"
#include "komaru_buttons.h"

void my_app_run(void) {
    int running = 1;
    while(running) {
        komaru_display_clear();
        komaru_display_string("My App", 45, 30);
        komaru_display_update();
        
        if(komaru_buttons_read() & BTN_POWER) {
            running = 0;
        }
        usleep(50000);
    }
}
```

Добавление в систему

1. Положи код в Apps/komaru_myapp.c
2. Добавь вызов в init/komaru_init.c
3. Собери: make

Создание своего драйвера

```c
#include "komaru_driver.h"

int my_driver_init(void) {
    // инициализация
    return 0;
}

void my_driver_cleanup(void) {
    // очистка
}
```

API стандартных драйверов

Все драйверы имеют единый интерфейс:

· *_init() - инициализация
· *_get_*() - получение данных
· *_set_*() - установка параметров
  EOF

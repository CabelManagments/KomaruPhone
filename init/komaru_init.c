// komaru_init.c
int main() {
    // 1. Монтируем /proc, /sys, /dev
    mount("proc", "/proc", "proc", 0, NULL);
    mount("sysfs", "/sys", "sysfs", 0, NULL);
    mount("devtmpfs", "/dev", "devtmpfs", 0, NULL);
    
    // 2. Инициализируем драйверы
    oled_init();
    modem_init();
    button_init();
    
    // 3. Показываем приветствие
    oled_write_string(0, 0, "KomaruPhone v0.1");
    oled_write_string(0, 2, "System ready.");
    
    // 4. Главный цикл
    while(1) {
        int btns = read_buttons();
        if(btns & 1) system_reboot();  // кнопка питания
        // ... остальная логика
        sleep(1);
    }
}

# 🍌 KomaruPhone · Самый открытый телефон в мире

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## Что это?

**KomaruPhone** — полностью открытый телефон. Всё с нуля:
- 🔓 Железо без блобов
- 🧠 Своё ядро (форк Linux)
- 🐧 Свои драйверы на C
- 📱 Своя ОС без слежки
- 🍌 Стиль — бананы и кошки Komaru

## Железо

| Компонент | Модель |
|-----------|--------|
| Процессор | Raspberry Pi Zero 2 W |
| Модем | SIM800C (2G) |
| Экран | OLED 1.3" SH1106 |
| Батарея | Li-Po 2000mAh |

## Драйверы (36+)

- Display (SH1106 I2C)
- Touch (сенсорный экран)
- Buttons (GPIO кнопки)
- Modem (SIM800C UART)
- WiFi (wpa_supplicant)
- Bluetooth (BlueZ)
- GPS (NMEA parser)
- Audio (ALSA)
- Camera (V4L2)
- Power (батарея, reboot)
- Vibrator (вибрация)
- RTC (часы)
- Storage (SD card)
- Sensors (акселерометр, гироскоп)
- и другие...

## Приложения

- KomaruBrowser — веб-браузер
- KomaruNotes — заметки
- KomaruGallery — галерея
- KomaruAppStore — магазин приложений
- KomaruTerminal — терминал
- KomaruSettings — настройки

## Сборка

```bash
cd KomaruPhone
make
```

Лицензия

GNU General Public License v3.0

Автор

CabelManagments
Сделано с ненавистью к проприетарному говну и любовью к бананам.

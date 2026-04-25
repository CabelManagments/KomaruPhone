# 📱 KomaruPhone · Самый открытый телефон в мире

> **"Свобода, открытость и кошки."**

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/m/CabelManagments/KomaruPhone)](https://github.com/CabelManagments/KomaruPhone/commits)
[![GitHub last commit](https://img.shields.io/github/last-commit/CabelManagments/KomaruPhone)](https://github.com/CabelManagments/KomaruPhone)

---

## 🎯 Что это?

**KomaruPhone** — это полностью открытый телефон.  
Не "кастомная прошивка на чужом железе", а **всё с нуля**:

- 🔓 Железо без блобов
- 🧠 Своё ядро (форк Linux)
- 🐧 Свои драйверы на C
- 📱 Своя ОС без слежки
- 🐱 Стиль — кошка Komaru везде

---

## 🛠 Технологии

| Компонент | Технология |
|-----------|------------|
| Язык ядра и драйверов | ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white) |
| Init процесс | ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white) |
| Сборка ОС | Buildroot |
| Ядро | Linux (форк) |
| Модем | SIM800C (AT-команды) |
| Экран | OLED SH1106 (I2C) |
| Контроль версий | ![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white) |
| Лицензия | ![GPLv3](https://img.shields.io/badge/license-GPLv3-green.svg) |

---

## 📦 Компоненты

| Компонент | Модель | Назначение |
|-----------|--------|------------|
| 🧠 Мозг | Raspberry Pi Zero 2 W | Основной процессор |
| 📡 Связь | SIM800C | Звонки, SMS, 2G |
| 🖥 Экран | OLED 1.3" SH1106 | Дисплей 128x64 |
| 🔋 Питание | Li-Po 2000mAh | Аккумулятор |
| ⚡️ Повышение | MT3608 | 3.7V → 5V |
| 🔌 Зарядка | TP4056 | Зарядка Li-Po |
| 🔊 Звук | USB звуковая карта + динамик + микрофон | Аудио |
| 🔘 Управление | Тактовые кнопки | Питание, громкость, программируемая |
| 🔪 Отключение | Микровыключатель SPST | Физический разрыв батареи |

---

## 🧱 Структура проекта

```

KomaruPhone/
├── drivers/           # Драйверы (дисплей, модем, кнопки)
├── init/              # Init процесс
├── devtool/           # KomaruDevTool (управление системой)
├── kernel-patches/    # Патчи для ядра Linux
├── buildroot-config/  # Конфиг сборки OS
├── docs/              # Схемы подключения, AT-команды
└── README.md          # Ты здесь

```

---

## 🚀 Статус разработки

| Этап | Статус |
|------|--------|
| 🔧 Выбор компонентов | ✅ Готов |
| 📦 Заказ железа | ✅ Сделан |
| 🐚 Написание драйверов | ⏳ В процессе |
| 🔨 Сборка прототипа | ⏳ Ожидает железо |
| 🐱 Первый запуск | ⏳ Скоро |
| 📱 Звонок через модем | 🎯 Цель v0.2 |

---

## 🔗 Репозиторий

```

https://github.com/CabelManagments/KomaruPhone

```

---

## 📜 Лицензия

**GNU General Public License v3.0**  
Полностью открытый код. Бери, меняй, улучшай, но не закрывай.

---

## 🐱 Автор

**CabelManagments**  
*Сделано с ненавистью к проприетарному говну и любовью к кошкам.*

---

> *"Если ты не контролируешь свой телефон — он контролирует тебя."*  
> — KomaruPhone Manifesto

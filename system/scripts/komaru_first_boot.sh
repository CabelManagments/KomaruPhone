#!/system/bin/sh

echo "KomaruOS First Boot Setup"

# Создаём пользовательские папки
mkdir -p /home/komaru/{notes,pics,downloads,backup,config}

# Копируем конфиги по умолчанию
cp -r /etc/komaru_default/* /etc/komaru/ 2>/dev/null

# Запускаем сервисы
komaru_services start_all

echo "Setup complete. Rebooting in 3 seconds..."
sleep 3
reboot

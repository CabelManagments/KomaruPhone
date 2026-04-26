#!/system/bin/sh

echo "WARNING: This will erase all data!"
echo "Press Power to confirm, Vol+ to cancel"

# Ждём кнопку (заглушка)
sleep 2

echo "Resetting..."
rm -rf /home/komaru/*
rm -rf /etc/komaru/*
echo "Reset complete. Rebooting..."
reboot

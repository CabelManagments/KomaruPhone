#!/system/bin/sh

echo "=== KomaruOS Logs ==="
echo "1. System log"
echo "2. Kernel log"
echo "3. Application log"
echo "4. Clear logs"
read choice

case $choice in
    1) cat /var/log/komaru/system.log ;;
    2) dmesg | tail -50 ;;
    3) cat /var/log/komaru/apps.log ;;
    4) > /var/log/komaru/system.log ;;
esac

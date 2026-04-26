#!/system/bin/sh

echo "=== KomaruOS Debug ==="
echo "Battery: $(cat /sys/class/power_supply/battery/capacity 2>/dev/null || echo "N/A")%"
echo "WiFi: $(iwgetid -r 2>/dev/null || echo "off")"
echo "IP: $(ifconfig wlan0 | grep inet | awk '{print $2}')"
echo "Memory: $(free -h | grep Mem | awk '{print $3"/"$2}')"
echo "Storage: $(df -h /home | awk 'NR==2 {print $3"/"$2}')"
echo "Uptime: $(uptime | awk '{print $3,$4}')"

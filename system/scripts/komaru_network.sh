#!/system/bin/sh

case $1 in
    up)
        ifconfig wlan0 up
        wpa_supplicant -B -i wlan0 -c /etc/komaru/wpa_supplicant.conf
        dhclient wlan0
        ;;
    down)
        ifconfig wlan0 down
        killall wpa_supplicant
        ;;
    status)
        ifconfig wlan0 | grep inet
        ;;
esac

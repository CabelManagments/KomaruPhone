# KomaruOS API Documentation

## Display
- `komaru_display_init()` - init display
- `komaru_display_clear()` - clear screen
- `komaru_display_string(text, x, y)` - print text

## Buttons
- `komaru_buttons_init()` - init buttons
- `komaru_buttons_read()` - get button state

## Power
- `komaru_power_get_battery_level()` - get battery %
- `komaru_power_shutdown()` - shutdown system
- `komaru_power_reboot()` - reboot system

## Modem
- `komaru_modem_init()` - init modem
- `komaru_modem_call(number)` - make call
- `komaru_modem_sms(number, message)` - send SMS

## WiFi
- `komaru_wifi_init()` - init WiFi
- `komaru_wifi_set_enabled(enabled)` - enable/disable
- `komaru_wifi_connect(ssid, password)` - connect to network

## Bluetooth
- `komaru_bluetooth_init()` - init BT
- `komaru_bluetooth_set_enabled(enabled)` - enable/disable
- `komaru_bluetooth_send_file(filename, mac)` - send file

## GPS
- `komaru_gps_init()` - init GPS
- `komaru_gps_update()` - update position
- `komaru_gps_get_data()` - get coordinates

## Audio
- `komaru_audio_init()` - init audio
- `komaru_audio_set_volume(percent)` - set volume
- `komaru_audio_beep(freq, ms)` - beep sound

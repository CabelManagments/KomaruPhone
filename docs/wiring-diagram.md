# KomaruPhone Wiring Diagram

## Pin Connections

### OLED SH1106 (I2C)
| OLED Pin | RPi Zero Pin | GPIO |
|----------|--------------|------|
| VCC      | Pin 1        | 3.3V |
| GND      | Pin 6        | GND  |
| SCL      | Pin 5        | GPIO3|
| SDA      | Pin 3        | GPIO2|

### SIM800C Modem (UART)
| SIM800C    | RPi Zero Pin | Notes                 |
|------------|--------------|-----------------------|
| VCC (5V)   | MT3608 out   | through 1N4007 diode  |
| GND        | Pin 9        | GND                   |
| TX (SIM)   | Pin 10       | RX (GPIO15)           |
| RX (SIM)   | Pin 8        | TX (GPIO14)           |
| RST        | Pin 22       | optional              |

### Buttons (GPIO)
| Button     | Pin | GPIO | Logic    |
|------------|-----|------|----------|
| Power      | 11  | 17   | LOW=press|
| Volume Up  | 13  | 27   | LOW=press|
| Volume Down| 15  | 22   | LOW=press|
| Program    | 16  | 23   | LOW=press|

### Power Management
| Component   | Connection                    |
|-------------|-------------------------------|
| Battery +   | MT3608 IN+ and TP4056 BAT+    |
| Battery -   | Common GND                    |
| MT3608 OUT+ | RPi Pin 2 (5V) + USB sound    |
| MT3608 OUT+ | 1N4007 -> SIM800C VCC         |
| TP4056 IN+  | USB-C (charging)              |

## Power Switch Location
Place SPST switch between Battery+ and MT3608+ to completely cut power.

## USB Sound Card
Plug into RPi Zero USB port. Connect speaker to green wires, mic to pink.

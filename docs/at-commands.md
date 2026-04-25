# SIM800C AT Commands Reference

## Basic Commands

| Command | Response | Description |
|---------|----------|-------------|
| `AT` | OK | Test connection |
| `AT+CPIN?` | +CPIN: READY | SIM card status |
| `AT+CREG?` | +CREG: 0,1 | Network registration |

## Calls

| Command | Description |
|---------|-------------|
| `ATD+380XXXXXXXX;` | Make voice call |
| `ATA` | Answer incoming call |
| `ATH` | Hang up |
| `AT+CLCC` | List current calls |

## SMS

| Command | Description |
|---------|-------------|
| `AT+CMGF=1` | Text mode |
| `AT+CMGS="+380XXXXXXXX"` | Send SMS (text follow, end with Ctrl+Z) |
| `AT+CMGR=1` | Read SMS #1 |
| `AT+CMGD=1` | Delete SMS #1 |

## Network

| Command | Description |
|---------|-------------|
| `AT+COPS?` | Current operator |
| `AT+CSQ` | Signal quality (0-31) |

## KomaruPhone Examples

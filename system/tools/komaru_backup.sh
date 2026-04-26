#!/system/bin/sh

BACKUP_DIR="/home/komaru/backup"
DATE=$(date +%Y%m%d_%H%M%S)

mkdir -p $BACKUP_DIR

echo "Backup to $BACKUP_DIR/backup_$DATE.tar.gz"
tar -czf $BACKUP_DIR/backup_$DATE.tar.gz /home/komaru /etc /usr/local 2>/dev/null

echo "Done."

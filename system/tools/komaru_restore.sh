#!/system/bin/sh

BACKUP_DIR="/home/komaru/backup"

echo "Available backups:"
ls -1 $BACKUP_DIR/*.tar.gz 2>/dev/null | xargs -n1 basename
echo ""
echo "Enter backup filename: "
read filename

if [ -f "$BACKUP_DIR/$filename" ]; then
    echo "Restoring $filename..."
    tar -xzf "$BACKUP_DIR/$filename" -C /
    echo "Done."
else
    echo "Backup not found."
fi

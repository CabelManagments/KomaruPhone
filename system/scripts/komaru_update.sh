#!/system/bin/sh

echo "KomaruOS Updater"
echo "Checking updates..."

cd /tmp
git clone https://github.com/CabelManagments/KomaruPhone.git update 2>/dev/null

if [ -d update ]; then
    echo "Update found. Installing..."
    cp -r update/Drivers/* /usr/lib/komaru/drivers/
    cp -r update/Apps/* /usr/share/komaru/apps/
    cp update/system/scripts/* /usr/lib/komaru/scripts/
    echo "Update complete. Reboot required."
    rm -rf update
else
    echo "No updates available"
fi

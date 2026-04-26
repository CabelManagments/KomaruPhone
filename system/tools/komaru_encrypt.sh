#!/system/bin/sh

if [ $# -ne 2 ]; then
    echo "Usage: komaru_encrypt file password"
    exit 1
fi

openssl enc -aes-256-cbc -salt -in "$1" -out "$1.enc" -k "$2"
echo "Encrypted to $1.enc"

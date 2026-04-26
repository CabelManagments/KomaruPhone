#!/system/bin/sh

if [ $# -ne 2 ]; then
    echo "Usage: komaru_decrypt file.enc password"
    exit 1
fi

OUT="${1%.enc}"
openssl enc -aes-256-cbc -d -in "$1" -out "$OUT" -k "$2"
echo "Decrypted to $OUT"

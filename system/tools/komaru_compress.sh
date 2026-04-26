#!/system/bin/sh

case $1 in
    pack)
        tar -czf "$2.tar.gz" "$2"
        echo "Packed to $2.tar.gz"
        ;;
    unpack)
        tar -xzf "$2"
        echo "Unpacked $2"
        ;;
    *)
        echo "Usage: komaru_compress pack|unpack file"
        ;;
esac

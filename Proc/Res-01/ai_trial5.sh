while true; do
    pid=$(pgrep -d',' -u "$USER" -f "top")
    if [ -n "$pid" ]; then
        top -b -n 1 -p "$pid" | awk -v p="$pid" '/^ *[0-9]/ { if($9 > 50.0) { print p; system("kill -9 " p) } }'
    fi
    sleep 1
done

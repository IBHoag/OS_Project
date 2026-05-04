while true; do
    pid=$(pgrep -d',' -u "$USER" | tr ',' '\n' | head -n 1)
    if [ -n "$pid" ]; then
        usage=$(top -b -n 1 -p "$pid" | awk -v p="$pid" '$1 == p {print $9}' | cut -d. -f1)
        if [ -n "$usage" ] && [ "$usage" -gt 50 ]; then
            echo "Killing process $pid (CPU usage: $usage%)"
            kill -9 "$pid"
        fi
    fi
    sleep 1
done

while true; do
    pid=$(pgrep -d',' -u "$USER" | tr ',' '\n' | head -n 1)
    if [ -n "$pid" ]; then
        cpu=$(top -b -n 1 -p "$pid" | awk -v p="$pid" '$1 == p {print $9}' | cut -d. -f1)
        if [ -n "$cpu" ] && [ "$cpu" -gt 50 ]; then
            echo "Killing process $pid for exceeding 50% CPU ($cpu%)"
            kill -9 "$pid"
        fi
    fi
    sleep 1
done

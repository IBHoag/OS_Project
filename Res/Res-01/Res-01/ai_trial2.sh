while true; do
    PID=$(top -b -n 1 | grep "echo" | awk '$9 > 50.0 {print $1}')
    if [ ! -z "$PID" ]; then
        kill -9 $PID
    fi
    sleep 1
done

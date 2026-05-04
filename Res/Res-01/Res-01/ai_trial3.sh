while true; do
    top -b -n 1 | awk 'NR>7 && $9 > 50.0 {print $1}' | xargs -r kill -9
    sleep 1
done

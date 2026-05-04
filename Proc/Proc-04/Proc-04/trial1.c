OLDEST_PID=$(ps -u $USER -o pid=,start_time=,comm= --sort=start_time | grep -vE "(bash|sh|zsh|fish|tcsh|csh)" | head -n 1 | awk '{print $1}')
ps -u $USER && [ ! -z "$OLDEST_PID" ] && echo "kill $OLDEST_PID"

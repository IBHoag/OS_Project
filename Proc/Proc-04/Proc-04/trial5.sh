pgrep -U $(id -u) | grep -v -w -f <(ps -o pid= -p $$ -p $PPID) | xargs -r ps -o start_time=,pid= -p | sort | head -n 1 | awk '{print "echo kill " $2}' | sh

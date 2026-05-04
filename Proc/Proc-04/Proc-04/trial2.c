ps -u $(whoami) -o pid,start_time,comm --sort=start_time | grep -vE "(bash|zsh|sh|ps|grep|PID)" | head -n 1 | awk '{print "echo killing process " $1 " (" $3 ")"}' | sh

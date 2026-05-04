ps -u $(whoami) -o pid,start_time,comm --sort=start_time | grep -vE "(bash|sh|zsh|fish|tcsh|csh|PID)" | head -n 1 | awk '{print "echo kill " $1}' | sh

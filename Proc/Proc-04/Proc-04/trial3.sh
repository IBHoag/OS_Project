ps -u $USER -o pid,start_time,comm --sort=start_time | grep -vE "(bash|sh|zsh|fish|ps|grep)" | awk 'NR==1 {print "echo kill " $1}'

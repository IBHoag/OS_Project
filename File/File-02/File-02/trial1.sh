chown $USER "$1" && ls -l "$1" | awk '{print $1}'

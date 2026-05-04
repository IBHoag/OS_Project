chown $USER "$1" && stat -c "%A %U:%G %n" "$1"

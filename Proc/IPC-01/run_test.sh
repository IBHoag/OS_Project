#!/bin/bash
# This script runs AI-generated code safely using ulimit.
# Usage: ./run_test.sh <executable_name> (e.g., ./run_test.sh ai_task)

# Safety limits (the "OS Cage"):
# -t 120: Limit CPU time to 120 seconds (kills infinite loops).
# -f 102400: Limit file size to 100MB (prevents filling disk).
# -u 30: Limit processes to 30 (prevents fork bombs).

ulimit -t 120
ulimit -f 102400
ulimit -u 1000

# Run the program and log output/errors.
./$1 > output.log 2> error.log

# Check if ulimit killed it.
if [ $? -ne 0 ]; then
  echo "Ulimit triggered: Program exceeded limits!" >> error.log
fi

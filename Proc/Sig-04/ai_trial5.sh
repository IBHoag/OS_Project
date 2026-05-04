#!/bin/bash

TEMP_FILE=$(mktemp)

cleanup() {
    rm -f "$TEMP_FILE"
    exit
}

trap cleanup SIGINT

while true; do
    sleep 1
done

#!/bin/bash

TEMP_FILE=$(mktemp)

trap 'rm -f "$TEMP_FILE"; exit' SIGINT

while true; do
    sleep 1
done

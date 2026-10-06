#!/bin/bash

PROCESS = "my_app"

while true
do
    if pgrep "$PROCESS" > /dev/null
    then
        echo "$(date): $PROCESS is running.."
    else
        echo "$(date): $PROCESS is not running.."
        echo "Restarting $PROCESS.."
    fi

    sleep 5

done 
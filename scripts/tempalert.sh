#!/bin/bash

### BEGIN INIT INFO
# Provides: tempalert
# Required-Start: $local_fs $network $remote_fs
# Required-Stop: $local_fs $network $remote_fs
# Default-Start: 2 3 4 5
# Default-Stop: 0 1 2 3 4 5 6
# Short-Description: CPU temperature alerts
# Description: Reads CPU temperatures, calculates average
#		temperature and sends an alert via e-mail, if the average
#		is above the temperature threshold.

PATH=/sbin:/usr/sbin:/bin:/usr/bin
DAEMON=/usr/local/bin/tempalert
PIDFILE=/run/tempalert.pid

## Arguments for executable ##
recipient="root"
interval=1
temperature_threshold=60

## Service start/stop functions ##
start() {
    echo "Starting Tempalert..."
    start-stop-daemon --chuid tempalert --start --background --make-pidfile --pidfile $PIDFILE --exec $DAEMON --  $temperature_threshold $interval $recipient
}

stop () {
    echo "Stopping Tempalert..."
    start-stop-daemon --stop --pidfile $PIDFILE --remove-pidfile --retry 5
}

status () {
    start-stop-daemon --pidfile $PIDFILE --status
    if [[ $? -eq 0  ]] ; then
	    echo "Tempalert is running"
    else
	    echo "Tempalert is stopped"
    fi
}

## case statement to be used to call functions ##
case "$1" in
start)
start
;;
stop)
stop
;;
status)
status
;;
*)
echo $"Usage: $0 {start|stop|status}"
exit 5
esac
exit $?

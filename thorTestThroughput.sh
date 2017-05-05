#!/bin/sh

MACHINE=$1
PORT=$2
SPIDEY_MODE=$3

echo --------------Testing for $3 --------------------

# Testing directory listing time
echo Testing 1KB access time with $SPIDEY_MODE ...
for i in 4; do
	ITIME=$(./thor.py -p $i -r 2 http://student${MACHINE}.cse.nd.edu:$PORT/1k.txt | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2)
    echo Average time per request with $i processes: $ITIME
    echo "Average throughput: $(echo "1000/$ITIME" | bc) bytes/second"
done
echo
echo



# Testing static files access time
echo Testing 1MB access time with $SPIDEY_MODE ...
COUNT=0
for i in 4; do
	ITIME=$(./thor.py -p $i -r 2 http://student${MACHINE}.cse.nd.edu:$PORT/1m.txt | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2)
    echo Average time per request $i processes: $ITIME
    echo "Average throughput: $(echo "1000000/$ITIME" | bc) bytes/second"
done
echo
echo



# Testing CGI script time
echo Testing 1GB access time with $SPIDEY_MODE ...
COUNT=0
for i in 4; do
	ITIME=$(./thor.py -p $i -r 2 http://student${MACHINE}.cse.nd.edu:$PORT/1g.txt | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2)
    echo Average time per request $i processes: $ITIME
    echo "Average throughput: $(echo "1000000000/$ITIME" | bc) bytes/second"
done
echo
echo




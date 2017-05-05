#!/bin/sh

MACHINE=$1
PORT=$2
SPIDEY_MODE=$3

echo --------------Testing for $3 --------------------

# Testing directory listing time
echo Testing 1KB access time with $SPIDEY_MODE ...
COUNT=0
for i in 1 2 4; do
	ITIME=$(./thor.py -p $i -r 100 http://student${MACHINE}.cse.nd.edu:$PORT/1k.html | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2)
    echo Time taken with $i processes: $ITIME
    COUNT=$(echo "$COUNT + $ITIME" | bc)
done
echo "Total bytes transferred: 700KB"
echo "Total time it took to run Directory Listing: $COUNT"
echo "Overall Throughput: "$(echo "700000/$COUNT" | bc) bytes/second
echo
echo



# Testing static files access time
echo Testing 1MB access time with $SPIDEY_MODE ...
COUNT=0
for i in 1 2 4; do
	ITIME=$(./thor.py -p $i -r 100 http://student${MACHINE}.cse.nd.edu:$PORT/1m.html | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2)
    echo Time taken with $i processes: $ITIME
    COUNT=$(echo "$COUNT + $ITIME" | bc)
done
echo "Total bytes transferred: 700MB"
echo "Total time it took to get Static File: $COUNT"
echo "Overall Throughput: "$(echo "700000000/$COUNT" | bc) bytes/second
echo
echo



# Testing CGI script time
echo Testing 500MB access time with $SPIDEY_MODE ...
COUNT=0
for i in 1 2 4; do
	ITIME=$(./thor.py -p $i -r 100 http://student${MACHINE}.cse.nd.edu:$PORT/500m.html | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2)
    echo Time taken with $i processes: $ITIME
    COUNT=$(echo "$COUNT + $ITIME" | bc)
done
echo "Total bytes transferred: 350GB"
echo "Total time it took to run CGI Script: $COUNT"
echo "Overall Throughput: "$(echo "350000000000/$COUNT") bytes/second
echo
echo




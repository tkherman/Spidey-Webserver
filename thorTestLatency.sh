#!/bin/sh

MACHINE=$1
PORT=$2
SPIDEY_MODE=$3

echo --------------Testing for $3 --------------------

# Testing directory listing time
echo Testing directory listing time...
COUNT=0
for i in 1 2 4; do
	ITIME=$(./thor.py -p $i -r 100 http://student${MACHINE}.cse.nd.edu:$PORT/html/index.html/ | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2)
    echo Time taken with $i processes: $ITIME
    COUNT=$(echo "$COUNT + $ITIME" | bc)
done
echo "Sum of average time it took to run Directory Listing: $COUNT"
echo
echo



# Testing static files access time
echo Testing static file access time...
COUNT=0
for i in 1 2 4; do
	ITIME=$(./thor.py -p $i -r 100 http://student${MACHINE}.cse.nd.edu:$PORT/text/hackers.txt/ | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2)
    echo Time taken with $i processes: $ITIME
    COUNT=$(echo "$COUNT + $ITIME" | bc)
done
echo "Sum of average time it took to get Static File: $COUNT"
echo
echo



# Testing CGI script time
echo Testing CGI script run time...
COUNT=0
for i in 1 2 4; do
	ITIME=$(./thor.py -p $i -r 100 http://student${MACHINE}.cse.nd.edu:$PORT/scripts/env.sh/ | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2)
    echo Time taken with $i processes: $ITIME
    COUNT=$(echo "$COUNT + $ITIME" | bc)
done
echo "Sum of average time it took to run CGI Script: $COUNT"
echo
echo




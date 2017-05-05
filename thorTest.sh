#!/bin/sh

COUNT=0
for i in 1 2 4; do
	./thor.py -p $i -r 100 http://student01.cse.nd.edu:9978/html/index.html/ | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2 >> singleD.txt
done
while read -r line
do
	#echo $line
	COUNT=$(echo "$COUNT + $line" | bc)
done < "singleD.txt"
echo "Average Forking Directory Listing Time: $COUNT"

COUNT=0
for i in 1 2 4; do
	./thor.py -p $i -r 100 http://student01.cse.nd.edu:9978/text/hackers.txt/ | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2 >> singleS.txt
done
while read -r line
do
	#echo $line
	COUNT=$(echo "$COUNT + $line" | bc)
done < "singleS.txt"
echo "Average Forking Static files Time: $COUNT"

COUNT=0
for i in 1 2 4; do
	./thor.py -p $i -r 100 http://student01.cse.nd.edu:9978/scripts/env.sh/ | grep 'TOTAL AVERAGE ELAPSED TIME: ' | cut -d ':' -f 2 | cut -d ' ' -f 2 >> singleC.txt
done
while read -r line
do 
	#echo $line
	COUNT=$(echo "$COUNT + $line" | bc)
done < "singleC.txt"
echo "Average Forking CGI Scripts Time: $COUNT"

rm singleD.txt
rm singleS.txt
rm singleC.txt

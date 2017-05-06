Project 02 - README
===================

Members
-------

- Kendyll Kraus (kkraus1@nd.edu)
- John McGuinness (jmcguin1@nd.edu)
- Herman Tong (ktong@nd.edu)

Summary
-------
Our group was able to implement the browse request, CGI request, and the file request.  All of these options worked in both single and forking mode.  We were able to get everything working.  Work was divided amongst group members by each taking separate functions (or programs in the case of thor.py).  Once we had all of the functions written, we all got together to debug program in its entirety.  There was some testing along the way as well to make sure that each function worked individually.

We went about measuring the average latency of the different types of requests by measuring the latency using 1, 2, and 4 processes on 100 requests to get a directory, static file, or CGI script.  We used thor.py to make all of these requests and get an average time.  Our shell script then took the average of all of the processes' average time.  We went about measuring the average throughput by creating dummy directories 1KB, 1MB, and 1GB in size.  Our shell script divided the total average by the size of the directory to get the throughput.

Latency
-------
--------------Testing for Single --------------------
Testing directory listing time...
Time taken with 1 processes: 0.00586994409561
Time taken with 2 processes: 0.00807530760765
Time taken with 4 processes: 0.0161406314373
Sum of average time it took to run Directory Listing: .03008588314056


Testing static file access time...
Time taken with 1 processes: 0.00599909305573
Time taken with 2 processes: 0.00805834412575
Time taken with 4 processes: 0.0160337513685
Sum of average time it took to get Static File: .03009118854998


Testing CGI script run time...
Time taken with 1 processes: 0.0145317196846
Time taken with 2 processes: 0.0254430055618
Time taken with 4 processes: 0.0515404713154
Sum of average time it took to run CGI Script: .0915151965618


--------------Testing for Forking --------------------
Testing directory listing time...
Time taken with 1 processes: 0.00605878591537
Time taken with 2 processes: 0.00753060460091
Time taken with 4 processes: 0.0143668007851
Sum of average time it took to run Directory Listing: .02795619130138


Testing static file access time...
Time taken with 1 processes: 0.00614438295364
Time taken with 2 processes: 0.0073814368248
Time taken with 4 processes: 0.0147290688753
Sum of average time it took to get Static File: .02825488865374


Testing CGI script run time...
Time taken with 1 processes: 0.0146270275116
Time taken with 2 processes: 0.0161751103401
Time taken with 4 processes: 0.0344047898054
Sum of average time it took to run CGI Script: .0652069276571


Throughput
----------
Running thor.py with 1 process and 10 requests

--------------Testing for Single --------------------
Testing 1KB access time with Single ...
Average time per request with 4 processes: 0.0593566298485
Average throughput: 16847 bytes/second


Testing 1MB access time with Single ...
Average time per request 4 processes: 0.0461816489697
Average throughput: 21653622 bytes/second


Testing 1GB access time with Single ...
Average time per request 4 processes: 18.6294230521
Average throughput: 53678527 bytes/second

--------------Testing for Forking --------------------
Testing 1KB access time with Forking ...
Average time per request with 4 processes: 0.0269251167774
Average throughput: 37140 bytes/second


Testing 1MB access time with Forking ...
Average time per request 4 processes: 0.0306865274906
Average throughput: 32587590 bytes/second


Testing 1GB access time with Forking ...
Average time per request 4 processes: 18.5900267661
Average throughput: 53792284 bytes/second




Running thor.py with 4 processes and 2 requests

--------------Testing for Single --------------------
Testing 1KB access time with Single ...
Average time per request with 4 processes: 0.0593566298485
Average throughput: 16847 bytes/second


Testing 1MB access time with Single ...
Average time per request 4 processes: 0.0461816489697
Average throughput: 21653622 bytes/second


Testing 1GB access time with Single ...
Average time per request 4 processes: 18.6294230521
Average throughput: 53678527 bytes/second

--------------Testing for Forking --------------------
Testing 1KB access time with Forking ...
Average time per request with 4 processes: 0.0269251167774
Average throughput: 37140 bytes/second


Testing 1MB access time with Forking ...
Average time per request 4 processes: 0.0306865274906
Average throughput: 32587590 bytes/second


Testing 1GB access time with Forking ...
Average time per request 4 processes: 18.5900267661
Average throughput: 53792284 bytes/second

Analysis
--------
In latency testing, we got comparable value for single and forking mode.  This is because the size of the requests did not make a huge difference between the speeds of the modes.  However, in throughput testing, we did see a difference between the modes with the different sizes.  Forking actually took longer than single because the overhead was higher than the actual speed gain from forking.  This is the difference between theoretical speed differences and actual speed differences.  Theoretically, forking should have been must faster but in reality, the overhead was too costly to make a difference.  With a bigger size than 1GB, it can be assumed that forking would be faster because the single and forking throughput for that size was the same.

Conclusion
----------
In this assignment, we practiced using low-level system calls related to sockets and networking.  We also learned about costs of forking and how theory can be different from practice depending on the resources.

Contributions
-------------
Kendyll:
	Makefile
	thor.py
	part of utils.c
	debugging
	testThor.sh which was modified later by Herman to separate latency and throughput tests
	README.md
	
John:

Herman:

Project 02 - README
===================

Members
-------

- Kendyll Kraus (kkraus1@nd.edu)
- John McGuinness (jmcguin1@nd.edu)
- Herman Tong (ktong@nd.edu)

Summary
-------

Our group was able to implement the browse request, CGI request, and the file 
request.  All of these options worked in both single and forking mode.  We were 
able to get everything working.  Work was divided amongst group members by each 
taking separate functions (or programs in the case of thor.py).  Once we had all
of the functions written, we all got together to debug program in its entirety.
There was some testing along the way as well to make sure that each function 
worked individually.

We went about measuring the average latency of the different types of requests 
by measuring the latency using 1, 2, and 4 processes on 100 requests to get a 
directory, static file, or CGI script.  We used thor.py to make all of these 
requests and get an average time.  Our shell script then took the average of all
of the processes' average time.  We went about measuring the average throughput 
by creating dummy directories 1KB, 1MB, and 1GB in size.  Our shell script 
divided the total average by the size of the directory to get the throughput.

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


----------Markdown Table for Latency Tests------------

| Mode    | File Type   | Number of Processes | Time  |
|---------|-------------|---------------------|-------|
| Single  | Directory   | 1                   | .0059 |
| Forking | Directory   | 1                   | .0061 |
| Single  | Directory   | 2                   | .0081 |
| Forking | Directory   | 2                   | .0075 |
| Single  | Directory   | 4                   | .0161 |
| Forking | Directory   | 4                   | .0147 |
| Single  | Static File | 1                   | .0060 |
| Forking | Static File | 1                   | .0061 |
| Single  | Static File | 2                   | .0081 |
| Forking | Static File | 2                   | .0074 |
| Single  | Static File | 4                   | .0160 |
| Forking | Static File | 4                   | .0143 |
| Single  | CGI Script  | 1                   | .0145 |
| Forking | CGI Script  | 1                   | .0146 |
| Single  | CGI Script  | 2                   | .0254 |
| Forking | CGI Script  | 2                   | .0161 |
| Single  | CGI Script  | 4                   | .0515 |
| Forking | CGI Script  | 4                   | .0344 |



Throughput
----------

Running thor.py with 4 processes and 2 requests

--------------Testing for Single --------------------
Testing 1KB access time with Single ...
Average time per request with 4 processes: 0.027409106493
Average throughput: 36484 bytes/second


Testing 1MB access time with Single ...
Average time per request 4 processes: 0.0340571701527
Average throughput: 29362392 bytes/second


Testing 1GB access time with Single ...
Average time per request 4 processes: 22.3494885266
Average throughput: 44743753 bytes/second


--------------Testing for Forking --------------------
Testing 1KB access time with Forking ...
Average time per request with 4 processes: 0.0248177945614
Average throughput: 40293 bytes/second


Testing 1MB access time with Forking ...
Average time per request 4 processes: 0.0284159779549
Average throughput: 35191468 bytes/second


Testing 1GB access time with Forking ...
Average time per request 4 processes: 10.5630527437
Average throughput: 94669602 bytes/second


--------Markdown Table for Throughput Tests--------

| Mode    | File Size | Average Throughput (GB/s) |
|---------|-----------|---------------------------|
| Single  | 1 KB      | .036                      |
| Forking | 1 KB      | .040                      |
| Single  | 1 MB      | 29.3                      |
| Forking | 1 MB      | 35.2                      |
| Single  | 1 GB      | 44.7                      |
| Forking | 1 GB      | 94.7                      |


Analysis
--------
Our results clearly display that forking to handle requests has both advantages
and disadvantages.  When running in forking mode, the parent process forks to
create a new child process to handle get requests.  This way, the parent can
focus on accepting requests while delegating the handling of these requests to
children (which gently kill themselves when they finish).  This process of 
copying the entire process over to create a child, so this does not always yield
the expeted benefits.  However, our results do clearly show that this parallel
processing does yield significant benefits.  As noted above in our markdown 
tables, all of our tests with forking show significant advantages over single
processing.  For instance our test with forking for the 1GB file yielded a
throughput over twice as high as the analogous single processing test.  The
only tests in which single processing performed better were the latency tests
with one process and (100 requests). This makes sense because much of the 
benefits of forking are lost when only using one process, so the overhead of 
forking worsened performance as explained above.

Conclusion
----------
In this assignment, we practiced using low-level system calls related to sockets
and networking.  We also learned about costs of forking and how theory can be 
different from practice depending on the resources.

Contributions
-------------

Kendyll:
        Makefile
        thor.py
        part of utils.c
        debugged forking.c
        general debugging
        testThor.sh which was modified later by Herman 
                        to separate latency and throughput tests
        README.md

John:
        fixed problem with thor.py
        part of utils.c
        general debugging
        did substantial amount of experimental testing
                and helped modify testLatency.sh and testThroughput.sh
        spidey.c
        helped write handler.c
        README.md

Herman:
        forking.c
        single.c
        testLatency.sh and testThroughput.sh
        helped write handler.c
        request.c
        part of utils.c
        socket.c
        general debugging
Project 02 - README
===================

Members
-------

- Kendyll Kraus (kkraus1@nd.edu)
- John McGuinness (jmcguin1@nd.edu)
- Herman Tong (ktong@nd.edu)

Summary
-------

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

Conclusion
----------

Contributions
-------------

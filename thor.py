#!/usr/bin/env python2.7

import multiprocessing
import itertools
import os
import requests
import sys
import time

# Globals
ARGUMENTS = sys.argv[1:]
PROCESSES = 1
REQUESTS  = 1
VERBOSE   = False
URL       = None

# Functions

def usage(status=0):
    print '''Usage: {} [-p PROCESSES -r REQUESTS -v] URL
    -h              Display help message
    -v              Display verbose output

    -p  PROCESSES   Number of processes to utilize (1)
    -r  REQUESTS    Number of requests per process (1)
    '''.format(os.path.basename(sys.argv[0]))
    sys.exit(status)



def do_request(pid):
<<<<<<< HEAD
    sumOfTime = 0
    for r in range(REQUESTS):
        start = time.time()
        request = requests.get(URL)
        end = time.time()
        timeT = end - start
        sumOfTime += timeT
        if VERBOSE:
            print r.text.rstrip()
        print("Process: {}, Request: {}, Elapsed Time: {}".format(pid, r, timeT))
    
    averageTime = sumOfTime/REQUESTS
    print("Process: {}, AVERAGE   , Elapsed Time: {}".format(pid, averageTime))
    
    return averageTime


# Main execution

if __name__ == '__main__':
    # Parse command line arguments
    while len(ARGUMENTS) and ARGUMENTS[0].startswith('-') and len(ARGUMENTS[0]) > 1:
        arg = ARGUMENTS.pop(0)
        if arg == '-h':
            usage(0)
        elif arg == '-v':
            VERBOSE = True
        elif arg == '-p':
            PROCESSES = int(ARGUMENTS.pop(0))
        elif arg == '-r':
            REQUESTS = int(ARGUMENTS.pop(0))
        else:
            usage(1)

    URL = ARGUMENTS.pop(0)


    # Create pool of workers and perform requests
    pool = multiprocessing.Pool(PROCESSES)
    results = pool.imap(do_request, range(PROCESSES))

    avg_time = 0
    for r in results:
        avg_time += r
    
    avg_time = avg_time / PROCESSES
    print("TOTAL AVERAGE ELAPSED TIME: {}".format(avg_time))
    

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:

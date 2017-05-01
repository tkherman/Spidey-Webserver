CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
TARGETS=	spidey

all:		$(TARGETS)

spidey: forking.o handler.o request.o single.o socket.o spidey.o utils.o
	@echo Linking spidey...
	@$(LD) $(LDFLAGS) -o $@ $^

test_request: test_request.o request.o socket.o utils.o
	@echo Linking test_request...
	@$(LD) $(LDFLAGS) -o $@ $^

forking.o: forking.c spidey.h
	@echo Compiling forking.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

handler.o: handler.c spidey.h
	@echo Compiling handler.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

request.o: request.c spidey.h
	@echo Compiling request.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

single.o: single.c spidey.h
	@echo Compiling single.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

socket.o: socket.c spidey.h
	@echo Compiling socket.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

spidey.o: spidey.c spidey.h
	@echo Compiling spidey.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

utils.o: utils.c spidey.h
	@echo Compiling utils.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

test_request.o: test_request.c spidey.h
	@echo Compiling test_request.o...
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o *.log *.input

.PHONY:		all clean

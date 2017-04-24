CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
TARGETS=	spidey

all:		$(TARGETS)

forking.o: forking.c spidey.h
	@echo Compiling forking.o...
	@$(CC) $(CFLAGS) -o $@ $<

handler.o: handler.c spidey.h
	@echo Compiling handler.o...
	@$(CC) $(CFLAGS) -o $@ $<

request.o: request.c spidey.h
	@echo Compiling request.o...
	@$(CC) $(CFLAGS) -o $@ $<

single.o: single.c spidey.h
	@echo Compiling single.o...
	@$(CC) $(CFLAGS) -o $@ $<

socket.o: socket.c spidey.h
	@echo Compiling socket.o...
	@$(CC) $(CFLAGS) -o $@ $<

spidey.o: spidey.c spidey.h
	@echo Compiling spidey.o...
	@$(CC) $(CFLAGS) -o $@ $<

utils.o: utils.c spidey.h
	@echo Compiling utils.o...
	@$(CC) $(CFLAGS) -o $@ $<

spidey: forking.o handler.o request.o single.o socket.o spidey.o utils.o
	@echo Linking spidey...
	@$(LD) $(LDFLAGS) -o $@ $^
	


clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o *.log *.input

.PHONY:		all clean

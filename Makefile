all: libfdr.a strsort strrsort1 strrsort2 strusort strisort nsort nsort2 nsort3 perfTesting

CC=gcc -m64
CFLAGS = -g -std=gnu18 
OBJS = dllist.o fields.o jval.o jrb.o
LIBS = -lfdr -L./

libfdr.a: $(OBJS)
	ar ru libfdr.a $(OBJS)
	ranlib libfdr.a 

%.o:%.c
	${CC} -c ${CFLAGS} $< -o $@

strsort: strsort.o
	${CC} -o $@ $^ ${LIBS}

strrsort1: strrsort1.o
	${CC} -o $@ $^ ${LIBS}

strrsort2: strrsort2.o
	${CC} -o $@ $^ ${LIBS}

strusort: strusort.o
	${CC} -o $@ $^ ${LIBS}

strisort: strisort.o
	${CC} -o $@ $^ ${LIBS}

nsort: nsort.o
	${CC} -o $@ $^ ${LIBS}

perfTesting: perfTesting.o
	${CC} -o $@ $^ ${LIBS}

nsort2: nsort2.o
	${CC} -o $@ $^ ${LIBS}

nsort3: nsort3.o
	${CC} -o $@ $^ ${LIBS}

clean:
	rm -f core *.o libfdr.a

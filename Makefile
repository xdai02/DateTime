CC=gcc
CFLAGS=-std=c89 -pedantic -Wall
LDFLAGS=
AR=ar
LIBNAME=libdatetime.a
LIBNAME_SHARED=libdatetime.so

all: demo test_datetime

demo: demo.o libdatetime.a
	$(CC) $(LDFLAGS) -o $@ $^

test_datetime: test_datetime.o libdatetime.a
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

libdatetime.a: datetime.o
	$(AR) rcs $@ $^

libdatetime.so: datetime.o
	$(CC) -shared -o $@ $^

clean:
	rm -f *.o demo test_datetime $(LIBNAME) $(LIBNAME_SHARED)

.PHONY: all clean

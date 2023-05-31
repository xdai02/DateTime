CC=gcc
CFLAGS_C89=-std=c89 -pedantic -Wall
CFLAGS_C99=-std=c99 -pedantic -Wall
LDFLAGS=
AR=ar
LIBNAME=libdatetime.a
LIBNAME_SHARED=libdatetime.so

all: demo test_datetime

demo: demo.o libdatetime.a
	$(CC) $(LDFLAGS) -o $@ $^

test_datetime: test_datetime.o libdatetime.a
	$(CC) $(LDFLAGS) -o $@ $^

demo.o: demo.c
	$(CC) $(CFLAGS_C99) -c $<

test_datetime.o: test_datetime.c
	$(CC) $(CFLAGS_C89) -c $<

datetime.o: datetime.c
	$(CC) $(CFLAGS_C89) -c $<  # Assuming datetime.c also needs to be compiled with C89

libdatetime.a: datetime.o
	$(AR) rcs $@ $^

libdatetime.so: datetime.o
	$(CC) -shared -o $@ $^

clean:
	rm -f *.o demo test_datetime $(LIBNAME) $(LIBNAME_SHARED)

.PHONY: all clean

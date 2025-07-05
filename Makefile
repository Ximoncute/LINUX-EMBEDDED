CC = gcc
CFLAGS = -Wall -fPIC
AR = ar rcs

STATIC_LIB = libstrutils.a
SHARED_LIB = libstrutils.so
OBJS = strutils.o

.PHONY: all static shared clean

all: static shared

# === Static ===
static: $(STATIC_LIB) main_static

$(STATIC_LIB): $(OBJS)
	$(AR) $@ $^

main_static: main.c $(STATIC_LIB)
	$(CC) main.c -L. -lstrutils -o $@

# === Shared ===
shared: $(SHARED_LIB) main_shared

$(SHARED_LIB): $(OBJS)
	$(CC) -shared -o $@ $^

main_shared: main.c $(SHARED_LIB)
	$(CC) main.c -L. -lstrutils -o $@ -Wl,-rpath,.

# === Object files ===
strutils.o: strutils.c strutils.h
	$(CC) $(CFLAGS) -c strutils.c

# === Clean ===
clean:
	rm -f *.o *.a *.so main_static main_shared

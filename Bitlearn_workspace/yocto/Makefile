#compiler flags:
#-g adds debugging
#-Wall turns on most
#run: make DESTDIR=/usr/bin
CFLAGS = -g -Wall -DUSE_SYSCALL

TARGET = capp

all: $(TARGET)

$(TARGET): hello.c
	${CC} $(CFLAGS) ${LDFLAGS} -o $(TARGET) hello.c

install:
	install -d $(DESTDIR)
	install -m 0755 $(TARGET) $(DESTDIR)

clean:
	rm -f $(TARGET)

uninstall:
	rm $(DESTDIR)/$(TARGET)


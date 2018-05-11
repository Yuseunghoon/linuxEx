OBJECTS = upper.o\
		  useupper.o
SRCS = $(OBJECTS:.o=.c)
TARGET = upper useupper
CC = gcc

all : $(TARGET)

upper : upper.c
	$(CC) -o $@ $<

useupper  : useupper.c
	$(CC) -o $@ $<

clean :
	$(RM) $(OBJECTS) $(TARGET)

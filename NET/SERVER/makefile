CC = gcc

CFLAGS = -Wall -Wextra -I./json

SRCS = main.c json/json_builder.c

OBJS = $(SRCS)

TARGET = server

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)


clean:
	rm -f $(TARGET) $(OBJS)
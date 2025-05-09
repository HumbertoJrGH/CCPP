CC = gcc
CFLAGS = -Wall -Wextra -I./json -I./server -I./router -I./controllers

# ARQUIVOS-FONTE
SRCS = \
    main.c \
    json/json_builder.c \
    server/server.c \
    router/router.c \
    controllers/status_controller.c \
    controllers/shutdown_controller.c

# OBJETOS COMPILADOS
OBJS = $(SRCS:.c=.o)

# NOME DO EXECUTÁVEL FINAL
TARGET = ccppserver

# REGRA PADRÃO
all: $(TARGET)

# LINK FINAL
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# COMPILAÇÃO INDIVIDUAL
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# LIMPAR BINÁRIOS E OBJETOS
clean:
	rm -f $(TARGET) $(OBJS)

CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm
TARGET = sistema_estacoes

OBJS = main.o estacao.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: main.c estacao.h
	$(CC) $(CFLAGS) -c main.c

estacao.o: estacao.c estacao.h
	$(CC) $(CFLAGS) -c estacao.c

clean:
	rm -f *.o $(TARGET) $(TARGET).exe

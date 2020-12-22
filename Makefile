# GRR20190363 Luan Machado Bernardt

CC = gcc
CFLAGS = -Wall

# Programas a serem compilados
BINARIES = wavcat wavecho wavinfo wavmix wavnorm wavrev wavvol wavwide

all: $(BINARIES)

# Regra para compilar um programa
$(BINARIES): %: %.o wavlib.o
	$(CC) $(CFLAGS) $^ -o $@

# Regra para criar os arquivos objeto
%.o: %.c wavlib.h
	$(CC) $(CFLAGS) -c $<

clean:
	-rm -f *.o

purge: 
	-rm -f $(BINARIES)

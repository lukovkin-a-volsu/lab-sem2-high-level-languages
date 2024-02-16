PROG = main
CC = cc 
SRCS = main.c functions.c
OBJS = $(SRCS:.c=.o)
FLS = phone_book.txt phone_book_binary.txt

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

clean:
	rm -f $(PROG) $(OBJS) $(FLS)

.c.o : functions.h ; $(CC) -c $*.c
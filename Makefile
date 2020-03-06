CC   = gcc
OBJ=160101003.o
CFLAGS = -c
SOURCES= 160101003.c
BIN  = yalphone
RM = rm -f

all: obj

derle:
	$(CC) $(CFLAGS) $(SOURCES)

obj: derle
	$(CC) $(OBJ) -o $(BIN)

calistir: derle
	./$(BIN) -a add "Kutay Goren" "5467689966" "Bilgisayar"
	./$(BIN) -a update "15" "phone" "2265467896"
	./$(BIN) -a update "12" "name" "Kutay"
	./$(BIN) -a update "26" "department" "Bilgisayar"
	./$(BIN) -a delete "26"
	./$(BIN) -u filter "B"
	./$(BIN) -u filter "5863"
	./$(BIN) -u


val: derle
	valgrind --leak-check=yes ./$(BIN) -a add "Kutay" "5467689966" "Bilgisayar"
	valgrind --leak-check=yes ./$(BIN) -a update "15" "phone" "2265467896"
	valgrind --leak-check=yes ./$(BIN) -a update "12" "name" "Kutay"
	valgrind --leak-check=yes ./$(BIN) -a update "26" "department" "Bilgisayar"
	valgrind --leak-check=yes ./$(BIN) -a delete "26"
	valgrind --leak-check=yes ./$(BIN) -u filter "B"
	valgrind --leak-check=yes ./$(BIN) -u filter "5863"
	valgrind --leak-check=yes ./$(BIN) -u
clean:
	${RM} $(OBJ) $(BIN)

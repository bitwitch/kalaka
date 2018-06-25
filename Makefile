CC = g++ 
CFLAGS = -g -Wall

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = -framework SDL2 -framework SDL2_image

kalaka: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o kalaka
run: kalaka
	./kalaka
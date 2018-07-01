CC = clang++
CFLAGS = -g -Wall
LDFLAGS = -framework SDL2 -framework SDL2_image -framework SDL2_ttf

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

kalaka: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o kalaka

run: kalaka
	./kalaka
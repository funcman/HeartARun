CFLAGS?=-Os -Wall

all: HeartARun

HeartARun: main.o menu_scene.o credit_scene.o game_scene.o
	$(CC) *.o -o HeartARun `sdl-config --cflags --libs` -framework OpenGl -lstdc++ -lbsgl

main.o: src/main.cpp src/scene.h src/menu_scene.h src/credit_scene.h src/game_scene.h
	$(CC) src/main.cpp -c

menu_scene.o: src/menu_scene.cpp src/menu_scene.h src/credit_scene.h src/game_scene.h
	$(CC) src/menu_scene.cpp -c

credit_scene.o: src/credit_scene.cpp src/credit_scene.h src/menu_scene.h
	$(CC) src/credit_scene.cpp -c

game_scene.o: src/game_scene.cpp src/game_scene.h
	$(CC) src/game_scene.cpp -c

clean:
	rm -f *.o
	rm -f HeartARun

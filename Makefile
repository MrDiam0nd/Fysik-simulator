default:
	g++ -o main.exe main.cpp matte.cpp matte.h objekt.cpp objekt.h -s -static -O2 -Wall -IC:\raylib\raylib\src -LC:\raylib\raylib\src -lraylib -lgdi32 -lwinmm
	.\main.exe

exp:
	g++ -o experiment.exe experiment.cpp matte.cpp objekt.cpp matte.h objekt.h -s -static -O2 -Wall -IC:\raylib\raylib\src -LC:\raylib\raylib\src -lraylib -lgdi32 -lwinmm
	.\experiment.exe

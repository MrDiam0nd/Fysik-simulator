default:
	g++ -o main.exe *.cpp headers/* scenes/* -s -static -O2 -Wall -IC:\raylib\raylib\src -LC:\raylib\raylib\src -Iheaders -lraylib -lgdi32 -lwinmm
	.\main.exe
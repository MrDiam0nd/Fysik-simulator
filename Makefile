default:
	g++ -o main.exe main.cpp -s -static -O2 -Wall -IC:\raylib\raylib\src -Iexternal -LC:\raylib\raylib\src -Lexternal -lraylib -lopengl32 -lgdi32 -lwinmm
	.\main.exe
notepad:
	g++ -o main.exe main.cpp -s -static -O2 -Wall -IC:\raylib\raylib\src -LC:\raylib\raylib\src -lraylib -lgdi32 -lwinmm
	.\main.exe
# C:\raylib\raylib\src\raylib.rc.data
#   gcc -o main.exe main.c -s -static -O2 -std=c99 -Wall -IC:\raylib\raylib\src -Iexternal -DPLATFORM_DESKTOP -LC:\raylib\raylib\src -Lexternal -lraylib -lopengl32 -lgdi32 -lwinmm
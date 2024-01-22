
LIB = D:\code\c_\Clashed\lib\libSDL2.a D:\code\c_\Clashed\lib\libSDL2main.a D:\code\c_\Clashed\lib\libSDL2_ttf.a D:\code\c_\Clashed\lib\libSDL2_mixer.a D:\code\c_\Clashed\lib\libSDL2_image.a 
DLL =  D:\lib\SDL2.dll D:\lib\SDL2_image.dll D:\lib\SDL2_mixer.dll D:\lib\SDL2_ttf.dll

main.exe: src/*
	gcc -o main.exe -lmingw32 $(LIB) $(DLL) -I include $^
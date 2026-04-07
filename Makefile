COMPILADOR=g++
ARQUIVOS=main.cpp snake.cpp
FLAGS=-Wall
BUILD=executavel

all:
		$(COMPILADOR) $(ARQUIVOS) -o $(BUILD) $(FLAGS) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:$(BUILD)
		rm -f a.out && rm executavel

exec:$(BUILD)

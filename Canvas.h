/*
* Canvas.h
* Coco07
* 2020.8.27
*/

#ifndef CANVAS_H
#define CANVAS_H

#include <windows.h>
#include <ctime>
#include <stdio.h>

#define MAP_X 20
#define MAP_Y 40
#define SNAKE_CHAR '*'
#define WALL_CHAR '#'
#define SPACE_CHAR ' '
#define SUPRISE_CHAR_L '1'
#define SUPRISE_CHAR_H '5'

class Canvas{
 public:
 	char page[MAP_X][MAP_Y];
 	
 	bool draw();
 	void init();
 	char *operator[] (const int i) {return page[i];}
 	
 private:
	char pageOUT[MAP_X][MAP_Y];
};

bool Set_Cursor(const int x, const int y);

void Canvas::init(){
	srand(time(NULL));
	for(int i = 0; i < MAP_X; ++i){
		for(int j = 0; j < MAP_Y; ++j){
			if(i == 0 || j == 0 || i == MAP_X-1 || j == MAP_Y-1) page[i][j] = WALL_CHAR;
			else page[i][j] = SPACE_CHAR;
		}
	}
}

bool Canvas::draw(){
	for(int i = 0; i < MAP_X; ++i){
		for(int j = 0; j < MAP_Y; ++j){
			if(pageOUT[i][j] != page[i][j]){
				pageOUT[i][j] = page[i][j];
				Set_Cursor(j, i);
				putchar(pageOUT[i][j]);
			}
		}
	}
}

COORD coord;
bool Set_Cursor(const int x, const int y){
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#endif

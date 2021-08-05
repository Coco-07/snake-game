/*
* Snake.cpp
* Coco07
* 2020.8.28 
*/

#include <Windows.h>
#include <stdio.h>
#include "Snake.h"
#include "Canvas.h"

#define SNAKE_INIT_X 10
#define SNAKE_INIT_Y 10

using namespace std;

Snake snake(SNAKE_INIT_X, SNAKE_INIT_Y);

int Get_Message(){
	if(GetAsyncKeyState(VK_SPACE)) return -1;
	else if(GetAsyncKeyState(VK_LEFT)) return 1;
	else if(GetAsyncKeyState(VK_RIGHT)) return 2;
	else if(GetAsyncKeyState(VK_UP)) return 3;
	else if(GetAsyncKeyState(VK_DOWN)) return 4;
	return 0;
}

const int PATH_X[4] = {0, 0, -1, 1}, PATH_Y[4] = {-1, 1, 0, 0};
bool mirr(int msg){
	if(msg < 1) goto ret;
	
	snake.next = snake.body.back();
	snake.next.first += PATH_X[msg-1];
	snake.next.second += PATH_Y[msg-1];
	
ret:return snake.move();
}

void SetConsoleCursor(const bool bo){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = bo;
	SetConsoleCursorInfo(handle, &CursorInfo);
}

void welcome(){
	system("cls");
	system("mode con:cols=50 lines=25");
	system("title Snake1.1");
	system("color 0f");
	
	printf("Copyright Coco07\n");
	printf("https://www.coco07.com/\n\n");
	for(int i = 0; i < 50; ++i){
		putchar('.');
		Sleep(20);
	}
	Sleep(500);
	putchar('\n');
	system("pause");
	system("cls");
	
	SetConsoleCursor(0);
}

void game_over(){
	system("color 0c");
	Sleep(2000);
	system("cls");
	SetConsoleCursor(1);
	Set_Cursor(0, 0);
	printf("GAME OVER\n\n");
	Sleep(500);
}

void DEBUG(){
	Set_Cursor(0, 24);
	printf("%d %d %d  ", snake.body.front().first, snake.body.front().second, snake.body.size());
}

int main(){
	welcome();
	while(1){
		DEBUG();
		int msg = Get_Message();
		if(msg == -1){	//wait
			system("color 0a");
			while(Get_Message() == -1){}
			system("color 0f");
		}
		else if(!mirr(msg)){
			game_over();
			goto program_exit;
		}
		snake.canvas.draw();
		Sleep(120);
	}
	
program_exit:
	system("pause");
	return 0;
}
/*
* Snake.h
* Coco07
* 2020.8.27
*/

#ifndef SNAKE_H
#define SNAKE_H

#include <queue>
#include <utility>

#include "Canvas.h"

#define SNAKE_CHAR '*'
#define WALL_CHAR '#'
#define SPACE_CHAR ' '
#define SUPRISE_CHAR_L '1'
#define SUPRISE_CHAR_H '5'

using std::pair;
using std::queue;

class Snake{
 public:
 	queue<pair<int, int> > body;
 	pair<int, int> next;
 	Canvas canvas;
 	
 	Snake(const int x, const int y);
	bool move();
	char Make_Suprise();
	
 private:
	int tail_size;
};

Snake::Snake(const int x, const int y){
 	while(!body.empty()) body.pop();
	body.push((pair<int, int>){x, y});
	next = (pair<int, int>){x, y};
	tail_size = 0;
	canvas.init();
	canvas[x+1][y+1] = SNAKE_CHAR;
	Make_Suprise();
}

bool Snake::move(){
	int nextX = next.first, nextY = next.second, 
		headX = body.back().first, headY = body.back().second,
		tailX = body.front().first, tailY = body.front().second;
	
	if(canvas[nextX+1][nextY+1] >= SUPRISE_CHAR_L && canvas[nextX+1][nextY+1] <= SUPRISE_CHAR_H){
		tail_size += (int)canvas[nextX+1][nextY+1]-'0';
		Make_Suprise();
	}
	else if(canvas[nextX+1][nextY+1] != SPACE_CHAR && next != body.back()){
		return 0; //game over
	}
	
	body.push(next);
	canvas[nextX+1][nextY+1] = SNAKE_CHAR;
	
	if(tail_size){
		--tail_size;
	}
	else{
		body.pop();
		canvas[tailX+1][tailY+1] = SPACE_CHAR;
	}
	
	if(nextX == headX){
		next.first = nextX;
		if(headY > nextY) next.second = nextY-1;
		else next.second = nextY+1;
	}
	else{
		if(headX > nextX) next.first = nextX-1;
		else next.first = nextX+1;
		next.second = nextY;
	}
	
	return 1;
}

pair<int, int> random(){return (pair<int, int>){rand()%(MAP_X+1), rand()%(MAP_Y+1)};}

char Snake::Make_Suprise(){
con:pair<int, int> where = random();
	if(canvas[where.first][where.second] != SPACE_CHAR) goto con; //maybe bug
	char p = SUPRISE_CHAR_L+rand()%(SUPRISE_CHAR_H-SUPRISE_CHAR_L+1);
	canvas[where.first][where.second] = p;
	return p;
}

#endif

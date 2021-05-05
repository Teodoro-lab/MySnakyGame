#include <stdio.h>	//printf
#include <conio.h>	//getch
#include <stdlib.h>	//rand //malloc
#include <windows.h> //sleep
#include <time.h>    //time

#define table_len 15
#define snakePiece (char)220
#define snakeFood (char)169

char table[table_len][table_len];
char snake_direction = 'w';

void fill_table(){
	for(int i = 0; i < table_len; i++){
		for(int j = 0; j < table_len; j++){
			if(i == 0 || i == table_len - 1)
				table[i][j] = '-';
			else if(j == 0 || j == table_len - 1)
				table[i][j] = '|';
			else
				table[i][j] = ' ';
		}
	}
}

void print_table(){
	for(int i = 0; i < table_len; i++){
		for(int j = 0; j < table_len; j++){
			printf("%c", table[i][j]);
		}
		printf("\n");
	}
}

struct snake_node{
	int x, y;
	char body = snakePiece;
	struct snake_node * behindNode = NULL;
}; struct snake_node head;

struct Fruit{
	int x, y;
	char fruit = snakeFood;
}; struct Fruit fruit;

void position_fruit(){
	int x, y;
	srand(time(0));
	do {
		x = (rand() % table_len-1) + 1;
		y = (rand() % table_len-1) + 1;
	} while(table[y][x] == snakePiece);
	fruit.x = x; fruit.y = y;
	table[y][x] = fruit.fruit;
}

void position_snake(){
	struct snake_node * aux = &head;
	while (true){
		table[(*aux).y][(*aux).x] = snakePiece;
		if ((*aux).behindNode == NULL)
			break;
		aux = (*aux).behindNode;
	}
}
	
void snake_grow(){
	struct snake_node * aux  = &head;
	while (true){
		if ((*aux).behindNode == NULL){
			(*aux).behindNode = (struct snake_node *)(malloc(sizeof(struct snake_node)));
			switch(snake_direction){
				case 'w':
					(*(*aux).behindNode).x = (*aux).x;
					(*(*aux).behindNode).y = (*aux).y + 1;
					break;
				case 's':
					(*(*aux).behindNode).x = (*aux).x;
					(*(*aux).behindNode).y = (*aux).y - 1;
					break;
				case 'd':
					(*(*aux).behindNode).x = (*aux).x - 1;
					(*(*aux).behindNode).y = (*aux).y;
					break;
				case 'a':
					(*(*aux).behindNode).x = (*aux).x + 1;
					(*(*aux).behindNode).y = (*aux).y;
					break;
			}
			(*(*aux).behindNode).behindNode = NULL;
			return;
		}
		aux = (*aux).behindNode;
	}
}

void snake_food_cheker(){
	if (head.x == fruit.x && head.y == fruit.y){
		position_fruit();
		snake_grow();
	}
}

void snake_body_mov(){
	struct snake_node * aux = &head;
	int x_g = (*aux).x, y_g = (*aux).y;
	int x_b, y_b;
	
	while (true){
		if ((*aux).behindNode == NULL){
			table[(*aux).y][(*aux).x] = ' ';
			(*aux).x = x_g;
			(*aux).y = y_g;
			break;
		}
		x_b = x_g;
		y_b = y_g;
		(*aux).x = x_g;
		(*aux).y = y_g;
		x_g = x_b; 
		y_g = y_b;
		
		aux = (*aux).behindNode;
	}	
}

void movement(){
	fflush(stdin);
	switch(getch()) {
      case 'w':
     		snake_direction = 'w';
     		table[head.y][head.x] = ' ';
     		snake_body_mov();
         head.y--;
         break;
     case 's':
     		snake_direction = 's';
     		table[head.y][head.x] = ' ';
     		snake_body_mov();
         head.y++;
         break;
     case 'd':
     		snake_direction = 'd';
     		table[head.y][head.x] = ' ';
     		snake_body_mov();
         head.x++;
         break;
     case 'a':
     		snake_direction = 'a';
     		table[head.y][head.x] = ' ';
     		snake_body_mov();
         head.x--;
         break;	
	}	
}

int main(){
	fill_table();
	head.x = head.y = table_len/2;
	position_fruit();
	while (true){
		print_table();
		movement();
		position_snake();
		snake_food_cheker();
		position_snake();
		system("cls");
	}
}


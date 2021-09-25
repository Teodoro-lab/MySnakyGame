#include <stdio.h>	//printf
#include <conio.h>	//getch
#include <stdlib.h>	//rand //malloc
#include <windows.h> //sleep
#include <time.h>    //time

#define table_len 20
#define snakePiece (char)220
#define snakeFood (char)169

char table[table_len][table_len];
char snake_direction = 'w';

void fill_table( void ){
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

void print_table( void ){
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

void position_fruit( void ){
	int x = 1, y = 1;
	srand(time(0));
	do {
		x += (rand() % (table_len-2));
		y += (rand() % (table_len-2));
	} while(table[y][x] == snakePiece);
	fruit.x = x; fruit.y = y;
	table[y][x] = fruit.fruit;
}

void position_snake( void ){
	struct snake_node * aux = &head;
	while (true){
		table[(*aux).y][(*aux).x] = snakePiece;
		if ((*aux).behindNode == NULL)
			break;
		aux = (*aux).behindNode;
	}
}
	
void snake_grow( void ){
	struct snake_node * aux  = &head;
	while (true){
		if ((*aux).behindNode == NULL){
			(*aux).behindNode = (struct snake_node *)(malloc(sizeof(struct snake_node)));
			switch(snake_direction){
				case 'w':
					aux->behindNode->x = aux->x;
					aux->behindNode->y = aux->y + 1;
					break;
				case 's':
					aux->behindNode->x = aux->x;
					aux->behindNode->y = aux->y - 1;
					break;
				case 'd':
					aux->behindNode->x = aux->x - 1;
					aux->behindNode->y = aux->y;
					break;
				case 'a':
					aux->behindNode->x = aux->x + 1;
					aux->behindNode->y = aux->y;
					break;
			}
			(*(*aux).behindNode).behindNode = NULL;
			return;
		}
		aux = (*aux).behindNode;
	}
}

void snake_food_cheker( void ){
	if (head.x == fruit.x && head.y == fruit.y){
		position_fruit();
		snake_grow();
	}
}

void snake_body_mov( void ){
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
		x_b = (*aux).x;
		y_b = (*aux).y;
		(*aux).x = x_g;
		(*aux).y = y_g;
		x_g = x_b; 
		y_g = y_b;
		
		aux = (*aux).behindNode;
	}	
}

void movement( void ){
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

bool crash_against_walls( void ){
	if((head.x == 0 || head.x == table_len-1) || (head.y == 0 || head.y == table_len-1)){
		return true;
	}
	return false;
}

bool you_eat_yourself( void ){
	if (head.behindNode == NULL)
			return false;
	struct snake_node * aux = head.behindNode;
	while (true){
		if ((*aux).behindNode == NULL)
			return false;
		else if(head.x == (*aux).x && head.y == (*aux).y)
			return true;
		aux = (*aux).behindNode;
	}
}

int main(){
	fill_table();
	head.x = head.y = table_len/2;
	position_fruit();
	fflush(stdin);
	printf("Usa w,s,d,a para mover la serpiente\nVerifica que no estén en mayusculas!\n");
	printf("Presiona enter para continuar\n");
	getchar();
	fflush(stdin);
	while (true){
		print_table();
		printf("Presiona cualquier tecla y comienza a moverte!\n");
		movement();
		position_snake();
		snake_food_cheker();
		system("cls");
		if (crash_against_walls()){
			printf("You loose!!\n");
			printf("Don't crash against walls!!");
			break;
		}
		else if(you_eat_yourself()){
			printf("You loose!!\n");
			printf("Don't eat yourself!!");
			break;
		}
	}
	printf("Presione enter para salir del programa!");
	getchar();
}

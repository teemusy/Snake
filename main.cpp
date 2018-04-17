/*compile with -lncurses option*/

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <unistd.h>

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */
//determines the size of the map
#define ROWS 20
#define COLUMNS 20
#define SNAKE_MAX_LEN 5

void map_filler (struct cell_info map[ROWS][COLUMNS]);
void draw_static (WINDOW *local_win);
void draw_creatures (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win);
void sleep_for_seconds (float s);
void array_shift(int arr[], int len, int dir);
void console_message (WINDOW *local_win, char *message);
//array_shift(arr, sizeof(arr)/sizeof(0), 1);
void array_shift(int arr[2][SNAKE_MAX_LEN], int len, int dir);

int random_value_filler ();

struct cell_info {
	   int current_status;
	   //int future_status;
	   int snake_head;
	   int snake_body;
};

class Snake{
	private:
		int i;
		int snake_length;
		int snake_head_var[2];
		int snake_old_head_var[2];	
		int last_dir;
		int snake_location[2][SNAKE_MAX_LEN];
	
	public:
		void set_head_location (struct cell_info map[ROWS][COLUMNS], int loc_x, int loc_y);
		void move_snake (struct cell_info map[ROWS][COLUMNS]);
};

void Snake::set_head_location (struct cell_info map[ROWS][COLUMNS], int loc_x, int loc_y){
	snake_head_var[0] = loc_y;
	snake_head_var[1] = loc_x;
	map[snake_head_var[0]][snake_head_var[1]].current_status == 0;
	last_dir = 0;
	snake_length = 0;
	
	for (i = 0; i < SNAKE_MAX_LEN; i++){
		snake_location[0][i] = 0;
		snake_location[1][i] = 0;
		
	}
	
}

void Snake::move_snake (struct cell_info map[ROWS][COLUMNS]){
	int direction, legal_direction;
	
	snake_old_head_var[0] = snake_head_var[0];
	snake_old_head_var[1] = snake_head_var[1];
	//check for legal direction
	do{
		direction = random_value_filler ();
		legal_direction = 1;

		switch (direction){
			case 2:
				snake_head_var[0]++;
				last_dir = 8;
				mvprintw(40, 40, "2");
				break;		
			
			case 4:
				snake_head_var[1]--;
				last_dir = 6;
				mvprintw(40, 40, "4");
				break;		
			
			case 6:
				snake_head_var[1]++;
				last_dir = 4;
				mvprintw(40, 40, "6");
				break;		
			
			case 8:
				snake_head_var[0]--;
				last_dir = 2;
				mvprintw(40, 40, "8");
				break;
			default:
				break;
		
		}
		
		if (map[snake_head_var[0]][snake_head_var[1]].snake_body == 1){
			snake_head_var[0] = snake_old_head_var[0];
			snake_head_var[1] = snake_old_head_var[1];
			legal_direction = 0;
		}
		
		if(((snake_head_var[1] == COLUMNS && direction == 6) ||
			(snake_head_var[1] < 0 && direction == 4) ||
			(snake_head_var[0] == ROWS && direction == 2) ||
			(snake_head_var[0] < 0 && direction == 8))){
				snake_head_var[0] = snake_old_head_var[0];
				snake_head_var[1] = snake_old_head_var[1];
				legal_direction = 0;
		}
	}
	while(!legal_direction);
	
	if(map[snake_head_var[0]][snake_head_var[1]].current_status == 1){
		map[snake_head_var[0]][snake_head_var[1]].current_status = 0;
		
		//if there's existing tail
		if (snake_length > 0 && snake_length < SNAKE_MAX_LEN){
			
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
			map[snake_location[0][snake_length]][snake_location[1][snake_length]].snake_body = 0;
			array_shift(snake_location, SNAKE_MAX_LEN, 1);
			snake_location[0][0] = snake_old_head_var[0];
			snake_location[1][0] = snake_old_head_var[1];
			snake_length++;
			mvprintw(41, 40, "tail exists and ate creature");
			
		}
		else if (snake_length >= SNAKE_MAX_LEN){

			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
			map[snake_location[0][SNAKE_MAX_LEN-1]][snake_location[1][SNAKE_MAX_LEN-1]].snake_body = 0;
			array_shift(snake_location, SNAKE_MAX_LEN, 1);
			snake_location[0][0] = snake_old_head_var[0];
			snake_location[1][0] = snake_old_head_var[1];
			
			mvprintw(41, 40, "tail exists and max length and ate creature");
		}
		
		else {
			
			
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
			snake_location[0][0] = snake_old_head_var[0];
			snake_location[1][0] = snake_old_head_var[1];
			snake_length++;
			mvprintw(41, 40, "no tail and ate creature");
		}
		
		
		
	}
	
	//if there's no life in cell
	else {
		if (snake_length > 0 && snake_length < SNAKE_MAX_LEN){
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
			map[snake_location[0][snake_length-1]][snake_location[1][snake_length-1]].snake_body = 0;
			array_shift(snake_location, SNAKE_MAX_LEN, 1);
			snake_location[0][0] = snake_old_head_var[0];
			snake_location[1][0] = snake_old_head_var[1];
			mvprintw(41, 40, "tail and no creature");
		}
		else if (snake_length >= SNAKE_MAX_LEN){
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
			map[snake_location[0][SNAKE_MAX_LEN-1]][snake_location[1][SNAKE_MAX_LEN-1]].snake_body = 0;
			array_shift(snake_location, SNAKE_MAX_LEN, 1);
			snake_location[0][0] = snake_old_head_var[0];
			snake_location[1][0] = snake_old_head_var[1];
			
			

			mvprintw(41, 40, "tail exists and max length and no creature");
		}
		
		else{
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
			
			
			mvprintw(41, 40, "no tail and no creature");
		}
	}
	mvprintw(42, 40, "Length %d ", snake_length);
	mvprintw(43, 40, "Snake row: %d column %d", snake_head_var[0], snake_head_var[1]);
}

int main() {
	srand( time(NULL) ); //Randomize seed initialization for map_fill
	//snake init
	Snake testi;
	struct cell_info new_map[ROWS][COLUMNS];
	map_filler (new_map);
	initscr(); //ncurses init
	curs_set(0);
	start_color();
	WINDOW* map_window = newwin(ROWS, COLUMNS, 0, 0);
	WINDOW* console_window = newwin(30, 30, 30, 30);
	//draw_static (map_window); 
	testi.set_head_location(new_map, 10,10);
	char testip[] = "xyz";
	
	//MAIN LOOP
	while(true){
		testi.move_snake(new_map);
		draw_creatures (new_map, map_window);
		//draw_static (map_window); 
		
		refresh();
		wrefresh(map_window);
		wrefresh(console_window);
		//console_message (console_window, testip);
		sleep_for_seconds(0.1);
		werase(map_window);
	}
	endwin();
	return 0;	
}/* end of main */

void array_shift(int arr[2][SNAKE_MAX_LEN], int len, int dir){
	int i, temp_array[2][100], temp0, temp1, last0, last1;

	switch(dir){
		case 1:
			last0 = arr[0][len-1];
			last1 = arr[1][len-1];
			for (i=0; i < len; i++){
				temp0 = arr[0][i];
				temp1 = arr[1][i];
				temp_array[0][i] = temp0;
				temp_array[1][i] = temp1;
			}
			
			for(i = 0; i < len; i++){
				if(i < len - 1){
					temp0 = temp_array[0][i];
					temp1 = temp_array[1][i];
					arr[0][i+1] = temp0;
					arr[1][i+1] = temp1;
				}
			}
			arr[0][0] = last0;
			arr[1][0] = last1;
			break;
		case -1:
			last0 = arr[0][0];
			last1 = arr[1][0];
			for (i=0; i < len; i++){
				temp0 = arr[0][i];
				temp1 = arr[1][i];
				temp_array[0][i] = temp0;
				temp_array[1][i] = temp1;
			}
			for(i = len; i > 0; i--){
				if(i > 0){
					temp0 = temp_array[0][i];
					temp1 = temp_array[1][i];
					arr[0][i-1] = temp0;
					arr[1][i-1] = temp1;
				}
			}
			arr[0][len-1] = last0;
			arr[1][len-1] = last1;
			break;
	}
}

void map_filler (struct cell_info map[ROWS][COLUMNS]){
	int i, j;
	
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			if (j % 2 == 0 && i % 2 == 0){
			map[i][j].current_status = 1;
			map[i][j].snake_head = 0;
			map[i][j].snake_body = 0;
			}
			else {
				
			map[i][j].current_status = 0;
			map[i][j].snake_head = 0;
			map[i][j].snake_body = 0;
			}
		}
	}
}

int random_value_filler (){
	int random_value;

	random_value = (rand() % 100) + 1;
	if (random_value < 25){
		random_value = 2;
	}	
	
	else if (random_value >= 25 && random_value < 50){
		random_value = 4;
	}	
	
	else if (random_value >= 50 && random_value < 75){
		random_value = 6;
	}
	else {
		random_value = 8;
	}
	return random_value;
}

void draw_creatures (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win){
	int i, j;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
		
	//draw creatures
	for(i = 0; i < ROWS; i++){
		
		for(j = 0; j < COLUMNS; j++){
			
			if (map[i][j].current_status == 1){
				wattron(local_win, COLOR_PAIR(1));
				mvwprintw(local_win, i, j, "@");
				wattroff(local_win, COLOR_PAIR(1));	
			}			
			if (map[i][j].snake_head == 1){
				wattron(local_win, COLOR_PAIR(2));
				mvwprintw(local_win, i, j, "X");
				wattroff(local_win, COLOR_PAIR(2));	
			}			
			
			if (map[i][j].snake_body == 1){
				wattron(local_win, COLOR_PAIR(2));
				mvwprintw(local_win, i, j, "I");
				wattroff(local_win, COLOR_PAIR(2));	
			}

			else if (map[i][j].current_status == 0 && map[i][j].snake_body == 0 && map[i][j].snake_head == 0){
				wattron(local_win, COLOR_PAIR(3));
				mvwprintw(local_win, i, j, ".");
				wattroff(local_win, COLOR_PAIR(3));	
			
			}
		}
	}
}

void console_message (WINDOW *local_win, char *message){
	int rows, char_count, max_rows, i;
	char old_message1[200], old_message2[200], old_message3[200], old_message4[200];
	
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	
	max_rows = 10;
	for (i = 1; i < max_rows; i++){
		wattron(local_win, COLOR_PAIR(1));
		mvwprintw(local_win, i, 1, "%s", message);
		wattroff(local_win, COLOR_PAIR(1));	
	}
}

void draw_static (WINDOW *local_win){
	int i;
	
	//declare color pairs
	init_pair(1, COLOR_BLUE, COLOR_YELLOW);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	
	//draw horizontal borders
	wattron(local_win, COLOR_PAIR(2));
	for(i = 0; i < COLUMNS + 2; i++){
		mvwprintw(local_win, 0, i, "#");
		mvwprintw(local_win, ROWS + 1, i, "#");
	}
	//draw vertical borders
	for(i = 0; i < ROWS + 2; i++){
		mvwprintw(local_win, i, 0, "#");
		mvwprintw(local_win, i, COLUMNS + 1, "#");
	}
	wattroff(local_win, COLOR_PAIR(2));
}

void sleep_for_seconds (float s){ 
	int sec = s*1000000; 
	usleep(sec); 
} 

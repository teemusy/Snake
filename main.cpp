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

int random_value_filler ();

struct cell_info {
	   int current_status;
	   int future_status;
	   int snake_head;
	   int snake_body;
};






class Snake{
	private:
		int snake_length;
		int snake_head_var[2];
		int snake_tail_var[2];	
		int snake_old_head_var[2];	
		int last_dir;
	
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
}

void Snake::move_snake (struct cell_info map[ROWS][COLUMNS]){
	int direction, legal_direction;
	
	snake_old_head_var[0] = snake_head_var[0];
	snake_old_head_var[1] = snake_head_var[1];
	
	//check for legal direction
	do{
		direction = random_value_filler ();
		legal_direction = 1;
		if(((snake_head_var[1] == COLUMNS-1 && direction == 6) ||
			(snake_head_var[1] == 0 && direction == 4) ||
			(snake_head_var[0] == ROWS-1 && direction == 2) ||
			(snake_head_var[0] == 0 && direction == 8)) && last_dir != direction){
				
				legal_direction = 0;
		}
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
	}
	
	while(!legal_direction);
	

	
	if(map[snake_head_var[0]][snake_head_var[1]].current_status == 1){
		
		map[snake_head_var[0]][snake_head_var[1]].current_status = 0;
		//if there's existing tail
		if (snake_length > 0 && snake_length < SNAKE_MAX_LEN){
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;
			map[snake_tail_var[0]][snake_tail_var[1]].snake_body = 0;
			snake_tail_var[0] = snake_old_head_var[0];
			snake_tail_var[1] = snake_old_head_var[1];
			map[snake_tail_var[0]][snake_tail_var[1]].snake_body = 1;
			
			snake_length++;
			mvprintw(41, 40, "tail exists and ate creature");
			
		}
		else if (snake_length > SNAKE_MAX_LEN){

			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;
			map[snake_tail_var[0]][snake_tail_var[1]].snake_body = 0;
			snake_tail_var[0] = snake_old_head_var[0];
			snake_tail_var[1] = snake_old_head_var[1];
			map[snake_tail_var[0]][snake_tail_var[1]].snake_body = 1;
			mvprintw(41, 40, "tail exists and max length and ate creature");
		}
		
		else {
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
			snake_tail_var[0] = snake_old_head_var[0];
			snake_tail_var[1] = snake_old_head_var[1];
			snake_length++;
			mvprintw(41, 40, "no tail and ate creature");
		}
		
		mvprintw(42, 40, "Length %d ", snake_length);
	}
	
	//if there's no life in cell
	else {
	
		if (snake_length > 0){
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;
			map[snake_tail_var[0]][snake_tail_var[1]].snake_body = 0;
			snake_tail_var[0] = snake_old_head_var[0];
			snake_tail_var[1] = snake_old_head_var[1];
			map[snake_tail_var[0]][snake_tail_var[1]].snake_body = 1;
			mvprintw(41, 40, "tail and no creature");
			
		}
		
		else if (snake_length > SNAKE_MAX_LEN){

			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;
			map[snake_tail_var[0]][snake_tail_var[1]].snake_body = 0;
			snake_tail_var[0] = snake_old_head_var[0];
			snake_tail_var[1] = snake_old_head_var[1];
			map[snake_tail_var[0]][snake_tail_var[1]].snake_body = 1;
			mvprintw(41, 40, "tail exists and max length and no creature");
		}
		
		else{
			map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
			map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;
			
			mvprintw(41, 40, "no tail and no creature");
			
		}
		
	}
	
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
	WINDOW* map_window = newwin(ROWS + 2, COLUMNS + 2, 0, 0);
	WINDOW* console_window = newwin(30, 30, 30, 30);
	draw_static (map_window); 
	testi.set_head_location(new_map, 10,10);
	
	char testip[] = "xyz";
	
	//MAIN LOOP
	while(true){

		draw_creatures (new_map, map_window);
		draw_static (map_window); 
		testi.move_snake(new_map);
		refresh();
		wrefresh(map_window);
		wrefresh(console_window);
		//console_message (console_window, testip);
		sleep_for_seconds(1);
		werase(map_window);
		
	}
	endwin();
	return 0;


	
}/* end of main */


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
				mvwprintw(local_win, i+1, j+1, "@");
				wattroff(local_win, COLOR_PAIR(1));	
			}			
			if (map[i][j].snake_head == 1){
				wattron(local_win, COLOR_PAIR(2));
				mvwprintw(local_win, i+1, j+1, "X");
				wattroff(local_win, COLOR_PAIR(2));	
			}			
			
			if (map[i][j].snake_body == 1){
				wattron(local_win, COLOR_PAIR(2));
				mvwprintw(local_win, i+1, j+1, "I");
				wattroff(local_win, COLOR_PAIR(2));	
			}

			else if (map[i][j].current_status == 0 && map[i][j].snake_body == 0 && map[i][j].snake_head == 0){
				wattron(local_win, COLOR_PAIR(3));
				mvwprintw(local_win, i+1, j+1, ".");
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

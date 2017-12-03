#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
using namespace std;

string board[16][25] = {};
int counter = 0;
int done = 0;
char x;
char move;
int count_jump = 0;
int mario[2];
int monster[4][4] = {};
int movment;
int opt;
int coins = 0;
int lives = 3;
int up = 0;
int esc = 0;
int top = 0;
string temp;
void Print (string v[16][25]){
	cout << string (100,'\n');
	cout << "Coins: "<<coins<< "\nLives: "<<lives<< endl<<counter<<endl;
	for (int row = 0; row < 16; row ++){
		for (int col = 0; col < 25; col++ ){
			if (v[row][col] != ""){
				cout << v[row][col] << "  ";
			}else{
				cout << v[row][col] << "   ";
			}	
		}
		cout << endl;
	}
}

void clean_board(){
	for (int row = 0; row < 16; row++){
		for (int col = 0; col < 25; col++){
			board[row][col] = "";
		}
	}
}
void monster_check (string (&board)[16][25]){
	for (int i = 0;i < 4;i++){
		if (monster[i] [3] == 0){
			if (board [monster[i][0]][monster[i][1]+monster[i][2]] == "|" || monster[i][1] == 0 || monster[i][1] == 24){
				monster[i][2] *= -1;
			}
			board [monster[i][0]][monster[i][1]] = "";
			monster[i][1] += monster[i][2];
			board [monster[i][0]][monster[i][1]] = "X";
		}else{
			board [monster[i][0]][monster[i][1]] = "";
		}
	
	}

}
int check_mario (string (&board)[16][25], int (&mario)[2], int movment, int count_jump ){
//deadth by monster
	if (board[mario[0]][mario[1]+movment] == "X" || board[mario[0]][mario[1]] == "X"){
		return 1;
	}
// die in esc and move to the next one 
	if (top == 3 && esc == 0 &&  board [mario[0]+movment][mario[1]+movment] == "" && count_jump == 0){
		return 1;
	}else if (top == 3 && count_jump == 1 && esc == 0){
		board [mario[0]][mario[1]] = "";
		mario [1] += 3;
		counter += 3;
		esc = 1;
		top = -3;
	} 
//go up the pipe
	if (esc == 0 && count_jump == 1 && board[mario[0]+1][mario[1]+movment] == "|"){
		mario[0] -= 2;
		mario[1] += movment;
		counter += movment;
		up = 1;
		esc = 1;
		top ++;
	}else {
		esc = 0;
	}
//kill monster
	if (count_jump == 1 &&  board[mario[0]+1][mario[1]] == "X"){
		coins ++;
		if (mario[0]+1 == monster[0][0] && mario[1] == monster[0][1]){
			monster[0][3] = 1;
			board [monster[0][0]][monster[0][1]] = "*";
		}
		if (mario[0]+1 == monster[1][0] && mario[1] == monster[1][1]){
			monster[1][3] = 1;
			board [monster[1][0]][monster[1][1]] = "*";
		}	
		if (mario[0]+1 == monster[2][0] && mario[1] == monster[2][1]){
			monster[2][3] = 1;
			board [monster[2][0]][monster[2][1]] = "*";
		}
		if (mario[0]+1 == monster[3][0] && mario[1] == monster[3][1]){
			monster[3][3] = 1;
			board [monster[3][0]][monster[3][1]] = "*";
		}
		for (int i = 1; i <=3; i++){
			temp = board [mario[0]-i][mario[1]];
			board [mario[0]-i][mario[1]] = "C";
			Print (board);
			usleep(300000);
			board [mario[0]-i][mario[1]] = temp;
		}
	}
//go up the box	
	if (up == 1){

		if (count_jump == 1 && board [mario[0]+1][mario[1]+movment*2] == "B"){
			board[mario[0]][mario[1]+1] == "";
			mario[0] -=1;
			mario[1] +=movment*2; 
			counter += movment;
			up = 0;
			top = 0;
		}

	}
// go down pipe or box
	if (count_jump == 0 && board [mario[0]+1][mario[1]] == ""){
		if (board [mario[0]+1][mario[1]-movment] == "B"){
			mario[0] += 3;
		}else{
			mario[0] += 2;
			mario[1] ++;
			counter += movment;
		}
		top = 0;
	}
// destroy box
	if ( board [mario[0]-1][mario[1]] == "B" && count_jump == 1 && movment == 0){
		board [mario[0]-1][mario[1]] = "";
		Print (board);
	}
	if ( board [mario[0]-1][mario[1]] == "?"  && count_jump == 1 && movment == 0){
		board [mario[0]-1][mario[1]] = "";
		coins ++;
		for (int i = 2; i <=4; i++){
			temp = board [mario[0]-i][mario[1]];
			board [mario[0]-i][mario[1]] = "C";
			Print (board);
			usleep(300000);
			board [mario[0]-i][mario[1]] = temp;
		}
		Print (board);
	}
// lives
	if ( board [mario[0]-1][mario[1]] == "V" && count_jump == 1 && movment == 0){
		board [mario[0]-1][mario[1]] = "";
   		lives ++;
		for (int i = 2; i <=4; i++){
			temp = board [mario[0]-i][mario[1]];
			board [mario[0]-i][mario[1]] = "<L>";
			Print (board);
			usleep(300000);
			board [mario[0]-i][mario[1]] = temp;
		}
		Print (board);
	}
// die in voide
	if (count_jump == 0  && board [mario[0]+1][mario[1]] == " "){
		return 1;
	}
//jump voide 
	if (count_jump == 1 && board [mario[0]+2][mario[1]] == " "){
		mario[1] += movment;
        	counter += movment;
	}
	
return 0;
} 

void boards (int counter, string (&board)[16][25],int (&mario) [2]){
	switch(counter){
		case 0:
			clean_board();
			for (int i = 0; i < 25; i++){
				board [15][i] = "-";
			}
			mario[0] = 14;
			mario[1] = 0;
			monster[0][0] = 14;
			monster[0][1] = 4;
			monster[0][2] = -1;
			monster[0][3] = 0;
			monster[1][3] = 1;
			monster[2][3] = 1;
			monster[3][3] = 1;
			board [14][0] = "m";
			board [14][4] = "X";
	        	board [14][16] = "|";
        		board [14][18] = "|";
			board [15][16] = "|";
        		board [15][18] = "|";
			board [13][17] = "_";
			board [12][10] = "B";
			board [12][11] = "?";
			board [12][12] = "B";
			board [12][13] = "?";
			board [12][14] = "B";
			board [12][5] = "?";
			board [9][12] = "?";
			
		break;
		
		case 25:
			clean_board();			
			for (int i = 0; i < 25; i++){
				board [15][i] = "-";
			}
			mario[0] = 14;
			mario[1] = -1;			
	        	board [14][4] = "|";
        		board [14][6] = "|";
			board [15][4] = "|";
        		board [15][6] = "|";
			board [13][5] = "_";
	        	board [14][11] = "|";
        		board [14][13] = "|";
			board [15][11] = "|";
        		board [15][13] = "|";
			board [13][12] = "_";
	        	board [14][20] = "|";
        		board [14][22] = "|";
			board [15][20] = "|";
        		board [15][22] = "|";
			board [13][21] = "_";
			board [14][8] = "X";
			board [14][18] = "X";
  			board [14][16] = "X";
			monster[0][0] = 14;
			monster[0][1] = 8;
			monster[0][2] = -1;
			monster[0][3] = 0;
			monster[1][0] = 14;
			monster[1][1] = 18;
			monster[1][2] = -1;
			monster[1][3] = 0;
			monster[2][0] = 14;
			monster[2][1] = 16;
			monster[2][2] = -1;
			monster[2][3] = 0;
			monster[3][3] = 1;
		break;
		case 50: 
			clean_board();			
			for (int i = 0; i < 25; i++){
				board [15][i] = "-";
			}
			mario[0] = 14;
			mario[1] = -1;			
	        	board [12][4] = "V";
        		board [15][6] = " ";
			board [12][8] = "B";
        		board [12][9] = "?";
			board [12][10] = "B";
	        	board [15][12] = " ";
			board [14][20] = "|";
        		board [14][22] = "|";
			board [15][20] = "|";
        		board [15][22] = "|";
			board [13][21] = "_";
			board [14][16] = "X";
			board [14][18] = "X";
			monster[0][0] = 14;
			monster[0][1] = 16;
			monster[0][2] = -1;
			monster[0][3] = 0;
			monster[1][0] = 14;
			monster[1][1] = 18;
			monster[1][2] = -1;
			monster[1][3] = 0;
			monster[2][0] = 14;
			monster[2][1] = 18;
  			monster[2][2] = -1;
			monster[2][3] = 0;
			monster[3][3] = 1;
		
		break;
		case 75:
			clean_board();			
			for (int i = 0; i < 25; i++){
				board [15][i] = "-";
			}
			mario[0] = 14;
			mario[1] = -1;			
	        	board [12][4] = "?";
        		board [12][6] = "?";
			board [12][8] = "?";
        		board [12][13] = "B";
			board [12][18] = "B";
	        	board [12][19] = "B";
        		board [10][17] = "B";
			board [10][18] = "?";
			board [10][19] = "?";
	        	board [14][21] = "|";
        		board [14][23] = "|";
			board [15][21] = "|";
        		board [15][23] = "|";
			board [13][22] = "_";
			board [10][20] = "B";
			board [14][10] = "X";
			board [14][12] = "X";
			board [14][16] = "X";
			board [14][18] = "X";
			monster[0][0] = 14;
			monster[0][1] = 10;
			monster[0][2] = -1;
			monster[0][3] = 0;
			monster[1][0] = 14;
			monster[1][1] = 12;
			monster[1][2] = -1;
			monster[1][3] = 0;
			monster[2][0] = 14;
			monster[2][1] = 16;
  			monster[2][2] = -1;
			monster[2][3] = 0;
			monster[3][0] = 14;
			monster[3][1] = 18;
			monster[3][2] =-1;
			monster[3][3] = 0;
		
		break;
		case 100:
			clean_board();
			for (int i = 0; i < 25; i++){
				board [15][i] = "-";
			}
			mario[0] = 14;
			mario[1] = -1;
			board [14][0] = "m";
	        	board [14][4] = "|";
			board [15][4] = "|";
        		board [13][5] = "_";
			board [13][6] = "|";
			board [12][6] = "|";
			board [11][7] = "_";
			board [11][8] = "|";
			board [10][8] = "|";
			board [9][9] = "_";
			board [10][10] = "|";
			board [11][10] = "|";
			board [12][10] = "|";
			board [13][10] = "|";
			board [14][10] = "|";
			board [15][10] = "|";
			board [10][12] = "|";
			board [11][12] = "|";
			board [12][12] = "|";
			board [13][12] = "|";
			board [14][12] = "|";
			board [15][12] = "|";
	        	board [14][18] = "|";
			board [15][18] = "|";
        		board [13][17] = "_";
			board [13][16] = "|";
			board [12][16] = "|";
			board [11][15] = "_";
			board [11][14] = "|";
			board [10][14] = "|";
			board [9][13] = "_";
			board [15][11] = "";
			board [12][20] = "?";
			board [12][21] = "B";
			board [12][22] = "?";
			monster[0][3] = 1;
			monster[1][3] = 1;
			monster[2][3] = 1;
			monster[3][3] = 1;
		break;

		case 125:
			clean_board();
			for (int i = 0; i < 25; i++){
				board [15][i] = "-";
			}
			mario[0] = 14;
			mario[1] = -1;
			board [14][0] = "m";
	        	board [14][8] = "|";
			board [15][8] = "|";
        		board [13][9] = "_";
			board [13][10] = "|";
			board [12][10] = "|";
			board [11][11] = "_";
			board [11][12] = "|";
			board [10][12] = "|";
			board [9][13] = "_";
			board [10][14] = "|";
			board [11][14] = "|";
			board [12][14] = "|";
			board [13][14] = "|";
			board [14][14] = "|";
			board [15][14] = "|";
			board [10][16] = "|";
			board [11][16] = "|";
			board [12][16] = "|";
			board [13][16] = "|";
			board [14][16] = "|";
			board [15][16] = "|";
	        	board [14][22] = "|";
			board [15][22] = "|";
        		board [13][21] = "_";
			board [13][20] = "|";
			board [12][20] = "|";
			board [11][19] = "_";
			board [11][18] = "|";
			board [10][18] = "|";
			board [9][17] = "_";
			board [15][15] = "";
			board [12][4] = "?";
			board [12][5] = "B";
			board [12][6] = "?";
			monster[0][3] = 1;
			monster[1][3] = 1;
			monster[2][3] = 1;
			monster[3][3] = 1;
		break;
		case 150:
			clean_board();			
			for (int i = 0; i < 25; i++){
				board [15][i] = "-";
			}
			mario[0] = 14;
			mario[1] = -1;
	        	board [14][4] = "|";
        		board [14][6] = "|";
			board [15][4] = "|";
        		board [15][6] = "|";
			board [13][5] = "_";			
	        	board [12][8] = "B";
        		board [12][9] = "?";
			board [12][10] = "?";
        		board [12][11] = "B";
			board [14][9] = "X";
			board [14][11] = "X";
	        	board [14][13] = "|";
        		board [14][15] = "|";
			board [15][13] = "|";
        		board [15][15] = "|";
			board [13][14] = "_";			
	        	board [12][17] = "B";
        		board [12][18] = "?";
			board [12][19] = "?";
        		board [12][20] = "B";
			board [14][17] = "X";
			board [14][19] = "X";
	        	board [14][22] = "|";
        		board [14][24] = "|";
			board [15][22] = "|";
        		board [15][24] = "|";
			board [13][23] = "_";
			monster[0][0] = 14;
			monster[0][1] = 9;
			monster[0][2] = -1;
			monster[0][3] = 0;
			monster[1][0] = 14;
			monster[1][1] = 11;
			monster[1][2] = -1;
			monster[1][3] = 0;
			monster[2][0] = 14;
			monster[2][1] = 17;
			monster[2][2] = -1;
			monster[2][3] = 0;
			monster[3][0] = 14;
			monster[3][1] = 19;
			monster[3][2] = -1;
			monster[3][3] = 0; 
		
		break;
		
	}

}
int main (){
	int MM = 0;
	while (MM == 0){
		cout <<  "Main Menu \n 1. Start\n 2. How To Play\n 3. Exit\n";
		cin >> opt;	
	
		switch (opt){
	
			case 1:
			{
			while (lives > 0){
				if (coins == 100){
					lives ++;
					coins = 0;
				}
	 			boards(counter,board, mario);
				if (counter == 0){
					Print (board);
					counter =149 ;
				}
				cout <<"movement\n";
				cin >> move;
				switch (move){
					case 'd'://right
						if (mario [1] != 24 && board[mario[0]][mario[1]+1] != "|"){
							board [mario[0]][mario[1]] = "";
							mario [1] ++;
							done = check_mario(board,mario,1,count_jump);
							monster_check(board);
							board [mario[0]][mario[1]] = "m";
							counter ++;
						}
					break;
	
					case 'a'://left
						if (mario [1] != 0  && board[mario[0]][mario[1]-1] != "|"){
							board [mario[0]][mario[1]] = "";
							mario [1] --;
							done = check_mario(board,mario,-1, count_jump);
							monster_check (board);
							board [mario[0]][mario[1]] = "m";
							counter --;			
						}
					break;
		
					case 's'://down
						if (mario [0] != 14 && count_jump == 1){	
							board [mario[0]][mario[1]] = "";
							mario [0]++;
							board [mario[0]][mario[1]] = "m";
							count_jump = 2;
							done = check_mario(board,mario,1,count_jump);
						}
	
					break;
	
					case 'w'://jump
						
						count_jump = 1;
						board [mario[0]][mario[1]] = "";
						mario [0] --;
						board [mario[0]][mario[1]] = "m";
						Print (board);
						done = check_mario(board,mario,0,count_jump);
						if (cin >> move);
						switch (move){
							case 'd'://right
								if (mario [1] != 24 && board[mario[0]][mario[1]+1] != "|"){
									board [mario[0]][mario[1]] = "";
									monster_check(board);
									done = check_mario(board,mario,1,count_jump);
									mario[1]++;
									if (up == 0 ){
										board [mario[0]][mario[1]] = "m";
									}
									done = check_mario(board,mario,1,count_jump);
									counter ++;
								}
							break;

							case 'a'://left
								if (mario [1] != 0  && board[mario[0]][mario[1]-1] != "|"){
									board [mario[0]][mario[1]] = "";
									monster_check(board);
									done = check_mario(board,mario,-1,count_jump);
									mario [1] --;
									if (up == 0){
										board [mario[0]][mario[1]] = "m";
									}
									done = check_mario(board,mario,-1,count_jump);
									counter --;			
								}
							break;
	
							case 's'://down	change to deafault
									board [mario[0]][mario[1]] = "";
									monster_check(board);
									mario [0]++;
									board [mario[0]][mario[1]] = "m";
								//	done = check_mario(board,mario,3,count_jump);
									count_jump = 2;
	
							break;	
						
						}
						Print (board);
						usleep(500000);
						if (count_jump != 2){
							board [mario[0]][mario[1]] = "";
							mario [0]++;
							board [mario[0]][mario[1]] = "m";
	
						}
							count_jump = 0;
					break;
				
					case 'x':
						cout << "thx for playing\n";
						return 0;
					break;
				
					default:
						monster_check(board);
					break;
				}

			if (done == 0){
				Print (board);
			}
				if (done == 1){
					lives--;
					counter = 0;
					board [mario[0]][mario[1]]="";
					cout << string(100,'\n');
					cout << "\nYou moron, you lost a live. Lives remaining:"<< lives<<endl;
					usleep(1500000); 
					top = 0;
				}	
			}
			cout << "game over you lost shame on you\n wanna playagain (0 yes 1 no)";
			cin >> MM;
			lives = 3;
			break;
			}	
			case 2:
			{
				cout << "Welcome to Super NUMario\n\n      Contols:\n      e = up\n      f = right\n      s = left\n      x = end game\n\n when you press e it should be fallowed by f s or d to jump and move left right or just go down to the same position you started.\n\n m is mario\n X are monsters be aware they are closer than it seams\n C are coins\n B are regular boxed that can hide coins\n ? may have special avilities or coins.  ";
				cin >> MM;
			break;
			}

			case 3:
			{
				cout << "Thanks For playing\n";
				MM = 1;
			break;	
			}
		}
	}
	return 0;
}

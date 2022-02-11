#include<iostream>
#include<algorithm>
using namespace std;

int player1 = 1;  //Human
int player2 = 2;  // computer
struct minmax_return
{
	int colm;
	int score;
};
bool winner_found(int board[7][7], int player_value)
{

	// Check horizontal locations for win
	for (int c = 0; c < (7 - 3); c++)  //colm
	{
		for (int r = 0; r < 7; r++) //row
		{
			if (board[r][c] == player_value && board[r][c + 1] == player_value && board[r][c + 2] == player_value && board[r][c + 3] == player_value)
				return true;
		}
	}
	// Check vertical locations for win
	for (int c = 0; c < 7; c++)  //colm
	{
		for (int r = 6; r >= (7 - 4); r--) //row
		{
			if (board[r][c] == player_value && board[r - 1][c] == player_value && board[r - 2][c] == player_value && board[r - 3][c] == player_value)
				return true;
		}
	}

	// Check positively sloped diaganols
	for (int c = 0; c < (7 - 3); c++)  //colm
	{
		for (int r = 3; r < 7; r++) //row
		{
			if (board[r][c] == player_value && board[r - 1][c + 1] == player_value && board[r - 2][c + 2] == player_value && board[r - 3][c + 3] == player_value)
				return true;
		}
	}
	// Check negatively sloped diaganols
	for (int c = 0; c < (7 - 3); c++)  //colm
	{
		for (int r = 3; r >= 0; r--) //row
		{
			if (board[r][c] == player_value && board[r + 1][c + 1] == player_value && board[r + 2][c + 2] == player_value && board[r + 3][c + 3] == player_value)
				return true;
		}
	}
	return false;

}

int free_row(int board[][7], int col)
{
	for (int row = 6; row >= 0; row--)
	{
		if (board[row][col] == 0)
			return row;
	}
}
int Counter(int row, int colm, int val, int game[][7],char search_type)
{
	int counter_value = 0;
	int counter_zero = 0;
	int points = 0;
	int opponent_counter = 0;
	int opp_val = player1;
	if (val == player1)
	{
		opp_val = player2;
	}

	if (search_type == 'H')
	{
		for (int index = colm; index <= colm + 3; index++)
		{
			if (game[row][index] == val)
			{
				counter_value++;
			}
			if (game[row][index] == opp_val)
			{
				opponent_counter++;
			}

			else if (game[row][index] == 0)
			{
				counter_zero++;

			}

		}
	}

	else if (search_type == 'V')
	{
		for (int index = row; index >= row - 3; index--)
		{
			if (game[index][colm] == val)
			{
				counter_value++;
			}
			if (game[index][colm] == opp_val)
			{
				opponent_counter++;
			}
			else if (game[index][colm] == 0)
			{
				counter_zero++;

			}
		}
	}
	else if (search_type == 'P')
	{
		//positive diogonal
		for (int index = 0; index <= 3; index++)
		{
			if (game[row - index][colm + index] == val)
			{
				counter_value++;
			}
			if (game[row - index][colm + index] == opp_val)
			{
				opponent_counter++;
			}
			else if (game[row][index + 1] == 0)
			{
				counter_zero++;

			}
		}
	}
	else if (search_type == 'N')
	{
		for (int index = 0; index <= 3; index++)
		{
			if (game[row + 3 - index][colm + index] == val)
			{
				counter_value++;
			}
			if (game[row + 3 - index][colm + index] == opp_val)
			{
				opponent_counter++;
			}
			else if (game[row][index + 1] == 0)
			{
				counter_zero++;

			}
		}
	}

	if (counter_value == 4)   // hint that this move will make you winner
		points += 100;
	else if (counter_value == 3 && counter_zero == 1)   // hint that there are 3 colms of your piece
	{
		points += 10;
	}
	else if (counter_value == 2 && counter_zero == 2)   // hint that there are 3 colms of your piece
	{
		points += 5;
	}
	if (opponent_counter == 3 && counter_zero == 1)  // higher chances of opponent to win
	{
		points -= 80;
	}

	return points;

}

int assign_score(int game[][7],int val)
{
	int points = 0;
	

	//For horizontal 
	for (int row = 6; row >= 0; row--)
	{
		for (int colm = 0; colm < 7 - 3; colm++)
		{
			points += Counter(row, colm, val, game, 'H');
		}
	}
	

//// For vertical 
	for (int colm = 0; colm < 7; colm++)
	{
		for (int row = 6; row >= 6 - 3; row--)
		{
			points += Counter(row, colm, val, game, 'V');
			
		}
	}
	//For positively diognoal
	for (int row = 6; row >= 6 - 3; row--)
	{
		for (int colm = 0; colm < 7 - 3; colm++)
		{
			
			points += Counter(row, colm, val, game, 'P');
		}
	}
	//For negatively slopped diagonal 

	for (int row = 6; row >= 6 - 3; row--)
	{
		for (int colm = 0; colm < 7 - 3; colm++)
		{
			points += Counter(row, colm, val, game, 'N');
		}
	}

	return points;
}

void copy_board(int new_board[][7],int board[][7])
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			new_board[i][j] = board[i][j];
		}
	}
}

void displayStates(int states[][7])
{
	cout << "\n";
	for (int i = 0; i<7; i++)
	{
		for (int j = 0; j < 7; j++)
			cout << states[i][j] << " ";
		cout << endl;
	}

}
int count_free_locations(int board[][7])
{
	int count = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (board[i][j] == 0)
			{
				count++;
			}
		}
	}
	return count;
}
bool end_of_game(int board[][7])   
{
	int free_location = count_free_locations(board);
	return winner_found(board, player1) || winner_found(board, player2) || free_location == 0;
}
minmax_return minmax(int states[][7],int alpha,int beta, int depth, bool isMax) 
{
	minmax_return r1;
	minmax_return res;
	int row;
	int best_Colm = -1;
	int updated_score;
	int temp_state[7][7];
	if (depth == 0 || end_of_game(states))
	{
		if (end_of_game(states))
		{
			if (winner_found(states, player1))
			{
				r1.colm = -1;
				r1.score = -10000000000;
				return r1;  // beause human is min ( - infinity)
			}
			else if (winner_found(states, player2))
			{
				r1.colm = -1;
				r1.score = 10000000000;

				return r1;  // because computer is max ( + infinity)
			}
			else
			{
				r1.colm = -1;
				r1.score = 0;
				return r1;  // game is over
			}
				
		}
		else
		{
			r1.colm = -1;
			r1.score= assign_score(states, player2); // player2 because computer is second player
			return r1;
		}
			
	}

	/////////
	if (isMax)
	{

		int value = -99999;
		for (int colm = 0; colm < 7; colm++)
		{
			row = free_row(states, colm);
			copy_board(temp_state, states);
			temp_state[row][colm] = player2;
			updated_score = minmax(temp_state,alpha,beta ,depth - 1, false).score;
			if (updated_score > value)
			{
				
				value = updated_score;
				best_Colm = colm;
				res.colm = best_Colm;
				res.score = value;
			}
			if (alpha < value)
			{
				alpha = value;
			}
			if (alpha >= beta)
			{
				break;
			}
		}
		return res;
			
	}
	else  // a  min node
	{
		int value = 99999;
		for (int colm = 0; colm < 7; colm++)
		{
			row = free_row(states, colm);
			copy_board(temp_state, states);
			temp_state[row][colm] = player1;
			updated_score = minmax(temp_state,alpha,beta, depth - 1, true).score;
			if (updated_score < value)
			{
				value = updated_score;
				best_Colm = colm;
				res.colm = best_Colm;
				res.score = value;
			}
			if (beta > value)
			{
				beta = value;
			}
			if (alpha >= beta)
				break;
			
		}
		return res;

		
		

	}

	
}


int main()
{
	//For player 1 -> 1  (human)
	//for player 2 -> 2  (computer)

	int board[7][7] = { { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 } };
	int game_over = 1;
	int player = 1;
	int colm_choice;
	int row, depth;
	char level;
	

	cout << "\n****************************\n";
	cout << "\nChoose your dificulty level\n";
	cout << "\t\t E-> Easy\n ";
	cout << "\t\t H-> Hard\n";
	cout << "\n****************************\n";
	cin >> level;

	//*******************   This portion is required if we dont male buttons *******************
	if (level != 'E')
	{
		if (level != 'H')
		{
			cout << "You have not choose correct so by default depth =2";
			depth = 2;
		}
	}
	//**********************************************************************************************
	if (level == 'E')
	{
		depth = 1;
	}
	if (level == 'H')
	{
		depth = 3;
	}
	displayStates(board);
	while (game_over)
	{
		if (player == 1)
		{

			cout << "\nPlayer 1 enter your choice from range(0-6) : ";
			cin >> colm_choice;



			row = 6;
			while (board[row][colm_choice] != 0)
			{
				row--;
				if (row == -1)
				{
					cout << "Select another colm this is full";
					cin >> colm_choice;
					row = 6;
				}
			}

			board[row][colm_choice] = 1;
			displayStates(board);
			if (winner_found(board, 1))
			{
				cout << "Yahooo player 1 wins  ";
				return 0;
			}


			player = 2;
		}
		else /// player 2
		{
			int my_row;
			int my_colm = minmax(board,-999999,999999, depth, true).colm;

			if (board[0][my_colm] == 0)
			{
				my_row = free_row(board, my_colm);
				board[my_row][my_colm] = player2;

			}
			displayStates(board);

			if (winner_found(board, 2))
			{
				cout << "Yahooo player 2 wins  ";
				return 0;
			}
			player = 1;


		}

		cout << endl;
	}

}













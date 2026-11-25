#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define PLAYER_COUNT 2
#define BOARD_SIZE 3

#define SCORE_WIN 1
#define SCORE_DRAW 0.5


typedef enum Mark {
	unmakred = '.',
	marked_x = 'X',
	marked_o = 'O'
} Mark;

typedef enum WinState {
	state_none,
	state_player1_win,
	state_player2_win,
	state_draw
} WinState;

typedef struct BoardInputData {
	short pos_row;
	short pos_col;
	Mark mark;
} BoardInputData;

typedef struct PlayerData {
	short turn_index;
	float score;
	char name[64];
} PlayerData;


void initialize_board(char board[BOARD_SIZE][BOARD_SIZE])
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
		for (size_t j = 0; j < BOARD_SIZE; j++)
			board[i][j] = (char) unmakred;
}

_Bool is_valid_board_input(const BoardInputData input)
{
	return
		(1 <= input.pos_row && input.pos_row <= BOARD_SIZE) &&
		(1 <= input.pos_col && input.pos_col <= BOARD_SIZE);
}

WinState check_win_state(const char board[BOARD_SIZE][BOARD_SIZE], const PlayerData player1, const PlayerData player2)
{
	WinState state;

	const _Bool x_row_1 = board[0][0] == marked_x && board[0][1] == marked_x && board[0][2] == marked_x;
	const _Bool x_row_2 = board[1][0] == marked_x && board[1][1] == marked_x && board[1][2] == marked_x;
	const _Bool x_row_3 = board[2][0] == marked_x && board[2][1] == marked_x && board[2][2] == marked_x;
	const _Bool x_col_1 = board[0][0] == marked_x && board[1][0] == marked_x && board[2][0] == marked_x;
	const _Bool x_col_2 = board[0][1] == marked_x && board[1][1] == marked_x && board[2][1] == marked_x;
	const _Bool x_col_3 = board[0][2] == marked_x && board[1][2] == marked_x && board[2][2] == marked_x;
	const _Bool x_diag_tlbr = board[0][0] == marked_x && board[1][1] == marked_x && board[2][2] == marked_x;
	const _Bool x_diag_trbl = board[2][0] == marked_x && board[1][1] == marked_x && board[0][2] == marked_x;

	const _Bool o_row_1 = board[0][0] == marked_o && board[0][1] == marked_o && board[0][2] == marked_o;
	const _Bool o_row_2 = board[1][0] == marked_o && board[1][1] == marked_o && board[1][2] == marked_o;
	const _Bool o_row_3 = board[2][0] == marked_o && board[2][1] == marked_o && board[2][2] == marked_o;
	const _Bool o_col_1 = board[0][0] == marked_o && board[1][0] == marked_o && board[2][0] == marked_o;
	const _Bool o_col_2 = board[0][1] == marked_o && board[1][1] == marked_o && board[2][1] == marked_o;
	const _Bool o_col_3 = board[0][2] == marked_o && board[1][2] == marked_o && board[2][2] == marked_o;
	const _Bool o_diag_tlbr = board[0][0] == marked_o && board[1][1] == marked_o && board[2][2] == marked_o;
	const _Bool o_diag_trbl = board[2][0] == marked_o && board[1][1] == marked_o && board[0][2] == marked_o;

	if (x_row_1 || x_row_2 || x_row_3 || x_col_1 || x_col_2 || x_col_3 || x_diag_tlbr || x_diag_trbl)
	{
		if (player1.turn_index == 0)
			state = state_player1_win;
		else if (player2.turn_index == 0)
			state = state_player2_win;
	}
	else if (o_row_1 || o_row_2 || o_row_3 || o_col_1 || o_col_2 || o_col_3 || o_diag_tlbr || o_diag_trbl)
	{
		if (player1.turn_index == 1)
			state = state_player1_win;
		else if (player2.turn_index == 1)
			state = state_player2_win;
	}
	else
	{
		state = state_none;
	}

	return state;
}

void mark(char board[BOARD_SIZE][BOARD_SIZE], const BoardInputData input)
{
	board[input.pos_row - 1][input.pos_col - 1] = input.mark;
}

void print_game_name()
{
	printf("Tic-Tac-Toe\n");
	printf("===========\n");
}

void print_msg_current_score(const PlayerData player1, const PlayerData player2)
{
	printf("%s (%.1f)\tvs\t%s (%.1f)\n",
		player1.name, player1.score,
		player2.name, player2.score
	);
}

void print_msg_invalid_input()
{
	printf("Invalid Input! Please enter a valid row (1-3) and column (A-C).\n");
}

void print_msg_current_turn(const PlayerData player1, const PlayerData player2, const unsigned int turn)
{
	PlayerData turn_player_data;
	const short turn_index = (turn + 1) % 2;

	if (player1.turn_index == turn_index)
		turn_player_data = player1;
	else if (player2.turn_index == turn_index)
		turn_player_data = player2;
	
	switch (turn % 2)
	{
	case 0:
		printf("It's %s's (%c) turn!\n", turn_player_data.name, marked_o);
		break;

	case 1:
		printf("It's %s's (%c) turn!\n", turn_player_data.name, marked_x);
		break;
	}
}

void print_msg_win_state(const PlayerData player)
{
	printf("%s is the winner.\n", player.name);
}

void print_msg_draw_state()
{
	printf("The game was a draw.\n");
}

void print_board(const char board[BOARD_SIZE][BOARD_SIZE])
{
	#define PRINT_SIZE 14

	char print[PRINT_SIZE][PRINT_SIZE] = {
		{ '@', ' ', '|', 'A', '|', ' ', '|', 'B', '|', ' ', '|', 'C', '|', ' ' },
		{ ' ', '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*' },
		{ '-', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|' },
		{ '1', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|' },
		{ '-', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|' },
		{ ' ', '|', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '|' },
		{ '-', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|' },
		{ '2', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|' },
		{ '-', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|' },
		{ ' ', '|', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '|' },
		{ '-', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|' },
		{ '3', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|' },
		{ '-', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|' },
		{ ' ', '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*' }
	};

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			const size_t pos_tl_i = i * 4 + 2;
			const size_t pos_tl_j = j * 4 + 2;

			switch (board[i][j])
			{
			case marked_x:
				print[pos_tl_i + 0][pos_tl_j + 0] = marked_x;
				print[pos_tl_i + 0][pos_tl_j + 2] = marked_x;
				print[pos_tl_i + 1][pos_tl_j + 1] = marked_x;
				print[pos_tl_i + 2][pos_tl_j + 0] = marked_x;
				print[pos_tl_i + 2][pos_tl_j + 2] = marked_x;
				break;

			case marked_o:
				print[pos_tl_i + 0][pos_tl_j + 1] = marked_o;
				print[pos_tl_i + 1][pos_tl_j + 0] = marked_o;
				print[pos_tl_i + 1][pos_tl_j + 2] = marked_o;
				print[pos_tl_i + 2][pos_tl_j + 1] = marked_o;
				break;

			case unmakred:
			default:
				break;
			}
		}
	}

	for (size_t i = 0; i < PRINT_SIZE; i++)
	{
		for (size_t j = 0; j < PRINT_SIZE; j++)
		{
			putchar(' ');
			putchar(print[i][j]);
			putchar(' ');
		}

		putchar('\n');
	}
}

BoardInputData take_board_input(unsigned int turn)
{
	BoardInputData data;

	char input[64];

	_Bool is_valid = false;

	do
	{
		printf("> ");

		if (!fgets(input, sizeof(input), stdin))
		{
			print_msg_invalid_input();
			continue;
		}

		input[63] = '\0';
		size_t input_length = strlen(input);

		if (input_length != 3)
		{
			print_msg_invalid_input();
			continue;
		}

		if ('a' <= input[0] && input[0] <= 'c')
		{
			data.pos_col = (short) (input[0] - 'a' + 1);
		}
		else if ('A' <= input[0] && input[0] <= 'C')
		{
			data.pos_col = (short) (input[0] - 'A' + 1);
		}
		else
		{
			print_msg_invalid_input();
			continue;
		}

		if ('1' <= input[1] && input[1] <= '3')
		{
			data.pos_row = (short) (input[1] - '1' + 1);
		}
		else
		{
			print_msg_invalid_input();
			continue;
		}

		switch (turn % 2)
		{
		case 0:
			data.mark = marked_o;
			break;

		case 1:
			data.mark = marked_x;
			break;
		}

		is_valid = true;
	} while (!is_valid);

	return data;
}

void get_player_name(PlayerData *player_data)
{
	printf("Enter Player-%d's name: ", player_data->turn_index + 1);
	fgets(player_data->name, sizeof(player_data->name), stdin);
	player_data->name[strcspn(player_data->name, "\n")] = '\0';
}

_Bool get_rematch()
{
	char choice[64];

	while (true)
	{
		printf("Want to rematch? (Y/N)\n> ");
		
		if (!fgets(choice, sizeof(choice), stdin))
			return false;
		
		choice[63] = '\0';
		size_t input_length = strlen(choice);

		if (input_length == 2)
		{
			if (choice[0] == 'Y' || choice[0] == 'y')
				return true;
			if (choice[0] == 'N' || choice[0] == 'n')
				return false;
		}

		printf("Invalid input.\n");
	}
}


int main()
{
	_Bool game_loop = true;

	unsigned int turn = 1;

	char board[BOARD_SIZE][BOARD_SIZE];
	initialize_board(board);

	print_game_name();

	PlayerData player1 = { .turn_index = 0 };
	PlayerData player2 = { .turn_index = 1 };
	get_player_name(&player1);
	get_player_name(&player2);

	do {
		print_msg_current_turn(player1, player2, turn);
		print_board(board);
		mark(board, take_board_input(turn));

		WinState current_state = check_win_state(board, player1, player2);

		switch (current_state)
		{
		case state_player1_win:
			player1.score += SCORE_WIN;

			print_msg_win_state(player1);
			print_msg_current_score(player1, player2);
			break;

		case state_player2_win:
			player2.score += SCORE_WIN;

			print_msg_win_state(player2);
			print_msg_current_score(player1, player2);
			break;

		case state_draw:
			player1.score += SCORE_DRAW;
			player2.score += SCORE_DRAW;

			print_msg_draw_state();
			print_msg_current_score(player1, player2);
			break;
			
		case state_none:
			turn++;
			break;
		default:
			break;
		}

		if (current_state == state_player1_win || current_state == state_player2_win || current_state == state_draw)
		{
			turn = 1;
			initialize_board(board);

			game_loop = get_rematch();
		}
	} while (game_loop);

	return 0;
}

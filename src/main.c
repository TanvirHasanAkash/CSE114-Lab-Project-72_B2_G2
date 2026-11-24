#include <stdbool.h>
#include <stdio.h>


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

_Bool is_valid_board_input(const BoardInputData input);

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

	if (o_row_1 || o_row_2 || o_row_3 || o_col_1 || o_col_2 || o_col_3 || o_diag_tlbr || o_diag_trbl)
	{
		if (player1.turn_index == 1)
			state = state_player1_win;
		else if (player2.turn_index == 1)
			state = state_player2_win;
	}

	return state;
}

void mark(const BoardInputData input);

void print_game_name()
{
	printf("Tic-Tac-Toe\n");
	printf("===========\n");
}

void print_msg_current_score(const PlayerData player1, const PlayerData player2)
{
	printf("%s (%.1f)\tvs\t%s (%.1f)",
		player1.name, player1.score,
		player2.name, player2.score
	);
}

void print_msg_invalid_input();
void print_msg_current_turn(const PlayerData player1, const PlayerData player2, const unsigned int turn);

void print_msg_win_state(const PlayerData player)
{
	printf("%s is the winner.\n", player.name);
}

void print_msg_draw_state()
{
	printf("The game was a draw.\n");
}

void print_board();

BoardInputData take_board_input();

void get_player_name(PlayerData *player_data)
{
	printf("Enter Player-%d's name: ", player_data->name);
	fgets(player_data->name, sizeof(player_data->name), stdin);
	player_data->name[strcspn(player_data->name, "\n")] = '\0';
}

_Bool get_rematch();


int main()
{
	_Bool game_loop = true;

	unsigned int turn = 0;

	char board[BOARD_SIZE][BOARD_SIZE];
	initialize_board(board);

	print_game_name();

	PlayerData player1 = { .turn_index = 0 };
	PlayerData player2 = { .turn_index = 1 };
	get_player_name(&player1);
	get_player_name(&player2);

	do {
		print_msg_current_turn(player1, player2, turn);
		print_board();
		mark(take_board_input());

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
		default:
			break;
		}

		if (current_state == state_player1_win || current_state == state_player2_win || current_state == state_draw)
		{
			turn = 0;
			initialize_board(board);

			game_loop = get_rematch();
		}
	} while (game_loop);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int ID = 0;
int PLAYER_INDEX = 0;
int GAME_INDEX = 0;
int player = 5;
int game = 10;

/******************************************************* 
                    Structures
*******************************************************/

typedef struct playerAccount {
    int playerID;
    char firstName[25];
    char lastName[25];
    char email[100];
    int score;
    int numGames;
} Player;

typedef struct game {
    int id;
    int player1;
    int player2;
    char move1;
    char move2;
    char lastMove;
    char status[20];
} Game;

/******************************************************* 
                    Prototype
*******************************************************/

void InitializeBoard(int m, int n , char board[][n]);
void PrintBoard(int m, int n, char board[][n]);
void CreateBoard(int m, int n, char board[][n], char mark);
int IsValidBoard(int m, int n, char board[][n]);
char ListWinningCells(int m, int n, char board[][n]);
void WhoIsTheWinner(int m, int n, char board[][n], Player list1[], Game list2[], int player1, int player2);

/******************************************************* 
                    New Functions
*******************************************************/

void CreateAccount(Player list[]) {
    int check, valid = 0;
    list[ID].playerID = PLAYER_INDEX;
    list[ID].score = 100;

    printf("\nYou are player #%d\n", list[ID].playerID);

    printf("Enter first name: ");
    scanf(" %[^\n]s", list[ID].firstName);

    printf("Enter last name: ");
    scanf(" %[^\n]s", list[ID].lastName);
    
   do {
        printf("Enter valid email: ");
        scanf(" %[^\n]s", list[ID].email);

        for (int i = 0; list[ID].email[i] != '\0'; i++ ) {
            if(list[ID].email[i] == '@') {
                check = 1;
            }
            else if(list[ID].email[i] == '.') {
                break;
            }
        }
        if(check != 1) {
            valid = 0;
            printf("Invalid email\n");
        }
        else {
            valid = 1;
        }
    
    } while(valid == 0); 

    ID++;
    PLAYER_INDEX++;
}
void CheckArrayPlayer(int n, struct playerAccount list[]) {
    player = n+(n/2);
    list = realloc(list, n * sizeof (struct playerAccount *));
}
void CheckArrayGame(int n, Game list[]) {
    game = n+(n/2);
    list = realloc(list, n * sizeof (struct game *));
}
void CreateGame(Player list1[], Game list2[]) {
    int id1, id2;

    srand(time(NULL));
    list2[GAME_INDEX].id = rand()%10000 +1;
    printf("Your game id is %d\n",  list2[GAME_INDEX].id);

    printf("Enter player 1 ID: ");
    scanf(" %d", &id1);

    printf("Enter player 2 ID: ");
    scanf(" %d", &id2);

    if(list1[id1].score < list1[id2].score) {
        list2[GAME_INDEX].player1 = id1;
        list2[GAME_INDEX].player2 = id2;
        list2[GAME_INDEX].move1 = 'X';
        list2[GAME_INDEX].move2 = 'O';

        printf("Player 1 has ID %d and move %c\n", list2[GAME_INDEX].player1, list2[GAME_INDEX].move1);
        printf("Player 2 has ID %d and move %c\n", list2[GAME_INDEX].player2, list2[GAME_INDEX].move2);
    }
    else if(list1[id1].score > list1[id2].score) {
        list2[GAME_INDEX].player1 = id2;
        list2[GAME_INDEX].player2 = id1;
        list2[GAME_INDEX].move1 = 'X';
        list2[GAME_INDEX].move2 = 'O';
        printf("Player 1 has ID %d and move %c\n", list2[GAME_INDEX].player1, list2[GAME_INDEX].move1);
        printf("Player 2 has ID %d and move %c\n", list2[GAME_INDEX].player2, list2[GAME_INDEX].move2);
    }
    else {
        list2[GAME_INDEX].player1 = id1;
        list2[GAME_INDEX].player2 = id2;
        list2[GAME_INDEX].move1 = 'X';
        list2[GAME_INDEX].move2 = 'O';

        printf("Player 1 has ID %d and move %c\n", list2[GAME_INDEX].player1, list2[GAME_INDEX].move1);
        printf("Player 2 has ID %d and move %c\n", list2[GAME_INDEX].player2, list2[GAME_INDEX].move2);
    }
    list1[id1].numGames++; //increment number of games player played
    list1[id2].numGames++;
    GAME_INDEX++;
}
void LeadershipBoard (Player list[]) { 

    Player leader[50];
    Player temp;
    int tempScore, tempID;
    char choice;

    for(int i = 0; i < PLAYER_INDEX; i++) {
        leader[i].playerID = list[i].playerID;
        leader[i].score = list[i].score;
        leader[i].numGames = list[i].numGames;
        strcpy(leader[i].email, list[i].email);
    }
    
    while(1) {
        printf("Press 'd' to print leadership board in descending order\nPress 'a' to print leadership board in descending order\n");
        printf("Press 'n' to print leadership board by player's total number of games\nPress 'e' to Exit\n");
            scanf(" %c", &choice);
        if (choice == 'd') {
            for(int i = 0; i < PLAYER_INDEX -1; i++) {
                for(int j = i + 1; j < PLAYER_INDEX; j++) {
                    if(leader[i].score  < leader[j].score) {
                        temp.score = leader[i].score;
                        temp.playerID = leader[i].playerID;
                        strcpy(temp.email, leader[i].email);

                        leader[i].score = leader[j].score;
                        leader[i].playerID = leader[j].playerID;
                        strcpy(leader[i].email, leader[j].email);

                        leader[j].score = temp.score;
                        leader[j].playerID = temp.playerID;
                        strcpy(leader[j].email, leader[i].email);
                    }
                }
            } 
            for(int i = 0; i < PLAYER_INDEX; i++)
                printf("Player ID: %d, Email: %s, Score: %d\n", leader[i].playerID, leader[i].email, leader[i].score);
        }
        else if (choice == 'a') {
            for(int i = 0; i < PLAYER_INDEX -1; i++) {
                for(int j = i + 1; j > PLAYER_INDEX; j++) {
                    if(leader[i].score  < leader[j].score) {
                        temp.score = leader[i].score;
                        temp.playerID = leader[i].playerID;
                        strcpy(temp.email, leader[i].email);

                        leader[i].score = leader[j].score;
                        leader[i].playerID = leader[j].playerID;
                        strcpy(leader[i].email, leader[j].email);

                        leader[j].score = temp.score;
                        leader[j].playerID = temp.playerID;
                        strcpy(leader[j].email, leader[i].email);
                    }
                }
            } 
            for(int i = 0; i < PLAYER_INDEX; i++)
                printf("Player ID: %d, Email: %s, Score: %d\n", leader[i].playerID, leader[i].email, leader[i].score);
        }
        else if (choice == 'n') {
            for(int i = 0; i < PLAYER_INDEX -1; i++) {
                for(int j = i + 1; j > PLAYER_INDEX; j++) {
                    if(leader[i].numGames  < leader[j].numGames) {
                        temp.numGames = leader[i].numGames;
                        temp.playerID = leader[i].playerID;

                        leader[i].numGames = leader[j].numGames;
                        leader[i].playerID = leader[j].playerID;

                        leader[j].numGames = temp.numGames;
                        leader[j].playerID = temp.playerID;
                    }
                }
            } 
            for(int i = 0; i < PLAYER_INDEX; i++)
                printf("Player #%d has number of games is %d\n", leader[i].playerID, leader[i].numGames);
        }
        else if (choice == 'e')
            break;
    }
    
}
void PrintGames(Game list[]) {
    int n;
    for(int i = 0; i < GAME_INDEX; i++) {
        printf("Game index %d has game ID of %d\n", i, list[i].id);
    }
    printf("Enter game ID to see information\n");
    scanf("%d", &n);

    for(int i=0; i < GAME_INDEX; i++) {
        if(list[i].id == n) {
            printf("\n\nGame ID %d\n", list[i].id);
            printf("Game last move %c\n", list[i].lastMove);
            printf("Player 1 has ID %d and move %c\n", list[i].player1, list[i].move1);
            printf("Player 2 has ID %d and move %c\n", list[i].player2, list[i].move2);
            printf("Game status: %s\n\n", list[i].status);
        }
    }
}

/******************************************************* 
                Main Function
*******************************************************/

int main(void) {
    int test, player1, player2, player = 1;
    char choice, mark, win;

    char board[3][3];
    Player *list1 = malloc(player * sizeof(struct playerAccount*));
    Game *list2 = malloc(game * sizeof(struct Game*));
    InitializeBoard(3, 3 , board);

    while(1) {
        printf("\nPress 'P' to add player\nPress 'G' to play a new game or load and play a saved game\nPress 'L' to print leadership board\n");
        printf("Press 'p' to print the tic-tac-toe board\n");
        printf("Press 'c' to create a tic-tac-toe board with some X and O cells\n");
        printf("Press 't' to test if a tic-tac-toe board is valid or invalid board\n");
        printf("Press 'w' to predict winning cell for player X or O\n");
        printf("Press 'e' to exit\n");
        scanf(" %c", &choice);

        if (choice == 'P') {
            CreateAccount(list1);
            if(PLAYER_INDEX == player - 1) {
                CheckArrayPlayer(player, list1);
                printf("\nNew player index = %d\n\n", player);
            }
            if(GAME_INDEX == game - 1) {
                CheckArrayGame(game, list2);
                printf("\nNew game index = %d\n\n", game);
            }
        }
        else if (choice == 'G') {
        
            int c, num;
            printf("Enter 1 to create new game\nEnter 2 to load game\n");
            scanf("%d", &c);

            if(c == 1) {
                InitializeBoard(3, 3, board);
                InitializeBoard(3, 3, board);
                CreateGame(list1, list2);
            }
            else if(c == 2) {
                PrintGames(list2);    
            }
        }
        else if (choice == 'L') {
            LeadershipBoard(list1);
        }
        else if (choice == 'p') {
            PrintBoard(3,3,board);
        }
        else if (choice == 'c') {
            player = (player % 2) ? 1 : 2;
            mark = (player % 2) ? 'X' : 'O';
            list2[GAME_INDEX-1].lastMove = mark; // put in last move
            CreateBoard(3, 3, board, mark);
            player++;

            PrintBoard(3,3,board);
            int id1 = list2[GAME_INDEX-1].player1;
            int id2 = list2[GAME_INDEX-1].player2;
            printf("\nPlayer ID %d has score of %d\n", list2[GAME_INDEX-1].player1, list1[id1].score);
            printf("Player ID %d has score of %d\n", list2[GAME_INDEX-1].player2, list1[id2].score);

        }
        else if (choice == 't') {
            test = IsValidBoard(3,3,board);
            if(test)
                printf("\nBoard is valid!!\n");
            else
                printf("\nBoard is not valid :(\n");
        }
        else if (choice == 'w') { 
            int n = (player % 2) ? 1 : 2;
            char m = ListWinningCells(3,3, board);
            if(n == 1 && list2[GAME_INDEX-1].move1 == m)
                list1[player1].score--;
            else if(n == 2 && list2[GAME_INDEX-1].move2 == m)
                list1[player2].score--;
        }
        else if (choice == 'e') {
            break;
        }
        WhoIsTheWinner(3, 3, board, list1, list2, player1, player2);
    }
    return 0;
}

/******************************************************* 
                Old Functions
*******************************************************/

void InitializeBoard(int m, int n , char board[][n]){
    int c =1;
    for(int i =0; i<m; i++){
        for(int j=0; j< n; j++){
            board[i][j] = c+'0';
            c++;
        }
    }
}

void PrintBoard(int m, int n, char board[][n]){
    for (int i = 0; i < m; i++){
        printf("     |     |     \n");
        for (int j = 0; j < n; j++){
            if (j != 2) {
                printf("  %c  |", board[i][j] );
            }
            else {
                printf("  %c   ", board[i][j] );
            }
        }
        printf("\n");
        if (i != 2)
            printf("_____|_____|_____\n");
        else 
            printf("     |     |     \n");
    } 
}

void CreateBoard(int m, int n, char board[][n], char mark){
    int loc;

    PrintBoard(3,3, board);
    printf("\nPlayer %c, enter the number of the cell where you want to insert X or O\n", mark); 
    scanf("%d", &loc);

    if(loc > 0 && loc < 10){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if (board[i][j] == (loc + '0'))
                    board[i][j] = mark;
            }
        }
    }
    else
        printf("Invalid cell number");
}

int IsValidBoard(int m, int n, char board[][n]){
    int countX = 0;
    int countO = 0;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]=='X')
                countX++;
            if(board[i][j]=='O')
              countO++;
        }
    }
    if(abs(countO-countX)== 0 || abs(countO-countX)==1)
        return 1;
    else
        return 0;
}

void WhoIsTheWinner(int m, int n, char board[][n], Player list1[], Game list2[] ,int player1, int player2) {
    char win;
    int countX = 0;
    int countO = 0;
    int id1 = list2[GAME_INDEX-1].player1;
    int id2 = list2[GAME_INDEX-1].player2;

    if(board[0][0] == board[0][1] && board[0][1]== board[0][2])
       win = board[0][0];
    else if(board[1][0] == board[1][1] && board[1][1]== board[1][2])
       win = board[1][0];
    else if(board[2][0] == board[2][1] && board[2][1]== board[2][2])
       win = board[2][0];
    else if(board[0][0] == board[1][0] && board[1][0]== board[2][0])
        win = board[0][0];
    else if(board[0][1] == board[1][1] && board[1][1]== board[2][1])
        win = board[0][1];
    else if(board[0][2] == board[1][2] && board[1][2]== board[2][2])
        win = board[0][2];
    else if(board[0][0] == board[1][1] && board[1][1]== board[2][2])
        win = board[0][0];
    else if(board[0][2] == board[1][1] && board[1][1]== board[2][0])
        win = board[0][2];
    else 
        win = 'T';
    
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]=='X')
                countX++;
            if(board[i][j]=='O')
              countO++;
        }
    }
    int sum = countX + countO;

    if(win == 'X') {
        printf("Winner is X\n");
        strcpy(list2[GAME_INDEX-1].status, "Winner is X");

        if(list1[id1].score > list1[id2].score)
            list1[id1].score++;
        if(list1[id1].score < list1[id2].score) {
            list1[id1].score+=3; //Winner wins against player with higher score
            list1[id2].score-=2; //Loser lost to winner with lower score
        }  

    }
    else if(win == 'O') {
        strcpy(list2[GAME_INDEX-1].status, "Winner is O");
        printf("Winner is O\n");

        if(list1[id2].score > list1[id1].score)
            list1[id2].score++;
        if(list1[id2].score < list1[id1].score) {
            list1[id2].score+=3; //Winner wins against player with higher score
            list1[id1].score-=2; //Loser lost to winner with lower score
        }  
    }
    else if(win == 'T' && sum == 9) {
        strcpy(list2[GAME_INDEX-1].status, "Draw occurred");
        printf("Draw occured\n");
    }
    else {
        strcpy(list2[GAME_INDEX-1].status, "Incomplete game");
        printf("Incomplete game\n");
    }
    printf("\nPlayer ID %d has score of %d\n", list2[GAME_INDEX-1].player1, list1[id1].score);
    printf("Player ID %d has score of %d\n", list2[GAME_INDEX-1].player2, list1[id2].score);
}

int IsWinningCell(int n, int slice[], int *cellID){
    int sum = 0;

    for(int i=0; i<n ; i++){
        if(slice[i]!=0) {
            sum+=slice[i];
        } 
        else {
            *cellID= i;
        }
    }
    if(sum == 2)
        return 1;
    if(sum == 10)
        return 5;
    return 0;
}

char ListWinningCells(int m, int n, char board[][n]) {
    char mark;
    if(!IsValidBoard(m,n,board)) {
        printf("\nit is not a valid board\n\n");
    }
    int boardStatus[9] = {0};
    int winningCombination[8][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
            {0,3,6},
            {1,4,7},
            {2,5,8},
            {0,4,8},
            {2,4,6}
    };

    for(int i =0; i<m; i++){
        for(int j=0; j< n; j++){
            if(board[i][j]=='X'){
                boardStatus[i*(m)+j ]= 1;
            }
            else if(board[i][j]=='O'){
                boardStatus[i*(m)+j] = 5;
            }
        }
    }
    int slice[3];
    int winCell = -1;
    int result;
    int flag = 1;
    
    for(int i =0; i<8; i++){
        for(int j=0; j<3;j++){
            slice[j] = boardStatus[winningCombination[i][j]];
        }
        winCell = -1;
        result = IsWinningCell(3,slice,&winCell);
        if(winCell!=-1 && result!=0) {
            mark = ((result==1)? 'X':'O');
            printf("\nWining cell is: %d for %c\n", winningCombination[i][winCell]+1, mark);
            flag = 0;
        }
    }
    if(flag){
        printf("\nNo winning cell detected\n");
    }
    return mark;
}
#include <stdio.h>
#include <string.h>

struct Player {
    char playerName[50];
    int ballScores[12];
    int totalScore;
};

int validateScore(int score) {
    return (score >= 0 && score <= 6);
}

void playGame(struct Player *player) {
    printf("\nPlayer: %s, Enter your scores for 12 balls:\n", player->playerName);
    player->totalScore = 0; 
    for (int i = 0; i < 12; i++) {
        printf("Ball %d: ", i + 1);
        int score;
        scanf("%d", &score);
        if (validateScore(score)) {
            player->ballScores[i] = score;
            player->totalScore += score;
        } else {
            printf("Invalid score! Ball marked but no runs awarded.\n");
            player->ballScores[i] = 0; 
        }
    }
}

void findWinner(struct Player player1, struct Player player2) {
    printf("\n--- Match Result ---\n");
    if (player1.totalScore > player2.totalScore) {
        printf("Winner: %s with %d runs!\n", player1.playerName, player1.totalScore);
    } else if (player2.totalScore > player1.totalScore) {
        printf("Winner: %s with %d runs!\n", player2.playerName, player2.totalScore);
    } else {
        printf("It's a tie! Both players scored %d runs.\n", player1.totalScore);
    }
}

void displayMatchScoreboard(struct Player player1, struct Player player2) {
    printf("\n--- Match Scoreboard ---\n");
    struct Player players[2] = {player1, player2};

    for (int i = 0; i < 2; i++) {
        printf("\nPlayer: %s\n", players[i].playerName);
        printf("Scores by ball: ");
        for (int j = 0; j < 12; j++) {
            printf("%d ", players[i].ballScores[j]);
        }
        double averageScore = players[i].totalScore / 12.0;
        printf("\nTotal Score: %d\n", players[i].totalScore);
        printf("Average Score: %.2f\n", averageScore);
    }
}

int main() {
    struct Player player1, player2;

    printf("Enter name for Player 1: ");
    scanf("%s", player1.playerName);
    printf("Enter name for Player 2: ");
    scanf("%s", player2.playerName);

    playGame(&player1);
    playGame(&player2);
    
    displayMatchScoreboard(player1, player2);

    findWinner(player1, player2);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define N 52

typedef struct {
    char rank[3];
    char *suit;
} card;

void init_rank_digit(card *arr, int d)
{
    sprintf(arr[0].rank, "%d", d);
    arr[0].suit = "♠";
    sprintf(arr[1].rank, "%d", d);
    arr[1].suit = "♦";
    sprintf(arr[2].rank, "%d", d);
    arr[2].suit = "♣";
    sprintf(arr[3].rank, "%d", d);
    arr[3].suit = "♥";
}

void init_rank_string(card *arr, char *s)
{
    sprintf(arr[0].rank, "%s", s);
    arr[0].suit = "♠";
    sprintf(arr[1].rank, "%s", s);
    arr[1].suit = "♦";
    sprintf(arr[2].rank, "%s", s);
    arr[2].suit = "♣";
    sprintf(arr[3].rank, "%s", s);
    arr[3].suit = "♥";
}

void init(card *arr)
{
    int i = 0;

    for (int j = 2; j != 10; ++j) {
        init_rank_digit(&arr[i], j);
        i += 4;
    }

    init_rank_string(&arr[i], "10");
    i += 4;
    init_rank_string(&arr[i], "J");
    i += 4;
    init_rank_string(&arr[i], "Q");
    i += 4;
    init_rank_string(&arr[i], "K");
    i += 4;
    init_rank_string(&arr[i], "A");
    i += 4;
}

void shuffle(card *arr)
{
    srand(time(NULL));
    for (int i = 0; i != N; ++i) {
        int pos = rand() % N;
        card tmp = arr[i];
        arr[i] = arr[pos];
        arr[pos] = tmp;
    }
}

void print_a_card(card *c)
{
    printf("+------------------+\n");

    if (strcmp(c->rank, "10") == 0)
        printf("| %s %s %6c %s %s |\n", c->rank, c->suit, ' ', c->rank, c->suit);
    else
        printf("| %s %s %8c %s %s |\n", c->rank, c->suit, ' ', c->rank, c->suit);

    for (int i = 0; i!= 10; ++i)
        printf("| %16c |\n", ' ');

    if (strcmp(c->rank, "10") == 0)
        printf("| %s %s %6c %s %s |\n", c->rank, c->suit, ' ', c->rank, c->suit);
    else
        printf("| %s %s %8c %s %s |\n", c->rank, c->suit, ' ', c->rank, c->suit);

    printf("+------------------+\n");
}

void print_a_card_head(card *c)
{
    printf("+------------------+\n");

    if (strcmp(c->rank, "10") == 0)
        printf("| %s %s %6c %s %s |\n", c->rank, c->suit, ' ', c->rank, c->suit);
    else
        printf("| %s %s %8c %s %s |\n", c->rank, c->suit, ' ', c->rank, c->suit);

}

void print_a_card_left(card *c, int size, int show)
{
    if (size <= 0) {
        for (int i = 0; i != 14; ++i)
            printf("\n");
        return;
    }

    for (int i = 0; i < size - 1; ++i)
        printf("+-----");
    printf("+------------------+\n");

    for (int i = 0; i < size - 1; ++i)
        if (!show)
            printf("|*****");
        else if (strcmp(c[i].rank, "10") == 0)
            printf("| %s %s", c[i].rank, c[i].suit);
        else
            printf("| %s %s ", c[i].rank, c[i].suit);

    if (!show)
        printf("|******************|\n");
    else if (strcmp(c[size - 1].rank, "10") == 0)
        printf("| %s %s %6c %s %s |\n", c[size - 1].rank, c[size - 1].suit, ' ', c[size - 1].rank, c[size - 1].suit);
    else
        printf("| %s %s %8c %s %s |\n", c[size - 1].rank, c[size - 1].suit, ' ', c[size - 1].rank, c[size - 1].suit);

    for (int i = 0; i != 10; ++i) {
        for (int j = 0; j < size - 1; ++j)
            if (!show)
                printf("|*****");
            else
                printf("|     ");
        if (!show)
            printf("|******************|\n");
        else
            printf("| %16c |\n", ' ');
    }

    for (int i = 0; i < size - 1; ++i)
        if (!show)
            printf("|*****");
        else if (strcmp(c[i].rank, "10") == 0)
            printf("| %s %s", c[i].rank, c[i].suit);
        else
            printf("| %s %s ", c[i].rank, c[i].suit);

    if (!show)
        printf("|******************|\n");
    else if (strcmp(c[size - 1].rank, "10") == 0)
        printf("| %s %s %6c %s %s |\n", c[size - 1].rank, c[size - 1].suit, ' ', c[size - 1].rank, c[size - 1].suit);
    else
        printf("| %s %s %8c %s %s |\n", c[size - 1].rank, c[size - 1].suit, ' ', c[size - 1].rank, c[size - 1].suit);

    for (int i = 0; i < size - 1; ++i)
        printf("+-----");
    printf("+------------------+\n");

}

int main(int argc, char **argv)
{
    card cards[N];
    card stack[N];

    int me = 0, bot = N/2;

    int rounds = N/2;

    int sp = 0;
    int my = 0, bots = 0;

    init(cards);
    shuffle(cards);

    for (; rounds > 0; --rounds) {
        for (int i = 0; i != 200; ++i)
            printf("\n");

        print_a_card_left(&cards[bot], rounds, 0);
        printf("--------------------------------> SCORE: %d\n", bots);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        print_a_card_left(stack, sp, 1);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("                                  SCORE: %d\n", my);
        print_a_card_left(&cards[me], rounds, 1);

        sleep(1); // bot's turn

        for (int i = 0; i != 200; ++i)
            printf("\n");

        print_a_card_left(&cards[bot], rounds - 1, 0);
        printf("                                  SCORE: %d\n", bots);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        stack[sp++] = cards[bot + rounds - 1]; // bot's card
        print_a_card_left(stack, sp, 1);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("                                  SCORE: %d\n", my);
        print_a_card_left(&cards[me], rounds, 1);

        sleep(1);

        for (int i = 0; i != sp - 1; ++i) {
            if (strcmp(stack[i].rank, stack[sp - 1].rank) == 0) {
                bots += sp - i;
                sp = i;
                break;
            }
        }

        for (int i = 0; i != 200; ++i)
            printf("\n");

        print_a_card_left(&cards[bot], rounds - 1, 0);
        printf("                                  SCORE: %d\n", bots);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        print_a_card_left(stack, sp, 1);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("--------- YOUR TURN ------------> SCORE: %d\n", my);
        print_a_card_left(&cards[me], rounds, 1);

        getchar(); // my turn

        for (int i = 0; i != 200; ++i)
            printf("\n");

        print_a_card_left(&cards[bot], rounds - 1, 0);
        printf("                                  SCORE: %d\n", bots);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        stack[sp++] = cards[me + rounds - 1]; // my card
        print_a_card_left(stack, sp, 1);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("                                  SCORE: %d\n", my);
        print_a_card_left(&cards[me], rounds - 1, 1);

        sleep(1);

        for (int i = 0; i != sp - 1; ++i) {
            if (strcmp(stack[i].rank, stack[sp - 1].rank) == 0) {
                my += sp - i;
                sp = i;
                break;
            }
        }
    }

    print_a_card_left(&cards[bot], 0, 0);
    printf("                                  SCORE: %d\n", bots);
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    print_a_card_left(stack, sp, 1);
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                                  SCORE: %d     %s\n", my, (my >= bots) ? "YOU WIN!" : "YOU LOSE...");
    print_a_card_left(&cards[me], 0, 1);


    return 0;
}

/*
Question:01
Assume that you are the main developer of a famous Satellite Television company that plays movies to its subscribed users
(but not on demand). You are supposed to write their software to implement the following criteria:
1) The movies are stored in the database with its rating, length, and genre.
2) The rating should be a number from 1 to 5. The length should be from 30 to 200 minutes.
The genre should be classic, action, or drama. You must place checks to keep things in these limits.
3) The movie having the highest rating will be played first.
4) If the rating of two movies is same, the one having longer length will be played first.
5) If the length of two movies is same, the one having action genre will be played first.
*/

//Code

#include<stdio.h>
#include<conio.h>
#include<string.h>
#define SIZE 5

typedef struct movie {

    int length;
    int rating;
    char genre[10];
}Movie;

void initilize(Movie *movie);
void display(Movie *movie);
void sort(Movie *movie);
void changeTemp(Movie *movie, int i, int j);

int main() {

    Movie movie[SIZE];
    initilize(movie);

    puts(">>>>>>-------------User Input------------->>>>>>>>>");
    display(movie);

    puts("\n\n>>>>>>-------------Sorted------------->>>>>>>>>");
    sort(movie);
    display(movie);

    int timer = 0;
    puts("\n\n-----------------------------");
    puts("Movie Time Slot\t |   Genre  |");
    puts("-----------------------------");
    for(int i = 0; i < SIZE; i++) {
        if(i == 0) {
            printf("%3d --- %3d\t | %8s |\n", timer, movie[i].length + timer, movie[i].genre);
            timer += movie[i].length;
        }
        else {
            printf("%3d --- %3d\t | %8s |\n", timer + 1, movie[i].length + timer, movie[i].genre);
            timer += movie[i].length;
        }
    }

    return 0;
}

void sort(Movie *movie) {

    for(int i = 0; i < SIZE; i++) {

        for(int j = 1 + i; j < SIZE; j++) {

            if(movie[i].rating < movie[j].rating) {
                changeTemp(movie, i, j);
            }
            else {
                if(movie[i].rating == movie[j].rating) {
                    if(movie[i].length < movie[j].length) {
                        changeTemp(movie, i, j);
                    }//inner if
                    else {
                        if(movie[i].length == movie[j].length) {
                            if(strcmp(movie[i].genre, "Action")) {
                                changeTemp(movie, i, j);
                            }
                        }//inner most if
                    }
                } //outer if
            }//else

        }//inner loop
    }//outer loop

}

void changeTemp(Movie *movie, int i, int j) {

    int rTemp, lTemp;
    char gTemp[10];

    rTemp = movie[i].rating;
    lTemp = movie[i].length;
    strcpy(gTemp, movie[i].genre);

    movie[i].rating = movie[j].rating;
    movie[i].length = movie[j].length;
    strcpy(movie[i].genre, movie[j].genre);

    movie[j].rating = rTemp;
    movie[j].length = lTemp;
    strcpy(movie[j].genre, gTemp);
}

void display(Movie *movie) {

    puts("---------------------------------------------------");
    printf("  %s\t\t | \tRating\t | \t  Length  |\n", "Genre");
    puts("---------------------------------------------------");
    for(int i = 0; i < SIZE; i++) {
        printf("%8s \t | \t %3d \t |\t  %4d    |\n",
               movie[i].genre, movie[i].rating, movie[i].length);
    }
}

//for dynamic input
void initilize(Movie *movie) {

    int sent = 0;
    char str[10];
    char type[3][10] = {"Action", "Drama", "Classic"};

    for(int i = 0; i < SIZE; i++) {

        int sent = 0;
        printf("Enter the Movie %d Detail :->\n", i + 1);

        do {
            printf("Enter the Movie Rating (1 to 5) : ");
            scanf("%d", &movie[i].rating);
        }while(!(movie[i].rating >= 1 && movie[i].rating <= 5));

        do {
            printf("Enter the Movie Length (30 to 200) : ");
            scanf("%d", &movie[i].length);
        }while(!(movie[i].length >= 30 && movie[i].length <= 200));

        do {
            printf("Enter the Movie Genre (Classic, Action, Drama) : ");
            scanf("%s", movie[i].genre);
            //movie[i].genre = str;

            for(int j = 0; j < 3; j++) {
                if(!strcmp(movie[i].genre, type[j])) {
                    sent = -1;
                    break;
                }
            }
        }while(sent != -1);

        puts(" ");
        printf("%s", movie[i].genre);
    }
}

/*
//for static input
void initilize(Movie *movie) {

    movie[0].length = 150;
    movie[0].rating = 3;
    strcpy(movie[0].genre, "Classic");

    movie[1].length = 100;
    movie[1].rating = 4;
    strcpy(movie[1].genre, "Drama");

    movie[2].length = 90;
    movie[2].rating = 2;
    strcpy(movie[2].genre, "Action");

    movie[3].length = 95;
    movie[3].rating = 2;
    strcpy(movie[3].genre, "Drama");

    movie[4].length = 100;
    movie[4].rating = 4;
    strcpy(movie[4].genre, "Action");

}
*/

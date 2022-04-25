/*
0 --> Arrival Time
1 --> Brust Time
2 --> Priority
*/

#include<stdio.h>
#include<conio.h>
#define SIZE 5

void display(int cpu[SIZE][3], char *id[]);
void arrivalSort(int cpu[SIZE][3], char *id[]);
void prioritySort(int cpu[SIZE][3], char *id[]);

int main() {

    int cpu[SIZE][3] = {{1, 3, 2}, {4, 4, 4}, {6, 5, 5}, {5, 6, 3}, {3, 7, 1}};
    char *processId[SIZE] = {"P1", "P2", "P3", "P4", "P5"};

    puts(">>>>------------User Input-----------<<<<<\n");
    display(cpu, processId);

    puts("\n\n>>>>------------Arrival Sort-----------<<<<<\n");
    arrivalSort(cpu, processId);
    display(cpu, processId);

    puts("\n\n>>>>------------Priority Sort-----------<<<<<\n");
    prioritySort(cpu, processId);
    display(cpu, processId);

    int timer = 0;
    float free = 0;
    float wait = 0;
    int waitingTime = 0;
    float turnTime = 0;

    puts("\n\n>>>>------------Output-----------<<<<<\n");
    puts("Time Slot\tProcess ID\tWaiting Time\tTurn Around Time");
    for(int i = 0; i < SIZE; i++) {
        if(timer < cpu[i][0]) {
            printf("%2d -- %2d\t Free\n", timer, cpu[i][0]);

            while(timer != cpu[i][0]) {
                timer++;
                free++;
            }
            i--;
        } else {
            waitingTime = timer - cpu[i][0];
            turnTime += waitingTime + cpu[i][1];
            wait += waitingTime;
            printf("%2d -- %2d\t  %s\t\t  %d\t\t  %d\n", timer, (timer + cpu[i][1]), processId[i], waitingTime, waitingTime + cpu[i][1]);
            timer += cpu[i][1];
        }
    }

    printf("\n%s = %.2f sec", "Average Waiting Time", (wait / SIZE));
    printf("\n%s = %.2f sec", "Average Turn Around Time", (turnTime / SIZE));
    printf("\n%s = %.2f%s\n", "CPU Utilization", ( (timer - free) / timer) * 100, "%");


    return 0;
}

void prioritySort(int cpu[SIZE][3], char *id[]) {

    int bTemp;
    int aTemp;
    int prorityTemp;
    char *pTemp;
    int timer = 0;

     for(int i = 1; i < SIZE; i++) {
            timer += cpu[i - 1][1] + cpu[i - 1][0];

            if(cpu[i][0] > timer)
                timer += (-timer + cpu[i][0]);

        for(int j = i + 1; j < SIZE; j++) {
            if(cpu[i][2] > cpu[j][2] && cpu[i][0] <= timer) {
                pTemp = id[i];
                aTemp = cpu[i][0];
                bTemp = cpu[i][1];
                prorityTemp = cpu[i][2];

                id[i] = id[j];
                cpu[i][0] =  cpu[j][0];
                cpu[i][1] = cpu[j][1];
                cpu[i][2] = cpu[j][2];

                id[j] = pTemp;
                cpu[j][0] = aTemp;
                cpu[j][1] = bTemp;
                cpu[j][2] = prorityTemp;
            }
        }
    }
}

void arrivalSort(int cpu[SIZE][3], char *id[]) {

    int bTemp;
    int aTemp;
    int prorityTemp;
    char *pTemp;

     for(int i = 0; i < SIZE; i++) {
        for(int j = i + 1; j < SIZE; j++) {
            if(cpu[i][0] > cpu[j][0]) {
                pTemp = id[i];
                aTemp = cpu[i][0];
                bTemp = cpu[i][1];
                prorityTemp = cpu[i][2];

                id[i] = id[j];
                cpu[i][0] =  cpu[j][0];
                cpu[i][1] = cpu[j][1];
                cpu[i][2] = cpu[j][2];

                id[j] = pTemp;
                cpu[j][0] = aTemp;
                cpu[j][1] = bTemp;
                cpu[j][2] = prorityTemp;
            }
        }
    }
}

void display(int cpu[SIZE][3], char *id[]) {

    printf("Process Id\tArrival Time\tBrust Time\tPriority\n");
    for(int i = 0; i < SIZE; i++) {
        printf("%s\t\t  %2d\t\t  %2d\t\t  %2d\n", id[i], cpu[i][0], cpu[i][1], cpu[i][2]);
    }
}

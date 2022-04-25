#include<stdio.h>
#include<conio.h>
#define row 5

//Function Prototypes
void display(int (*cpu)[3]);
void sortArrivalTime(int (*cpu)[3]);

int main() {

    int cpu[row][3] = {{1, 5, 4}, {2, 4, 6}, {3, 3, 0}, {4, 2, 6}, {5, 4, 5} };

    puts("---------------User Input----------------------");
    display(cpu);


    puts("\n---------------Sorted Arrival Time----------------------");
    sortArrivalTime(cpu);
    display(cpu);

    int timer = 0;
    int dummyId = 0;
    int waiting[5];
    int T_A_T[5];
    float sum = 0;
    float free = 0;

    puts("\n\n-------------OutPut--------------\n");
    puts("Time Slot\tProcess ID");
    for(int i = 0; i < row; i++) {
        if(timer < cpu[i][2]) {
            printf("%2d -- %2d\t Free\n", timer, cpu[i][2]);

            while(timer != cpu[i][2]) {
                timer++;
                free++;
            }
            i--;
        } else {
                printf("%2d -- %2d\t  P%d\n", timer, (timer + cpu[i][1]), cpu[i][0]);
                dummyId = cpu[i][0];
                waiting[dummyId] = timer - cpu[i][2];
                sum += waiting[dummyId];
                T_A_T[dummyId] = waiting[dummyId] + cpu[i][1];
                timer += cpu[i][1];
        }
    }

    puts("\n\nProcess ID\tWaiting Time\tTurn Around Time");
    for(int i = 1; i < row + 1; i++) {
        printf("P%d\t\t %2d\t\t   %2d\n", i, waiting[i], T_A_T[i]);
    }

    printf("\n%s = %.2f sec", "Average Waiting Time", (sum / 5));
    printf("\n%s = %.2f%s\n", "CPU Utilization", ( (timer - free) / timer) * 100, "%");

    return 0;
}

void sortArrivalTime(int (*cpu)[3]) {

    int processTemp, brustTemp, arrivalTemp;

    for(int i = 0; i < row; i++) {
        for(int j = i + 1; j < row; j++) {
            if(cpu[i][2] > cpu[j][2]) {
                processTemp = cpu[i][0];
                brustTemp = cpu[i][1];
                arrivalTemp = cpu[i][2];

                cpu[i][0] =  cpu[j][0];
                cpu[i][1] = cpu[j][1];
                cpu[i][2] = cpu[j][2];

                cpu[j][0] = processTemp;
                cpu[j][1] = brustTemp;
                cpu[j][2] = arrivalTemp;
            }
        }
    }
}

void display(int (*cpu)[3]) {

    puts("Process ID\tBrust Time\tArrival Time");
    for(int i = 0; i < row; i++) {
        printf("P%d\t\t%4d\t\t%4d", cpu[i][0], cpu[i][1], cpu[i][2]);
        puts("");
    }

}

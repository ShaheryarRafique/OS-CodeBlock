#include<stdio.h>
#include<conio.h>
#define SIZE 5

typedef struct cpu {

    int brustTime;
    int arrivalTime;
    char *processId;

}CPU;

void initilize(CPU *cpu);
void display(CPU *cpu);
void arrivalSort(CPU *cpu);
void brustSort(CPU *cpu);

int main() {

    CPU cpu[SIZE];
    initilize(cpu);

    puts(">>>>------------User Input-----------<<<<<\n");
    display(cpu);

    puts("\n\n>>>>------------Arrival Sort-----------<<<<<\n");
    arrivalSort(cpu);
    display(cpu);

    puts("\n\n>>>>------------Brust Sort-----------<<<<<\n");
    brustSort(cpu);
    display(cpu);

    int timer = 0;
    float waiting = 0;
    float turnTime = 0;
    int wait = 0;
    float extraTime = 0;

    puts("\n\n>>>>------------Output-----------<<<<<\n");
    puts("Time Slot\tProcess ID\tWaiting Time\tTurn Around Time");
    for(int i = 0; i < SIZE; i++) {
        if(timer < cpu[i].arrivalTime) {
            printf("%2d -- %2d\t Free\n", timer, cpu[i].arrivalTime);
            while(timer < cpu[i].arrivalTime)
                timer++;
            extraTime += timer;
            i--;
        }
        else {
            waiting += timer - cpu[i].arrivalTime;
            wait = timer - cpu[i].arrivalTime;
            turnTime += wait + cpu[i].brustTime;
            printf("%2d -- %2d\t  %s\t\t    %d\t\t    %d\n", timer, (timer + cpu[i].brustTime), cpu[i].processId, wait, wait + cpu[i].brustTime);
            timer += cpu[i].brustTime;
        }
    }

    printf("\n%s = %.2f sec", "Average Waiting Time", (waiting / SIZE));
    printf("\n%s = %.2f sec", "Average Turn Around Time", (turnTime / SIZE));
    printf("\n%s = %.2f%s\n", "CPU Utilization", ((timer - extraTime) / timer) * 100, "%");

    return 0;
}

void brustSort(CPU *cpu) {

    int bTemp;
    int aTemp;
    char *pTemp;
    int timer = 0;

    for(int i = 1; i < SIZE; i++) {
            timer += cpu[i - 1].brustTime + cpu[i - 1].arrivalTime;

            if(cpu[i].arrivalTime > timer) {
                timer += (cpu[i].arrivalTime - timer);
            }

        for(int j = 1 + i; j < SIZE; j++) {
            if(cpu[i].brustTime > cpu[j].brustTime && cpu[j].arrivalTime <= timer) {
                pTemp = cpu[i].processId;
                aTemp = cpu[i].arrivalTime;
                bTemp = cpu[i].brustTime;

                cpu[i].processId = cpu[j].processId;
                cpu[i].arrivalTime = cpu[j].arrivalTime;
                cpu[i].brustTime = cpu[j].brustTime;


                cpu[j].processId = pTemp;
                cpu[j].arrivalTime = aTemp;
                cpu[j].brustTime = bTemp;
            }
        }
    }
}

void arrivalSort(CPU *cpu) {

    int bTemp;
    int aTemp;
    char *pTemp;

    for(int i = 0; i < SIZE; i++) {
        for(int j = 1 + i; j < SIZE; j++) {
            if(cpu[i].arrivalTime >= cpu[j].arrivalTime) {
                pTemp = cpu[i].processId;
                aTemp = cpu[i].arrivalTime;
                bTemp = cpu[i].brustTime;

                cpu[i].processId = cpu[j].processId;
                cpu[i].arrivalTime = cpu[j].arrivalTime;
                cpu[i].brustTime = cpu[j].brustTime;


                cpu[j].processId = pTemp;
                cpu[j].arrivalTime = aTemp;
                cpu[j].brustTime = bTemp;
            }
        }
    }
}

void display(CPU *cpu) {

    printf("Process Id\tBrust Time\tArrival Time\n");

    for(int i = 0; i < SIZE; i++) {
        printf("%2s\t\t  %2d\t\t  %2d\n", cpu[i].processId, cpu[i].brustTime, cpu[i].arrivalTime);
    }
}

void initilize(CPU *cpu) {

    cpu[0].arrivalTime = 1;
    cpu[0].brustTime = 3;
    cpu[0].processId = "P1";

    cpu[1].arrivalTime = 4;
    cpu[1].brustTime = 4;
    cpu[1].processId = "P2";

    cpu[2].arrivalTime = 6;
    cpu[2].brustTime = 5;
    cpu[2].processId = "P3";

    cpu[3].arrivalTime = 5;
    cpu[3].brustTime = 6;
    cpu[3].processId = "P4";

    cpu[4].arrivalTime = 3;
    cpu[4].brustTime = 7;
    cpu[4].processId = "P5";

}

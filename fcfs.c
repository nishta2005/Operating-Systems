#include<stdio.h>

    int n, i, j, pos, temp, choice, Burst_time[20], Waiting_time[20], Turn_around_time[20], process[20], total=0;

    float avg_Turn_around_time=0, avg_Waiting_time=0;



int FCFS()

{

    Waiting_time[0]=0;



    for(i=1;i<n;i++)

    {

        Waiting_time[i]=0;

        for(j=0;j<i;j++)

            Waiting_time[i]+=Burst_time[j];

    }



    printf("\nProcess\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time");



    for(i=0;i<n;i++)

    {

        Turn_around_time[i]=Burst_time[i]+Waiting_time[i];

        avg_Waiting_time+=Waiting_time[i];

        avg_Turn_around_time+=Turn_around_time[i];

        printf("\nP[%d]\t\t%d\t\t\t%d\t\t\t\t%d",i+1,Burst_time[i],Waiting_time[i],Turn_around_time[i]);

    }



    avg_Waiting_time =(float)(avg_Waiting_time)/(float)i;

    avg_Turn_around_time=(float)(avg_Turn_around_time)/(float)i;

    printf("\nAverage Waiting Time:%.2f",avg_Waiting_time);

    printf("\nAverage Turnaround Time:%.2f\n",avg_Turn_around_time);



    return 0;

}



int SJF()

{

    //sorting

    for(i=0;i<n;i++)

    {

        pos=i;

        for(j=i+1;j<n;j++)

        {

            if(Burst_time[j]<Burst_time[pos])

                pos=j;

        }



        temp=Burst_time[i];

        Burst_time[i]=Burst_time[pos];

        Burst_time[pos]=temp;



        temp=process[i];

        process[i]=process[pos];

        process[pos]=temp;

    }

        Waiting_time[0]=0;





    for(i=1;i<n;i++)

    {

        Waiting_time[i]=0;



        for(j=0;j<i;j++)

            Waiting_time[i]+=Burst_time[j];



        total+=Waiting_time[i];

    }



    avg_Waiting_time=(float)total/n;

    total=0;



    printf("\nProcess\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time");



    for(i=0;i<n;i++)

    {

        Turn_around_time[i]=Burst_time[i]+Waiting_time[i];

        total+=Turn_around_time[i];

        printf("\nP[%d]\t\t%d\t\t\t%d\t\t\t\t%d",process[i],Burst_time[i],Waiting_time[i],Turn_around_time[i]);

    }



    avg_Turn_around_time=(float)total/n;

    printf("\n\nAverage Waiting Time=%f",avg_Waiting_time);

    printf("\nAverage Turnaround Time=%f\n",avg_Turn_around_time);

}



int main()

{

    printf("Enter the total number of processes:");

    scanf("%d",&n);



    printf("\nEnter Burst Time:\n");

    for(i=0;i<n;i++)

    {

        printf("P[%d]:",i+1);

        scanf("%d",&Burst_time[i]);

        process[i]=i+1;

    }



    while(1)

    {   printf("\n-----MAIN MENU-----\n");

        printf("1. FCFS Scheduling\n2. SJF Scheduling\n");

        printf("\nEnter your choice:");

        scanf("%d", &choice);

        switch(choice)

        {

            case 1: FCFS();

            break;



            case 2: SJF();

            break;



            default: printf("Invalid Input!!!");

        }

    }

    return 0;

}

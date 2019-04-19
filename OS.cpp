#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct Queue
{
	int pid;
	int ArrivalTime;
	int BurstTime;
};

float CalTotalBurstTime(struct Queue* Que,int n)
{
	float BurstTime=0;//to calculate total burst time
	for(int i=0;i<n;i++)
	{
		BurstTime+=(Que+i)->BurstTime;
	}
	return BurstTime;
}

float processFun(struct Queue* q, int size,struct Queue* Que);
void minArrivalTime(struct Queue* que,int size);
void minBurstTime(struct Queue* que,int size);
int CheckAllProcessFinish(struct Queue* Que,int size);

int main()
{
	int i,n1,n2;
	float TotalTurnAroundTime,AvgTurnAroundTime,AvgWaitingTime,TotalBurstTime;
	printf("\n Multilevel Queue On Preemptive Shortest Job Remaining First \n");
	printf("\nNo of Processes in Queue1: ");
	scanf("%d",&n1);
	struct Queue *q1=(struct Queue*)malloc(n1*sizeof(struct Queue));
	struct Queue *Que1=(struct Queue*)malloc(n1*sizeof(struct Queue));
	printf("\n Details for Processes in Queue1:\n");

	for(i=0;i<n1;i++)
	{
		printf("For Process %d:\n",i+1);
		(q1+i)->pid=i+1;
		(Que1+i)->pid=i+1;
		printf("PId: %d\n", (q1+i)->pid);
		printf("Arrival Time: ");
		scanf("%d",&(q1+i)->ArrivalTime);
		(Que1+i)->ArrivalTime=(q1+i)->ArrivalTime;
		printf("Burst Time: ");
		scanf("%d",&(q1+i)->BurstTime);
		(Que1+i)->BurstTime=(q1+i)->BurstTime;
		printf("\n");
	}
	
	printf("Number of Processes in Queue2: ");
	scanf("%d",&n2);
	struct Queue *q2=(struct Queue*)malloc(n1*sizeof(struct Queue));
	struct Queue *Que2=(struct Queue*)malloc(n1*sizeof(struct Queue));
	printf("\nDetails for Processes in Queue2:\n");
	for(i=0;i<n2;i++)
	{
		printf("For Process %d:\n",i+1);
		(q2+i)->pid=i+1;
		(Que2+i)->pid=i+1;
		printf("PId: %d\n", (q2+i)->pid);
		
		printf("Arrival Time: ");
		scanf("%d",&(q2+i)->ArrivalTime);
		(Que2+i)->ArrivalTime=(q2+i)->ArrivalTime;
		printf("Burst Time: ");
		scanf("%d",&(q2+i)->BurstTime);
		(Que2+i)->BurstTime=(q2+i)->BurstTime;
		printf("\n");
	}
	printf("\n");

	printf("\nDetails Of Processes in Queue1\n");
	printf("\n Process: | Arrival Time:  | Burst Time:");
	for(i=0;i<n1;i++)
    {
        printf("\n P%d          %d               %d      ",(q1+i)->pid,(q1+i)->ArrivalTime,(q1+i)->BurstTime);
    }
    printf("\n");

    printf("\nDetails Of Processes in Queue2\n");
	printf("\n Process: | Arival Time: | Burst Time: ");
	for(i=0;i<n2;i++)
    {
        printf("\n P%d         %d              %d  ",(q2+i)->pid,(q2+i)->ArrivalTime,(q2+i)->BurstTime);
    }
    printf("\n\n");
    
    TotalTurnAroundTime=processFun(q1,n1,Que1);
    AvgTurnAroundTime=TotalTurnAroundTime/n1;
    TotalBurstTime=CalTotalBurstTime(q1,n1);
    AvgWaitingTime=(TotalTurnAroundTime-TotalBurstTime)/n1;

    printf("\n");
    printf("\nAverage TurnAroundTime: %.2f\n", AvgTurnAroundTime);
    printf("\nAverage WaitingTime: %.2f\n",AvgWaitingTime);

    printf("\n\n");
	return 0;
}

float processFun(struct Queue* q, int size,struct Queue* Que)
{
	int TimeCounter=0,flag=0;
	float tAt=0,Wt=0;
	while(!CheckAllProcessFinish(Que,size))
	{
		if(flag==0)
		{
			minArrivalTime(Que,size);
			TimeCounter+=Que->ArrivalTime;
			flag++;
		}
		else
		{
			minBurstTime(Que,size);
		}
		int check=0;
		for(int i=0;i<size;i++)
		{
			if((Que+i)->BurstTime!=0 && TimeCounter>=(Que+i)->ArrivalTime)
			{
				check=1;
				break;
			}
					
		}
		if(check==0)
		{
			minArrivalTime(Que,size);
			for(int i=0;i<size;i++)
			{
				if((Que+i)->BurstTime!=0)
				{
					int x=TimeCounter;
					TimeCounter+=((Que+i)->ArrivalTime)-x;
					break;
				}
			}
		}
		for(int i=0;i<size;i++)
		{
			if((Que+i)->BurstTime!=0 && TimeCounter>=(Que+i)->ArrivalTime)
			{
				if((Que+i)->BurstTime>2)
				{
					(Que+i)->BurstTime=(Que+i)->BurstTime-2;
					TimeCounter+=2;
				}
				else
				{
					TimeCounter+=(Que+i)->BurstTime;
					(Que+i)->BurstTime=0;
					int x=TimeCounter;
					tAt+=x-((Que+i)->ArrivalTime);
				}
				break;				
			}
		}
	}
	return tAt;
}

void minArrivalTime(struct Queue* que,int size)
{
	int i,j;
	for(i=1;i<=size-1;i++)
	{
		for(j=0;j<size-1;j++)
		{
			if(((que+j)->ArrivalTime)>((que+j+1)->ArrivalTime))
			{
				//to swap Arrival time in dec Order
				int temp=(que+j)->ArrivalTime;
				(que+j)->ArrivalTime=(que+j+1)->ArrivalTime;
				(que+j+1)->ArrivalTime=temp;

				//to swap Burst Time in dec Order
				temp=(que+j)->BurstTime;
				(que+j)->BurstTime=(que+j+1)->BurstTime;
				(que+j+1)->BurstTime=temp;

				//to swap pid 
				temp=(que+j)->pid;
				(que+j)->pid=(que+j+1)->pid;
				(que+j+1)->pid=temp;
			}
			else if(((que+j)->ArrivalTime)==((que+j+1)->ArrivalTime))
			{
				if(((que+j)->BurstTime)>((que+j+1)->BurstTime))
				{
					//to swap Burst Time in dec Order
					int temp=(que+j)->BurstTime;
					(que+j)->BurstTime=(que+j+1)->BurstTime;
					(que+j+1)->BurstTime=temp;

					//to swap pid 
					temp=(que+j)->pid;
					(que+j)->pid=(que+j+1)->pid;
					(que+j+1)->pid=temp;

					//to swap Arrival time in dec Order
					temp=(que+j)->ArrivalTime;
					(que+j)->ArrivalTime=(que+j+1)->ArrivalTime;
					(que+j+1)->ArrivalTime=temp;
				}
			}
		}
	}
}

void minBurstTime(struct Queue* que,int size)
{
	int i,j;
	for(i=1;i<=size-1;i++)
	{
		for(j=0;j<size-1;j++)
		{
			if(((que+j)->BurstTime)>((que+j+1)->BurstTime))
			{
				int temp=(que+j)->BurstTime;////swap Burst Time in decreasing Order
				(que+j)->BurstTime=(que+j+1)->BurstTime;
				(que+j+1)->BurstTime=temp;

				temp=(que+j)->pid;//swap pid 
				(que+j)->pid=(que+j+1)->pid;
				(que+j+1)->pid=temp;

				temp=(que+j)->ArrivalTime;////swap Arrival time in decreasing Order
				(que+j)->ArrivalTime=(que+j+1)->ArrivalTime;
				(que+j+1)->ArrivalTime=temp;	
			}
		}
	}
}
int CheckAllProcessFinish(struct Queue* Que,int size)
{
	int flag=1;////to check is there any processes left yet to be processed
	for(int i=0;i<size;i++)
	{
		if((Que+i)->BurstTime!=0)
		{
			flag=0;
			return flag;
		}	
	}
	return flag;
}


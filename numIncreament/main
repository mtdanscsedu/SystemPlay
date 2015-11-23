using namespace std;

#include<iostream>
#include<ctime>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/sem.h>




int main(void)
{
	int sem_id,i,status=0;
	key_t key = 1234567;
	unsigned short *semval;

	semval = (unsigned short*)malloc(sizeof(unsigned short)*2);
	sem_id = semget(key,2,IPC_CREAT|0666);				

	semval[0]=1;
	semval[1]=0;

	semctl(sem_id,0,SETALL,semval);

	for(i=0;i<5;i++)
	{
		int pid=fork();

		if(pid==0)
		{		
			execl("child","child",NULL,NULL);
		}
	}
	
	sleep(50);
	semctl(sem_id,0,IPC_RMID);
	cout<<"All Semaphore removed"<<endl;

return 0;
}

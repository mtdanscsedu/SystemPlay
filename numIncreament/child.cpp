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
	int semid,pid,i;
	key_t key = 1234567;
	unsigned short *semval;
	struct sembuf wait[2],signal[2];

	semval = (unsigned short*)malloc(sizeof(unsigned short)*2);
	semid = semget(key,2,IPC_CREAT);				
	time_t now = time(0);
	tm *ltm = localtime(&now);

	//cout<<"Now :"<<ltm->tm_sec<<endl;

    wait[0].sem_num = 0;
    wait[0].sem_op = -1;
    wait[0].sem_flg = SEM_UNDO;

    signal[0].sem_num = 0;
    signal[0].sem_op = 1;
    signal[0].sem_flg = SEM_UNDO;

    wait[1].sem_num = 1;
    wait[1].sem_op = -1;
    wait[1].sem_flg = SEM_UNDO;

    signal[1].sem_num = 1;
    signal[1].sem_op = 1;
    signal[1].sem_flg = IPC_NOWAIT;


	while(1)
	{
		//semctl(semid,0,GETALL,semval);
		semop(semid,&wait[0],1);
		semctl(semid,0,GETALL,semval);

		if(semval[1]<20)
		{
			semop(semid,&signal[1],1);
			semctl(semid,0,GETALL,semval);
			cout<<"Process "<<getpid()<<" : "<<semval[1]<<endl;
		}
		else
		{
			semop(semid,&signal[0],1);
			break;
		}
		sleep(ltm->tm_sec/20);
		//semctl(semid,0,GETALL,semval);
		semop(semid,&signal[0],1);	
	}	


return 0;
}

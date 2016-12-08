#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(){
	srand(time(NULL));
	int x = random() % 10 + 5;
	
	int semid = semget(ftok("makefile", 22), 1, 0);
	printf("[%d] before access\n", getpid());
	
	struct sembuf sb;
	sb.sem_num = 0; //index. there's only one so 0
	sb.sem_flg = SEM_UNDO; //in case something happens the OS can up a semaphore before it crashes
	sb.sem_op = -1;
	
	semop(semid, &sb, 1); //gotta give address to sembuf structure. 1 bc there's only 1 semaphore
	printf("%d\n", semid);
	printf("[%d] I'm in!\n" , getpid());
	sleep(5);
	sb.sem_op = 1;
	semop(semid, &sb, 1);
	printf("[%d] I'm done\n", getpid());
	return 0;
}

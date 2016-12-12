#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

int main(){
	int *shmp; 
	int semid, shmid, key, len;
	key = ftok("makefile",22);
	semid = semget(key, 1, 0);
	printf("[%d]: hello.\n",getpid());
	
	struct sembuf sb;
	sb.sem_num = 0; //index. there's only one so 0
	sb.sem_flg = SEM_UNDO; //in case something happens the OS can up a semaphore before it crashes
	sb.sem_op = -1;
	
	semop(semid, &sb, 1); //gotta give address to sembuf structure. 1 bc there's only 1 semaphore
	
	shmid = shmget(key, sizeof(int), 0644);
	shmp = (int *)shmat(shmid,0,0);
	len = *shmp;
	
	int fd = open("story.txt", O_RDONLY);
	lseek(fd, len * -1, SEEK_END);
	char line[len+1];
	read(fd, line, len);
	line[len] = 0;	
	close(fd);
	printf(">> %s\n",line);
	
	printf(">> ");
	char new_line[500];
	fgets(new_line, sizeof(new_line), stdin);
	fd = open("story.txt", O_WRONLY | O_APPEND);
	*shmp = strlen(new_line); 
	write(fd, new_line, *shmp);
	close(fd);
	
	sb.sem_op = 1;
	semop(semid, &sb, 1);
	
	printf("[%d]: thank you for your contribution.\n", getpid());
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

void printstory(){
	int fd = open("story.txt", O_RDONLY);
	struct stat buffer;
	stat("story.txt", &buffer);
	
	char storage[buffer.st_size + 1];
	read(fd, storage, buffer.st_size);
	//set end to null
	storage[buffer.st_size + 1] = "\0";
	
	printf("Full story:\n");
	printf("%s", storage);
	
}

int main(int argc, char *argv[]){
		int semid, shmid;
		//call ftok on a random file name with a random number and it'll create or attempt to create unique key
		int key = ftok("makefile" , 22);
		int sc, sh;
		int value;
		int * shmatr;
		if (argv[2])
			value = atoi(argv[2]);
		else
			value = 1;
			
		if (strncmp(argv[1], "-c", strlen(argv[1])) == 0){
			//creating a shared memory
			shmid = shmget(key, 0, O_CREAT | 0644);
			shmatr = (int *)shmat(shmid, 0, 0);
			*shmatr = 0;
			
			//creating a semaphore
			semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644);
			union semun su;
			su.val = value; //setting val of int to 1;
			//setting semaphore value
			sc = semctl(semid, 0, SETVAL, su);
			
			//make file
			int fd = open("story.txt", O_CREAT | O_TRUNC, 0644);
			if (fd == -1){
				printf("file not opened.");
				exit(0);
			}
			close(fd);
			printf("New story created.");
		}
		else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0){
			printstory();
		}
		else if(strncmp(argv[1], "-r", strlen(argv[1])) == 0){
			//removing a semaphore
			semid = semget(key, 1, 0);
			sc = semctl(semid, 0, IPC_RMID);
			
			shmid = shmget(key, sizeof(shmid), 0);
			sh = semctl(shmid, 0, IPC_RMID);
			
			printstory();
		 }

		return 0;
}
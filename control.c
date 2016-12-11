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
#include <errno.h>

void printstory(){
	int fd = open("story.txt", O_RDONLY);
	struct stat buffer;
	stat("story.txt", &buffer);
	
	char storage[buffer.st_size + 1];
	read(fd, storage, buffer.st_size);
	//set end to null
	storage[buffer.st_size + 1] = 0;
	
	printf("Full story:\n");
	printf("%s\n", storage);
	
}

int main(int argc, char *argv[]){
		int semid, shmid;
		//call ftok on a random file name with a random number and it'll create or attempt to create unique key
		int key = ftok("makefile" , 22);
		int fd, value;
		int * shmatr;
		if (argv[2])
			value = atoi(argv[2]);
		else
			value = 1;
			
		if (strncmp(argv[1], "-c", strlen(argv[1])) == 0){
			//hello semaphore
			semid = semget(key, 1, IPC_CREAT | 0644);
			printf("semaphore created: %d\n", semid);

			//setting semaphore value
			union semun su;
			su.val = value;
			semctl(semid, 0, SETVAL, su);

			//hello shared memory
			shmid = shmget(key, sizeof(key), IPC_CREAT | /*IPC_EXCL*/ 0644);
			shmatr = (int *)shmat(shmid, 0, 0);
			*shmatr = 0;

			//hello story.txt
			fd = open("story.txt", O_CREAT | O_TRUNC, 0644);
			close(fd);
		}
		else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0){
			printstory();
		}
		else if(strncmp(argv[1], "-r", strlen(argv[1])) == 0){
			//removing a semaphore
			semid = semget(key, 1, 0);
			semctl(semid, 0, IPC_RMID);

			//removing shared mem
			shmid = shmget(key, sizeof(key), 0);
			shmctl(shmid, IPC_RMID, 0);
			printf("%s\n", strerror(errno));
			
			printstory();
		 }

		return 0;
}
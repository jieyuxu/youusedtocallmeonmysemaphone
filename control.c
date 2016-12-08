#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char *argv[]){
		int semid;
		//call ftok on a random file name with a random number and it'll create or attempt to create unique key
		int key = ftok("makefile" , 22);
		int sc;
		int value;
		if (argv[2])
			value = atoi(argv[2]);
		else
			value = 1;
		if (strncmp(argv[1], "-c", strlen(argv[1])) == 0){
			//creating a semaphore
			semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644);
			printf("semaphore createdL %d\n", semid);
			union semun su;
			//su is a union, which is kind of like a struct except you can only hold one type
			su.val = value; //setting val of int to 1;
			//setting semaphore value
			sc = semctl(semid, 0, SETVAL, su);
			printf("value set: %d\n", sc);
		}
		else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0){
			semid = semget(key, 1, 0);
			//getting the value of a semaphore
			sc = semctl(semid, 0, GETVAL);
		
			printf("semaphore value: %d\n",sc);
		}
		else if(strncmp(argv[1], "-r", strlen(argv[1])) == 0){
			semid = semget(key, 1, 0);
			  //removing a semaphore
			sc = semctl(semid, 0, IPC_RMID);
			printf("semaphore removed: %d\n", sc);
		 }

		return 0;
}
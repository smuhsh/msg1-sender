/*sh2-fork.c*/

#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define KEY_NUM 45450000
#define MEM_SIZE 1024

int main(void){
	int shm_id;
	void *shm_addr;
	int *cal_num;
	int pid;

	if(-1 == (shm_id = shmget((key_t)KEY_NUM, MEM_SIZE, IPC_CREAT | 0666))){
		perror("shmget() error");
		return -1;
	}

	if((void *)-1 == (shm_addr = shmat(shm_id, (void *)0, 0))){
		perror("shmat() error");
		return -1;
	}

	cal_num = (int *)shm_addr;

	while(1){
		//write in the shared memory
		sprintf((char *)shm_addr, "%d", count++);

		printf("test\n");
		sleep(1);
	}
	return(0);
}

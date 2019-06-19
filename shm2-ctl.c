/*shm2-ctl.c*/
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>


#define KEY_NUM 554500
#define MEM_SIZE 1024

int main(void){
	void *shm_addr;
	struct shmid_ds shm_info;

	if(-1 == (shm_id = shmget((key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666))){
		printf("공유 메모리 생성 실패\n");
		return -1;
	}
	else{
		printf("공유 메모리 생성 성공\n");
	}
	if((void *)-1 == (shm_addr = shmat(shm_id, (void*)0,  0))){
		printf("공유 메모리 첨부 실패\n");
		return -1;
	}
	else {
		printf("공유 메모리 첨부 성공\n");
	}


/*pthread3.c*/
/*gcc pthread3.c -lpthread -o pthread*/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

//쓰레드 함수
void *t_function(void *data){
	int id;
	id = *((int *)data);
	printf("Thread start with %d\n",id);
	sleep(5);
	printf("Thread end\n");
}

int main(void){
	pthread_t p_thread;

	int thr_id;
	int status;
	int a = 100;
	int i;

	printf("Before Thred\n");
	thr_id = pthread_creat(&p_thread, NULL, t_function, (void *)&a);
	if(thr_id < 0) {
		perror("thread creat error : ");
		exit(0);
	}
	
	//식별번호 p_thread를 가지는 쓰레드를 detach
	 pthread_datach(p_thread);

	for(i =0; i < 10; i++){
		sleep(1);
		perror("thread detached! \n");
	}

	
	return 0;
	
}


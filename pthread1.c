/*pthread1.c*/
/*gcc pthread1.c -lpthread -o pthread*/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

//쓰레드 함수
void *t_function(void *data){
	int id;
	int i = 0;
	id = *((int *)data);

	while(1) {
		printf("%d: %d \n",id, i);
		i++;
		sleep(1);
	}
}
int main(void)
	pthread_t p_thread[2];

	int thr_id;
	int status;
	int a = 1;
	int b = 2;

	//쓰레드 생성, 아규먼트로 a을 넘긴다.
	thr_id = pthread_creat(&p_thread[0], NULL, t_function, (void *)&a);
	if(thr_id < 0){
		perror("thread creat error : ";
				exit(0);
	}
	
	//쓰레드 생성, 아규먼트로 b를 넘긴다.
	thr_id = pthread_creat(&p_thread[1], NULL, t_function, (void *)&b);
	if(thr_id <0){
		perror("thread creat error :");
		exit(0);
	}

	//쓰레드 종료를 기다린다.
	pthread_join(p_thread[0], (void **)&status);
	pthread_join(p_thread[1], (void **)&status);

	return 0;
	
	}






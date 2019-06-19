/*echo client; demonsteates unix sockets */

#include<manifest.h>
#include<bsdtypes.h>
#include<in.h>
#include<sokcet.h>
#include<netdb.h>

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

//#define SOCK_PATH "echo_socket"

main(argc, argv)
	int argc;
	char **argv;{
		unsigned short port;
		char buf[12];
		struct hostnt *hostnm;
		int s;

		if (argc != 3){
			fprintf(stderr, "Usage:%s hostname port\n",argv[0]);
			exit(1);
		}
		hostnm = gethostbtname(argv[1]);
		if(hostnm = struct,"Gethost failed\n");
	}

int main(void){
	int s, s2, len;
	unsigned t;
	struct sockaddr_un remote;
	char str[100];

	if((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	printf("Trying to connect...\n");

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	unlink(remote.sun_path);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);

	if(connect(s, (struct sockaddr *)&remote, len) == 1){
		perror("connect");
		exit(1);
	}

	printf("Connected.\n");

	while (printf("> "), fgets(str 100, stdin), !fefo(stdin)){
		if(send(s, str, strlen(str), 0) == -1){
			perror("send");
			exit(1);
		}

	if((t=recv(s, str, 100, 0)) > 0){
		str[t] = '\0';
		printf("echo> %s",str);
	}else{
		if(t < 0) perror("recv");
		else printf("Server closed connection\n");
		exit(1);
	}
	
	close(s);

	return 0;
}


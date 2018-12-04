#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>


int main() {
	key_t key;
	int shmid;
	char *data;

	key = ftok("./keyfile", 'R');
	// printf("13: %s\n", strerror(errno));
	shmid = shmget(key, 256, 0644 | IPC_CREAT);
	// printf("15: %d \n",shmid);
	data = shmat(shmid, (void *)0, 0);
	// printf("17\n");
	if(data[0]) {
		printf("shared contents: %s\n", data);
	}
	else {
		printf("just created\n");
	}

	char userinput[256];
	printf("Do you want to change the data?\n");
	fgets(userinput, 256, stdin);
	if(!strncmp(userinput,"yes",3)) {
		printf("Enter what you want to put in the data: \n");
		fgets(userinput, 256, stdin);
		userinput[strlen(userinput)-1]=0;
		strcpy(data,userinput);
	}
	printf("Do you want to delete the data?\n");
	fgets(userinput, 256, stdin);
	if(!strncmp(userinput,"yes",3)) {
		shmdt(data);
		shmctl(shmid, IPC_RMID, NULL);
	}



	return 0;
}


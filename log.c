/*
*__author__= Brindal
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define path 20

void log_write(char *log_mesg){

	time_t timer;
	char log_time[20];
	struct tm* tm_info;
    char path[path_size];
    char base_path[path_size];

    struct stat st;
	if (!(stat("/home/log/",&st) == 0)){
		//create directory, if directory doesn't exist
		system("mkdir /home/log");

		// if it still has issue while creating, it should be directory permission issue.
		if (!(stat("/home/log",&st) == 0))
		{
			printf("Unable to create directory due to permission issue so log is printed on the screen\n");
			printf("%s",log_mesg);
			return;
		}
	}

    //log_file is the name of the file, if you want to change the name change it here.
    strcpy(path, "/home/log/log_file");

    //to note current time of the current system
	time(&timer);
	tm_info = localtime(&timer);
	strftime(log_time, 20, "%y-%m-%d %H:%M:%S", tm_info);

	FILE *file;

	file = fopen(path,"r");


    if (!file)
	{ //if file doesn't exist, create it
		file=fopen(path, "w");
		fclose(file);
	}

	//to append log to the existed file
    file = fopen(path,"a");

	//to write a message into the file
	if (file==NULL){
			printf("unable to access log-file\n");
			return;
	}
	else{
            //writing to the file
			fprintf(file, log_time);
			fprintf(file, "\t");
			fprintf(file, log_mesg);
			fprintf(file, "\n");
	}

	//file closing
	if (file){
		fclose(file);
	}

}

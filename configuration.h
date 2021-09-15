#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEMPERATURE_COUNT 100
#define REQUIRED_ARG_COUNT 4
#define TEMPERATURE_FILE "./example_files/temp1"

typedef struct Configurations {
	char recipient[50];
	int intervalInSeconds;
	double temperatureThreshold;
} Configuration;

Configuration  parseArguments(int count, char *arguments[]) {

	if(count < REQUIRED_ARG_COUNT){
		fprintf(stderr, "Missing arguments.. Program will terminate!\n");
		exit(EXIT_FAILURE);
	}

	Configuration config;
	config.temperatureThreshold = atof(arguments[1]);
	config.intervalInSeconds = atoi(arguments[2]);
	strncpy(config.recipient, arguments[3], sizeof(config.recipient));

	return config;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define REQUIRED_ARG_COUNT 4
#define TEMPERATURE_COUNT 100
#define TEMPERATURE_FILE "./example_files/temp1"

typedef struct Configurations {
	char recipient[50];
	int intervalInSeconds;	
	double temperatureThreshold;
} Configuration;

double readTemperature(char *filePath){
	FILE *tempFile;
	tempFile = fopen(filePath, "r");
	if(tempFile == NULL)
		return 1;

	double temperature;
	fscanf(tempFile, "%lf", &temperature);
	fclose(tempFile);
	temperature /= 1000;

	return temperature;	
}

double  *collectTemperatureValues(double tempArr[], int temperatureCount, int intervalInSeconds){
	int i;
	for (i = 0; i < temperatureCount; i++){
		sleep(intervalInSeconds); // Sleep before reading the next value
		tempArr[i] = readTemperature(TEMPERATURE_FILE);
	}
	
	return tempArr;
}

double calculateAverage(double values[], int size){
	double sum, average;
	int i;

	for (i = 0; i < size; i++)
		sum += values[i];

	average = sum / size;
	return average;
}

void sendMail(char *recipient){
	printf("Sending email to %s", recipient);
}

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

int main( int argc, char *argv[] ) {

	Configuration config;
	
	config = parseArguments(argc, argv);

	double temperatures[TEMPERATURE_COUNT];

	collectTemperatureValues(temperatures, TEMPERATURE_COUNT, config.intervalInSeconds);
	
	printf("Temperatures: \n");
	int i;
	for (i = 0; i < TEMPERATURE_COUNT; i++ ){
		printf("%lf \n", temperatures[i]);
	}
	
	double average;
	average = calculateAverage(temperatures, TEMPERATURE_COUNT);

	printf("Average: %lf \n", average);

	if(average < config.temperatureThreshold)
		return 0;

	char emailAddress[]  = "d@stuhrs.dk";
	sendMail(emailAddress);

	return 0;
}


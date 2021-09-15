#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "configuration.h"

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

double  *collectTemperatureValues(
	double tempArr[],
	int temperatureCount,
	int intervalInSeconds)
 {
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "configuration.h"
#include "temperature.h"

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

	double temperatures[config.temperatureCount];

	collectTemperatureValues(
		config.temperatureFile,
		 temperatures,
		 config.temperatureCount,
		 config.intervalInSeconds);

	printf("Temperatures: \n");
	int i;
	for (i = 0; i < config.temperatureCount; i++ ){
		printf("%lf \n", temperatures[i]);
	}

	double average;
	average = calculateAverage(temperatures, config.temperatureCount);

	printf("Average: %lf \n", average);

	if(average < config.temperatureThreshold)
		return 0;

	char emailAddress[]  = "d@stuhrs.dk";
	sendMail(emailAddress);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "configuration.h"
#include "temperature.h"

double calculate_average(double values[], int size){
	double sum, average;
	int i;

	for (i = 0; i < size; i++)
		sum += values[i];

	average = sum / size;
	return average;
}

void send_mail(char *recipient){
	printf("Sending email to %s", recipient);
}

int main( int argc, char *argv[] ) {

	struct config config;
	config = parse_args(argc, argv);

	double temperatures[config.temperature_read_count];

	collect_temp_values(
		config.temperature_source_file,
		 temperatures,
		 config.temperature_read_count,
		 config.interval_seconds);

	printf("Temperatures: \n");
	int i;
	for (i = 0; i < config.temperature_read_count; i++ ){
		printf("%lf \n", temperatures[i]);
	}

	double average;
	average = calculate_average(temperatures, config.temperature_read_count);

	printf("Average: %lf \n", average);

	if(average < config.temperature_threshold)
		return 0;

	char emailAddress[]  = "d@stuhrs.dk";
	send_mail(emailAddress);

	return 0;
}

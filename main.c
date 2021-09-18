#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "configuration.h"
#include "temperature.h"

#define MAIL_COMMAND " | mail -s \"Temperature alert\" "
#define ECHO_COMMAND "echo Average temperature was " 

double calculate_average(double values[], int size){
	double sum, average;
	int i;

	for (i = 0; i < size; i++)
		sum += values[i];

	average = sum / size;
	return average;
}

void send_mail(char *recipient, double temperature){
	printf("Sending email to %s\n", recipient);

	char temp_str[10];
	snprintf(temp_str, sizeof(temp_str), "%f", temperature);

	int size = strlen(ECHO_COMMAND) + strlen(temp_str) + strlen(recipient) + strlen(MAIL_COMMAND) + 1;
	char *command = malloc(size);
	if(command == NULL){
		fprintf(stderr, "Failed to allocate memory.. Program will terminate!\n");
		exit(EXIT_FAILURE);
	}

	strcpy(command, ECHO_COMMAND);
	strcat(command, temp_str);
	strcat(command, MAIL_COMMAND);
	strcat(command, recipient);
	system(command);
	printf("%s", command);
}

int main(int argc, char *argv[] ) {

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

	if(average < config.temperature_threshold){
		send_mail(config.mail_recipient, average);
	}

	char emailAddress[]  = "d@stuhrs.dk";
	send_mail(emailAddress, average);

	return 0;
}

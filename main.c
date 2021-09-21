#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "configuration.h"
#include "temperature.h"

double calculate_average(double values[], int size) {
	double sum, average;
	int i;

	for (i = 0; i < size; i++)
		sum += values[i];

	average = sum / size;
	return average;
}

void *ec_malloc(int size) {
	void *pointer;
	pointer = malloc(size);

	if(pointer == NULL) {
		fprintf(stderr, "Failed to allocate memory.. Program will terminate!\n");
		exit(EXIT_FAILURE);
	}

	return pointer;
}

char *get_mail_command(char *recipient, double temperature) {
	char mail_cmd[] =  " | mail -s \"Temperature alert\" ";
	char echo_cmd[] = "echo Average temperature was ";
	char temp_str[10];

	snprintf(temp_str, sizeof(temp_str), "%f", temperature);
	int size = strlen(echo_cmd) + strlen(temp_str) + strlen(recipient) + strlen(mail_cmd) + 1;

	char *command = (char *) ec_malloc(size);

	strcpy(command, echo_cmd);
	strcat(command, temp_str);
	strcat(command, mail_cmd);
	strcat(command, recipient);

	return command;
}

int send_mail(char *recipient, double temperature) {
	printf("Sending email to %s\n", recipient);
	char *command = get_mail_command(recipient, temperature);

	int exitcode = system(command);
	free(command);

	return exitcode;
}

int main(int argc, char *argv[] ) {
	struct config config;
	config = parse_args(argc, argv);

	bool running = true;
	double temperatures[config.temperature_read_count];

	while (running) {
		printf("Reading %d temperature values from %s with interval %d \n", config.temperature_read_count, config.temperature_source_file, config.interval_seconds);
		collect_temp_values(
			config.temperature_source_file,
			 temperatures,
			 config.temperature_read_count,
			 config.interval_seconds);

		double average;
		average = calculate_average(temperatures, config.temperature_read_count);

		printf("Temperature average: %lf \n", average);

		int exitcode;
		if(average > config.temperature_threshold) {
			exitcode = send_mail(config.mail_recipient, average);

			if(exitcode != 0) {
				printf("Failed to send mail! Command exited with code: %d\n", exitcode);
				running = false;
			}
		}
	}

	return 0;
}

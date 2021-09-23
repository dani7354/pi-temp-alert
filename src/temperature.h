#define MIN_VALID_TEMP 0
#define MAX_VALID_TEMP 110

double read_temp(char *file_path){
	FILE *temp_source;
	temp_source = fopen(file_path, "r");

	if(temp_source == NULL){
		fprintf(stderr, "Failed to read temperature source file.. Program will terminate!\n");
		exit(EXIT_FAILURE);
	}

	double temperature;
	fscanf(temp_source, "%lf", &temperature);
	fclose(temp_source);
	temperature /= 1000;

	return temperature;
}

double *collect_temp_values(
	char *file_path,
	double temperatures[],
	int temperature_read_count,
	int interval_seconds) {
	int i;
	for (i = 0; i < temperature_read_count; i++){
		double temp;
		temp = read_temp(file_path);

		if(temp >= MIN_VALID_TEMP && temp <= MAX_VALID_TEMP )
			temperatures[i] = temp;
		else{
			fprintf(stderr, "The temperature is invalid: %f.. Minimum value used!\n", temp);
			temperatures[i] = MIN_VALID_TEMP;
		}

		sleep(interval_seconds); // Sleep before reading the next value
	}

	return temperatures;
}

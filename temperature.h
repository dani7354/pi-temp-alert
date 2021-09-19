
double read_temp(char *file_path){
	FILE *temp_source;
	temp_source = fopen(file_path, "r");
	if(temp_source == NULL)
		return -1;

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
	int interval_seconds)
 {
	int i;
	for (i = 0; i < temperature_read_count; i++){
		sleep(interval_seconds); // Sleep before reading the next value
		temperatures[i] = read_temp(file_path);
	}

	return temperatures;
}

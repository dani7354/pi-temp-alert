
double read_temp(char *filePath){
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

double *collect_temp_values(
  char *filePath,
	double tempArr[],
	int temperatureCount,
	int intervalInSeconds)
 {
	int i;
	for (i = 0; i < temperatureCount; i++){
		sleep(intervalInSeconds); // Sleep before reading the next value
		tempArr[i] = read_temp(filePath);
	}

	return tempArr;
}

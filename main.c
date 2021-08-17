#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
		tempArr[i] = readTemperature("./example_files/temp1");
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

int main(){
	int temperatureCount;
	temperatureCount = 20;
	double temperatures[temperatureCount];

	collectTemperatureValues(temperatures, temperatureCount, 1);
	
	printf("Temperatures: \n");
	int i;
	for (i = 0; i < temperatureCount; i++ ){
		printf("%lf \n", temperatures[i]);
	}
	
	double average;
	average = calculateAverage(temperatures, temperatureCount);

	printf("Average: %lf \n", average);

	if(average < 40)
		return 0;

	char emailAddress[]  = "d@stuhrs.dk";
	sendMail(emailAddress);

	return 0;
}


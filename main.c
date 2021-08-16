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

int *collectTemperaturevalues(int tempArr[], int temperatureCount, int intervalInSeconds){
	int i;
	for (i = 0; i < tempratureCount; i++){
		sleep(intervalInSeconds); // Sleep before reading the next value
		tempArr[i] = readTemperature("./example_files/temp1");
	}

}

void sendMail(char *recipient){

}

int main(){
	double temperature;
       	temperature = readTemperature("./example_files/temp1");
	if(temperature != 1)
		printf("%lf \n", temperature);



}


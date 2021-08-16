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

void sendMail(char *recipient){

}

int main(){
	double temperatures[20];
	collectTemperatureValues(temperatures, 20, 1);
	int i;
	for (i = 0; i < 20; i++ ){
		printf("%lf \n", temperatures[i]);
	}


}


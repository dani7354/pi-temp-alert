# pi-temp-alert
This is a small program written in C, which reads the CPU temperature,
calculates the average and sends an email alert to a specified e-mail-
address, if the average is above the defined temperature threshold.

## Setup
Tested on Ubuntu 20.04 for Raspberry Pi 4

1. Clone the repository:
```
$ git clone --single-branch https://github.com/dani7354/04_NmapCredentialsPsScript.git 
```

2. (Optional) Change values in the init script
```
$ vim pi-temp-alert/scripts/tempalert.sh
```
Change the values of the following three variables.
```
recipient="root"
interval=1
temperature_threshold=60
```

3. Run the setup.sh script to compile the program and setup the init script
```
$ ./pi-temp-alert/scripts/setup.sh 
```

4. Try to stop and start the daemon. You can also check the status to see
if it is running.
```
$ sudo service tempalert stop
```
```
$ sudo service tempalert start
```
```
$ sudo service tempalert status
```

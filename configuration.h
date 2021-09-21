#define TEMPERATURE_COUNT 10
#define REQUIRED_ARG_COUNT 4
#define TEMPERATURE_FILE "/sys/class/thermal/thermal_zone0/temp"

struct config {
	char mail_recipient[50];
	char temperature_source_file[50];
	int temperature_read_count;
	int interval_seconds;
	double temperature_threshold;
};

struct config parse_args(int count, char *arguments[]) {

	if(count < REQUIRED_ARG_COUNT){
		fprintf(stderr, "Missing arguments.. Program will terminate!\n");
		exit(EXIT_FAILURE);
	}
	struct config config;

	config.temperature_read_count = TEMPERATURE_COUNT;
	config.temperature_threshold = atof(arguments[1]);
	config.interval_seconds = atoi(arguments[2]);
	strncpy(config.mail_recipient, arguments[3], sizeof(config.mail_recipient));
	strncpy(config.temperature_source_file, TEMPERATURE_FILE,
	sizeof(config.temperature_source_file));

	return config;
}

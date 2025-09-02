#include <stdio.h>

#define INPUT_LENGTH 6

int main(void)
{
	int left_input[INPUT_LENGTH] = {0};
	int right_input[INPUT_LENGTH] = {0};
	
	const char *filename = "test_input.txt";
	FILE *f = fopen(filename, "r");

	char line[16] = {0};
	char *fgets_stats;
	
	while ((fgets_stats = fgets(line, sizeof line, f)) != NULL) {
		printf("%s", line);
	}
	
	fclose(f);
	return 0;
}

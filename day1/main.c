#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define INPUT_LENGTH 1000

typedef struct String_List {
	char **items;
	int capacity;
	int count;
} String_List;

String_List string_list_new(int capacity)
{
	String_List list = {0};
	list.capacity = capacity;
	list.count = 0;
	list.items = malloc(list.capacity * sizeof(char*));
	assert(list.items != NULL);
	return list;
}

void string_list_dump(String_List str_list)
{
	printf("[ ");
	for (int i = 0; i < str_list.count; ++i) {
		if (i == str_list.count - 1) {
			printf("%s ", str_list.items[i]);
		} else {
			printf("%s, ", str_list.items[i]);
		}
	}
	printf("]\n");
}

void string_list_append(String_List *str_list, char *string)
{
	if (str_list->count + 1 >= str_list->capacity) {
		str_list->capacity *= 2;
		char **list_realloc = realloc(str_list->items, str_list->capacity * sizeof(char*));
		assert(list_realloc != NULL);
		str_list->items = list_realloc;
	}
	
	size_t str_len = strlen(string);
	str_list->items[str_list->count] = malloc(str_len * sizeof(char) + 1);
	assert(str_list->items[str_list->count] != NULL);
	strcpy(str_list->items[str_list->count], string);
	str_list->items[str_list->count][str_len] = '\0';
	str_list->count++;
}

void string_list_free(String_List *str_list)
{
	for (int i = 0; i < str_list->count; ++i) {
		free(str_list->items[i]);
	}
	free(str_list->items);
}

String_List split_string_by_delim(char *str, char *delim)
{
	String_List str_list = string_list_new(2);
	
	for (char *p = strtok(str, delim); p != NULL; p = strtok(NULL, delim)) {
		string_list_append(&str_list, p);
	}

	return str_list;
}

int compar(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int main(void)
{
	int left_input[INPUT_LENGTH] = {0};
	int right_input[INPUT_LENGTH] = {0};
	
	const char *filename = "real_input.txt";
	FILE *f = fopen(filename, "r");

	char line[16] = {0};
	char *fgets_stats;
	String_List splited_string;
	int input_index = 0;
	
	while ((fgets_stats = fgets(line, sizeof line, f)) != NULL) {
		char *line_clean = strtok(line, "\n");
	    splited_string = split_string_by_delim(line_clean, " ");
		left_input[input_index] = atoi(splited_string.items[0]);
		right_input[input_index] = atoi(splited_string.items[1]);
		string_list_dump(splited_string);
		string_list_free(&splited_string);
		input_index++;
	}

	// Sort Left Input and Right Input
	qsort(left_input, INPUT_LENGTH, sizeof(int), compar);
	qsort(right_input, INPUT_LENGTH, sizeof(int), compar);
	int result = 0;
	for (int i = 0; i < INPUT_LENGTH; ++i) {
		result += abs(left_input[i] - right_input[i]);
	}
	printf("result: %d\n", result);
	
	fclose(f);
	return 0;
}

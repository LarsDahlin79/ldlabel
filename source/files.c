
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "files.h"

/*
 * Read layout data from the given stream, can be either a file or stdin.
 */
char* read_file_content(FILE* stream){
    const size_t max_size = 100;
    char* layout_data = NULL;
    char temp_buffer[max_size];
    char next_char = 0;
    size_t pos = 0;
    size_t buffer_pos = 0;
    
    /* read until end-of-file */
    while(true){
	next_char = fgetc(stream);
	if (next_char == EOF){
	    buffer_pos += pos;
	    temp_buffer[pos] = '\0';
	    break;
	}
	temp_buffer[pos] = next_char;
	pos++;
	if (pos >= max_size){
	    pos = 0;
	    if (NULL == layout_data){
		layout_data = calloc(sizeof(char), max_size);
	    }else{
		layout_data = realloc(layout_data, sizeof(char) * (buffer_pos + max_size));
	    }
	    strncpy(layout_data + buffer_pos, temp_buffer, strlen(temp_buffer));
	    buffer_pos += max_size;
	}
    }

    if (NULL == layout_data){
	layout_data = calloc(sizeof(char), pos);
    }else{
	layout_data = realloc(layout_data, sizeof(char) * (pos + buffer_pos));
    }
    if (NULL != layout_data){
	strncpy(layout_data + buffer_pos - pos, temp_buffer, strlen(temp_buffer));
	layout_data[buffer_pos] = '\0';
    }
    return layout_data;
}


#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test_main.h"
#include "ldlabel.h"
#include "utils.h"
#include "sysvar.h"
#include "variables.h"

const char version[] = "0.2";
const char software_name[] = "ldlabel";

static void help_function(void);
static char* read_layout_data(FILE* stream);

int main(int argc, char** argv){

    int arg_nr = 1;
    bool unit_test = false;
    bool show_version = false;
    bool show_help = false;
    const char* filename;
    while(arg_nr < argc){
	if (!strcmp(argv[arg_nr], "-t") || !strcmp(argv[arg_nr], "--test")){
	    unit_test = true;
	}else if (!strcmp(argv[arg_nr], "--version")){
	    /* -v normally means verbose */
	    show_version = true;
	}else if (!strcmp(argv[arg_nr], "-h") || !strcmp(argv[arg_nr], "--help")){
	    show_help = true;
	}else{
	    /* Assume that a filename has been given */
	    filename = argv[1];
	}
	arg_nr++;
    }

    if (show_version){
	fprintf(stdout, "Version %s of %s, %s\n", version, software_name, __DATE__);
    }else if (show_help){
	help_function();
    }else if (unit_test){
	test_all();
    }else{
	sysvar_set_font_location("/usr/share/fonts/dejavu-sans-fonts/");
	sysvar_set_default_font("DejaVuSans.ttf");
	variable_init();
	FILE* fp = fopen(filename, "r");
	char* layout_data = read_layout_data(fp);
	uint16_t pos = 0;
	while (true){
	    char* current_line = utils_get_substring(layout_data, &pos, '\n');
	    if (NULL == current_line){
		break;
	    }
	    ldlabel_execute(current_line);
	    free(current_line);
	}
    }
    return 0;
}

/*
 * Show available command line arguments.
 */
static void help_function(void){
    fprintf(stdout, "Usage:\n");
    fprintf(stdout, "%s <arg>\n", software_name);
    fprintf(stdout, "<arg> can be:\n");
    fprintf(stdout, "-h / --help: This dialog\n");
    fprintf(stdout, "--version: Version info\n");
    fprintf(stdout, "-t / --test: Unittest software\n");
    fprintf(stdout, "<filename>: Create a label\n");
}

/*
 * Read layout data from the given stream, can be either a file or stdin.
 */
static char* read_layout_data(FILE* stream){
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

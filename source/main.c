
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
#include "main.h"
#include "files.h"

const char version[] = "0.2";
const char software_name[] = "ldlabel";
static char* layout_data = NULL;
static uint16_t layout_pos = 0;

static void help_function(void);

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
	if (NULL == fp)
	{
	    fprintf (stderr, "Unable to open file %s\n", filename);
	    return 1;
	}
	layout_data = read_file_content(fp);
	fclose(fp);
	layout_pos = 0;
	while (true){
	    char* current_line = utils_get_substring(layout_data, &layout_pos, '\n');
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
 * Add the the given text to the layout buffer.
 */
bool main_add_layout_commands(char* new_layout_data){

    /* layout_pos is the current position */
    /* layout_pos = utils_find_char_index(layout_data, layout_pos,'\n'); */

    /* user is importing at the end of the file, which is pointless, but should */
    /* still not lead to a program crash */
    if (0xFFFF == layout_pos){
	layout_pos = utils_find_char_index(layout_data, layout_pos,'\0');
    }

    layout_data = utils_insert_string(layout_data, new_layout_data, layout_pos);
    layout_pos = utils_find_char_index(layout_data, layout_pos,'\n');

    return true;
}

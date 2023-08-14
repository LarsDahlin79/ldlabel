

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "graphics.h"
#include "sysvar.h"
#include "variables.h"
#include "main.h"
#include "files.h"

/*
  Overview ldlabel protocol
  # Comments start with #, can be at the start of a line or in the middle, ldlabel ignores everything after until end-of-line or end-of-file
  actor, layout, style, size, colour    FUTURE VERSION
  append, variable, value
  arrow, layout, direction, x1, x2, width, colour (direction can be left, right, both or neither)  FUTURE VERSION
  barcode, layout, xpos, ypos, data, type, colour
  circle, layout, xpos, ypos, radious, colour    FUTURE VERSION
  font, fontname
  font_location, directory
  image, layout, image, xpos, ypos     FUTURE VERSION
  import, filename
  insert, variable, value, position
  layout, name, resolution, width, height, background colour
  line, layout, style, x1, y1, x2, y2, colour
  save, layout
  square, layout, x1, y1, x2, y2, colour  FUTURE VERSION
  text, layout, xpos, ypos, text, colour
  update, variable, value
  variable, name, value
 */

typedef bool (ldlabel_com_ptr)(char*);
static bool com_layout(char* line);
static bool com_save(char* line);
static bool com_text(char* line);
static bool com_barcode(char* line);
static bool com_line(char* line);
static bool com_square(char* line);
static bool com_arrow(char* line);
static bool com_circle(char* line);
static bool com_variable(char* line);
static bool com_import(char* line);
static bool com_append(char* line);
static bool com_insert(char* line);
static bool com_update(char* line);
static bool com_font(char* line);
static bool com_font_location(char* line);
static bool com_actor(char* line);

struct ldlabel_command{
    ldlabel_com_ptr* function_ptr;
    char* command;
}commands[] = {
    {com_layout, "layout"},
    {com_save, "save"},
    {com_text, "text"},
    {com_barcode, "barcode"},
    {com_line, "line"},
    {com_square, "square"},
    {com_arrow, "arrow"},
    {com_circle, "circle"},
    {com_variable, "variable"},
    {com_import, "import"},
    {com_append, "append"},
    {com_insert, "insert"},
    {com_update, "update"},
    {com_font_location, "font_location"},  /* must come before font command */
    {com_font, "font"},
    {com_actor, "actor"},
    {NULL, NULL},
};

bool ldlabel_execute(char* line){
    uint8_t it = 0;
    bool success = false;
    while (NULL != commands[it].command){
	if (utils_string_begins_with(line, commands[it].command)){
	    success = commands[it].function_ptr(line);
	    break;
	}
	it++;
    }
    return success;
}

static bool com_layout(char* line){
    /* command name, resolution, width, height, bgcolour red, green, blue */
    uint16_t width = 100, height = 100;
    uint16_t pos = strlen("layout,");
    char* layout_name = utils_get_substring(line, &pos, ',');
    utils_trim_string(layout_name);
    sysvar_set_layout_name(layout_name);

    uint8_t resolution = utils_get_substring_uint(line, &pos, ',');
    sysvar_set_layout_resolution(resolution);

    width = utils_get_substring_uint(line, &pos, ',');

    height = utils_get_substring_uint(line, &pos, ',');
    sysvar_set_layout_size(width, height);

    bool success = graphics_create(layout_name, width, height, resolution);
    if (!success){
	free(layout_name);
	return success;
    }
    
    uint32_t red = utils_get_substring_uint(line, &pos, ',');
    uint32_t green = utils_get_substring_uint(line, &pos, ',');
    uint32_t blue = utils_get_substring_uint(line, &pos, ',');
    uint32_t alpha = utils_get_substring_uint(line, &pos, ',');

    success = graphics_fill_image(layout_name, red, green, blue, alpha);
    free(layout_name);
    return success;
}

static bool com_save(char* line){
    /* only one parameter, filename */
    uint16_t pos = strlen("save,");
    char* filename = utils_get_substring(line, &pos, ',');
    utils_trim_string(filename);
    bool success = graphics_save_file(filename);
    free(filename);
    return success;
}

static bool com_text(char* line){
    /* text, layout, xpos, ypos, text, red, green, blue, alpha, font */
    
    /* get layout name */
    uint16_t pos = strlen("text,");
    char* layout = utils_get_substring(line, &pos, ',');
    utils_trim_string(layout);

    /* get xpos & ypos */
    uint16_t xpos = (uint16_t)utils_get_substring_uint(line, &pos, ',');
    uint16_t ypos = (uint16_t)utils_get_substring_uint(line, &pos, ',');

    /* get the text */
    char* text = utils_get_substring(line, &pos, ',');
    utils_trim_string(text);
    char* updated_text = utils_update_string(text);
    free(text);

    /* get the colour */
    uint32_t red = utils_get_substring_uint(line, &pos, ',');
    uint32_t green = utils_get_substring_uint(line, &pos, ',');
    uint32_t blue = utils_get_substring_uint(line, &pos, ',');
    uint32_t alpha = utils_get_substring_uint(line, &pos, ',');
    char* font = utils_get_substring(line, &pos, ',');
    bool success = graphics_text(layout, updated_text, xpos, ypos, red, green, blue, alpha, font);
    free(layout);
    free(updated_text);
    
    return success;
}

static bool com_barcode(char* line){

    /* barcode, layout, x, y, type, data, red, green, blue, alpha*/
    
    /* get layout name */
    uint16_t pos = strlen("barcode,");
    char* layout = utils_get_substring(line, &pos, ',');
    utils_trim_string(layout);

    /* get xpos & ypos */
    uint16_t xpos = (uint16_t)utils_get_substring_uint(line, &pos, ',');
    uint16_t ypos = (uint16_t)utils_get_substring_uint(line, &pos, ',');

    uint16_t type = (uint16_t)utils_get_substring_uint(line, &pos, ',');

    char* data = utils_get_substring(line, &pos, ',');
    utils_trim_string(data);

    /* TODO: Remove unnecessary quotes and read value if variable */

    uint32_t red = utils_get_substring_uint(line, &pos, ',');
    uint32_t green = utils_get_substring_uint(line, &pos, ',');
    uint32_t blue = utils_get_substring_uint(line, &pos, ',');
    uint32_t alpha = utils_get_substring_uint(line, &pos, ',');

    if (!graphics_draw_barcode(layout, type, data, xpos, ypos,
			       red, green, blue, alpha)){
	return false;
    }

    free(layout);
    free(data);

    return true;
}

static bool com_line(char* line){
    printf ("Hello from line command\n\n");
    return false;
}

static bool com_square(char* line){
    printf ("Hello from square command\n\n");
    return false;
}

static bool com_arrow(char* line){
    printf ("Hello from arrow command\n\n");
    return false;
}

static bool com_circle(char* line){
    printf ("Hello from circle command\n\n");
    return false;
}

static bool com_variable(char* line){
    /* variable, name, value */
    uint16_t pos = strlen("variable,");
    char* name = utils_get_substring(line, &pos, ',');
    utils_trim_string(name);
    char* value = utils_get_substring(line, &pos, ',');
    utils_trim_string(value);
    variable_create(name);
    if (NULL != value){
	variable_update(name, value);
	free(value);
    }
    free(name);
    return true;
}

static bool com_import(char* line){
    /* import, filename */
    uint16_t pos = strlen("import,");

    /* get argument filename */
    char* filename = utils_get_substring(line, &pos, ',');
    utils_trim_string(filename);

    /* check for variable and if so, read the value */
    char* updated_filename = utils_update_string(filename);
    if (utils_text_is_quote(updated_filename)){
	size_t len = strlen(updated_filename);
	strncpy(updated_filename, updated_filename + 1, len - 2);
	updated_filename[len - 2] = '\0';
    }

    /* check that the file exists and is readable */
    FILE* fp = fopen(updated_filename, "r");
    if (NULL == fp){
	fprintf (stderr, "Unable to open file %s\n", updated_filename);
	return 1;
    }
    /* read the data from the file */
    char* data = read_file_content(fp);
    main_add_layout_commands(data);
    fclose(fp);

    free(updated_filename);
    return true;
}

bool ldlabel_is_correct_layout(char* layout_data){
    /* the first command must layout */
    return  false;
}

static bool com_append(char* line){
    /* append, variable, value */
    
    uint16_t pos = strlen("append,");
    char* name = utils_get_substring(line, &pos, ',');
    utils_trim_string(name);

    char* value = utils_get_substring(line, &pos, ',');
    utils_trim_string(value);

    char* variable_value = variable_read(name);
    utils_update_string(variable_value);
    utils_update_string(value);
    utils_append_string(variable_value, value);
    variable_update(name, variable_value);

    free(name);
    free(value);
    free(variable_value);

    return true;
}

static bool com_insert(char* line){
    /* insert, variable, value, position */

    uint16_t pos = strlen("insert,");
    char* name = utils_get_substring(line, &pos, ',');
    utils_trim_string(name);
    char* variable_value = variable_read(name);

    char* value = utils_get_substring(line, &pos, ',');
    utils_trim_string(value);

    uint32_t position = utils_get_substring_uint(line, &pos, ',');

    variable_value = utils_insert_string(variable_value, value, position);
    if (!variable_update(name, variable_value)){
	fprintf (stderr, "Syntax error: Variable cannot be updated\n");
	return false;
    }

    return true;
}

static bool com_update(char* line){
    printf ("Hello from update command\n\n");
    return false;
}

static bool com_font(char* line){
    uint16_t pos = strlen("font,");
    char* font = utils_get_substring(line, &pos, ',');
    utils_trim_string(font);
    sysvar_set_default_font(font);
    free(font);
    return true;
}

static bool com_font_location(char* line){
    uint16_t pos = strlen("font_location,");
    char* location = utils_get_substring(line, &pos, ',');
    utils_trim_string(location);
    sysvar_set_font_location(location);
    free(location);
    return true;
}

static bool com_actor(char* line){
    printf ("Hello from actor command\n\n");
    return false;
}

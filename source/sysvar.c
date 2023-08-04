

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "sysvar.h"

/*
  Current date:years:months:days  Add to current date FUTURE VERSION
  Current time:hours:minutes   Add to current time FUTURE VERSION
  Current weekday:years:months:days
  Current layout name
  Current layout size
  Current format
  Current resolution
  Current date format  FUTURE VERSION
  Current time format  FUTURE VERSION
  Current language  FUTURE VERSION
  Default font location
  Default font
 */

static char* week_days_eng[] = {
    "sunday",
    "monday",
    "tuesday",
    "wednesday",
    "thursday",
    "friday",
    "saturday",
};

static char* layout_name = NULL;
static uint16_t layout_width = 0, layout_height = 0;
static uint16_t layout_resolution = 0;
static char* layout_format = NULL;
static char* font_location = NULL;
static char* default_font = NULL;

char* sysvar_current_date(void){

    /* The current date + optional years, months and days added */
    /* variable, name, value */
    /* variable, best_before_date, current_date:0:0:10 */
    /* to read the date 10 days ahead. */

    char* current_date = calloc(sizeof(char), 11);
    if (NULL == current_date){
	return NULL;
    }
    time_t current_time = time(NULL);
    struct tm local_time = *localtime(&current_time);
    
    /* Future version */
    /* Check for optional argument years */
    /* Check for optional argument months */
    /* Check for optional argument days */

    /* Format YYYY-MM-DD */
    /* Future version: any format */
    sprintf (current_date,
	     "%04d-%02d-%02d",
	     local_time.tm_year + 1900,
	     local_time.tm_mon + 1,
	     local_time.tm_mday);
    return current_date;
}

char* sysvar_current_time(void){

    /* option arguments can add hour and minutes to the current time */
    /* variable, current_time:14:45 */
    /* to get the time 14h and 45 minutes from now */

    char* time_str = calloc(sizeof(char), 6);
    if (NULL == time_str){
	return NULL;
    }
    time_t current_time = time(NULL);
    struct tm local_time = *localtime(&current_time);

    /* check for optional hour parameter */

    /* check for optional minute parameter */
    
    /* Format 24h format */
    /* Future version: 12h format */
    sprintf (time_str,
	     "%02d:%02d",
	     local_time.tm_hour,
	     local_time.tm_min);
    return time_str;
}

char* sysvar_current_weekday(void){
    time_t current_time = time(NULL);
    struct tm local_time = *localtime(&current_time);
    
    /* The current weekday + optional years, months and days added */
    /* variable, name, value */
    /* variable, best_before_date, current_weekday:0:0:10 */
    /* to read the weekday 10 days ahead. */

    /* Until support for other languages, assume english */
    size_t len = strlen(week_days_eng[local_time.tm_wday]);
    char* weekday = calloc(sizeof(char), len + 1);
    strcpy (weekday, week_days_eng[local_time.tm_wday]);
    return weekday;
}

/* The name of the last layout to be accessed */
void sysvar_set_layout_name(char* name){
    if (NULL != layout_name){
	free(layout_name);
    }
    layout_name = calloc(sizeof(char), strlen(name) + 1);
    strncpy(layout_name, name, strlen(name));
}

/* The name of the last layout to be accessed */
char* sysvar_get_layout_name(void){
    char* name = calloc(sizeof(char), strlen(layout_name) + 1);
    if (NULL == name){
	return NULL;
    }
    if (NULL != layout_name){
	strncpy(name, layout_name, strlen(layout_name));
    }
    return name;
}

/* The size of the last layout to be accessed */
void sysvar_set_layout_size(uint16_t width, uint16_t height){
    layout_width = width;
    layout_height = height;
}

/* The size of the last layout to be accessed */
void sysvar_get_layout_size(uint16_t* width, uint16_t* height){
    *width = layout_width;
    *height = layout_height;
}

/* The format of the last layout to be accessed, bmp, gif, png etc */
void sysvar_set_layout_format(char* format){    
    if (NULL != layout_format){
	free(layout_format);
    }
    layout_format = calloc(sizeof(char), strlen(format) + 1);
    strncpy(layout_format, format, strlen(format));
}

/* The format of the last layout to be accessed, bmp, gif, png etc */
char* sysvar_get_layout_format(void){
    char* format;
    if (NULL != layout_format){
	format = calloc(sizeof(char), strlen(layout_format) + 1);
	if (NULL == format){
	    return NULL;
	}
	strncpy(format, layout_format, strlen(layout_format));
    }
    return format;
}

/* The resolution of the last layout to be accessed */
void sysvar_set_layout_resolution(uint16_t resolution){
    layout_resolution = resolution ;
}

/* The resolution of the last layout to be accessed */
uint16_t sysvar_get_layout_resolution(void){
    return layout_resolution;
}

void sysvar_set_font_location(char* location){
    if (font_location){
	/* TODO: Only realloc if the new string is longer then the current? */
	font_location = realloc(font_location, strlen(location) + 1);
    }else{
	font_location = calloc(sizeof(char), strlen(location) + 1);
    }
    strncpy(font_location, location, strlen(location));
}

char* sysvar_get_font_location(void){
    char* location;
    if (NULL != font_location){
	location = calloc(sizeof(char), strlen(font_location) + 1);
	if (NULL == location){
	    return NULL;
	}
	strncpy(location, font_location, strlen(font_location));
    }
    return location;
}

void sysvar_set_default_font(char* font){
    if (default_font){
	free(default_font);
    }
    default_font = calloc(sizeof(char), strlen(font) + 1);
    strncpy(default_font, font, strlen(font));
}

char* sysvar_get_default_font(void){
    return default_font;
}

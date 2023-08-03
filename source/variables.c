

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "variables.h"

#define nr_of_variables 100u

struct variable{
    char* name;
    char* value;
}variables[nr_of_variables];

bool variable_init(void){
    uint8_t pos = 0;
    while (pos < nr_of_variables){
	variables[pos].name = NULL;
	variables[pos].value = NULL;
	pos++;
    }
    return true;
}

bool variable_is_variable(char* name){
    uint8_t pos = 0;
    while (pos < nr_of_variables){
	if (NULL != variables[pos].name &&
	    !strcmp(name, variables[pos].name)){
	    return true;
	}
	pos++;
    }
    return false;
}

char* variable_read(char* name){
    uint8_t pos = 0;
    char* value;
    while (pos < nr_of_variables){
	if (NULL != variables[pos].name &&
	    !strcmp(name, variables[pos].name)){
	    value = calloc(sizeof(char), strlen(variables[pos].value));
	    if (NULL == value){
		return NULL;
	    }
	    strcpy(value, variables[pos].value);
	    return value;
	}
	pos++;
    }
    return NULL;
}

bool variable_create(char* name){
    uint8_t pos = 0;
    while (pos < nr_of_variables){
	if (NULL == variables[pos].name){
	    break;
	}
	pos++;
    }
    if (pos < nr_of_variables){
	variables[pos].name = calloc(sizeof(char), strlen(name) + 1);
	if (NULL == variables[pos].name){
	    return false;
	}
	strncpy(variables[pos].name, name, strlen(name));
    }
    return true;
}

bool variable_update(char* name, char* value){
    uint8_t pos = 0;
    while (pos < nr_of_variables){
	if (NULL != variables[pos].name &&
	    !strcmp(variables[pos].name, name)){
	    variables[pos].value = calloc(sizeof(char), strlen(value) + 1);
	    strncpy(variables[pos].value, value, strlen(value));
	    break;
	}
	pos++;
    }
    return pos < nr_of_variables;
}

bool variable_destroy(char* name){
    uint8_t pos = 0;
    while (pos < nr_of_variables){
	if (NULL != variables[pos].name &&
	    !strcmp(variables[pos].name, name)){
	    free(variables[pos].name);
	    variables[pos].name = NULL;
	    free(variables[pos].value);
	    variables[pos].value = NULL;
	    return true;
	}
	pos++;
    }    
    return false;
}


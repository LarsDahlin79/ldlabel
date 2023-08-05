

bool utils_string_ends_with(char* str, char* substr);
bool utils_string_begins_with(char* str, char* substr);
char* utils_get_substring(char* input, uint16_t* start_pos, char separator);
uint32_t utils_get_substring_uint(char* line, uint16_t* start, char separator);
void utils_trim_string(char* input);
void utils_append_string(char* original, char* append);
bool utils_text_is_quote(char* input);
char* utils_insert_string(char* original, char* insert, uint32_t position);
char* utils_update_string(char* text);
uint16_t utils_get_barcode_id(char* barcode_type);



char* sysvar_current_date(void);
char* sysvar_current_time(void);
char* sysvar_current_weekday(void);
void sysvar_set_layout_name(char* name);
char* sysvar_get_layout_name(void);
void sysvar_set_layout_size(uint16_t width, uint16_t height);
void sysvar_get_layout_size(uint16_t* width, uint16_t* height);
void sysvar_set_layout_format(char* format);
char* sysvar_get_layout_format(void);
void sysvar_set_layout_resolution(uint16_t resolution);
uint16_t sysvar_get_layout_resolution(void);
void sysvar_set_font_location(char* location);
char* sysvar_get_font_location(void);
void sysvar_set_default_font(char* font);
char* sysvar_get_default_font(void);

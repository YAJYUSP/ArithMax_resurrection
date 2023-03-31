#ifndef _GUI_H_
#define _GUI_H_

#include <stdint.h>

#define LINE0_LEN_MAX 128
#define MAPBIAS_MAX 112

extern uint8_t Line0CursorPos;
extern uint8_t Line0CursorDispFlag;
extern char *Line0;
extern char *Line0;
extern char Line0_disp[17];
extern char Line1_manifest[17];
extern uint8_t Line0mapBias;


void LCD_ShowCursor(uint8_t en, uint8_t posi);
void Line0Key2mani(uint8_t key_val, uint8_t* key_update);
uint8_t mapLine02mani(uint8_t pos);
void Line0cursorScroll(uint8_t dir, uint8_t mode);
uint8_t mapLine02dispBuf(uint8_t pos);


void Line0DispUpdt(void);
uint8_t Line0strcat(char *str,uint8_t cursor);
uint8_t Line0Backspace(uint8_t cursor);
void dispstr_malloc(void);
uint8_t strcat_dynamic(char *str, char **str0, uint8_t cursor);
#endif
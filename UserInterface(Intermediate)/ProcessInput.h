#ifndef _PROCESS_INPUT_H_
#define _PROCESS_INPUT_H_

volatile bool DotsPressed[6];
volatile char InterfaceType; //1=Reading, 2=Writing


void ResetCellState(void);
void ProcessTheDot(void);
void CaptureCellValue(void);


#endif

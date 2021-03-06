/**
 * @file MD6.h
 * @brief Declarations for mode 6 - Free Play
 * @author Vivek Nair (viveknair@cmu.edu)
 */

#ifndef _MD6_H_
#define _MD6_H_

void md6_main(void);
void md6_reset(void);
void md6_call_mode_yes_answer(void);
void md6_call_mode_no_answer(void);
void md6_input_dot(char this_dot);
void md6_input_cell(char this_cell);
void md6_call_mode_left(void);
void md6_call_mode_right(void);

#endif /* _MD6_H_ */

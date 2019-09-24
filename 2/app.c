/*
 * app.c
 *
 *  Created on: Aug 27, 2019
 *      Author: abdul
 */
#include "LCD.h"
#include "keypad.h"
#include "util/delay.h"
#include "os.h"
#include "keypad.h"

#define MAX_QUEST 5
uint8 testcount = 0;
enum {
	NOT_ANSWERED, ANSWERED
};
uint8 countCorrect = 0;
uint8 getQuestionLock = 0;
uint8 questionLockerTimer=0;
uint8 * questions[MAX_QUEST] = { (uint8*) "49+23= 72 OR 82 ?",
		(uint8*) "(138%6) equal 0 ?", (uint8*) "Morning or night", (uint8*) "Was it raining?",
		(uint8*) "Are you smart?" };
uint8 answers[MAX_QUEST] = { NO, YES, NO, NO, NO };

void questionDelay(void) {
	if(getQuestionLock==1){
		getQuestionLock=0;
	}
}
void GetQuestion(void) {
	static uint8 i = 0, answerdFlag = ANSWERED;

	if (getQuestionLock == 0) {
		if (i < MAX_QUEST && answerdFlag == ANSWERED) {

			LCD_clearScreen();
			LCD_Write_Word(questions[i]);
			answerdFlag = NOT_ANSWERED;

		} else if (i < MAX_QUEST && answerdFlag == NOT_ANSWERED) {

			if (keyValue != NO_RESULT) {

				answerdFlag = ANSWERED;

				if (answers[i] == keyValue) {
					LCD_GOTO(2, 1);
					LCD_Write_Word((uint8*) "CORRECT :)");
					countCorrect++;
				} else {
					LCD_GOTO(2, 1);
					LCD_Write_Word((uint8*) "WRONG :(");
				}
				keyValue = NO_RESULT;
				getQuestionLock = 1;
				i++;

			}
		} else if (i == MAX_QUEST) {
			LCD_clearScreen();
			LCD_Write_Word((uint8*) "YOUR FINAL SCORE IS");
			LCD_GOTO(2, 1);
			LCD_Write_Integer_Number(countCorrect);
			i++;
		}
	}
}
int main() {

	LCD_Intialization();

	OS_Init();

	OS_Task_t Task_GetQuestion = { 0, 50, TaskPaused, GetQuestion };
	OS_Task_t Task_GetKEY = { 0, 20, TaskPaused, KeyPAD_DebouncingHandler };
	OS_Task_t Task_QuestionDelay = { 0, 1000, TaskPaused, questionDelay };


	OS_Create_Task(&Task_GetQuestion, 0);
	OS_Create_Task(&Task_GetKEY, 1);
	OS_Create_Task(&Task_QuestionDelay, 2);

	OS_StartTask(0);
	OS_StartTask(1);
	OS_StartTask(2);




	OS_Run();
	for (;;) {

	}

}

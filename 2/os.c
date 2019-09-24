/****************************************
 *
 *  File Name: os.c
 *                       
 *  Created on: Sep 16, 2019
 * 
 *  Author: Stawro Walaa   
 *
 ****************************************/

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "os.h"
#include "timer0_cfg.h"

/*******************************************************************************/

/*******************************************************************************
 *                       	Global Variables                                   *
 *******************************************************************************/

OS_Task_t * arrTasks[MAX_TASK_NUMBERS];

uint32 i;

/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_Scheduler
 * Description: 	count time for each task and assign to ready state
 * parameters:
 *		Inputs:			None
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void OS_Scheduler(void) {

	for (i = 0; i < MAX_TASK_NUMBERS; i++) {
		if ((arrTasks[i] != NULL) && (arrTasks[i]->Status != TaskPaused)) {
			if (arrTasks[i]->firstDelay == 0) {

				arrTasks[i]->readyState = READY;

				arrTasks[i]->firstDelay = arrTasks[i]->periodicity - 1;
			} else {
				arrTasks[i]->firstDelay--;
			}
		} else {
			/*DO Nothing*/
		}
	}
}
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_Init
 * Description: 	OS Initialization to set timer configurations and start it
 * parameters:
 *		Inputs:			None
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void OS_Init(void) {

	uint8 u8LoopIterator;
	TIMER0_SetCallBack(OS_Scheduler);

	TIMER0_init(&Timer0Cfg);

	for (u8LoopIterator = 0; u8LoopIterator < MAX_TASK_NUMBERS;
			u8LoopIterator++) {
		arrTasks[u8LoopIterator] = NULL;
	}

}
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_StartTask
 * Description: 	Changes task state to from paused to execution state
 * parameters:
 *		Inputs:			TaskPriority
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void OS_StartTask(uint8 TaskPriority) {
	arrTasks[TaskPriority]->Status = TaskRunning;
}
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_StopTask
 * Description: 	Changes task state to from execution state to paused
 * parameters:
 *		Inputs:			TaskPriority
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void OS_StopTask(uint8 TaskPriority) {
	arrTasks[TaskPriority]->Status = TaskPaused;
}
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_Create_Task
 * Description: 	Takes task configurations from user and assign it to
 * 					array in specific priority location
 * parameters:
 *		Inputs:			task_cfg
 *						TaskPriority
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void OS_Create_Task(OS_Task_t* task_cfg, uint8 TaskPriority) {
	arrTasks[TaskPriority] = task_cfg;

}
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_Delete_Task
 * Description: 	Deletes task from execution array
 * parameters:
 *		Inputs:			TaskPriority
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void OS_Delete_Task(uint8 TaskPriority) {
	arrTasks[TaskPriority] = NULL;

}
/*******************************************************************************/

/*******************************************************************************
 *                             OS DeInitialization                             *
 *******************************************************************************/
void OS_DeInit(void) {
	void TIMER0_OFF(void);

}
/*******************************************************************************/

/*******************************************************************************
 *                             OS Run to start execution                       *
 *******************************************************************************/
void OS_Run(void) {
	TIMER0_ON(&Timer0Cfg);
	while (1) {
		for (i = 0; i < MAX_TASK_NUMBERS; i++) {
			if (arrTasks[i]->readyState == READY) {
				arrTasks[i]->ptr();
				if (arrTasks[i]->periodicity == 0) {
								arrTasks[i]->Status = TaskPaused;
							}
				arrTasks[i]->readyState = WAITING;
			}

		}
	}
}
/*******************************************************************************/


/****************************************
 *
 *  File Name: os.h
 *                       
 *  Created on: Sep 16, 2019
 * 
 *  Author: Stawro Walaa   
 *
 ****************************************/

#ifndef OS_H_
#define OS_H_


/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "timer0.h"


/*******************************************************************************
 *                               	Defines                                    *
 *******************************************************************************/

#define MAX_TASK_NUMBERS 5

				       /***** Task running status *****/
typedef enum
{
	TaskPaused,
	TaskRunning
}enmTaskStatus_t;


					   /***** Task control block  TCB *****/

typedef struct{

	uint32 firstDelay;
	uint32 periodicity;
	enmTaskStatus_t Status;
	void(*ptr)(void);
	uint8 readyState ;
}OS_Task_t;


					    	/***** Task ready state *****/
enum{
	WAITING,
	READY
};

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void 	OS_Init (void);
/*******************************************************************************/

/*******************************************************************************
 *                             OS DeInitialization                             *
 *******************************************************************************/
void 	OS_DeInit (void);
/*******************************************************************************/


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
void 	OS_Create_Task (OS_Task_t* task_cfg,uint8 TaskPriority);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_StartTask
 * Description: 	Changes task state to from paused to execution state
 * parameters:
 *		Inputs:			TaskPriority
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void 	OS_StartTask (uint8 TaskPriority);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_StopTask
 * Description: 	Changes task state to from execution state to paused
 * parameters:
 *		Inputs:			TaskPriority
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void 	OS_StopTask(uint8 TaskPriority);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_Delete_Task
 * Description: 	Deletes task from execution array
 * parameters:
 *		Inputs:			TaskPriority
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void	OS_Delete_Task(uint8 TaskPriority);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	OS_Run
 * Description: 	The short term function to check if task in ready state
 * 					to be executed
 * parameters:
 *		Inputs:			None
 *		Outputs:		None
 * Return:			None
 *******************************************************************************/
void 	OS_Run(void);

void    OS_CheckDispatcher(void);
/*******************************************************************************/

#endif /* OS_H_ */


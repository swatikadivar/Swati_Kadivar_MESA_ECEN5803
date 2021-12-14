/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	STATE_Running,
	STATE_Ready,
	STATE_Waiting,
	STATE_Pending,
	STATE_Terminated,
	STATE_Suspended_Blocked,
	STATE_Suspended_Ready,
	STATE_Suspended_Delayed,
	STATE_New_Task
} state_e;

typedef enum
{
	evt_Preempt,
	evt_Dispatch,
	evt_Exception,
	evt_Exception_Cleared,
	evt_Yield,
	evt_Terminate,
	evt_Wait_On_Resource,
	evt_Resource_Available,
	evt_Delay_Timeout,
	evt_Admit
} event_e;

typedef struct mythread{
    int id;
    int prio;
    event_e current_event;
    state_e current_state;
    state_e next_state;
} Mythread;

Mythread **mythreads = NULL;
int no_of_tasks = 0;
int task_max_prio = -1;

void Running_Handler(Mythread *t)
{
    printf("Task %d with Prio %d is Running.\n", t->id, t->prio);
}

void Ready_Handler(Mythread *t)
{
    
}

void Waiting_Handler(Mythread *t)
{
    
}

void Pending_Handler(Mythread *t)
{
    
}

void Terminated_Handler(Mythread *t)
{
    
}

void Suspended_Ready_Handler(Mythread *t)
{
    
}

void Suspended_Delayed_Handler(Mythread *t)
{
    
}

void Suspended_Blocked_Handler(Mythread *t)
{
    
}

void New_Task_Handler(Mythread *t)
{
    printf("New Task %d with Prio %d is Spawned.\n", t->id, t->prio);
    
    if(t->prio > task_max_prio) 
    {
        t->next_state = STATE_Running;
        task_max_prio = t->prio;

        for(int i = 0; i < no_of_tasks; i++)
        {
            if(mythreads[i]->id != t->id) {
                mythreads[i]->current_event = evt_Preempt;
            }
        }
    }
    else {
        t->next_state = STATE_Suspended_Ready ;
    }
}

void Error_Handler(Mythread *t)
{
    
}

void scheduler_statemachine(Mythread *t) {
    
    no_of_tasks++;
    
    while(1)
    {
        t->current_state = t->next_state;
        switch(t->current_state)
		{
			case(STATE_Running):
			    Running_Handler(t);
				if(t->current_event == evt_Terminate) {
					t->next_state = STATE_Terminated; }
				else if(t->current_event == evt_Wait_On_Resource){
					t->next_state = STATE_Pending; }
				else if(t->current_event == evt_Preempt){
					t->next_state = STATE_Ready;	}
				else if(t->current_event == evt_Exception) {
					t->next_state = STATE_Suspended_Ready; }
				else if(t->current_event == evt_Yield) {
					t->next_state = STATE_Waiting; }
				break;
			case(STATE_Ready):
			    Ready_Handler(t);
				if(t->current_event == evt_Dispatch) {
					t->next_state = STATE_Running; }
				else if(t->current_event == evt_Exception) {
					t->next_state = STATE_Suspended_Ready; }
				break;
			case(STATE_Waiting):
			    Waiting_Handler(t);
				if(t->current_event == evt_Delay_Timeout) {
					t->next_state = STATE_Ready; }
				else if(t->current_event == evt_Exception) {
					t->next_state = STATE_Suspended_Delayed; }
				break;
			case(STATE_Pending):
			    Pending_Handler(t);
				if(t->current_event == evt_Resource_Available)	{
					t->next_state = STATE_Ready; }
				else if(t->current_event == evt_Exception) {
					t->next_state = STATE_Suspended_Blocked;	}
				break;
			case(STATE_Terminated):
				Terminated_Handler(t);
				return;
				break;
			case(STATE_Suspended_Blocked):
				Suspended_Blocked_Handler(t);
				if(t->current_event == evt_Exception_Cleared)	{
					t->next_state = STATE_Pending; }
				else if(t->current_event == evt_Resource_Available) {
					t->next_state = STATE_Suspended_Ready;	}
				break;
			case(STATE_Suspended_Ready):
				Suspended_Ready_Handler(t);
				if(t->current_event == evt_Exception_Cleared)	{
					t->next_state = STATE_Ready; }
				break;
			case(STATE_Suspended_Delayed):
				Suspended_Delayed_Handler(t);
				if(t->current_event == evt_Exception_Cleared)	{
					t->next_state = STATE_Waiting; }
				else if(t->current_event == evt_Delay_Timeout) {
					t->next_state = STATE_Suspended_Ready;	}
				break;
			case(STATE_New_Task):
			    New_Task_Handler(t);
			    break;
			default:                    //Any other state
			    Error_Handler(t);
				t->next_state = STATE_Terminated;
				break;
		}
	}
}

void init_task(Mythread *p, int n, int pr)
{
    p->id = 0;
    p->prio = pr;
    p->current_event = evt_Admit;
    p->next_state = STATE_New_Task;
}

void init_tasks(int n)
{
    mythreads = (Mythread **)malloc(n * sizeof(Mythread *));
    for(int i = 0; i < 3; i++) {
        mythreads[i] = (Mythread *)malloc(sizeof(Mythread));
    }
    init_task(mythreads[0], 0, 0);
    init_task(mythreads[1], 1, 1);
    init_task(mythreads[2], 2, 2);
}

int main()
{
    init_tasks(3);

    scheduler_statemachine(mythreads[0]);
    
    //scheduler_statemachine(mythreads[1]);
    
    //scheduler_statemachine(mythreads[2]);
    
    return 0;  
}
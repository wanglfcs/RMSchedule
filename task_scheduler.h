#include<stdio.h>

typedef void(*Func)();

typedef struct Task
{
	char *name;
	int index;
	int t;//period
	int c;//execute time
	int d;//deadline
	int p;//priority
	int execute_time;
	Func *func;
	volatile unsigned int saved_state[33];//saved register data
}Task;

typedef struct TaskNode
{
	struct Task *task;
	struct TaskNode *next;
	int ready;//1 for ready 0 for not.
}TaskNode;

typedef struct TaskList
{
	struct TaskNode *head;
	struct TaskNode *tail;
	int count;
}TaskList;

typedef struct Processor
{
	//static data
	char *name;
	double usage;
	struct TaskList *tasks;

	//runtime data. sorted task list
	Task *cur_task;
}Processor;

#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

Task* new_task();
Processor* new_processor();
void init_processor(Processor *p);
TaskList* new_task_list();

void init_tasks_priority(Task *tasks, int task_cnt);

/* Sort tasks by period using insert sort. Task with the shortest period get the highest priority.*/
void insert_sort(Task *x, int n);

/*Push one task to the processor's task list*/
void push_task(Processor *p, Task *t);

void task_done(Processor *p);

/* Dump the infomation of the processor and its schedule table*/
void dump_processor(Processor *p);

void dump_task(Task *t);

/* Return whether the given tasks are schedulable by rm algorithm. Return 1 if it's schedulable.*/
int rm_schedulable(Task *tasks, int n);

/* Schedule task using RM algorithm. Tasks are preemptive if the first argument is set true */
Task* rm_schedule(int time, Processor *processor);

/* Schedule task using RMFF algorithm. Tasks are preemptive if the first argument is set true*/
void ff_distribute_task(Task *tasks, int task_cnt, Processor *processors, int processor_cnt);
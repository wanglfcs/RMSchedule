#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shared/intercore.h"
#include "shared/counters.h"
#include "shared/timerInterrupt.h"
#include "task_scheduler.h"
#include "binary_search_tree.h"
#include"myprintf.h"


//#define CLOCK_TO_MS(clock, ms) { ms = (clock/10000);}
const int CLOCK_TO_MS = 10000000;
static Processor *s_processor;
static int currentTask=2;
static Task *s_tasks;
int stacks[3][1000];
char *names[] = {
		"task1", "task2", "task3"
	};

static int wait_after_done = 0;
//static int is_idle=0;

/*Search tree for test*/
// static SearchTree *s_search_tree;

static volatile unsigned int timer = 0;

void task_1();
void task_2(); 
void task_3();

int reverse_integer(int x);
int test_func_execute_time(Func func);
void init_tasks(Processor *processor, Task *tasks, int count);
void idle(){while(1);}

void mc_init() {
}

void mc_main() {
	int core = corenum();
	if(core == 2){
		wait_after_done = 0;
		s_processor = new_processor("Processor1");
		s_tasks = new_tasks(names, 3);
		//puts(s_tasks[0].name);
		//puts(s_tasks[1].name);
		//puts(s_tasks[2].name);
		putchar(s_tasks[0].index+'0');
		putchar(s_tasks[1].index+'0');
		putchar(s_tasks[2].index+'0');
		init_tasks(s_processor, s_tasks, 3);
   /*     for(int i=0;i<3;i++)*/
		/*{*/
			/*j=0;*/
			/*while(s_tasks[i].name[j])*/
				/*putchar(s_tasks[i].name[j++]);*/
			/*putchar(10);*/
		/*}*/
		wait_after_done = 1;

		// Called concurrently in all cores except core #1, after mc_init returns
		//set timer interrupt handler
		set_handlerR((int)isr);
		//set timer interrupt intervals
		set_timerInterval(CLOCK_TO_MS);

		//set interrupt enable
		putchar('f');
		set_mask(0);
		task_3();
		while (1);
	}
}

int test_func_execute_time(Func func){
//		__asm__("j7 7");
	counters_start();
	(func)();
	/*counters_stop();*/
	/*int count = counters_readAndZero(0);*/
	/*return count/CLOCK_TO_MS;*/
	return 5;
}

void init_tasks(Processor *processor, Task *tasks, int count)
{
//__asm__("j7 7");
	puts("init_tasks");
	putchar(count+'0');
	putchar(10);
	Func t1 = task_1;
	tasks[0].func = t1;
	Func t2 = task_2;
	tasks[1].func = t2;
	Func t3 = task_3;
	tasks[2].func = t3;

	for(int i=0;i<count;i++){
		/*puts("test func execute time ");*/
		tasks[i].c = test_func_execute_time(tasks[i].func);
		tasks[i].t = tasks[i].c*5;
		tasks[i].saved_state[30] = (int)isr;
		/*putchar(10);*/
	}

	tasks[0].saved_state[31] = (int)task_1;
	tasks[0].saved_state[27] = (int)stacks[0];
	tasks[1].saved_state[31] = (int)task_2;
	tasks[1].saved_state[27] = (int)stacks[1];
	tasks[2].saved_state[31] = (int)task_3;
	tasks[2].saved_state[27] = (int)stacks[2];

	init_tasks_priority(tasks, count);
//	for(int i=0;i<length;i++){
//		dump_task(&tasks[i]);
//	}

	/*puts("push tasks\n");*/
	//set_tasks(processor,tasks,count);
	processor->tasks=tasks;
	processor->task_cnt=count;
//	dump_processor(processor);
	puts("task init finish");
}

void schedule(){
	int i, done;
	int *pData = (int *)(corenum() * 512 + 0x4000);
	Task *pre_task = s_processor->cur_task;
	Task *task_to_run= rm_schedule(timer, s_processor);

	int t = timer%10;
	putchar(48+t);
	putchar(10);
	if(task_to_run!=NULL){
		myprintf("%s\n",task_to_run->name);
	}
	timer++;
	
   /* pre_task=s_tasks+currentTask;*/
	//currentTask = (currentTask + 1) %3;
	//task_to_run=s_tasks+currentTask;

	if (task_to_run != pre_task){
		if (pre_task != NULL){
			//switch task
			//save previous task state
			for (i = 0; i < 32; i++){
				pre_task->saved_state[i] = pData[i];
			}
		}
		if (task_to_run != NULL){
			//restore current task state
			for (i = 0; i < 32; i++){
				pData[i] = task_to_run->saved_state[i];
				//is_idle=0;
			}
		}
   /*     else*/
		//{
			//pData[31]=idle;
			//is_idle=1;
		/*}*/
	}
}

/* Task 1 Reverse Integer */
void task_1() {
//start_Task1:
	if(wait_after_done==0){
		/*puts("task1 start\n");*/
   /*     putchar(10);*/
		/*putchar('1');*/
		/*putchar('s');*/
		/*putchar(10);*/
	}
//	CLI
__asm__("j7 7");
	putchar('A');
//	STI
	int dest0 = reverse_integer(123456789);
	int dest1 = reverse_integer(-123456789);
	int dest2 = reverse_integer(0);
	putchar('a');
	int dest3 = reverse_integer(1000);
	int dest4 = reverse_integer(-1000);
//	putchar('a');

	if(wait_after_done==1){
		task_done(s_processor);
	//	goto start_Task1;
		while (1)
		{
//			CLI
   /*         putchar('A');*/
			/*putchar(10);*/
//			STI
		}
	}else{
		/*puts("task1 done\n");*/
   /*    putchar('1');*/
		/*putchar('e');*/
		/*putchar(10);*/
	}
}

/* Task 2 Binary Search Tree -- insert & delete */
void task_2(){
//start_Task2:
	//puts("task2\n");
	//insert(s_search_tree, 14);
	//insert(s_search_tree, 15);
	//insert(s_search_tree, 2);

	//delete(s_search_tree, 14);
	//delete(s_search_tree, 15);
	//delete(s_search_tree, 2);

//	CLI
	putchar('B');
//	STI
	for(int i=0;i<3;i++){
		int dest0 = reverse_integer(123456789);
		int dest1 = reverse_integer(-123456789);
		int dest2 = reverse_integer(0);
		int dest3 = reverse_integer(1000);
		int dest4 = reverse_integer(-1000);
	}
	putchar('b');

	if(wait_after_done){
		task_done(s_processor);
//		goto start_Task2;
		while (1)
		{
//			CLI
   /*         putchar('B');*/
			/*putchar(10);*/
//			STI
		}

	}
	
}

/* Task 2 Binary Search Tree -- search */
void task_3(){
//start_Task3:
	//puts("task3\n");
	//search_node(s_search_tree, 5);
	//search_node(s_search_tree, 6);
	//search_node(s_search_tree, 12);
	/*putchar(10);*/

//	CLI
	putchar('C');
//	STI
	for(int i=0;i<5;i++){
		int dest0 = reverse_integer(123456789);
		int dest1 = reverse_integer(-123456789);
		int dest2 = reverse_integer(0);
		int dest3 = reverse_integer(1000);
		int dest4 = reverse_integer(-1000);
	}
	/*putchar('w');*/
	/*putchar(10);*/

	if(wait_after_done){
		task_done(s_processor);
//		goto start_Task3;
		while (1)
		{
   /*         putchar('C');*/
			/*putchar(10);*/
		}
	}
	
}

int reverse_integer(int x){
	int result = 0;
	int t;
	if (x<0){
		t = -x;
	}
	else{
		t = x;
	}
	int a = 0;
	while (t > 0){
		result *= 10;
		a = t % 10;
		t = t / 10;
		result += a;
	}
	if (x<0){
		result = -result;
	}
	return result;
}



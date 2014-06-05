#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shared/intercore.h"
#include "shared/counters.h"
#include "shared/timerInterrupt.h"
#include "task_scheduler.h"
#include "binary_search_tree.h"

//#define CLOCK_TO_MS(clock, ms) { ms = (clock/10000);}
const int CLOCK_TO_MS = 10000000;
static Processor *s_processor;
static Task *s_tasks;
char *names[] = {
		"task1", "task2", "task3"
	};

static int wait_after_done = 0;

/*Search tree for test*/
// static SearchTree *s_search_tree;

static volatile unsigned int timer = 0;

void task_1();
void task_2(); 
void task_3();

int reverse_integer(int x);
int test_func_execute_time(Func *func);
void init_tasks(Processor *processor, Task *tasks, int count);

void mc_init() {
	//set_mask(1);
	// Called in core #1 before the calls of mc_main
	// int treeValues[] = { 1, 4, 5, 7, 8, 2, 3, 9, 6, 5, 1, 0 };
	// int len = 0;
	// GET_ARRAY_LEN(treeValues, len);
	// printf("Build Search Tree");
	// s_search_tree = build_tree(treeValues, len);
	// dump_tree(s_search_tree);
	
	/*for(int i=0;i<3;i++)*/
		/*dump_task(s_tasks+i);*/
	/*cache_flushMem(s_processor,sizeof(Processor));*/
	/*cache_flushMem(s_tasks,sizeof(s_tasks)*3);*/
}

void mc_main() {
	int core = corenum();
	if(core == 2){
		s_processor = new_processor("Processor1");
		s_tasks = new_tasks(names, 3);
		puts(s_tasks[0].name);
		puts(s_tasks[1].name);
		puts(s_tasks[2].name);
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
		while (1);
	}
}

int test_func_execute_time(Func *func){
	/*counters_start();*/
	(*func)();
	/*counters_stop();*/
	/*int count = counters_readAndZero(0);*/
	/*return count/CLOCK_TO_MS;*/
	return 5;
}

void init_tasks(Processor *processor, Task *tasks, int count)
{
	/*puts("init_tasks");*/
	putchar(10);
	putchar(count+'0');
	putchar(10);
	Func t1 = task_1;
	tasks[0].func = &t1;
	Func t2 = task_2;
	tasks[1].func = &t2;
	Func t3 = task_3;
	tasks[2].func = &t3;

	for(int i=0;i<count;i++){
		/*puts("test func execute time ");*/
		putchar('e');
		tasks[i].c = test_func_execute_time(tasks[i].func);
		tasks[i].t = tasks[i].c*5;
		tasks[i].saved_state[30] = (int)isr;
		putchar(tasks[i].index+'0');
		/*putchar(10);*/
	}

	tasks[0].saved_state[31] = (int)task_1;
	tasks[1].saved_state[31] = (int)task_2;
	tasks[2].saved_state[31] = (int)task_3;

	init_tasks_priority(tasks, count);
//	for(int i=0;i<length;i++){
//		dump_task(&tasks[i]);
//	}

	/*puts("push tasks\n");*/
	set_tasks(processor,tasks,count);
	putchar('&');
	putchar(10);
//	dump_processor(processor);
}

void schedule(){
	int i, done;
	int *pData = (int *)(corenum() * 512 + 0x4000);
	Task *pre_task = s_processor->cur_task;
	Task *task_to_run = rm_schedule(timer, s_processor);

	int t = timer%10;
	putchar(48+t);
	putchar(10);
	if(task_to_run!=NULL){
		puts(task_to_run->name);
		putchar('o');
	}
	timer++;

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
			}
		}
	}
}

/* Task 1 Reverse Integer */
void task_1() {
	if(wait_after_done==0){
		/*puts("task1 start\n");*/
   /*     putchar(10);*/
		/*putchar('1');*/
		/*putchar('s');*/
		/*putchar(10);*/
	}
	int dest0 = reverse_integer(123456789);
	int dest1 = reverse_integer(-123456789);
	int dest2 = reverse_integer(0);
	int dest3 = reverse_integer(1000);
	int dest4 = reverse_integer(-1000);

	if(wait_after_done==1){
		task_done(s_processor);
		while (1);
	}else{
		/*puts("task1 done\n");*/
   /*    putchar('1');*/
		/*putchar('e');*/
		/*putchar(10);*/
	}
}

/* Task 2 Binary Search Tree -- insert & delete */
void task_2(){
	//puts("task2\n");
	//insert(s_search_tree, 14);
	//insert(s_search_tree, 15);
	//insert(s_search_tree, 2);

	//delete(s_search_tree, 14);
	//delete(s_search_tree, 15);
	//delete(s_search_tree, 2);

	for(int i=0;i<3;i++){
		int dest0 = reverse_integer(123456789);
		int dest1 = reverse_integer(-123456789);
		int dest2 = reverse_integer(0);
		int dest3 = reverse_integer(1000);
		int dest4 = reverse_integer(-1000);
	}

	if(wait_after_done){
		task_done(s_processor);
		while (1);
	}
	
}

/* Task 2 Binary Search Tree -- search */
void task_3(){
	//puts("task3\n");
	//search_node(s_search_tree, 5);
	//search_node(s_search_tree, 6);
	//search_node(s_search_tree, 12);
	/*putchar(10);*/

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
		while (1);
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

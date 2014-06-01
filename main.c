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
#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

//name, index, t, c, d, p, execute_time, func, state
static Task tasks[] = {

	{ "task1", 0, 0, 0, 0, 0, 0},
	{ "task2", 1, 0, 0, 0, 0, 0},
	{ "task3", 2, 0, 0, 0, 0, 0}
};

static int wait_after_done = 0;
static Processor *processor;

/*Search tree for test*/
SearchTree *s_search_tree;

static volatile unsigned int timer = 0;

void task_1();
void task_2(); 
void task_3();

int reverse_integer(int x);
int test_func_execute_time(Func *func);
void init_tasks();

void mc_init() {
	//set_mask(1);
	// Called in core #1 before the calls of mc_main
	int treeValues[] = { 1, 4, 5, 7, 8, 2, 3, 9, 6, 5, 1, 0 };
	int len = 0;
	GET_ARRAY_LEN(treeValues, len);
	s_search_tree = build_tree(treeValues, len);
	dump_tree(s_search_tree);
	
	processor = new_processor("Processor1");
	init_tasks();
	
	wait_after_done = 1;
}

void mc_main() {
	int core = corenum();
	if(core == 2){
		// Called concurrently in all cores except core #1, after mc_init returns
		//set timer interrupt handler
		set_handlerR((int)isr);
		//set timer interrupt intervals
		set_timerInterval(100000000);

		//set interrupt enable
		set_mask(0);
		while (1);
	}
}

int test_func_execute_time(Func *func){
	//counters_start();
	(*func)();
	return 3;
	//counters_stop();
	//int count = counters_readAndZero(0);
	//return count/10000;
}

void init_tasks()
{
	printf("init_tasks\n");
	int length;
	GET_ARRAY_LEN(tasks, length);
	Func t1 = task_1;
	tasks[0].func = &t1;
	Func t2 = task_2;
	tasks[1].func = &t2;
	Func t3 = task_3;
	tasks[2].func = &t3;

	for(int i=0;i<length;i++){
		printf("test func execute time %d\n" ,  i+1);
		//tasks[i].c = test_func_execute_time(tasks[i].func);
		tasks[i].c = i+2;
		tasks[i].t = tasks[i].c*5;
		tasks[i].saved_state[30] = (int)isr;
	}

	tasks[0].saved_state[31] = (int)task_1;
	tasks[1].saved_state[31] = (int)task_2;
	tasks[2].saved_state[31] = (int)task_3;

	init_tasks_priority(tasks, length);
	for(int i=0;i<length;i++){
		dump_task(&tasks[i]);
	}

	//Processor *p = new_processor("p0");

	printf("push tasks\n");
	for (int i = 0; i<length; i++){
		//push_task(p, &tasks[i]);
		push_task(processor, &tasks[i]);
	}

	dump_processor(processor);
/*
	int scheduable = rm_schedulable(tasks, length);
	if (scheduable>0){
		printf("RM scheduable\n");
		printf("Monitor RM schedule table\n");
		for (int i = 0; i < 10000; i++){
			Task *t = rm_schedule(i, p);
			if (t != NULL){
				if (t->c <= t->execute_time){
					t->execute_time = 0;
					task_done(p);
				}
				printf("%d ", t->index);
			}
			else{
				printf("* ");
			}
			if(i%50==0){
				printf("\n");
			}
		}
		printf("\n");
		printf("Preemptive schedule\n");
		dump_processor(p);
	}
	else{
		printf("Can't schedule by RM\n");
	}
	*/
}

void schedule(){
	int i, done;
	int *pData = (int *)(corenum() * 512 + 0x4000);
	Task *pre_task = processor->cur_task;
	Task *task_to_run = rm_schedule(timer, processor);

	int t = timer%10;
	putchar(48+t);
	if(task_to_run!=NULL){
		puts(task_to_run->name);
		putchar(10);
		puts("test\n");
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
	putchar(43);
}

/* Task 1 Reverse Integer */
void task_1() {
	printf("task1\n");
	int src0 = 123456789;
	int src1 = -123456789;
	int src2 = 0;
	int src3 = 1000;
	int src4 = -1000;
	int dest0 = reverse_integer(src0);
	int dest1 = reverse_integer(src1);
	int dest2 = reverse_integer(src2);
	int dest3 = reverse_integer(src3);
	int dest4 = reverse_integer(src4);

	if(wait_after_done){
		task_done(processor);
		while (1);
	}
}

/* Task 2 Binary Search Tree -- insert & delete */
void task_2(){
	printf("task2\n");
	//insert(s_search_tree, 14);
	//insert(s_search_tree, 15);
	//insert(s_search_tree, 2);
	search_node(s_search_tree, 10);
	search_node(s_search_tree, 11);


	//delete(s_search_tree, 14);
	//delete(s_search_tree, 15);
	//delete(s_search_tree, 2);

	if(wait_after_done){
		task_done(processor);
		while (1);
	}
	
}

/* Task 2 Binary Search Tree -- search */
void task_3(){
	printf("task3\n");
	search_node(s_search_tree, 5);
	search_node(s_search_tree, 6);
	search_node(s_search_tree, 12);

	if(wait_after_done){
		task_done(processor);
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
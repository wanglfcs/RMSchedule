#include<stdio.h>
#include<stdlib.h>
#include "task_scheduler.h"
Task* new_tasks(char *names[], int size){
	/*Task *task = (Task *)malloc(sizeof(Task)*size);*/
	Task *task =global_task;
	Task *t;
	for(int i=0;i<size;i++){
		t = task+i;
		t->c = 0;
		t->d = 0;
		t->p = 0;
		t->t = 0;
		t->index = i+1;
		t->func = NULL;
		t->name = names[i];
		t->ready = 0;
		t->execute_time=0;
	}
	return task;
}

Processor* new_processor(char* name){
	/*Processor *p = (Processor *)malloc(sizeof(Processor));*/
	Processor *p=&global_processor;
	p->usage = 0;
	p->tasks = NULL;
	p->cur_task = NULL;
	p->name = name;
	return p;
}

void init_tasks_priority(Task *tasks, int task_cnt){
	insert_sort(tasks, task_cnt);
	for (int i = 0; i < task_cnt; i++){
		tasks[i].p = task_cnt - i;
	};
}

void insert_sort(Task *x, int n)
{
	int i, j;
	Task t;
	for (i = 1; i<n; i++) /*ÒªÑ¡ÔñµÄ´ÎÊý£º1~n-1¹²n-1´Î*/
	{
		t = *(x + i);
		for (j = i - 1; j >= 0 && t.t<(*(x + j)).t; j--) /*×¢Òâ£ºj=i-1£¬j--£¬ÕâÀï¾ÍÊÇÏÂ±êÎªiµÄÊý£¬ÔÚËüÇ°ÃæÓÐÐòÁÐÖÐÕÒ²åÈëÎ»ÖÃ¡£*/
		{
			*(x + j + 1) = *(x + j); /*Èç¹ûÂú×ãÌõ¼þ¾ÍÍùºóÅ²¡£×î»µµÄÇé¿ö¾ÍÊÇt±ÈÏÂ±êÎª0µÄÊý¶¼Ð¡£¬ËüÒª·ÅÔÚ×îÇ°Ãæ£¬j==-1£¬ÍË³öÑ­»·*/
		}
		*(x + j + 1) = t; /*ÕÒµ½ÏÂ±êÎªiµÄÊýµÄ·ÅÖÃÎ»ÖÃ*/
	}
}

int rm_schedulable_inner(double totle_usage, int task_count)
{
	//double max_usage = task_count*(pow(2, ((double)1 / (double)task_count)) - 1);
	printf("Total cpu usage=%0.3f.", totle_usage * 100);
	//if (totle_usage >= 0 && totle_usage<max_usage && totle_usage <= 1){
	if (totle_usage >= 0 && totle_usage <= 1){
		return 1;
	}
	else{
		return 0;
	}
}

int rm_schedulable(Task *tasks, int n)
{
	double usage = 0, ui = 0;
	Task t;
	for (int i = 0; i < n; i++){
		t = *(tasks + i);
		ui = (double)t.c / (double)t.t;
		usage += ui;
	}
	return rm_schedulable_inner(usage, n);
}

Task* rm_schedule(int time, Processor *processor){
	Task *head = processor->tasks;
	Task *cur;
	Task *task_to_run = NULL;
	int first = 1;
	putchar(processor->task_cnt+'0');
	for(int i = 0;i< processor->task_cnt;i++){
		cur = head + i;
		if(cur)
			putchar('$');
		else
			putchar('&');

		if (time%cur->t == 0){
			cur->ready++;
		}
putchar(cur->ready+'0');
		if(first >0 && cur->ready>0){
putchar('-');
			first = 0;
			processor->cur_task = cur;
			task_to_run = cur;
			task_to_run->execute_time++;
			putchar(43);
		}
	}
	if(task_to_run)
		putchar('R');
	return task_to_run;
}

void task_done(Processor *p){
	putchar(45);
	Task *cur_task = p->cur_task;
	p->cur_task = NULL;
	Task *tasks = p->tasks;
	Task *cur;
	for(int i = 0;i<p->task_cnt;i++){
		cur = tasks + i;
		if(cur_task->index == cur->index){
			cur->ready--;
			return;
		}
	}
}

void set_tasks(Processor *p, Task *t, int task_cnt){
//putchar('T');
	p->tasks = t;
	p->task_cnt = task_cnt;
	double usage = 0;
	Task cur;
	for(int i=0;i<task_cnt;i++){
		cur = t[i];
		usage+=  (double)cur.c / (double)cur.t;
	}
//putchar('T');
}

void push_task(Processor *p, Task *t){
	// TaskNode *node = malloc(sizeof(TaskNode));
	// node->task = t;
	// node->next = NULL;

	// TaskNode *tail = p->tasks->tail;
	// if (tail == NULL){
	// 	p->tasks->head = node;
	// 	p->tasks->tail = node;
	// }
	// else{
	// 	tail->next = node;
	// 	p->tasks->tail = node;
	// }
	// p->tasks->count++;
	// p->usage += (double)t->c / (double)t->t;
}

void ff_distribute_task(Task *tasks, int task_cnt, Processor *processors, int processor_cnt){
	Task maxPeriodTask = *(tasks + task_cnt - 1);
	Task curTask;

	// devide tasks for processors using FF algorithm
	for (int i = 0; i < task_cnt; i++){
		curTask = *(tasks + i);
		//Find first non-empty processor and try to put curTask in it.
		for (int j = 0; j < processor_cnt; j++){
			Processor p = *(processors + j);
			double new_usage = p.usage + (double)curTask.c / (double)curTask.t;
			int count = p.task_cnt;
			if (rm_schedulable_inner(new_usage, count+1)){
				push_task(processors+j, tasks+i);
				break;
			}
		}
	}
}

void dump_processor(Processor *p){
	printf("{\n");
	printf("  Processor %s: usage=%0.3f\n", p->name, p->usage);
	Task *tasks = p->tasks;
	Task *cur;
	printf("  Tasks %d:", p->task_cnt);
	for(int i=0;i<p->task_cnt;i++){
		cur = tasks + i;
		printf("%s ", cur->name);
	}
}

void dump_task(Task *t){
	printf("{\n");
	printf("  Task %s\n", t->name);
	printf("  index %d\n", t->index);
	printf("  C:%d T:%d D:%d P:%d ExeTime:%d\n", t->c,t->t,t->d,t->p,t->execute_time);
	printf("}\n");
}

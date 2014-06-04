#include<stdio.h>
#include "task_scheduler.h"

Task* new_task(char* name){
	Task *task = malloc(sizeof(Task));
	task->c = 0;
	task->d = 0;
	task->p = 0;
	task->t = 0;
	task->func = NULL;
	task->name = name;
	return task;
}

Processor* new_processor(char* name){
	Processor *p = malloc(sizeof(Processor));
	init_processor(p);
	p->name = name;
	return p;
}

TaskList* new_task_list(){
	TaskList *list = malloc(sizeof(TaskList));
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
	return list;
}

void init_processor(Processor *p){
	p->usage = 0;
	p->tasks = new_task_list();
	p->cur_task = NULL;
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
	TaskNode *node = processor->tasks->head;
	Task *task_to_run = NULL;
	int first = 1;
	while (node!=NULL)
	{
		Task *t = node->task;
		if (time%t->t == 0){
			node->ready++;
		}
		if(first >0 && node->ready>0){
			first = 0;
			processor->cur_task = t;
			task_to_run = t;
			task_to_run->execute_time++;
			putchar(43);
		}
		node = node->next;
	}
	return task_to_run;
}

void task_done(Processor *p){
	putchar(45);
	Task *task = p->cur_task;
	p->cur_task = NULL;
	TaskNode *node = p->tasks->head;
	while (node!=NULL)
	{
		if(node->task->index == task->index){
			node->ready--;
			return;
		}
		node = node->next;
	}
}

void push_task(Processor *p, Task *t){
	TaskNode *node = malloc(sizeof(TaskNode));
	node->task = t;
	node->next = NULL;

	TaskNode *tail = p->tasks->tail;
	if (tail == NULL){
		p->tasks->head = node;
		p->tasks->tail = node;
	}
	else{
		tail->next = node;
		p->tasks->tail = node;
	}
	p->tasks->count++;
	p->usage += (double)t->c / (double)t->t;
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
			int count = p.tasks->count;
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
	TaskList *tl = p->tasks;
	TaskNode *cur = tl->head;
	printf("  Tasks %d:", tl->count);
	while (cur != NULL)
	{
		printf("%s ", cur->task->name);
		cur = cur->next;
	}
}

void dump_task(Task *t){
	printf("{\n");
	printf("  Task %s\n", t->name);
	printf("  C:%d T:%d D:%d P:%d ExeTime:%d\n", t->c,t->t,t->d,t->p,t->execute_time);
	printf("}\n");
}

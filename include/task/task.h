#ifndef TASK_H
#define TASK_H

#include<string>
#include<sys/types.h>

enum TaskState{READY,RUNNING,WAITING,TERMINATED};

struct Task {
	pid_t pid;
	int id;
	int burstTime;//运行时间
	int remainingTime;//剩余时间
	int priority;//优先级
	TaskState state;//任务状态
	time_t arrivalTime;//到达时间
	time_t startTime;//开始时间
	time_t endTime;//结束时间
};




#endif // TASK_H

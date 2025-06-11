#ifndef SCHEDULER_H
#define SCHEDULER_H

#include<vector>
#include"../task/task.h"

class Scheduler {
public:
	virtual void addTask(Task task) = 0;
	virtual void run() = 0;
	virtual void printStats() = 0;
	virtual ~Scheduler() = default;
};

#endif // !SCHEDULER_H

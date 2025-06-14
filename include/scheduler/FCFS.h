#ifndef FCFS_H
#define FCFS_H

#include "Scheduler.h"
#include <queue>
#include"../utils/utils.h"
#include<iostream>
#include<mutex>
#include<unistd.h>
#include<sys/wait.h>
class FCFS : public Scheduler {
	std::queue<Task> taskQueue;
	std::vector<Task> completedTasks;
	std::mutex queueMutex;
public:
	void addTask(Task task) override;
	void run() override;
	void printStatus() override;
};

#endif // !FCFS_H

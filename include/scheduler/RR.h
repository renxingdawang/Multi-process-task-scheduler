#ifndef RR_H
#define RR_H

#include"../task/task.h"
#include<queue>
#include<vector>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>
#include <chrono>
#include <thread>

class RoundRobin :public Scheduler {
public:
	explicit RoundRobin(int quantum);
	void addTask(Task task)override;
	void run()override;
	void printStatus() override;
private:
	int timeQuantum;
	std::queue<Task>taskQueue;
	std::vector<Task>completedTasks;
	//std::mutex queueMutex;
};
#endif // !RR_H

#include "FCFS.h"

void FCFS::addTask(Task task)
{
	taskQueue.push(task);
}

void FCFS::run()
{
	while(!taskQueue.empty()) {
		Task task = taskQueue.front();
		taskQueue.pop();

		pid_t pid = fork();
		if (pid == 0) {//pid=0为子进程
			sleep(task.burstTime);
			exit(0);
		}else {//父进程执行
			task.pid = pid;
			task.pid = RUNNING;
			task.startTime = time(nullptr);
			completedTasks.push_back(task);
			std::cout << "FCFS pid: " << pid << " Finished" << std::endl;
		}
	}
}

void FCFS::printStatus()
{
	double totalWait = 0, totalTurnaround = 0;
	for (auto& task : completedTasks) {
		int wait = task.startTime - task.arrivalTime;
		int turnaround = task.endTime - task.arrivalTime;
		totalWait += wait;
		totalTurnaround+ = turnaround;
	}
	std::cout << "FCFS avg wait-time: " << totalWait / completedTasks.size() << std::endl;
	std::cout << "FCFS avg turnaround-time: " << totalTurnaround / completedTasks.size() << std::endl;
}

#include "../../include/scheduler/RR.h"

RoundRobin::RoundRobin(int quantum) :
	timeQuantum(quantum){}


void RoundRobin::addTask(Task task)
{
	taskQueue.push(task);
}

void RoundRobin::run()
{
    while (!taskQueue.empty()) {
        Task task = taskQueue.front();
        taskQueue.pop();

        pid_t pid = fork();
        if (pid == 0) {
            int runTime = std::min(timeQuantum, task.burstTime);
            sleep(runTime);  // 模拟任务部分执行
            exit(0);
        }
        else {
            task.pid = pid;
            task.state = RUNNING;
            task.startTime = time(nullptr);
            std::cout << "RR PID: " << pid << " Running for "
                << std::min(timeQuantum, task.burstTime) << "s..." << std::endl;

            waitpid(pid, nullptr, 0);

            task.burstTime -= timeQuantum;
            if (task.burstTime > 0) {
                taskQueue.push(task); // 未完成，重新入队
            }
            else {
                task.state = TERMINATED;
                task.endTime = time(nullptr);
                completedTasks.push_back(task);
                std::cout << "RR PID: " << pid << " Finished" << std::endl;
            }
        }
    }
}

void RoundRobin::printStatus()
{
	double totalWait = 0, totalTurnaround = 0;
	for (auto& task : completedTasks) {
		int wait = task.startTime - task.arrivalTime;
		int turnaround = task.endTime - task.arrivalTime;
		totalWait += wait;
		totalTurnaround += turnaround;
	}
	std::cout << "RR avg wait-time: " << totalWait / completedTasks.size() << std::endl;
	std::cout << "RR avg turnaround-time: " << totalTurnaround / completedTasks.size() << std::endl;
}

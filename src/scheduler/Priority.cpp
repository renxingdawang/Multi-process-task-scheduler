#include "Priority.h"

void PriorityScheduler::addTask(Task task)
{
	taskQueue.push_back(task);
}

void PriorityScheduler::run()
{
    // 按照优先级升序（值越小优先级越高）
    std::sort(taskQueue.begin(), taskQueue.end(), [](const Task& a, const Task& b) {
        return a.priority < b.priority;
        });

    for (auto& task : taskQueue) {
        pid_t pid = fork();
        if (pid == 0) {
            sleep(task.burstTime);
            exit(0);
        }
        else {
            task.pid = pid;
            task.state = RUNNING;
            task.startTime = time(nullptr);
            std::cout << "Priority PID: " << pid << " (priority " << task.priority << ") Running..."<<std::endl;

            waitpid(pid, nullptr, 0);

            task.state = TERMINATED;
            task.endTime = time(nullptr);
            completedTasks.push_back(task);
            std::cout << "Priority PID: " << pid << " Finished"<<std::endl;
        }
    }
}

void PriorityScheduler::printStatus()
{
    double totalWait = 0, totalTurnaround = 0;
    for (auto& task : completedTasks) {
        int wait = task.startTime - task.arrivalTime;
        int turnaround = task.endTime - task.arrivalTime;
        totalWait += wait;
        totalTurnaround += turnaround;
    }
    std::cout << "Priority avg wait-time: " << totalWait / completedTasks.size() << "s"<<std::endl;
    std::cout << "Priority avg turnaround-time: " << totalTurnaround / completedTasks.size() << "s"<<std::endl;
}


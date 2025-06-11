#ifndef PRIORITY_H
#define PRIORITY_H
#include "Scheduler.h"
#include "../task/task.h"
#include <vector>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
class PriorityScheduler :public Scheduler {
public:
    void addTask(Task task) override;
    void run() override;
    void printStatus() override;

private:
    std::vector<Task> taskQueue;         // 任务列表（按优先级调度）
    std::vector<Task> completedTasks;    // 已完成任务
};

#endif // PRIORITY_H

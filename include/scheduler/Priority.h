#ifndef PRIORITY_H
#define PRIORITY_H

#include "../task/Task.h"
#include <vector>

class PriorityScheduler {
public:
    void addTask(Task task)override;
    void run() override;
    void printStatus() override;

private:
    std::vector<Task> taskQueue;         // �����б������ȼ����ȣ�
    std::vector<Task> completedTasks;    // ���������
};

#endif // PRIORITY_H

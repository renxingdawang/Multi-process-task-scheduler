#ifndef TASK_H
#define TASK_H

#include<string>
#include<sys/types.h>

enum TaskState{READY,RUNNING,WAITING,TERMINATED};

struct Task {
	pid_t pid;
	int id;
	int burstTime;//����ʱ��
	int remainingTime;//ʣ��ʱ��
	int priority;//���ȼ�
	TaskState state;//����״̬
	time_t arrivalTime;//����ʱ��
	time_t startTime;//��ʼʱ��
	time_t endTime;//����ʱ��
};




#endif // TASK_H

#include"include/scheduler/FCFS.h"

int main() {
	FCFS fcfs_scheduler;
	time_t now = time(nullptr);

	fcfs_scheduler.addTask({ -1,1,3,3,1,READY,now,0,0 });
	fcfs_scheduler.addTask({ -1,2,5,5,1,READY,now,0,0 });
	fcfs_scheduler.addTask({ -1,3,2,2,1,READY,now,0,0 });
	fcfs_scheduler.run();
	fcfs_scheduler.printStatus();

	return 0;
}
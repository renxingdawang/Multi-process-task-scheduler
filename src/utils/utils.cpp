#include"../../include/utils/utils.h"

void Utils::printTaskStatus(const Task& task) {
	std::string stateStr[] = { "READY","RUNNING","WAITING","TERMINATED" };
	std::cout << "Status PID" << task.pid
		<< ",Task ID: " << task.id
		<< ",State: " << stateStr[task.state]
		<< ",Remaining: " << task.remainingTime << "s"
		<< ",Priority: " << task.priority
		<< std::endl;
}
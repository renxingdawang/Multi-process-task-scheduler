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

auto Utils::parseTask(const std::string& data) -> Task
{
    Task task;
    // 初始化默认值
    task.pid = -1;
    task.state = READY;
    task.arrivalTime = time(nullptr);
    task.startTime = 0;
    task.endTime = 0;

    // 按逗号分割字符串
    size_t pos1 = data.find(',');
    size_t pos2 = data.find(',', pos1 + 1);
    if (pos1 == std::string::npos || pos2 == std::string::npos) {
        std::cerr << "Invalid task data format: " << data << std::endl;
        return task;
    }
    try {
        task.id = std::stoi(data.substr(0, pos1));
        task.burstTime = std::stoi(data.substr(pos1 + 1, pos2 - pos1 - 1));
        task.remainingTime = task.burstTime; // 剩余时间初始等于总时间
        task.priority = std::stoi(data.substr(pos2 + 1));
    }
    catch (const std::exception& e) {
        std::cerr << "Parse task failed: " << e.what() << std::endl;
    }
    return task;
}

#ifndef UTILS_H
#define UTILS_H

#include"../task/task.h"
#include<iostream>
#include<string>
class Utils {
public:
	static void printTaskStatus(const Task& task);
	static auto parseTask(const std::string& data)->Task;
};

#endif // !UTILS_H

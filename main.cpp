#include"include/scheduler/FCFS.h"
#include"include/scheduler/RR.h"
#include"include/scheduler/Priority.h"
#include"include/utils/utils.h"
#include <errno.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define PIPE_PATH "/tmp/task_pipe"
#include<ctime>

// 全局调度器指针（根据实际使用的调度器类型调整）
Scheduler* global_scheduler = nullptr;

// 管道监听线程函数（非阻塞读取）

void* listenPipe(void* arg) {
    char buffer[256];
    while (true) {
        // 读取管道数据（非阻塞模式）
        ssize_t bytesRead = read(*(int*)arg, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            Task newTask = Utils::parseTask(buffer);
            if (newTask.id != -1 && global_scheduler) {
                global_scheduler->addTask(newTask);
                std::cout << "成功添加新任务，ID: " << newTask.id << std::endl;
            }
        }
        else if (bytesRead == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // 无数据可读，休眠100ms降低CPU占用
                usleep(100000);
                continue;
            }
            perror("Read pipe failed");
            break;
        }
    }
    return nullptr;
}

int main() {
    
    // ---------------- FCFS Test----------------
    FCFS fcfs_scheduler;
    time_t now_fcfs = time(nullptr);
    fcfs_scheduler.addTask({ -1, 1, 3, 3, 1, READY, now_fcfs, 0, 0 });
    fcfs_scheduler.addTask({ -1, 2, 5, 5, 1, READY, now_fcfs, 0, 0 });
    fcfs_scheduler.addTask({ -1, 3, 2, 2, 1, READY, now_fcfs, 0, 0 });
    std::cout << "--- FCFS Test ---\n";
    fcfs_scheduler.run();
    fcfs_scheduler.printStatus();

    // ---------------- RR Test----------------
    RoundRobin rr_scheduler(2);  // 构造函数传入时间片参数（需与RR类定义一致）
    time_t now_rr = time(nullptr);
    rr_scheduler.addTask({ -1, 4, 4, 4, 1, READY, now_rr, 0, 0 });
    rr_scheduler.addTask({ -1, 5, 6, 6, 1, READY, now_rr, 0, 0 });
    rr_scheduler.addTask({ -1, 6, 3, 3, 1, READY, now_rr, 0, 0 });
    std::cout << "\n--- RR Test ---\n";
    rr_scheduler.run();
    rr_scheduler.printStatus();

    // ---------------- Priority Test  ----------------
    PriorityScheduler priority_scheduler;
    time_t now_pri = time(nullptr);
    priority_scheduler.addTask({ -1, 7, 2, 2, 3, READY, now_pri, 0, 0 });  // 优先级3
    priority_scheduler.addTask({ -1, 8, 5, 5, 1, READY, now_pri, 0, 0 });  // 优先级1
    priority_scheduler.addTask({ -1, 9, 4, 4, 2, READY, now_pri, 0, 0 });  // 优先级2
    std::cout << "\n--- Priority Test ---\n";
    priority_scheduler.run();
    priority_scheduler.printStatus();

    global_scheduler = &fcfs_scheduler;

    // 创建命名管道（若已存在则忽略错误）
    int ret = mkfifo(PIPE_PATH, 0666);
    if (ret == -1 && errno != EEXIST) {
        perror("Create pipe failed");
        return 1;
    }

    // 打开管道用于非阻塞读取
    int pipe_fd = open(PIPE_PATH, O_RDONLY | O_NONBLOCK);
    if (pipe_fd == -1) {
        perror("Open pipe failed");
        return 1;
    }

    // 启动监听线程
    pthread_t pipeThread;
    if (pthread_create(&pipeThread, nullptr, listenPipe, &pipe_fd) != 0) {
        perror("Create thread failed");
        close(pipe_fd);
        return 1;
    }

    std::cout << "--- main thread opened,please add task by pipe ---"<<std::endl;
    time_t now = time(nullptr);
    fcfs_scheduler.addTask({ -1, 1, 3, 3, 1, READY, now_fcfs, 0, 0 });
    fcfs_scheduler.addTask({ -1, 2, 5, 5, 1, READY, now_fcfs, 0, 0 });
    fcfs_scheduler.addTask({ -1, 3, 2, 2, 1, READY, now_fcfs, 0, 0 });
    fcfs_scheduler.run();

    // 等待监听线程结束（实际可根据需求调整退出逻辑）
    pthread_join(pipeThread, nullptr);
    close(pipe_fd);
    return 0;
}
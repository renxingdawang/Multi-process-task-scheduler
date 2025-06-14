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

// ȫ�ֵ�����ָ�루����ʵ��ʹ�õĵ��������͵�����
Scheduler* global_scheduler = nullptr;

// �ܵ������̺߳�������������ȡ��

void* listenPipe(void* arg) {
    char buffer[256];
    while (true) {
        // ��ȡ�ܵ����ݣ�������ģʽ��
        ssize_t bytesRead = read(*(int*)arg, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            Task newTask = Utils::parseTask(buffer);
            if (newTask.id != -1 && global_scheduler) {
                global_scheduler->addTask(newTask);
                std::cout << "�ɹ����������ID: " << newTask.id << std::endl;
            }
        }
        else if (bytesRead == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // �����ݿɶ�������100ms����CPUռ��
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
    RoundRobin rr_scheduler(2);  // ���캯������ʱ��Ƭ����������RR�ඨ��һ�£�
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
    priority_scheduler.addTask({ -1, 7, 2, 2, 3, READY, now_pri, 0, 0 });  // ���ȼ�3
    priority_scheduler.addTask({ -1, 8, 5, 5, 1, READY, now_pri, 0, 0 });  // ���ȼ�1
    priority_scheduler.addTask({ -1, 9, 4, 4, 2, READY, now_pri, 0, 0 });  // ���ȼ�2
    std::cout << "\n--- Priority Test ---\n";
    priority_scheduler.run();
    priority_scheduler.printStatus();

    global_scheduler = &fcfs_scheduler;

    // ���������ܵ������Ѵ�������Դ���
    int ret = mkfifo(PIPE_PATH, 0666);
    if (ret == -1 && errno != EEXIST) {
        perror("Create pipe failed");
        return 1;
    }

    // �򿪹ܵ����ڷ�������ȡ
    int pipe_fd = open(PIPE_PATH, O_RDONLY | O_NONBLOCK);
    if (pipe_fd == -1) {
        perror("Open pipe failed");
        return 1;
    }

    // ���������߳�
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

    // �ȴ������߳̽�����ʵ�ʿɸ�����������˳��߼���
    pthread_join(pipeThread, nullptr);
    close(pipe_fd);
    return 0;
}
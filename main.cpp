#include"include/scheduler/FCFS.h"
#include"include/scheduler/RR.h"
#include"include/scheduler/Priority.h"
//#include<ctime>
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

    return 0;
}
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

#define PRIO_High 3
#define PRIO_Med 5
#define PRIO_Low 7
#define PRIO_Coop -1
void t_high_fn (void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("Thread High is running");
        k_msleep(100);
    }
}

void t_med_fn (void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("Thread Medium is running");
        k_msleep(200);
    }
}

void t_low_fn (void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("Thread Low is running");
        k_msleep(300);
    }
}


void t_Coop_fn (void *p1, void *p2, void *p3)
{
  
    for(int i=0; i<5; i++){
        LOG_INF("Thread Coop is running");     
    }
    k_yield();

}

K_THREAD_DEFINE(thread_a, STACK_SIZE, t_high_fn,
                NULL, NULL, NULL, PRIO_High, 0, 0);
K_THREAD_DEFINE(thread_b, STACK_SIZE, t_med_fn,
                NULL, NULL, NULL, PRIO_Med, 0, 0);
K_THREAD_DEFINE(thread_c, STACK_SIZE, t_low_fn,
                NULL, NULL, NULL, PRIO_Low, 0, 0);
K_THREAD_DEFINE(thread_d, STACK_SIZE, t_Coop_fn,
                NULL, NULL, NULL, PRIO_Coop, 0, 0);                

int main(void)
{
    return 0;
}


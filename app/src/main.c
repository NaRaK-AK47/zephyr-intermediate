// build and run with: qemu_x86 to view the deffered counter results

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

#define PRIO_High 3
#define PRIO_Med 5
#define PRIO_Low 7
#define PRIO_Coop -1

#define INCREMENT_CNT 10000

static K_MUTEX_DEFINE(counter_mutex);

static volatile int counter = 0;

void t_high_fn (void *p1, void *p2, void *p3)
{

    for(int i=0; i<INCREMENT_CNT; i++){
        k_mutex_lock(&counter_mutex, K_FOREVER);
          counter++; 
          k_mutex_unlock(&counter_mutex);
    }
    LOG_INF("Counter value High: %d", counter);
    

}

void t_med_fn (void *p1, void *p2, void *p3)
{
    for(int i=0; i<INCREMENT_CNT; i++){
        k_mutex_lock(&counter_mutex, K_FOREVER);
          counter++; 
          k_mutex_unlock(&counter_mutex);
    }
    LOG_INF("Counter value Med: %d", counter);
    
}


K_THREAD_DEFINE(thread_a, STACK_SIZE, t_high_fn,
                NULL, NULL, NULL, PRIO_High, 0, 0);
K_THREAD_DEFINE(thread_b, STACK_SIZE, t_med_fn,
                NULL, NULL, NULL, PRIO_High, 0, 0);

int main(void)
{
    k_thread_join(thread_a, K_FOREVER);
    k_thread_join(thread_b, K_FOREVER);

    LOG_INF("Final counter value: %d", counter );
    LOG_INF("Final counter deferred: %d", (INCREMENT_CNT*2) - counter );

    return 0;
}




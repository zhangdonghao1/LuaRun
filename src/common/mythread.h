#ifdef _linux_
#include<pthread.h>
#elif _WIN32
#endif
#ifdef _linux_
/*------------------------------------------------------------
 *  函数名称：createThread
 *  功能描述：创建指定了调度策略的特定类型的线程
 *  参数说明：thread: 线程标识
 *            sched_policy：调度策略 SCHED_RR、SCHED_FIFO 或 SCHED_OTHER
 *            sched_priority: 调度优先级
 *            stacksize: 线程栈大小
 *            start_routine: 线程启动函数
 *            arg: 线程启动函数的参数
 *  返 回 值：线程创建成功，  0
 *            线程创建失败，非0
 */
/* 
 *  man sched_get_priority_max:
 *  Linux allows the static priority value range 1 to 99 for SCHED_FIFO and SCHED_RR
 *  and the priority 0 for SCHED_OTHER and SCHED_BATCH.
 *  Scheduling priority ranges for the various policies are not alterable.
 */
inline int createThread(pthread_t *thread, unsigned int sched_policy, unsigned int sched_priority,
                        size_t stacksize, void *(*start_routine) (void *), void *arg)
{
	int res = 0;
	pthread_attr_t attr;

	// 只有 RR 和 FIFO 时设置策略，其他情况忽略
	if (sched_policy == SCHED_RR || sched_policy == SCHED_FIFO)
	{
		int priority_max = sched_get_priority_max(sched_policy);
		int priority_min = sched_get_priority_min(sched_policy);
		struct sched_param sp;
		sp.sched_priority = priority_min + sched_priority;
		if (sp.sched_priority > priority_max)
			sp.sched_priority = priority_max;

		pthread_attr_init(&attr);
		pthread_attr_setstacksize(&attr, stacksize);
		pthread_attr_setschedpolicy(&attr, sched_policy);
		pthread_attr_setschedparam(&attr, &sp);
		pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		// 创建带调度策略模式的线程
		res = pthread_create(thread, &attr, start_routine, arg);

		pthread_attr_destroy(&attr);

		if (res == 0) // 成功
			return res;
		else
			; // 失败，重试创建无调度策略线程
	}
	else
		; // 按默认模式正常创建线程

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_attr_setstacksize(&attr, stacksize);
	res = pthread_create(thread, &attr, start_routine, arg);
	pthread_attr_destroy(&attr);

	return res;
}
#elif _WIN32

#endif
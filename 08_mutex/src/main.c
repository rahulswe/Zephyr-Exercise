/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define TASK_STK_SIZE (1024U)

#define TASK_PRIORITY (7U)

K_MUTEX_DEFINE(resource_mutex);

#define COMBINED_TOTAL (40U)

int32_t count1 = 0;
int32_t count2 = COMBINED_TOTAL;

void execute_shared_code()
{
	count1 += 1;
	count1 %= COMBINED_TOTAL;

	count2 -= 1;
	if(count2 == 0)
	{
		count2 = COMBINED_TOTAL;
	}

	if((count1 + count2) != COMBINED_TOTAL)
	{
		printk("Race Condition: Count1 = %d, Count2 = %d\n", count1, count2);
		k_msleep(1000);
	}
}

void thread1()
{
	printk("Thread1 Started\n");
	while (1)
	{
		//printk("Running Thread1\n");
		k_mutex_lock(&resource_mutex, K_FOREVER);
		execute_shared_code();
		k_mutex_unlock(&resource_mutex);
	}
}

void thread2()
{
	printk("Thread2 Started\n");
	while (1)
	{
		//printk("Running Thread2\n");
		k_mutex_lock(&resource_mutex, K_FOREVER);
		execute_shared_code();
		k_mutex_unlock(&resource_mutex);
	}
}

K_THREAD_DEFINE(thread1_id, TASK_STK_SIZE, thread1, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);
K_THREAD_DEFINE(thread2_id, TASK_STK_SIZE, thread2, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);
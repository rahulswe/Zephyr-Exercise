/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define TASK_STK_SIZE (1024U)
#define TASK_PRIORITY (7U)

void thread1()
{
	while (1)
	{
		printk("Running Thread1\n");
		k_busy_wait(1000000);
	}
}

void thread2()
{
	while (1)
	{
		printk("Running Thread2\n");
		k_busy_wait(1000000);
	}
}

K_THREAD_DEFINE(thread1_id, TASK_STK_SIZE, thread1, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);
K_THREAD_DEFINE(thread2_id, TASK_STK_SIZE, thread2, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);
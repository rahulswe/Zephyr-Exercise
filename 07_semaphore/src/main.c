/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define TASK_STK_SIZE (1024U)

#define PRODUCER_PRIORITY (7U)
#define CONSUMER_PRIORITY (6U)

static volatile uint32_t num_resources = 10;

K_SEM_DEFINE(resource_sem, 10, 10);

void producer()
{
	while (1)
	{
		//acquire_resource();
		k_sem_give(&resource_sem);
		num_resources++;
		printk("Running Producer Thread: %d Resources\n", num_resources);
		k_msleep(1000);
	}
}

void consumer()
{
	while (1)
	{
		//release_resource();
		k_sem_take(&resource_sem, K_FOREVER);
		num_resources--;
		printk("Running Consumer Thread: %d Resources\n", num_resources);
		k_msleep(1000);
	}
}

K_THREAD_DEFINE(p_id, TASK_STK_SIZE, producer, NULL, NULL, NULL, PRODUCER_PRIORITY, 0, 0);
K_THREAD_DEFINE(c_id, TASK_STK_SIZE, consumer, NULL, NULL, NULL, CONSUMER_PRIORITY, 0, 0);
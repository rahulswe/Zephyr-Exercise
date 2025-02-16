/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 10000 msec = 10 sec */
#define SLEEP_TIME_MS 10000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/* The devicetree node identifier for the "sw0" alias */
#define SW0_NODE DT_ALIAS(sw0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

static struct gpio_callback button_cb_data;

void button_press_isr(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	gpio_pin_toggle_dt(&led);
}

int main(void)
{
	int ret;

	if (!gpio_is_ready_dt(&led))
	{
		return -1;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
	{
		return -1;
	}

#if 1 // either of the two is fine
	if (!gpio_is_ready_dt(&button))
	{
		return 0;
	}
#else
	if (!device_is_ready(button.port))
	{
		return -1;
	}
#endif

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0)
	{
		return -1;
	}

	ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret < 0)
	{
		return -1;
	}

	gpio_init_callback(&button_cb_data, button_press_isr, BIT(button.pin));

	gpio_add_callback(button.port, &button_cb_data);

	while (1)
	{
		//k_msleep(SLEEP_TIME_MS);
		k_yield();
	}

	return 0;
}

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <stdio.h>
#include <stdbool.h>

#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define B13_NODE DT_PATH(gpio_portb, b_13)
#define B15_NODE DT_ALIAS(b15)
#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec pb13 = GPIO_DT_SPEC_GET(B13_NODE, gpios);
static const struct gpio_dt_spec pb15 = GPIO_DT_SPEC_GET(B15_NODE, gpios);
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

#define MY_DEV_IRQ  24       
#define MY_DEV_PRIO  2      
#define MY_ISR_ARG  DEVICE_GET(my_device)
#define MY_IRQ_FLAGS 0       /* IRQ flags */

static struct gpio_callback pb13_cb_data;

void pb13_callback(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
    gpio_pin_toggle(pb15.port, pb15.pin);
}

#define STACKSIZE 1024

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
int main()
{
    int ret;

	ret = gpio_pin_configure_dt(&pb13, GPIO_INPUT);
	ret = gpio_pin_configure_dt(&pb15, GPIO_OUTPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, pb13.port->name, pb13.pin);
		return 0;
	}

	ret = gpio_pin_interrupt_configure_dt(&pb13,
					      GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, pb13.port->name, pb13.pin);
		return 0;
	}

	gpio_init_callback(&pb13_cb_data, pb13_callback, BIT(pb13.pin));
	gpio_add_callback(pb13.port, &pb13_cb_data);

    while (1)
    {
        /* code */
    }
    
}


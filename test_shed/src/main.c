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
/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define B13_NODE DT_PATH(gpio_portb, b_13)
#define B15_NODE DT_ALIAS(b15)
#define LED0_NODE DT_ALIAS(led0)
#if !DT_NODE_HAS_STATUS(B13_NODE, okay)
#error "Unsupported board: led0 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec pb13 = GPIO_DT_SPEC_GET(B13_NODE, gpios);
//static const struct gpio_dt_spec pb15 = GPIO_DT_SPEC_GET_OR(B15_NODE, gpios, {0});
#define STACKSIZE 1024

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */

void vTask1Code(void *pvParameters)
{
    printk("Task2");

    //const struct gpio_driver_config *const cfg = (const struct gpio_driver_config *)pb13.port->config;
    //printk("%i\n\r", cfg->port_pin_mask);
    gpio_pin_configure_dt(&pb13, GPIO_INPUT);
    while (1)
    {
        gpio_pin_toggle(pb13.port, pb13.pin);
        // add GPIO toggle code here
        //k_yield();
        k_msleep(1000);
    }
}

void vTask2Code(void *pvParameters)
{
    while (1)
    {
        printk("Task2");
        gpio_pin_toggle(pb13.port, pb13.pin);

        // add GPIO toggle code here
        k_yield();
    }
}

void vTask3Code(void *pvParameters)
{
    while (1)
    {
        printf("Task3");
        gpio_pin_toggle(pb13.port, pb13.pin);
        // add GPIO toggle code here
        k_yield();
    }
}

void vTask4Code(void *pvParameters)
{
    while (1)
    {
        printf("Task4");
        gpio_pin_toggle(pb13.port, pb13.pin);
        // add GPIO toggle code here
        k_yield();
    }
}

void* vTask5Code(void *pvParameters)
{
    while (1)
    {
        printf("Task5");
        gpio_pin_toggle(pb13.port, pb13.pin);
        // add GPIO toggle code here
        k_yield();
    }
}

K_THREAD_DEFINE(thread1, STACKSIZE, vTask1Code, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(thread2, STACKSIZE, vTask2Code, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(thread3, STACKSIZE, vTask3Code, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(thread4, STACKSIZE, vTask4Code, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(thread5, STACKSIZE, vTask5Code, NULL, NULL, NULL, 5, 0, 0);



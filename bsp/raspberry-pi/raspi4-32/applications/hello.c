/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#define LED_PIN 2
static int led_init(void)
{
    /* 设定 LED 引脚为推挽输出模式 */
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    return 0;
}

static int led_on(void)
{
    /* 调用 API 输出低电平 */
    rt_pin_write(LED_PIN, PIN_LOW);

    return 0;
}

static int led_off(void)
{
    /* 调用 API 输出高电平 */
    rt_pin_write(LED_PIN, PIN_HIGH);

    return 0;
}

static int led_toggle(void)
{
    /* 调用 API 读出当前电平 然后输出相反电平 */
    rt_pin_write(LED_PIN, !rt_pin_read(LED_PIN));

    return 0;
}

static void hello(int argc, char** argv)
{
   // rt_kprintf("Hi, this is RT-Thread!!\n");
    led_init();
    led_on();
    int i=15;
    while(i--)
    {
        led_toggle();
        rt_kprintf("Hi, this is RT-Thread!!\n");
        rt_kprintf("the pin status is %d\n",rt_pin_read(LED_PIN));
        rt_thread_mdelay(500);
    }
}
MSH_CMD_EXPORT(hello,my first add function);
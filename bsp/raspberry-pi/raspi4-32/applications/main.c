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
int main(int argc, char** argv)
{
   // rt_kprintf("Hi, this is RT-Thread!!\n");
    int i=15;
    while(i--)
    {
        rt_kprintf("Hi, this is RT-Thread!!\n");
        rt_thread_mdelay(500);
    }
    return 0;
}
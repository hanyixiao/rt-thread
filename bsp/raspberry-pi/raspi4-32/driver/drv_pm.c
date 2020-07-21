/*
 *Copyright(c) 2006-2020
 * 
 *SPDX-License-Identifier: Apache-2.0 
 * 
 *Change Logs: 
 *Date             Author        Notes
 *2020-07-20       YixiaoHan    first version
 */

#include "drv_pm.h"


static void sleep(struct rt_pm *pm, uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
        rt_kprintf("kernel loaded sleep \n");
        break;

    case PM_SLEEP_MODE_IDLE:
        // __WFI();
        break;

    case PM_SLEEP_MODE_LIGHT:
        /* Enter SLEEP Mode, Main regulator is ON */
       // HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
        break;

    case PM_SLEEP_MODE_DEEP:
        /* Enter STOP 2 mode  */
       // HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
        break;

    case PM_SLEEP_MODE_STANDBY:
        /* Enter STANDBY mode */
     //   HAL_PWR_EnterSTANDBYMode();
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        /* Enter SHUTDOWNN mode */
        //HAL_PWREx_EnterSHUTDOWNMode();
        break;

    default:
        RT_ASSERT(0);
        break;
    }
}
static uint8_t run_speed[PM_RUN_MODE_MAX][2] =
{
    {80, 0},
    {80, 1},
    {24, 2},
    {2,  3},
};

static void run(struct rt_pm *pm, uint8_t mode)
{
    static uint8_t last_mode;
    static char *run_str[] = PM_RUN_MODE_NAMES;

    if (mode == last_mode)
        return;
    last_mode = mode;

    /* 1. 设置 MSI 作为 SYSCLK 时钟源,以修改 PLL */
    //SystemClock_MSI_ON();

    /* 2. 根据RUN模式切换时钟频率(HSI) */
    switch (mode)
    {
    case PM_RUN_MODE_HIGH_SPEED:
    case PM_RUN_MODE_NORMAL_SPEED:
        // HAL_PWREx_DisableLowPowerRunMode();
        // SystemClock_80M();
        // /* Configure the main internal regulator output voltage (Range1 by default)*/
        // HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
        break;
    case PM_RUN_MODE_MEDIUM_SPEED:
        // HAL_PWREx_DisableLowPowerRunMode();
        // SystemClock_24M();
        // /* Configure the main internal regulator output voltage */
        // // HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE2);
        break;
    case PM_RUN_MODE_LOW_SPEED:
        // SystemClock_2M();
        // /* Enter LP RUN mode */
        // HAL_PWREx_EnableLowPowerRunMode();
        break;
    default:
        break;
    }

    /* 3. 关闭 MSI 时钟 */
    // SystemClock_MSI_OFF();

    /* 4. 更新外设时钟 */
    // uart_console_reconfig();
    // /* Re-Configure the Systick time */
    // HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / RT_TICK_PER_SECOND);
    // /* Re-Configure the Systick */
    // HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    rt_kprintf("kernel load run code add/n");
    // rt_kprintf("switch to %s mode, frequency = %d MHz\n", run_str[mode], run_speed[mode][0]);
}
/**
 * This function start the timer of pm
 *
 * @param pm Pointer to power manage structure
 * @param timeout How many OS Ticks that MCU can sleep
 */
static void pm_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    RT_ASSERT(pm != RT_NULL);
    RT_ASSERT(timeout > 0);

    if (timeout != RT_TICK_MAX)
    {
        /* Convert OS Tick to pmtimer timeout value */
        // timeout = stm32l4_pm_tick_from_os_tick(timeout);
        // if (timeout > stm32l4_lptim_get_tick_max())
        // {
        //     timeout = stm32l4_lptim_get_tick_max();
        // }

        // /* Enter PM_TIMER_MODE */
        // stm32l4_lptim_start(timeout);
    }
    rt_kprintf("kernel load timer start \n");
}

/**
 * This function stop the timer of pm
 *
 * @param pm Pointer to power manage structure
 */
static void pm_timer_stop(struct rt_pm *pm)
{
    RT_ASSERT(pm != RT_NULL);

    /* Reset pmtimer status */
    // stm32l4_lptim_stop();
    rt_kprintf("kernel load stop\n");
}

/**
 * This function calculate how many OS Ticks that MCU have suspended
 *
 * @param pm Pointer to power manage structure
 *
 * @return OS Ticks
 */
static rt_tick_t pm_timer_get_tick(struct rt_pm *pm)
{
    rt_uint32_t timer_tick;

    RT_ASSERT(pm != RT_NULL);

    timer_tick = 100;

    rt_kprintf("kernel load timer\n");

    return (timer_tick);
}
int rt_hw_pm_init(void)
{
    static const struct rt_pm_ops _ops =
    {
        sleep,
        run,
        pm_timer_start,
        pm_timer_stop,
        pm_timer_get_tick
    };

    rt_uint8_t timer_mask = 0;

    /* Enable Power Clock */
  //  __HAL_RCC_PWR_CLK_ENABLE();

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_pm_init);
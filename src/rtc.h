#ifndef __RTC_H
#define __RTC_H

/** @defgroup RTC RTC
 * @{
 * Functions and constants to make RTC work
 */

#include <minix/syslib.h>
#include <minix/driver.h>
#include <minix/drivers.h>

/**
 * @brief Subscribes rtc
 *
 * @return Return irq Bit mask and negative value on failure
 */
int rtc_subscribe_int();

/**
 * @brief Unsubscribes rtc interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_unsubscribe_int();

/**
 * @brief Retuns days in real time
 *
 * @return Return days
 */
int day();

/**
 * @brief Retuns months in real time
 *
 * @return Return months
 */
int month();

/**
 * @brief Retuns years in real time
 *
 * @return Return years
 */
int year();

#endif

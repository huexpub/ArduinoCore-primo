/* Copyright (c) 2016, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**@file
 *
 * @defgroup sdk_error SDK Error codes
 * @{
 * @ingroup app_common
 * @{
 * @details Error codes are 32-bit unsigned integers with the most significant 16-bit reserved for
 *          identifying the module where the error occurred while the least least significant LSB
 *          are used to provide the cause or nature of error. Each module is assigned a 16-bit
 *          unsigned integer. Which it will use to identify all errors that occurred in it. 16-bit
 *          LSB range is with module id as the MSB in the 32-bit error code is reserved for the
 *          module. As an example, if 0x8800 identifies a certain SDK module, all values from 
 *          0x88000000 - 0x8800FFFF are reserved for this module.
 *          It should be noted that common error reasons have been assigned values to make it 
 *          possible to decode error reason easily. As an example, lets module uninitialized has
 *          been assigned an error code 0x000A0. Then, if application encounters an error code
 *          0xZZZZ00A0, it knows that it accessing a certain module without initializing it.
 *          Apart from this, each module is allowed to define error codes that are not covered by
 *          the common ones, however, these values are defined in a range that does not conflict
 *          with common error values. For module, specific error however, it is possible that the
 *          same error value is used by two different modules to indicated errors of very different
 *          nature. If error is already defined by the NRF common error codes, these are reused.
 *          A range is reserved for application as well, it can use this range for defining
 *          application specific errors.
 *
 * @note Success code, NRF_SUCCESS, does not include any module identifier.          

 */

#ifndef SDK_ERRORS_H__
#define SDK_ERRORS_H__

#include <stdint.h>
#include "nrf_error.h"

/**
 * @defgroup sdk_err_base Base defined for SDK Modules
 * @{
 */
#define SDK_ERROR_BASE         (NRF_ERROR_BASE_NUM + 0x8000)   /**< Base value defined for SDK module identifiers. */
#define SDK_COMMON_ERROR_BASE  (NRF_ERROR_BASE_NUM + 0x0080)   /**< Base error value to be used for SDK error values. */
/* @} */

/**
 * @defgroup sdk_module_codes Codes reserved as identification for module where the error occurred.
 * @{
 */
#define DEVICE_MANAGER_ERR_BASE   (0x8000)
#define MEMORY_MANAGER_ERR_BASE   (0x8100)
/* @} */


/**
 * @defgroup sdk_iot_errors Codes reserved as identification for IoT errors.
 * @{
 */
#define IOT_ERR_BASE_START        (0xA000)
#define IOT_ERR_BASE_STOP         (0xAFFF)
/* @} */
 

/**
 * @defgroup sdk_common_errors Codes reserved as identification for common errors.
 * @{
 */
#define MODULE_NOT_INITIALZED      (SDK_COMMON_ERROR_BASE + 0x0000)
#define MUTEX_INIT_FAILED          (SDK_COMMON_ERROR_BASE + 0x0001)
#define MUTEX_LOCK_FAILED          (SDK_COMMON_ERROR_BASE + 0x0002)
#define MUTEX_UNLOCK_FAILED        (SDK_COMMON_ERROR_BASE + 0x0003)
#define MUTEX_COND_INIT_FAILED     (SDK_COMMON_ERROR_BASE + 0x0004)
#define MODULE_ALREADY_INITIALIZED (SDK_COMMON_ERROR_BASE + 0x0005)
#define API_NOT_IMPLEMENTED        (SDK_COMMON_ERROR_BASE + 0x0010)
#define FEATURE_NOT_ENABLED        (SDK_COMMON_ERROR_BASE + 0x0011)
/* @} */


/**
 * @defgroup dm_specific_errors Error / status codes specific to device manager.
 * @{
 */
#define DM_NO_APP_CONTEXT                (DEVICE_MANAGER_ERR_BASE + 0x0040)
#define DM_SERVICE_CONTEXT_NOT_APPLIED   (DEVICE_MANAGER_ERR_BASE + 0x0041)
#define DM_CONTEXT_INFO_LOST             (DEVICE_MANAGER_ERR_BASE + 0x0042)
#define DM_DEVICE_CONTEXT_FULL           (DEVICE_MANAGER_ERR_BASE + 0x0043)
/* @} */

/**
 * @brief API Result.
 *
 * @details Indicates success or failure of an API procedure. In case of failure, a comprehensive
 *          error code indicating cause or reason for failure is provided.
 *
 *          Though called an API result, it could used in Asynchronous notifications callback along
 *          with asynchronous callback as event result. This mechanism is employed when an event
 *          marks the end of procedure initiated using API. API result, in this case, will only be
 *          an indicative of whether the procedure has been requested successfully.
 */
typedef uint32_t ret_code_t;
/** @} */
/** @} */

#endif // SDK_ERRORS_H__


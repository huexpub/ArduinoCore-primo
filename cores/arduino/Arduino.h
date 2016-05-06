/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2016 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include "nrf_gpio.h"
#include "nrf_delay.h"



/* sketch */
void setup( void ) ;
void loop( void ) ;

#include "WVariant.h"

// Include board variant
#include "variant.h"

#include "wiring_digital.h"

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif //Arduino_h
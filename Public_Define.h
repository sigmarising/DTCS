#pragma once

#include "DB_ACCESS.h"




//  season for slave use
extern int g_season;


//  define the debug option:
//      1.  if this option set true
//          the program will allow statmens throw
//          instead of assert
//      2.  if this option set false
//          the program will not allow throw
//          just use the assert
#define DEBUG_ALLOW_THROW   true


//  define for database connect
#define DB_CONNECT_TYPE     "QMYSQL"
#define DB_CONNECT_NAME     "DTCS"
#define DB_HOST_NAME        "api.mywsq.cn"
#define DB_USER_NAME        "bupt"
#define DB_PASSWORD         "bupt"
#define DB_DATABASE_NAME    "bupt"


//  define the wind speed
#define WIND_CLOSE  0
#define WIND_LOW    1
#define WIND_MEDIUM 2
#define WIND_HIGH   3


//  define for switch
#define SWITCH_ON   0
#define SWITCH_OFF  1


//  define for master mode
#define MODE_COLD       0
#define MODE_HOT        1
#define MODE_DEFAULT    0


//  define some temp value
#define TEMP_HOT_MIN        25
#define TEMP_HOT_MAX        30
#define TEMP_COLD_MIN       18
#define TEMP_COLD_MAX       25
#define TEMP_MIN            18
#define TEMP_MAX            30
#define TEMP_HOT_DEFAULT    28
#define TEMP_COLD_DEFAULT   22
#define TEMP_SUMMER_DEFAULT 31
#define TEMP_WINTER_DEFAULT 18

//  define for update frequent (ms)
#define FREQUENT_MASTER_DEFAULT     1000
#define FREQUENT_MASTER_MONEY       100
#define FREQUENT_SLAVE_UPDATE       1000

//  define for admin key default
#define ADMIN_KEY   "admin"


//  define for enegry amount rate
//  count by ms
#define ENERGY_WIND_LOW         double(0.8/60000)
#define ENERGY_WIND_MEDIUM      double(1/60000)
#define ENERGY_WIND_HIGH        double(1.3/60000)
#define ENERGY_AMOUNT_RATE      double(5)


//  define for temp progress
//  count by ms
#define PROGRESS_NATURE_SUMMER  double(1 /10000)
#define PROGRESS_NATURE_WINTER  double(-1/10000)
#define PROGRESS_WIND_1         double(1 /12500)
#define PROGRESS_WIND_2         double(1 /10000)
#define PROGRESS_WIND_3         double(1 / 7500)


// define for temp progress max min
#define PROGRESS_MIN            15
#define PROGRESS_MAX            32


//  define for season
#define SEASON_SUMMER   0
#define SEASON_WINTER   1

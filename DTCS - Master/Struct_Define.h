#pragma once

#include <QDateTime>
#include <string>
using namespace std;

//  -------------------------------------------------------
//  struct  :   Info_Slave
//  usage   :   record the slave info
//  notes   :   none
//  -------------------------------------------------------
struct Info_Slave {
    int     m_id;
    int     m_wind_speed;
    int     m_temp_target;
    int     m_temp_now;
    double  m_energy;
    double  m_amount;
};

//  -------------------------------------------------------
//  struct  :   Slave_req
//  usage   :   record the request info
//  notes   :   none
//  -------------------------------------------------------
struct Slave_req {
    int m_id;
    int m_target_wind;
    int m_target_temp;
};

//  -------------------------------------------------------
//  struct  :   Log_record
//  usage   :   record the log info
//  notes   :   none
//  -------------------------------------------------------
struct  Log_record{
    int         slave_id;
    int         speed;
    int         speed_pre;
    int         target_temp;
    int         target_temp_pre;
    int         cur_temp;
    QDateTime   res_time;
    string      date;
};

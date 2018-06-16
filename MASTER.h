#pragma once

#include <string>
#include <vector>
#include "DB_ACCESS.h"
#include "Struct_Define.h"
#include "Report.h"
using namespace std;


//  -------------------------------------------------------
//  class   :   MASTER
//  usage   :   define all the master need
//  notes   :   none
//  -------------------------------------------------------
class MASTER {
public:
    MASTER();
    ~MASTER();

    bool f_set_switch_on();
    bool f_set_switch_off();
    bool f_set_mode(int const target_mode);
    bool f_set_frequent_ms(int const ms);
    bool f_request_handle();
    bool f_update_slave_status();
    bool f_user_in(int const roomID, string const user_ID);
    bool f_user_out(int const roomID);
    bool f_money_calculate(double const delta_ms_time);
    bool f_report();

    int f_get_switch();
    int f_get_mode();
    int f_get_frequent();

    R_Month                 Report;
    vector<Info_Slave>      m_miniDB;           //  mini database to store the info now

private:
    MASTER(MASTER &object);

    string                  m_Admin_Key;        //  key for admin to login maybe no use
    int                     m_switch;           //  switch: on or off
    int                     m_mode;             //  master mode
    int                     m_frequent_ms;      //  update frequent - ms per update
};

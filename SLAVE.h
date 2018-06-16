#pragma once

#include "Public_Define.h"
#include "Struct_Define.h"
#include "DB_ACCESS.h"

//  the only reference of the DB_ACCESS
extern DB_ACCESS &db_access;

//  -------------------------------------------------------
//  class   :   SLAVE
//  usage   :   define all the slave need
//  notes   :   none
//  -------------------------------------------------------
class SLAVE {
public:
    SLAVE(int const roomID);
    ~SLAVE();

    bool f_Login(string const ID);
    bool f_switch_on();
    bool f_switch_off();
    bool f_status_update();
    bool f_check_and_auto_adjust();
    bool f_tempnow_progress(int const delta_ms);
    bool f_adjust_temp(const int t_temp);
    bool f_adjust_wind(const int t_wind);

    int     f_get_roomID();
    string  f_getUserID();
    int     f_get_wind();
    int     f_get_switch();
    int     f_get_temp_target();
    double  f_get_temp_now();


private:
    SLAVE();
    SLAVE(SLAVE &object);

    bool    f_request(int const wind, int const temp);

    bool    m_auto_adjust;
    bool    m_Login_success;
    int     m_Wind_remember;    // remember the wind last shutdown, use for next startup wind set

    int     m_roomID;
    string  m_UserID;           // set with login

    int     m_switch;
    int     m_Wind;
    int     m_Temp_Target;
    double  m_Temp_Now;

};

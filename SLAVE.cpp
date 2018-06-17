#include "SLAVE.h"

SLAVE::SLAVE() {
    qDebug() << "Class SLAVE's default constructor isn't allowed to use!\n";
    if (DEBUG_ALLOW_THROW)
        throw "Class SLAVE's default constructor isn't allowed to use!\n";
    else
        assert(false);
}

SLAVE::SLAVE(int const roomID) {
    m_roomID = roomID;
    m_Wind = WIND_CLOSE;
    m_Wind_remember = WIND_CLOSE;
    m_switch = SWITCH_OFF;
    if(g_season ==SEASON_SUMMER)
        m_Temp_Now = TEMP_SUMMER_DEFAULT;
    else
        m_Temp_Now = TEMP_WINTER_DEFAULT;
    m_Temp_Target = 25;
    m_Login_success = false;
    m_auto_adjust = false;

    Info_Slave i = db_access.f_slave_init(roomID);

    if(i.m_id == 123){
        m_Wind = i.m_wind_speed;
        m_Temp_Now = i.m_temp_now;
        m_Temp_Target = i.m_temp_target;
    }
}

SLAVE::SLAVE(SLAVE &object) {
    qDebug() << "Copy of class SLAVE isn't allowed!\n";
    if(DEBUG_ALLOW_THROW)
        throw "Copy of class SLAVE isn't allowed!\n";
    else
        assert(false);
}

SLAVE::~SLAVE() {
    // nothing
}

bool SLAVE::f_Login(const string ID) {
    if(db_access.f_slave_login(m_roomID, ID)){
        m_Login_success = true;

        m_UserID = ID;
        return true;
    }
    else{
        return false;
    }
}

bool SLAVE::f_switch_on() {
    if(!m_Login_success)
        return false;


    if (WIND_CLOSE != m_Wind_remember){
        if(f_request(m_Wind_remember, m_Temp_Target)){
            //m_switch = SWITCH_ON;
            return true;
        }
        else
            return false;
    }
    else{
        //m_switch = SWITCH_ON;
        return true;
    }
}

bool SLAVE::f_switch_off() {
    if(!m_Login_success)
        return false;

    if(f_request(WIND_CLOSE, m_Temp_Target)){
        m_Wind_remember = m_Wind;
        //m_switch = SWITCH_OFF;
        return true;
    }
    else{
        return false;
    }

}

bool SLAVE::f_status_update() {
    if(!m_Login_success)
        return false;

    try{
        Slave_req r = db_access.f_slave_status_update(m_roomID, m_Temp_Now);

        m_Wind = r.m_target_wind;
        m_Temp_Target = r.m_target_temp;

        if(WIND_CLOSE ==  m_Wind)
            m_switch = SWITCH_OFF;
        else
            m_switch = SWITCH_ON;

        return true;
    }
    catch(...){
        return false;
    }
}

bool SLAVE::f_check_and_auto_adjust() {
    if(!m_Login_success)
        return false;

    double delta = fabs(double(m_Temp_Target) - m_Temp_Now);

    if(delta < 0.1){
        m_auto_adjust = true;
        return f_switch_off();
    }
    else if (delta > 1.0 && m_auto_adjust){
        m_auto_adjust = false;
        return f_switch_on();
    }
    return true;
}

bool SLAVE::f_tempnow_progress(const int delta_ms) {
    if(!m_Login_success)
        return false;

    double p_nature;
    double p_wind;
    if(PROGRESS_MIN <m_Temp_Now && m_Temp_Now < PROGRESS_MAX){
        if(SEASON_SUMMER == g_season)
            p_nature = PROGRESS_NATURE_SUMMER;
        else
            p_nature = PROGRESS_NATURE_WINTER;

        if(m_Temp_Target<=25)
            p_wind = -1;
        else
            p_wind = 1;

        switch (m_Wind) {
        case WIND_CLOSE:
            m_Temp_Now = m_Temp_Now + p_nature * delta_ms;
            break;
        case WIND_LOW:
            m_Temp_Now = m_Temp_Now + p_wind * delta_ms * PROGRESS_WIND_1;
            break;
        case WIND_MEDIUM:
            m_Temp_Now = m_Temp_Now + p_wind * delta_ms * PROGRESS_WIND_2;
            break;
        case WIND_HIGH:
            m_Temp_Now = m_Temp_Now + p_wind * delta_ms * PROGRESS_WIND_3;
            break;
        default:
            break;
        }

    }

    return true;
}

bool SLAVE::f_adjust_temp(const int t_temp) {
    if(!m_Login_success)
        return false;

    return f_request(m_Wind, t_temp);
}

bool SLAVE::f_adjust_wind(const int t_wind) {
    if(!m_Login_success)
        return false;

    return f_request(t_wind, m_Temp_Target);

}

int SLAVE::f_get_roomID() {
    return m_roomID;
}

string SLAVE::f_getUserID() {
    return m_UserID;
}

int SLAVE::f_get_wind() {
    return m_Wind;
}

int SLAVE::f_get_switch() {
    return m_switch;
}

int SLAVE::f_get_temp_target() {
    return m_Temp_Target;
}

double SLAVE::f_get_temp_now() {
    return m_Temp_Now;
}

bool SLAVE::f_request(const int wind, const int temp) {
    if(!m_Login_success)
        return false;

    Slave_req r;
    r.m_id = m_roomID;
    r.m_target_temp = temp;
    r.m_target_wind = wind;

    if(db_access.f_slave_request(r))
        return true;
    else
        return false;
}

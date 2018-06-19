#include <algorithm>
#include "MASTER.h"


MASTER::MASTER() {
    m_Admin_Key         = ADMIN_KEY;
    m_switch            = SWITCH_OFF;
    m_mode              = MODE_DEFAULT;
    m_frequent_ms       = FREQUENT_MASTER_DEFAULT;

    vector<Info_Slave> v = db_access.f_master_init();

    for(int i = 0; i < v.size(); i++)
        m_miniDB.push_back(v[i]);

}

MASTER::MASTER(MASTER &object) {
    qDebug() << "Copy of Class MASTER is not allowed!\n";

    if(DEBUG_ALLOW_THROW)
        throw "Copy of Class MASTER is not allowed!\n";
    else
        assert(false);
}

MASTER::~MASTER() {
    //  fisrt judge the switch
    if(SWITCH_ON == m_switch)
        f_set_switch_off();

    m_miniDB.clear();
}

bool MASTER::f_set_switch_on() {
    if(SWITCH_ON == m_switch)
        return true;

    m_switch = SWITCH_ON;

    if(db_access.f_master_switch_on())
        return true;
    else
        return false;
}

bool MASTER::f_set_switch_off() {
    if(SWITCH_OFF == m_switch)
        return true;

    m_switch = SWITCH_OFF;

    if(db_access.f_master_switch_off()){
        for(int i = 0; i < m_miniDB.size(); i++)
            m_miniDB[i].m_wind_speed = 0;

        return true;
    }
    else
        return false;
}

bool MASTER::f_set_mode(const int target_mode) {
    if(target_mode == m_mode)
        return true;

    try{
        vector<int>v = db_access.f_master_mode_change(target_mode);

        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < m_miniDB.size(); j++)
                if(m_miniDB[j].m_id == v[i]){
                    if(MODE_COLD == m_mode)
                        m_miniDB[j].m_temp_target = TEMP_COLD_DEFAULT;
                    else
                        m_miniDB[j].m_temp_target = TEMP_HOT_DEFAULT;

                    break;
                }
        }

        m_mode = target_mode;
        return true;
    }
    catch(...){
        return false;
    }
}

bool MASTER::f_set_frequent_ms(const int ms) {
    return m_frequent_ms = ms;
}

bool MASTER::f_request_handle() {
    try{
        vector<Slave_req> v = db_access.f_master_request_handle(m_mode);

        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < m_miniDB.size(); j++)
                if(m_miniDB[j].m_id == v[i].m_id){
                    m_miniDB[j].m_temp_target = v[i].m_target_temp;
                    m_miniDB[j].m_wind_speed = v[i].m_target_wind;

                    break;
                }
        }
        return true;
    }
    catch(...){
        return false;
    }
}

bool MASTER::f_update_slave_status() {
    try{
        vector< pair<int, int> > v = db_access.f_master_update_status(m_miniDB);

        for(int i = 0; i<v.size(); i++){
            for(int j = 0; j<m_miniDB.size(); j++){
                if (m_miniDB[j].m_id == v[i].first){
                    m_miniDB[j].m_temp_now = v[i].second;
                    break;
                }
            }
        }

        return true;
    }
    catch(...){
        return false;
    }
}

bool MASTER::f_user_in(int const roomID, const string user_ID) {
    if(db_access.f_master_user_in(roomID, user_ID, m_mode)){
        Info_Slave i;
        i.m_id = roomID;
        i.m_wind_speed = 0;
        if(MODE_COLD == m_mode)
            i.m_temp_target = TEMP_COLD_DEFAULT;
        else
            i.m_temp_target = TEMP_HOT_DEFAULT;
        i.m_temp_now = 0;
        i.m_energy = 0.0;
        i.m_amount = 0.0;

        m_miniDB.push_back(i);

        return true;
    }
    else
        return false;
}

bool MASTER::f_user_out(const int roomID) {
    if(db_access.f_master_user_out(roomID)){
        vector<Info_Slave>::iterator it;
        for(it = m_miniDB.begin(); it!=m_miniDB.end(); it++){
            if(it->m_id == roomID){
                m_miniDB.erase(it);
                break;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool MASTER::f_money_calculate(const double delta_ms_time) {
    for(int i = 0; i<m_miniDB.size(); i++){
        switch (m_miniDB[i].m_wind_speed) {
        case WIND_LOW:
            m_miniDB[i].m_energy = m_miniDB[i].m_energy + delta_ms_time * ENERGY_WIND_LOW;
            m_miniDB[i].m_amount = m_miniDB[i].m_energy * ENERGY_AMOUNT_RATE;
            break;
        case WIND_MEDIUM:
            m_miniDB[i].m_energy = m_miniDB[i].m_energy + delta_ms_time * ENERGY_WIND_MEDIUM;
            m_miniDB[i].m_amount = m_miniDB[i].m_energy * ENERGY_AMOUNT_RATE;
            break;
        case WIND_HIGH:
            m_miniDB[i].m_energy = m_miniDB[i].m_energy + delta_ms_time * ENERGY_WIND_HIGH;
            m_miniDB[i].m_amount = m_miniDB[i].m_energy * ENERGY_AMOUNT_RATE;
            break;
        default:
            break;
        }
    }
    return true;
}

bool MASTER::f_report() {
    m_Report.record_clear();

    return db_access.f_master_report(m_Report);
}

int MASTER::f_get_switch() {
    return m_switch;
}

int MASTER::f_get_mode() {
    return m_mode;
}

int MASTER::f_get_frequent() {
    return m_frequent_ms;
}

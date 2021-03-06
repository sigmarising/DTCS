﻿#include "DB_ACCESS.h"
#include "Report.h"

bool compare_log_record(const Log_record &x, const Log_record &y){
    if(x.date == y.date){
        if(x.slave_id == y.slave_id){
            return x.res_time < y.res_time;
        }
        else{
            return x.slave_id < y.slave_id;
        }
    }
    else{
        return x.date < y.date;
    }
}


DB_ACCESS &DB_ACCESS::get_Instance() {
    static DB_ACCESS _db_access_instance;
    return _db_access_instance;
}

vector<Info_Slave> DB_ACCESS::f_master_init() {
    vector<Info_Slave> v;

    QSqlQuery query(db);
    if(!query.exec("SELECT * FROM status")){
        qDebug() << query.lastError();
        if(DEBUG_ALLOW_THROW){
            throw query.lastError();
            return vector<Info_Slave>();
        }
        else
            assert(false);
    }
    while(query.next()){
        Info_Slave i;
        i.m_id = query.value(0).toInt();
        i.m_temp_target = query.value(2).toInt();
        i.m_temp_now = query.value(3).toInt();
        i.m_wind_speed = query.value(4).toInt();
        i.m_energy = query.value(5).toDouble();
        i.m_amount = query.value(6).toDouble();

        v.push_back(i);
    }

    return v;
}

bool DB_ACCESS::f_master_switch_on() {

    QSqlQuery query(db);
    bool flag = query.exec("DELETE FROM request");

    query.finish();

    if(flag)
        return true;
    else{
        qDebug() << query.lastError() << endl;

        if(DEBUG_ALLOW_THROW)
            throw query.lastError();
        else
            assert(false);

        return false;
    }
}

bool DB_ACCESS::f_master_switch_off() {

    //db.transaction();

    QSqlQuery query1(db);
    QSqlQuery query2(db);
    query1.exec("SELECT * FROM status");
    query2.prepare(
                "INSERT INTO log(card_id, slave_id, speed, target_temp, cur_temp)"
                "VALUES(:card_id, :slave_id, :speed, :target_temp, :cur_temp)"
                );
    while (query1.next()) {
        if(0 != query1.value(4).toInt()){
            query2.bindValue(":card_id", query1.value(1).toString());
            query2.bindValue(":slave_id", query1.value(0).toString());
            query2.bindValue(":speed", 0);
            query2.bindValue(":target_temp", query1.value(2).toInt());
            query2.bindValue(":cur_temp", query1.value(3).toInt());
            query2.exec();
        }
    }
    if ( !query1.exec("UPDATE status SET speed = 0 WHERE speed > 0")){
        qDebug() << query1.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return false;
        }
        else
            assert(false);
    }
    if ( !query1.exec("DELETE FROM request")){
        qDebug() << query1.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return false;
        }
        else
            assert(false);
    }
    query1.finish();
    query2.finish();

    //    bool flag = db.commit();
    return true;
}

vector<int> DB_ACCESS::f_master_mode_change(int master_mode) {
    vector<int> v;

    //db.transaction();

    QSqlQuery query1(db);
    QSqlQuery query2(db);
    QSqlQuery query3(db);
    if(!query1.exec("SELECT * FROM status")){
        qDebug() << query1.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return vector<int>();
        }
        else
            assert(false);
    }
    query2.prepare(
                "INSERT INTO log(card_id, slave_id, speed, target_temp, cur_temp)"
                "VALUES(:card_id, :slave_id, :speed, :target_temp, :cur_temp)"
                );
    while(query1.next()){
        int temp = query1.value(2).toInt();
        if(MODE_COLD == master_mode){
            if(!( TEMP_COLD_MIN <= temp && temp <= TEMP_COLD_MAX)){
                query2.bindValue(":card_id", query1.value(1).toString());
                query2.bindValue(":slave_id", query1.value(0).toString());
                query2.bindValue(":speed", query1.value(4).toInt());
                query2.bindValue(":target_temp", TEMP_COLD_DEFAULT);
                query2.bindValue(":cur_temp", query1.value(3).toInt());
                if(!query2.exec()){
                    qDebug() << query2.lastError() << endl;
                    if(DEBUG_ALLOW_THROW){
                        throw db.lastError();
                        return vector<int>();
                    }
                    else
                        assert(false);
                }

                if(!query3.exec("UPDATE status SET target_temp = "
                                + QString::number(TEMP_COLD_DEFAULT)
                                + " WHERE `id` = "
                                + query1.value(0).toString())){
                    qDebug() << query3.lastError() << endl;
                    if(DEBUG_ALLOW_THROW){
                        throw db.lastError();
                        return vector<int>();
                    }
                    else
                        assert(false);
                }

                v.push_back(query1.value(0).toInt());
            }
        }
        else if(MODE_HOT == master_mode){
            if(!( TEMP_HOT_MIN <= temp && temp <= TEMP_HOT_MAX)){
                query2.bindValue(":card_id", query1.value(1).toString());
                query2.bindValue(":slave_id", query1.value(0).toString());
                query2.bindValue(":speed", query1.value(4).toInt());
                query2.bindValue(":target_temp", TEMP_HOT_DEFAULT);
                query2.bindValue(":cur_temp", query1.value(3).toInt());
                if(!query2.exec()){
                    qDebug() << query2.lastError() << endl;
                    if(DEBUG_ALLOW_THROW){
                        throw db.lastError();
                        return vector<int>();
                    }
                    else
                        assert(false);
                }

                if(!query3.exec("UPDATE status SET target_temp = "
                                + QString::number(TEMP_HOT_DEFAULT)
                                + " WHERE `id` = "
                                + query1.value(0).toString())){
                    qDebug() << query3.lastError() << endl;
                    if(DEBUG_ALLOW_THROW){
                        throw db.lastError();
                        return vector<int>();
                    }
                    else
                        assert(false);
                }

                v.push_back(query1.value(0).toInt());
            }
        }
    }

    query1.finish();
    query2.finish();
    query3.finish();

    //    bool flag = db.commit();
    return v;
}

vector<Slave_req> DB_ACCESS::f_master_request_handle(int master_mode) {
    vector<Slave_req> v;

    //db.transaction();

    QSqlQuery query1_1(db);
    QSqlQuery query1_2(db);
    QSqlQuery query2(db);
    QSqlQuery query3(db);
    if(!query1_1.exec("SELECT * FROM request LIMIT 3")){
        qDebug() << query1_1.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return vector<Slave_req>();
        }
        else
            assert(false);
    }
    query2.prepare(
                "INSERT INTO log(card_id, slave_id, speed, target_temp, cur_temp, req_time)"
                "VALUES(:card_id, :slave_id, :speed, :target_temp, :cur_temp, :req_time)"
                );
    while(query1_1.next()){
        if(!query1_2.exec("SELECT * FROM status WHERE `id` = " + query1_1.value(1).toString() )){
            qDebug() << query1_2.lastError() << endl;
            if(DEBUG_ALLOW_THROW){
                throw db.lastError();
                return vector<Slave_req>();
            }
            else
                assert(false);
        }

        query1_2.next();
        int speed_set = query1_1.value(2).toInt();
        int temp_set = query1_1.value(3).toInt();

        if(MODE_COLD == master_mode){
            if(temp_set > TEMP_COLD_MAX)
                temp_set = TEMP_COLD_MAX;
            else if(temp_set < TEMP_COLD_MIN)
                temp_set = TEMP_COLD_MIN;

            if(temp_set > query1_2.value(3).toInt())
                speed_set = 0;
        }
        else if(MODE_HOT == master_mode){
            if(temp_set > TEMP_HOT_MAX)
                temp_set = TEMP_HOT_MAX;
            else if(temp_set < TEMP_HOT_MIN)
                temp_set = TEMP_HOT_MIN;

            if(temp_set < query1_2.value(3).toInt())
                speed_set = 0;
        }

        query2.bindValue(":card_id", query1_2.value(1).toString());
        query2.bindValue(":slave_id", query1_2.value(0).toInt());
        query2.bindValue(":speed", speed_set);
        query2.bindValue(":target_temp", temp_set);
        query2.bindValue(":cur_temp", query1_2.value(3).toInt());
        query2.bindValue(":req_time", query1_1.value(4).toDateTime());
        if(!query2.exec()){
            qDebug() << query2.lastError() << endl;
            if(DEBUG_ALLOW_THROW){
                throw db.lastError();
                return vector<Slave_req>();
            }
            else
                assert(false);
        }

        if(!query3.exec("UPDATE status SET target_temp = "
                        + QString::number(temp_set)
                        + " , speed = "
                        + QString::number(speed_set)
                        + " WHERE `id` = "
                        + query1_1.value(1).toString())){
            qDebug() << query3.lastError() << endl;
            if(DEBUG_ALLOW_THROW){
                throw db.lastError();
                return vector<Slave_req>();
            }
            else
                assert(false);
        }

        if(!query3.exec("DELETE FROM request WHERE `id` = " + query1_1.value(0).toString())){
            qDebug() << query3.lastError() << endl;
            if(DEBUG_ALLOW_THROW){
                throw db.lastError();
                return vector<Slave_req>();
            }
            else
                assert(false);
        }

        Slave_req r;
        r.m_id = query1_1.value(1).toInt();
        r.m_target_temp = temp_set;
        r.m_target_wind = speed_set;
        v.push_back(r);
    }

    query1_1.finish();
    query1_2.finish();
    query2.finish();
    query3.finish();

    return v;

}

vector< pair<int, int> > DB_ACCESS::f_master_update_status(const vector<Info_Slave> info) {
    vector< pair<int, int> >  v;

    //db.transaction();

    QSqlQuery query1(db);
    for(int i = 0; i< info.size(); i++){
        QString t = "UPDATE status SET energy = "
                + QString::number(info[i].m_energy)
                + " , amount = "
                + QString::number(info[i].m_amount)
                + " WHERE id = "
                + QString::number(info[i].m_id);
        if(!query1.exec(t)){
            qDebug() << query1.lastError() << endl;
            if(DEBUG_ALLOW_THROW){
                throw db.lastError();
                return vector< pair<int,int> >();
            }
            else
                assert(false);
        }
    }
    if(!query1.exec("SELECT id, cur_temp FROM status")){
        qDebug() << query1.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return vector<pair<int,int> >();
        }
        else
            assert(false);
    }

    while(query1.next()){
        int id_i = query1.value(0).toInt();
        int temp = query1.value(1).toInt();

        v.push_back( pair<int, int>(id_i, temp) );
    }

    query1.finish();

    //    bool flag = db.commit();
    return v;

}

bool DB_ACCESS::f_master_user_in(int const roomID, const string userID, const int master_mode) {
    QSqlQuery query(db);
    QSqlQuery query_t(db);
    query_t.exec("SELECT * FROM status WHERE id = " + QString::number(roomID));

    if(query_t.next()){
        return false;
    }

    query.prepare(  "INSERT INTO status(id, card_id, target_temp)"
                    "VALUES(:id, :card_id, :target_temp)");
    query.bindValue(":id", roomID);
    query.bindValue(":card_id",  QString::fromStdString(userID));
    if(MODE_COLD == master_mode)
        query.bindValue(":target_temp", TEMP_COLD_DEFAULT);
    else
        query.bindValue(":target_temp", TEMP_HOT_DEFAULT);

    bool flag = query.exec();

    query.finish();

    if(flag){
        return true;
    }
    else{
        qDebug() << query.lastError() << endl;
        if(DEBUG_ALLOW_THROW)
            return false;

        else
            assert(false);
    }
}

bool DB_ACCESS::f_master_user_out(const int roomID) {

    //db.transaction();

    QSqlQuery query1(db);
    QSqlQuery query2(db);
    if(!query1.exec("SELECT * FROM status WHERE id = "
                    + QString::number(roomID))){
        qDebug() << query1.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return false;
        }
        else
            assert(false);
    }
    if(!query1.next())
        return false;

    query2.prepare(
                "INSERT INTO log(card_id, slave_id, speed, target_temp, cur_temp)"
                "VALUES(:card_id, :slave_id, :speed, :target_temp, :cur_temp)"
                );
    query2.bindValue(":card_id", query1.value(1).toString());
    query2.bindValue(":slave_id", query1.value(0).toString());
    query2.bindValue(":speed", 0);
    query2.bindValue(":target_temp", query1.value(2).toInt());
    query2.bindValue(":cur_temp", query1.value(3).toInt());
    if(!query2.exec()){
        qDebug() << query2.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return false;
        }
        else
            assert(false);
    }

    if(!query1.exec("DELETE FROM status WHERE id = "
                    + QString::number(roomID))){
        qDebug() << query1.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return false;
        }
        else
            assert(false);
    }

    query1.finish();
    query2.finish();

    return true;
}

bool DB_ACCESS::f_master_report(R_Month &Report) {
    vector<Log_record> v;

    //db.transaction();

    QSqlQuery query(db);
    if(!query.exec("SELECT * FROM log ORDER BY slave_id ASC, id ASC")){
        qDebug() << query.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return false;
        }
        else
            assert(false);
    }
    while(query.next()){
        Log_record r;
        r.slave_id      = query.value(2).toInt();
        r.speed         = query.value(3).toInt();
        if(v.size() == 0){
            r.speed_pre = 0;
            r.target_temp_pre = 0;
        }
        else{
            r.speed_pre = v[v.size()-1].speed;
            r.target_temp_pre = v[v.size()-1].target_temp;
        }
        r.target_temp   = query.value(4).toInt();
        r.cur_temp      = query.value(5).toInt();
        r.res_time      = query.value(7).toDateTime();
        r.date          = r.res_time.toString("yyyy/MM/dd").toStdString();

        v.push_back(r);
    }

    //    bool flag = db.commit();

    if(true){
        sort(v.begin(), v.end(), compare_log_record);

        int i1 = 0, i2 = 0, j1 = 0, j2 = 0;
        // i define for day and j define for room

        vector<R_Day> v_day;

        while(i1 != v.size()){// day
            while(i2 != v.size() && v[i1].date == v[i2].date ) i2++;

            QDateTime qd =  v[i1].res_time;
            qd.setTime(QTime());
            R_Day day(qd);

            while(j1 != i2){// room
                while(j2 != i2 && v[j1].slave_id == v[j2].slave_id ) j2++;


                R_Room room(v[j1].slave_id);

                int i;

                for( i = j1; i < j2; i++){// record

                    if(i==j1){
                        if(v[i].speed != 0){// need to add a record
                            QDateTime time_t = v[i].res_time; // clear time
                            time_t.setTime(QTime());
                            R_Record record(time_t, v[i].res_time, v[i].cur_temp, v[i].cur_temp, v[i].target_temp_pre, v[i].speed_pre);

                            room.record_push(record);
                        }
                    }
                    else{
                        R_Record record(v[i-1].res_time, v[i].res_time, v[i-1].cur_temp, v[i].cur_temp, v[i-1].target_temp, v[i-1].speed);

                        room.record_push(record);
                    }
                }
                i--;
                if(v[i].speed != 0){
                    QDateTime time_t = v[i].res_time;
                    time_t.setTime(QTime(23, 59, 59));
                    R_Record record(v[i].res_time, time_t, v[i].cur_temp, v[i].cur_temp, v[i].target_temp, v[i].speed);

                    room.record_push(record);
                }

                day.record_push(room);
                j1 = j2;
            }

            v_day.push_back(day);
            i1 = i2;
        }//


        int c = 0;
        int x, y;
        if(v_day.size() >= 30){
            x = v_day.size() - 30;
            y = v_day.size() - 1;
        }
        else{
            x = 0;
            y = v_day.size() - 1;
        }
        i1 = j1 = 0;

        QDateTime T1,T2;
        for(int i = x; i <= y; i++){
            c++;
            if(c == 1){
                T1 = v_day[i].get_Day();
                i1 = i;
            }
            else if(c == 7){
                T2 = v_day[i].get_Day();
                j1 = i;
                R_Week r(T1, T2);
                for(int k = i1; k <= j1; k++)
                    r.record_push(v_day[k]);
                Report.record_push(r);
                c = 0;
            }
            if(i == y){
                T2 = v_day[i].get_Day();
                j1 = i;
                R_Week r(T1, T2);
                for(int k = i1; k <= j1; k++)
                    r.record_push(v_day[k]);
                Report.record_push(r);
            }
        }
        return true;
    }
    else{
        return false;
    }
}

Info_Slave DB_ACCESS::f_slave_init(const int roomID)
{
    Info_Slave i;

    i.m_id = 0;

    QSqlQuery query(db);
    if(!query.exec("SELECT * FROM status WHERE `id` = " + QString::number(roomID))){
        qDebug() << query.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw query.lastError();
            return i;
        }
        else
            assert(false);
    }

    if(!query.next()){
        i.m_id = -1;
        return i;
    }
    i.m_id = -123;

    i.m_wind_speed = query.value(4).toInt();
    i.m_temp_now = query.value(3).toInt();
    i.m_temp_target = query.value(2).toInt();
    i.m_energy = query.value(5).toDouble();
    i.m_amount = query.value(6).toDouble();

    return i;
}

bool DB_ACCESS::f_slave_login(const int roomID, const string userID) {
    QSqlQuery query(db);
    bool flag = query.exec("SELECT card_id FROM status WHERE id = " + QString::number(roomID));

    if(flag){
        query.next();
        if(QString::fromStdString(userID) == query.value(0).toString())
            return true;
        else
            return false;
    }
    else{
        qDebug() << query.lastError() << endl;
        if(DEBUG_ALLOW_THROW)
            throw query.lastError();
        else
            assert(false);
    }
}

Info_Slave DB_ACCESS::f_slave_status_update(const int roomID, const double temp_now) {
    //db.transaction();

    QSqlQuery query1(db);
    if(!query1.exec("UPDATE status SET cur_temp = "
                    + QString::number(round(temp_now))
                    + " WHERE id = "
                    + QString::number(roomID)
                    )){
        qDebug() << query1.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return Info_Slave();
        }
        else
            assert(false);
    }
    if(!query1.exec("SELECT * FROM status WHERE `id` = "
                    + QString::number(roomID))){
        qDebug() << query1.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
            return Info_Slave();
        }
        else
            assert(false);
    }
    query1.next();

    Info_Slave info;
    info.m_id = roomID;
    info.m_temp_target = query1.value(2).toInt();
    info.m_wind_speed = query1.value(4).toInt();
    info.m_amount = query1.value(6).toDouble();
    info.m_energy = query1.value(5).toDouble();


    //    bool flag = db.commit();
    return info;
}

bool DB_ACCESS::f_slave_request(const Slave_req req) {
    QSqlQuery query(db);

    query.prepare(
                "INSERT INTO request(slave_id, speed, temp)"
                "VALUES(:slave_id, :speed, :temp)");
    query.bindValue(":slave_id", req.m_id);
    query.bindValue(":speed", req.m_target_wind);
    query.bindValue(":temp", req.m_target_temp);
    bool flag = query.exec();

    if(flag)
        return true;
    else{
        qDebug() << query.lastError() << endl;
        return false;
    }
}

DB_ACCESS::DB_ACCESS() {
    db = QSqlDatabase::addDatabase(DB_CONNECT_TYPE, DB_CONNECT_NAME);
    db.setHostName(DB_HOST_NAME);
    db.setUserName(DB_USER_NAME);
    db.setPassword(DB_PASSWORD);
    db.setDatabaseName(DB_DATABASE_NAME);

    if(!db.open()){
        qDebug() << db.lastError() << endl;
        if(DEBUG_ALLOW_THROW){
            throw db.lastError();
        }
        else
            assert(false);
    }
}

DB_ACCESS::DB_ACCESS(DB_ACCESS &object){
    // this is not allowed
    qDebug() << "Error! The use of copy constructor from a singleton!" << endl;
    if(DEBUG_ALLOW_THROW)
        throw "Error! The use of copy constructor from a singleton!\n";
    else
        assert(false);
}

DB_ACCESS::~DB_ACCESS() {
    // first close database
    db.close();
    // second remove connect
    QSqlDatabase::removeDatabase(DB_CONNECT_NAME);
}


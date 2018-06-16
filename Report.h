#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <QDateTime>
#include <QDebug>
#include "Public_Define.h"
using namespace std;


class R_Record{
public:
    R_Record(QDateTime time1, QDateTime time2, int temp1, int temp2, int temp_tar, int wind);
    ~R_Record();

    QDateTime   get_Time_Start();
    QDateTime   get_Time_End();
    int         get_Temp_Start();
    int         get_Temp_End();
    int         get_Temp_Target();
    int         get_Wind();
    double      get_Energy();
    double      get_Amount();

private:
    R_Record();
    R_Record(R_Record &R);

    QDateTime   Time_Start;
    QDateTime   Time_End;
    int         Temp_Start;
    int         Temp_End;
    int         Temp_Target;
    int         Wind;
    double      Energy;
    double      Amount;
};


class R_Room {
public:
    R_Room(int roomid);
    ~R_Room();

    void    record_push(R_Record &r);
    int     get_RoomID();
    int     get_SwitchTimes();
    double  get_Energy();
    double  get_Amount();

    // don't direct push
    vector<R_Record> v_Record;
private:
    R_Room();
    R_Room(R_Room &R);

    int     RoomID;
    int     Switch_Times;
    double  Energy;
    double  Amount;
};


class R_Day{
public:
    R_Day(QDateTime day);
    ~R_Day();

    void        record_push(R_Room &r);
    QDateTime   get_Day();
    double      get_Energy();
    double      get_Amount();

    // don't direct push
    vector<R_Room> v_Room;
private:
    R_Day();
    R_Day(R_Day &R);

    QDateTime   Day;
    double      Energy;
    double      Amount;
};


class R_Week{
public:
    R_Week(QDateTime day1, QDateTime day2);
    ~R_Week();

    void        record_push(R_Day &r);
    QDateTime   get_Day_Start();
    QDateTime   get_Day_End();
    double      get_Energy();
    double      get_Amount();

    // don't direct push
    vector<R_Day> v_Day;
private:
    R_Week();
    R_Week(R_Week &R);

    QDateTime   Day_Start;
    QDateTime   Day_End;
    double      Energy;
    double      Amount;
};


class R_Month{
public:
    R_Month();
    ~R_Month();

    void        record_push(R_Week &r);
    double      get_Energy();
    double      get_Amount();

    // don't direct push
    vector<R_Week> v_Week;
private:
    R_Month(R_Month &R);

    double      Energy;
    double      Amount;
};


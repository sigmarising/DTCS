#include "Report.h"


R_Record::R_Record()
{
    qDebug() << "Don't use this" << endl;
    if(DEBUG_ALLOW_THROW)
        throw "Don't use this";
    else
        assert(false);
}


R_Record::R_Record(QDateTime time1, QDateTime time2, int temp1, int temp2, int temp_tar, int wind) {
    Time_Start  = time1;
    Time_End    = time2;
    Temp_Start  = temp1;
    Temp_End    = temp2;
    Temp_Target = temp_tar;
    Wind        = wind;

    Energy      = 0.0;
    Amount      = 0.0;

    double delta    = double(Time_Start.secsTo(Time_End) * 1000);
    switch (Wind) {
    case WIND_LOW:
        Energy = delta * ENERGY_WIND_LOW;
        Amount = Energy * ENERGY_AMOUNT_RATE;
        break;
    case WIND_MEDIUM:
        Energy = delta * ENERGY_WIND_MEDIUM;
        Amount = Energy * ENERGY_AMOUNT_RATE;
        break;
    case WIND_HIGH:
        Energy = delta * ENERGY_WIND_HIGH;
        Amount = Energy * ENERGY_AMOUNT_RATE;
        break;
    default:
        break;
    }
}

R_Record::~R_Record()
{
    // nothing
}

QDateTime R_Record::get_Time_Start()
{
    return Time_Start;
}

QDateTime R_Record::get_Time_End()
{
    return Time_End;
}

int R_Record::get_Temp_Start()
{
    return Temp_Start;
}

int R_Record::get_Temp_End()
{
    return Temp_End;
}

int R_Record::get_Temp_Target()
{
    return Temp_Target;
}

int R_Record::get_Wind()
{
    return Wind;
}

double R_Record::get_Energy()
{
    return Energy;
}

double R_Record::get_Amount()
{
    return Amount;
}

R_Room::R_Room()
{
    qDebug() << "Don't use this" << endl;
    if(DEBUG_ALLOW_THROW)
        throw "Don't use this";
    else
        assert(false);
}


R_Room::R_Room(int roomid)
{
    RoomID          = roomid;
    Switch_Times    = 0;
    Energy          = 0.0;
    Amount          = 0.0;

    v_Record.clear();
}

R_Room::~R_Room()
{
    v_Record.clear();
}

void R_Room::record_push(R_Record &r)
{
    v_Record.push_back(r);

    if(0 == r.get_Wind())
        Switch_Times++;

    Energy += r.get_Energy();
    Amount += r.get_Amount();

}

int R_Room::get_RoomID()
{
    return RoomID;
}

int R_Room::get_SwitchTimes()
{
    return Switch_Times;
}

double R_Room::get_Energy()
{
    return Energy;
}

double R_Room::get_Amount()
{
    return Amount;
}

R_Day::R_Day()
{
    qDebug() << "Don't use this" << endl;
    if(DEBUG_ALLOW_THROW)
        throw "Don't use this";
    else
        assert(false);
}

R_Day::R_Day(QDateTime day)
{
    Day = day;
    Energy = 0;
    Amount = 0;

    v_Room.clear();
}

R_Day::~R_Day()
{
    v_Room.clear();
}

void R_Day::record_push(R_Room &r)
{
    v_Room.push_back(r);

    Energy += r.get_Energy();
    Amount += r.get_Amount();
}

QDateTime R_Day::get_Day()
{
    return Day;
}

double R_Day::get_Energy()
{
    return Energy;
}

double R_Day::get_Amount()
{
    return Amount;
}

R_Week::R_Week()
{
    qDebug() << "Don't use this" << endl;
    if(DEBUG_ALLOW_THROW)
        throw "Don't use this";
    else
        assert(false);
}


R_Week::R_Week(QDateTime day1, QDateTime day2)
{
    Day_Start = day1;
    Day_End = day2;

    Energy = 0;
    Amount = 0;

    v_Day.clear();
}

R_Week::~R_Week()
{
    v_Day.clear();
}

void R_Week::record_push(R_Day &r)
{
    v_Day.push_back(r);

    Energy += r.get_Energy();
    Amount += r.get_Amount();
}

QDateTime R_Week::get_Day_Start()
{
    return Day_Start;
}

QDateTime R_Week::get_Day_End()
{
    return Day_End;
}

double R_Week::get_Energy()
{
    return Energy;
}

double R_Week::get_Amount()
{
    return Amount;
}

R_Month::R_Month()
{
    // use this
    Energy = 0;
    Amount = 0;
}


R_Month::~R_Month()
{
    v_Week.clear();
}

void R_Month::record_push(R_Week &r)
{
    v_Week.push_back(r);

    Energy += r.get_Energy();
    Amount += r.get_Amount();
}

void R_Month::record_clear()
{
    v_Week.clear();
}

double R_Month::get_Energy()
{
    return Energy;
}

double R_Month::get_Amount()
{
    return Amount;
}

#pragma once

#include <QtSql>
#include <QDebug>
#include <cassert>
#include "Public_Define.h"
#include "Struct_Define.h"
#include "Report.h"
using namespace std;


//  -------------------------------------------------------
//  class   :   DB_ACCESS
//  usage   :   provide API for applications level
//              to operate the database
//  notes   :   use singleton to define this class
//              hungry mode
//  -------------------------------------------------------
class DB_ACCESS {
public:
    //  get the only instance to a reference_variable
    static DB_ACCESS &get_Instance();


    //  func: f_master_clear_request
    //      master use
    //      do the thing switch on
    //  return:
    //      exec ok or not
    bool f_master_switch_on();
    //  func: f_master_switch_off
    //      master use
    //      set speed to 0
    //      add log
    //      clear request
    //  return:
    //      commit ok or not
    bool f_master_switch_off();
    //  func: f_master_mode_change
    //      master use
    //      check status's no correct temp and change it
    //      also add change to log
    //  parameter:
    //      master_mode: current master mode
    //  return:
    //      a vector of slave id which need to set default temp
    vector<int> f_master_mode_change(int master_mode);
    //  func: f_master_request_handle
    //      master use
    //      check request and handle
    //      delete request
    //      add log
    //      update status
    //  parameter:
    //      master_mode
    //  return:
    //      all slave req after modify
    vector<Slave_req> f_master_request_handle(int master_mode);
    //  func: f_master_update_status
    //      master use
    //      update the status's enegry and amount
    //      get the temp_now
    //  parameter:
    //      m_miniDB from class Master
    //  return:
    //      vactor - pair<id, temp_now>
    vector< pair<int, int> > f_master_update_status(vector<Info_Slave> const info);
    //  func: f_master_user_in
    //      master use
    //      create a room in status
    //  parameter:
    //      roomID userID masterMODE
    //  return:
    //      exec ok or not
    bool f_master_user_in(int const roomID, string const userID, int const master_mode);
    //  func: f_master_user_out
    //      master use
    //      add a speed 0 log
    //      delete status and request (cascade)
    //  parameter:
    //      roomID
    //  return:
    //      ok or not
    bool f_master_user_out(int const roomID);
    //  func: f_master_report
    //      master use
    //      generate report
    //  parameter:
    //      A reference for a R_Month
    //  return:
    //      ok or not
    bool f_master_report(R_Month &Report);


    //  func: f_slave_login
    //      slave use for login
    //  parameter:
    //      user id
    //  return:
    //      login ok or not
    bool f_slave_login(int const roomID, string const userID);
    //  func: f_slave_status_update
    //      slave use for update all status and modify the temp_now
    //  parameter:
    //      roomid temp_now
    //  return:
    //      salve status
    Slave_req f_slave_status_update(int const roomID, double const temp_now);
    //  func: f_slave_request
    //      slave use for request
    //  parameter:
    //      request info
    //  return:
    //      ok or not
    bool f_slave_request(Slave_req const req);

private:
    //  private the constructors to ensure that:
    //      there is only one instance avaliable


    //  constructor_default
    //      use to connect the database
    DB_ACCESS();
    // constructor_copy
    //      nothing to do
    DB_ACCESS(DB_ACCESS &object);
    // destructor
    //      close the connect with database
    ~DB_ACCESS();


    // Qt Database
    QSqlDatabase db;
};

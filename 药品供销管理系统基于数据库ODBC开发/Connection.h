/*
* 数据库连接模块
* @author：LPH
* Date：2021-9-15
*/
#pragma once
#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>

/*引入C语言ODBC的头文件*/
extern "C"
{
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdlib.h>
#include <sal.h>
}

namespace DataBaseConnect
{
		  class Connection
		  {
		  public:
					Connection() = default;
					Connection(std::string m_szdsninfo, std::string m_uid, std::string m_szauthstr);
					~Connection();
		  public:
					void DataBaseInit() = delete;		  //已经废弃的数据库的初始化函数
		  protected:
					/*保护成员变量区*/
					HDBC* hdbc;
		  private:
					/*私有成员函数区*/
					RETCODE dataBaseOpenConnection();
					void dataBaseCloseConnection();
		  private:
					/*私有成员变量区*/
					HENV *henv;
					SQLCHAR* szdsninfo;			//连接名称
					SQLCHAR* uid;						//连接UID
					SQLCHAR* szauthstr;			//连接验证
		  };
}


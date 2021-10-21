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
#include<locale>
#include<regex>

/*引入C语言ODBC的头文件*/
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdlib.h>
#include <sal.h>
#pragma comment(lib,"odbc32.lib")
#pragma warning(disable:6386)

/*
*问题修复：SQLConnect函数数据库连接返回值=-2   -------  OK
*/
namespace DataBaseConnect
{
		  class Connection
		  {
		  public:
					Connection();
					~Connection();
		  public:
					void DataBaseInit() = delete;		  //已经废弃的数据库的初始化函数
		  protected:
					/*保护成员变量区*/
					HDBC* hdbc;
					bool ConnectionSatus = false;
		  private:
					/*私有成员函数区*/
					RETCODE dataBaseOpenConnection();
					void dataBaseCloseConnection();
		  private:
					/*私有成员变量区*/
					HENV *henv;
					SQLWCHAR* szdsninfo = nullptr;			//连接名称
					SQLWCHAR* uid = nullptr;						//连接UID
					SQLWCHAR* szauthstr = nullptr;			//连接验证
		  };
}
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

#pragma comment(lib,"odbc32.lib")

/*
*已知问题：SQLConnect函数数据库连接返回值=-2？
* 问题分析思路：
		  1、数据库ODBC的配置问题
		  2、程序的实现逻辑
* 
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
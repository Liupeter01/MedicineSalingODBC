/*
* 数据库连接模块
* @author：LPH
* Date：2021-9-15
*/
#pragma once
#include<iostream>
namespace DataBaseConnect
{
		  class Connection
		  {
		  public:
					Connection()
					{

					}
					~Connection()
					{

					}
		  public:
					void dataBaseOpenConnection();
					void dataBaseCloseConnection();
		  private:
		  };
}


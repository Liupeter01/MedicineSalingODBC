#pragma once
#include"Connection.h"
/*
* 数据库操作模块
* @author：LPH
* Date：2021-9-15
*/
class DataBaseOp :public DataBaseConnect::Connection
{
public:
		  DataBaseOp();
		  ~DataBaseOp();
private:
		  void sqlQueryInit();					  //SQL查询语句初始化函数
private:
		  HSTMT *stm1;					//连接句柄
		  std::vector<std::string> sqlQuery;			//SQL语句适用于多种查询情况
};


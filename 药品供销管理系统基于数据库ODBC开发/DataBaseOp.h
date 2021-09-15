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
		  DataBaseOp()
		  {
		  
		  }
		  ~DataBaseOp()
		  {

		  }
};


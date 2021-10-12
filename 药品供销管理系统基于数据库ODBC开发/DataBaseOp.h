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
		  void SQLInitQueryParttern();	//初始化SQL查询语句结构
		  void initMedcineBasicInfo();	//初始化药品的基本信息
		  void findMedcineBasicInfo();	//查询药品的基本信息
		  void statisticMedcineBasicInfo();		  //统计药品的基本信息

private:
		  HSTMT *stm1;					//连接句柄
		  SQLCHAR sqlQuery[1024] = { 0 };
		  SQLCHAR** sqlPatterns;				  //查询模式

private:
		  enum sqlquery {
					INIT_BASIC_INFO,	//录入药品基本信息
					MEDICINE_BUYING,	//药品基本信息的入库
					MEDICINE_SALING,	//药品基本信息的销售
					MODIFIY_BASIC_INFO,	//修改药品基本信息
					DISPLAY_ALL,	//输出全部药品的基本信息
					SEARCH_BASIC_INFO,	//查询基本的信息
					SEARCH_BUYING_INFO,//查询入库的信息
					SEARCH_SALING_INFO,//查询销售的信息
					STATISTICS_BASIC_INFO,	//统计基本的信息
					STATISTICS_BUYING_INFO,//统计入库的信息
					STATISTICS_SALING_INFO,//统计销售的信息
					OTHER	  //预留接口
		  };
};


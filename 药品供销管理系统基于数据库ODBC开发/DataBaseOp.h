#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
public:
		  void menu();
		  template<typename T>
		  void cleanMem(T* memzone, T data, int size);		//内存清空
		  template<typename T>
		  void eraseSpace(T* str);		//删除多余空格
private:
		  /*业务逻辑*/
		  int getInitQuerySize();
		  void sqlInitQueryParttern();	//初始化SQL查询语句结构
		  void initMedicineBasicInfo();	//初始化药品的基本信息
		  void initMedicinePurchase();	//初始化药品采购信息
		  void initMedicineSaling();	    //初始化药品销售信息

		  void displayAllBasicInfo();	    //输出全部药品基本信息
		  void findMedicineBasicInfo();	//查询药品的基本信息
		  void statisticMedicineBasicInfo();		  //统计药品的基本信息

private:
		  /*错误信息输出*/
		  void sqlErrorMsg();					  //错误信息输出函数

private:
		  HSTMT *stm1;					//连接句柄
		  SQLWCHAR sqlQuery[1024] = { 0 };
		  SQLWCHAR** sqlPatterns;				  //查询模式

private:
		  enum sqlquery {
					INIT_BASIC_INFO,	//录入药品基本信息
					MEDICINE_BUYING,	//药品基本信息的采购
					MEDICINE_SALING,	//药品基本信息的销售
					MODIFIY_BASIC_INFO,	//修改药品基本信息
					DISPLAY_ALL_BASIC_INFO,	//输出全部药品的基本信息
					SEARCH_BASIC_INFO,	//查询基本的信息
					SEARCH_BUYING_INFO,//查询入库的信息
					SEARCH_SALING_INFO,//查询销售的信息
					STATISTICS_BASIC_INFO,	//统计基本的信息
					STATISTICS_BUYING_INFO,//统计入库的信息
					STATISTICS_SALING_INFO,//统计销售的信息
					OTHER	  //预留接口
		  };
};


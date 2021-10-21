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
		  template<typename T> void cleanMem(T* memzone, T data, int size);		//内存清空
		  template<typename T> void eraseSpace(T* str);		//删除多余空格

private:/*STMT的分配与释放函数*/
		  void AllocateStmt();
		  void ReleaseStmt();

private:
		  /*业务逻辑*/
		  int getInitQuerySize();
		  void sqlInitQueryParttern();	//初始化SQL查询语句结构
		  void initMedicineBasicInfo();	//初始化药品的基本信息
		  void initMedicinePurchase();	//初始化药品采购信息
		  void initMedicineSaling();	    //初始化药品销售信息

		  void printBasicInfo();				  //输出全部基本信息子函数
		  void printPurchaseInfo();				  //输出全部采购信息子函数
		  void printSalingInfo();				  //输出全部销售信息子函数
		  void displayAllBasicInfo();	    //输出全部药品基本信息
		  bool findMedicineBasicInfo(const wchar_t* target, const wchar_t* Find);//查询药品的基本信息
		  bool findMedicinePurchaseInfo(const wchar_t*, const wchar_t*);	//查询药品的采购信息	  
		  bool findMedicineSalingInfo(const wchar_t*, const wchar_t*);		  //查询药品的销售信息	  
		  void statisticMedicineBasicInfo();		  //统计药品的基本信息

private:
		  /*函数专用SQL语句指针*/
		  SQLWCHAR* basicInfo;					  //printBasicInfo输出参数指针
		  //SQLWCHAR* printInfo;					  //printBasicInfo输出参数指针
		  //SQLWCHAR* printInfo;					  //printBasicInfo输出参数指针
		  const wchar_t* QueryBasicMedicineInfo[7]
		  {
					L"MedicineId = ",L"MedicineName = ",
					L"MedicineType = ",L"Manufacture = ",
					L"MedicinePrice = ",L"MedicineValidateDate = ",
					L"AdditionInfo = "
		  };

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
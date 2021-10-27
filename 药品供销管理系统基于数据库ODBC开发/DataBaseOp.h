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
		  void sqlErrorMsg();					  //错误信息输出函数

private:
		  void BasicDBExecute();				  //数据库基本信息操作工具
		  int getInitQuerySize();
		  void sqlInitQueryParttern();	//初始化SQL查询语句结构
		  void AllocateStmt();			//STMT的分配函数
		  void ReleaseStmt();			//STMT的释放函数
		  template<typename T>  void eraseSpace(T* str)	{[&]() {/*删除多余空格*/	
							  T* ptemp = str;
							  while (*ptemp++ != ' ');
							  *ptemp = ((!strcmp(typeid(T*).name(), "wchar_t*")) ? L'\0' : '\0');
		 };}
		  template<typename T>  void cleanMem(T* memzone, T data, int size){[&]() {		  /*内存清空函数*/
					for (int i = 0; i < size; ++i)		  *(memzone + i) = data;};
		  }

private:
		  /*业务逻辑*/
		  void initMedicineBasicInfo();	//初始化药品的基本信息
		  void initMedicinePurchase();	//初始化药品采购信息
		  void initMedicineSaling();	    //初始化药品销售信息

		  void printBasicInfo();				  //输出基本信息子函数
		  void printPurchaseInfo();				  //输出采购信息子函数
		  void printSalingInfo();				  //输出销售信息子函数
		  void displayAllBasicInfo();	    //输出全部药品基本信息
		  bool findMedicineBasicInfo(const wchar_t* target, const wchar_t* Find);//查询药品的基本信息
		  bool findMedicinePurchaseInfo(const wchar_t* target, const wchar_t* Find);	//查询药品的采购信息	  
		  bool findMedicineSalingInfo(const wchar_t* target, const wchar_t* Find);		  //查询药品的销售信息

		  bool modifyMedicineBasicInfo(const wchar_t* target, const wchar_t* expired, const wchar_t* uptodate);	  //修改药品的基本信息
		  bool modifyMedicinePurchaseInfo(const wchar_t* target);	  //修改采购信息(是否可以修改流水)	
		  bool modifyMedicineSalingInfo(const wchar_t* target);		  //修改销售信息(是否可以修改流水)

		  bool deleteMedicineBasicInfo(const wchar_t* target, const wchar_t* deleteitem); //删除药品的基本信息
		  bool deleteMedicinePurchaseInfo(const wchar_t* target, const wchar_t* deleteitem); //删除药品的采购信息(是否可以修改流水)	
		  bool deleteMedicineSalingInfo(const wchar_t* target, const wchar_t* deleteitem); //删除药品的销售信息(是否可以修改流水)	

		  void statisticMedicineBasicInfo();		  //统计药品的基本信息

private:
		  /*函数专用SQL语句指针*/
		  SQLWCHAR* BasicMedicineInfo;		//printBasicInfo输出参数指针
		  SQLWCHAR* PurchaseInfo;					  //printBuyingInfo输出参数指针
		  SQLWCHAR* SalingInfo;					  //printSalingInfo输出参数指针

		  const wchar_t* QueryBasicMedicineInfo[7]
		  {
					L"MedicineId = ",L"MedicineName = ",
					L"MedicineType = ",L"Manufacture = ",
					L"MedicinePrice = ",L"MedicineValidateDate = ",
					L"AdditionInfo = "
		  };
		  const wchar_t* QueryPurchaseMedicine[7]
		  {
					L"BuyingOrderNumber = ",L"MedicineId = ",L"MedicineName = ",
					L"TransActionAmmount = ",L"PriceInTotal = ",
					L"TransActionDate = ",L"OperatorName = "
		  };
		  const wchar_t* QuerySalingMedicine[8]
		  {
					L"SalingOrderNumber = ",L"MedicineId = ",L"MedicineName = ",
					L"MedicinePrice = ",L"TransActionAmmount = ",L"PriceInTotal = ",
					L"TransActionDate = ",L"BuyerName = "
		  };
private:
		  HSTMT *stm1;					//连接句柄
		  SQLWCHAR sqlQuery[1024] = { 0 };
		  SQLWCHAR** sqlPatterns;				  //查询模式

private:
		  enum sqlquery {
					/*增加信息  DBInsert.cpp*/
					INIT_BASIC_INFO,	//录入药品基本信息
					MEDICINE_BUYING,	//药品基本信息的采购
					MEDICINE_SALING,	//药品基本信息的销售

					/*修改信息*/
					MODIFIY_BASIC_INFO,	//修改WareBase中的基本信息
					MODIFIY_BUYING_INFO,	//修改入库的信息
					MODIFIY_SALING_INFO,	//修改销售的信息

					/*查询信息*/
					DISPLAY_ALL_BASIC_INFO,	//输出全部药品的基本信息
					SEARCH_BASIC_INFO,	//查询WareBase中的信息
					SEARCH_BUYING_INFO,//查询入库的信息
					SEARCH_SALING_INFO,//查询销售的信息

					/*删除信息*/
					DELETE_BASIC_INFO,		//删除WareBase中的信息
					DELETE_BUYING_INFO,//删除入库的信息
					DELETE_SALING_INFO,//删除销售的信息

					STATISTICS_BASIC_INFO,	//统计基本的信息
					STATISTICS_BUYING_INFO,//统计入库的信息
					STATISTICS_SALING_INFO,//统计销售的信息
					OTHER	  //预留接口
		  };
};
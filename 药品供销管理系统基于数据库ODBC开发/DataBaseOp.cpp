#include "DataBaseOp.h"

/*
* 内存清空函数
* @author：LPH
* Date：2021-10-14
*/
template<typename T>
void DataBaseOp::cleanMem(T* memzone, T data, int size)	//内存清空
{
		  for (int i = 0; i < size; ++i)
		  {
					*(memzone + i) = data;
		  }
}

/*
*删除多余空格
* @author：LPH
* Date：2021-10-14
*/
template<typename T>
void DataBaseOp::eraseSpace(T* str)				  //删除多余空格
{
		  T* ptemp = str;
		  while (*ptemp++ != ' ');
		  *ptemp = ((!strcmp(typeid(T*).name(), "wchar_t*")) ? L'\0' : '\0');
}

/*
* 动态获取枚举体内查询语句参数
* @author：LPH
* Date：2021-10-13
*/
int DataBaseOp::getInitQuerySize()
{
		  int querysize(0);
		  for (enum sqlquery temp = (enum DataBaseOp::sqlquery)sqlquery::INIT_BASIC_INFO;
					temp != sqlquery::OTHER; temp = (enum DataBaseOp::sqlquery)(temp + 1)){
					querysize++;
		  }
		  return querysize;
}

/*
* 初始化SQL查询语句结构
* @author：LPH
* Date：2021-10-12
*/
void DataBaseOp::sqlInitQueryParttern()
{
		  this->sqlPatterns = new SQLWCHAR * [this->getInitQuerySize()];			//动态分配查询语句的大小
		  for (int i = 0; i < this->getInitQuerySize(); ++i)
		  {
					(this->sqlPatterns)[i] = new SQLWCHAR[256]{ 0 };
		  }
		  //INIT_BASIC_INFO	录入药品基本信息
		  //MEDICINE_BUYING	药品基本信息的采购
		  //MEDICINE_SALING	药品基本信息的销售
		  //DISPLAY_ALL_BASIC_INFO				输出全部药品基本信息
		  //SEARCH_BASIC_INFO	查询基本的信息
		  wsprintf((this->sqlPatterns)[INIT_BASIC_INFO],L"INSERT INTO MedicineManagmentSys.dbo.MedicineWareBase values(?,?,?,?,?,?,?) ");	//7参数
		  wsprintf((this->sqlPatterns)[MEDICINE_BUYING], L"INSERT INTO MedicineManagmentSys.dbo.MedicineBuying values(?,?,?,?,?,?,?) ");	//7参数
		  wsprintf((this->sqlPatterns)[MEDICINE_SALING], L"INSERT INTO MedicineManagmentSys.dbo.MedicineSaling values(?,?,?,?,?,?,?,?) ");	//8参数
		  wsprintf((this->sqlPatterns)[DISPLAY_ALL_BASIC_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineWareBase");	
		  wsprintf((this->sqlPatterns)[SEARCH_BASIC_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineWareBase WHERE ");
}

/*
* SQL查询语句构造函数
* @author：LPH
* @descrition:
* Date：2021-9-16
* Date:   2021-10-12 增加数据库查询语句结构的初始化
*/
DataBaseOp::DataBaseOp()
{
		  this->sqlInitQueryParttern();
}

/*
* STMT分配函数
* @author：LPH
* Date：2021-10-21
*/
void DataBaseOp::AllocateStmt()
{
		  if (this->ConnectionSatus)
		  {
					this->stm1 = new HSTMT;
					SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//生成stmt
					try
					{
							  throw  SQLAllocHandle(SQL_HANDLE_STMT, *hdbc, reinterpret_cast<SQLHANDLE*>(&stm1));;
					}
					catch (SQLRETURN retcode)
					{
							  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
							  {
										std::cout << "[DATABASE STATUS]: 数据库句柄分配成功" << std::endl;
							  }
							  else
							  {
										std::cout << "[DATABASE STATUS]: 数据库句柄分配失败" << std::endl;
							  }
					}
		  }
}

/*
* STMT释放函数
* @author：LPH
* Date：2021-10-21
*/
void DataBaseOp::ReleaseStmt()
{
		  try
		  {
					throw SQLFreeHandle(SQL_HANDLE_STMT, reinterpret_cast<SQLHANDLE>(stm1));
		  }
		  catch (SQLRETURN retcode)
		  {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
							  std::cout << "[DATABASE STATUS]: 数据库句柄释放成功" << std::endl;
					else
							  std::cout << "[DATABASE STATUS]: 数据库句柄释放失败" << std::endl;
		  }
		  if (stm1 != nullptr)
		  {
					SQLFreeStmt(stm1, SQL_DROP);			//释放stmt
		  }
}



/*
* SQL查询语句析构函数
* @author：LPH
* Date：2021-9-16
* Date:   2021-10-12
		  1、修复指针的引用级别不匹配的问题
		  2、增加SQL查询语句没有被释放内存空间的问题
*/
DataBaseOp::~DataBaseOp()
{
		  if (this->ConnectionSatus)
		  {
					for (int i = 0; i < this->getInitQuerySize(); ++i)
					{
							  delete  (this->sqlPatterns)[i];
					}
					delete []this->sqlPatterns;		//释放SQL查询语句
		  }
}

/*
*录入商品的基本信息
* @author：LPH
* Date：2021-9-21
*/
void DataBaseOp::initMedicineBasicInfo()
{
		  int MedicineId(0);
		  wchar_t MedicineName[256] = { 0 };
		  wchar_t MedicineType[256] = { 0 };
		  wchar_t Manufacture[256] = { 0 };
		  float MedicinePrice(0.0f);
		  wchar_t MedicineValidateDate[256] = { 0 };
		  wchar_t AdditionInfo[256] = { 0 };
		  std::cout << "MedicineID:";
		  std::cin >> MedicineId;
		  std::cout << "MedicineName:";
		  std::wcin >> MedicineName;
		  std::cout << "MedicineType:";
		  std::wcin >> MedicineType;
		  std::cout << "Manufacture:";
		  std::wcin >> Manufacture;
		  std::cout << "MedicinePrice:";
		  std::cin >> MedicinePrice;
		  std::cout << "MedicineValidateDate:";
		  std::wcin >> MedicineValidateDate;
		  std::cout << "AdditionInfo:";
		  std::wcin.getline(AdditionInfo, 256);
		  std::wcin.get();

		  //std::regex					对于日期进行正则判断
		  try
		  {
					throw SQLPrepareW(reinterpret_cast<SQLHSTMT>(stm1), (this->sqlPatterns)[INIT_BASIC_INFO], SQL_NTS);
		  }
		  catch (SQLRETURN retcode)
		  {
					if(retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN strLength = SQL_NTS;
							  //绑定SQL语句的参数
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&MedicineId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName, wcslen(MedicineName), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)MedicineType, wcslen(MedicineType), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)Manufacture, wcslen(Manufacture), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT,  SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&MedicinePrice, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)MedicineValidateDate, wcslen(MedicineValidateDate), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)AdditionInfo, wcslen(AdditionInfo), &strLength);
							  try
							  {
										throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
							  }
							  catch (SQLRETURN retcode)
							  {
										if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE INSERT STATUS]: 基本信息插入操作成功" << std::endl;
										else
										{
												  std::cout << "[DATABASE INSERT STATUS]: 基本信息插入操作失败" << std::endl;
												  this->sqlErrorMsg();
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: 数据库参数绑定操作失败" << std::endl;
					}
		  }
}

/*
*录入药品采购信息
* @author：LPH
* Date：2021-10-14
*/
void DataBaseOp::initMedicinePurchase()	//初始化药品采购信息
{
		  try
		  {
					throw SQLPrepareW(reinterpret_cast<SQLHSTMT>(stm1), (this->sqlPatterns)[MEDICINE_BUYING], SQL_NTS);
		  }
		  catch (SQLRETURN retcode)
		  {
					int OrderId(0);
					int MedicineId(0);
					int TransactAmmount(0);
					float pricetotal(0.0);
					wchar_t MedicineName[256] = { 0 };
					wchar_t TransActionDate[256] = { 0 };
					wchar_t OperatorName[256] = { 0 };
					std::cout << "BuyingOrderId:";
					std::cin >> OrderId;
					std::cout << "MedicineID:";
					std::cin >> MedicineId;
					std::cout << "MedicineName:";
					std::wcin >> MedicineName;
					std::cout << "TransactAmmount:";
					std::cin >> TransactAmmount;
					std::cout << "TransActionDate:";
					std::wcin >> TransActionDate;
					std::cout << "OperatorName:";
					std::wcin.getline(OperatorName, 256);
					std::wcin.get();

					//std::regex					对于日期进行正则判断

					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN strLength = SQL_NTS;
							  //绑定SQL语句的参数
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&OrderId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&MedicineId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName, wcslen(MedicineName), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&TransactAmmount, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&pricetotal, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)TransActionDate, wcslen(TransActionDate), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)OperatorName, wcslen(OperatorName), &strLength);
							  try
							  {
										throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
							  }
							  catch (SQLRETURN retcode)
							  {
										if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE INSERT STATUS]: 采购表插入操作成功" << std::endl;
										else
										{
												  std::cout << "[DATABASE INSERT STATUS]: 采购表插入操作失败" << std::endl;
												  this->sqlErrorMsg();
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: 数据库参数绑定操作失败" << std::endl;
					}
		  }
}

/*
*录入药品销售信息
* @author：LPH
* Date：2021-10-14
*/
void DataBaseOp::initMedicineSaling()	    //初始化药品销售信息
{
		  this->AllocateStmt();
		  try
		  {
					throw SQLPrepareW(reinterpret_cast<SQLHSTMT>(stm1), (this->sqlPatterns)[MEDICINE_SALING], SQL_NTS);
		  }
		  catch (SQLRETURN retcode)
		  {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  int OrderId(0);
							  int MedicineId(0);
							  int TransactAmmount(0);
							  float MedicinePrice(0.0);
							  wchar_t MedicineName[256] = { 0 };
							  wchar_t TransActionDate[256] = { 0 };
							  wchar_t BuyerName[256] = { 0 };
							  std::cout << "SalingOrderId:";
							  std::cin >> OrderId;
							  std::cout << "MedicineID:";
							  std::cin >> MedicineId;
							  std::cout << "MedicineName:";
							  std::wcin >> MedicineName;
							  std::cout << "MedicinePrice:";
							  std::cin >> MedicinePrice;
							  std::cout << "TransactAmmount:";
							  std::cin >> TransactAmmount;
							  std::cout << "TransActionDate:";
							  std::wcin >> TransActionDate;
							  std::cout << "BuyerName:";
							  std::wcin.getline(BuyerName, 256);
							  std::wcin.get();
							  float pricetotal(TransactAmmount * MedicinePrice);

							  //std::regex					对于日期进行正则判断

							  SQLLEN strLength = SQL_NTS;
							  //绑定SQL语句的参数
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&OrderId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&MedicineId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName, wcslen(MedicineName), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&MedicinePrice, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&TransactAmmount, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&pricetotal, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)TransActionDate, wcslen(TransActionDate), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 8, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)BuyerName, wcslen(BuyerName), &strLength);
							  try
							  {
										throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
							  }
							  catch (SQLRETURN retcode)
							  {
										if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE INSERT STATUS]: 销售表插入操作成功" << std::endl;
										else
										{
												  std::cout << "[DATABASE INSERT STATUS]: 销售表插入操作失败" << std::endl;
												  this->sqlErrorMsg();
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: 数据库参数绑定操作失败" << std::endl;
					}
		  }
		  this->ReleaseStmt();
}

/*
*输出全部基本信息子函数
* @author：LPH
* Date：2021-10-14
*/
void DataBaseOp::printBasicInfo()
{
		  this->AllocateStmt();
		  try
		  {
					throw SQLExecDirectW(stm1, this->basicInfo, SQL_NTS);
		  }
		  catch (SQLRETURN retcode)
		  {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN sqlLength = SQL_NTS;
							  int MedicineId(0);
							  wchar_t MedicineName[256] = { 0 };
							  wchar_t MedicineType[256] = { 0 };
							  wchar_t Manufacture[256] = { 0 };
							  float MedicinePrice(0.0f);
							  wchar_t MedicineValidateDate[256] = { 0 };
							  wchar_t AdditionInfo[256] = { 0 };
							  int size[] = { 0,0,0,0,0 };
							  std::vector<wchar_t*>infoaddr{ MedicineName,MedicineType,Manufacture,MedicineValidateDate,AdditionInfo };
							  SQLBindCol(stm1, 1, SQL_C_LONG, &MedicineId, sizeof(MedicineId), 0);
							  SQLBindCol(stm1, 2, SQL_C_WCHAR, MedicineName, sizeof(MedicineName), &sqlLength);
							  SQLBindCol(stm1, 3, SQL_C_WCHAR, MedicineType, sizeof(MedicineType), &sqlLength);
							  SQLBindCol(stm1, 4, SQL_C_WCHAR, Manufacture, sizeof(Manufacture), &sqlLength);
							  SQLBindCol(stm1, 5, SQL_C_FLOAT, &MedicinePrice, sizeof(MedicinePrice), 0);
							  SQLBindCol(stm1, 6, SQL_C_WCHAR, MedicineValidateDate, sizeof(MedicineValidateDate), &sqlLength);
							  SQLBindCol(stm1, 7, SQL_C_WCHAR, AdditionInfo, sizeof(AdditionInfo), &sqlLength);
							  SQLRETURN ret(0);
							  while ((ret = SQLFetch(stm1)) != SQL_NO_DATA)
							  {
										eraseSpace<wchar_t>(MedicineName);
										eraseSpace<wchar_t>(MedicineType);
										eraseSpace<wchar_t>(Manufacture);
										eraseSpace<wchar_t>(MedicineValidateDate);
										eraseSpace<wchar_t>(AdditionInfo);
										std::wcout << MedicineId << " " << MedicineName << " " <<
												  MedicineType << " " << Manufacture << " " << MedicinePrice << " " <<
												  MedicineValidateDate << " " << AdditionInfo << " " << std::endl;

										for (auto ib = infoaddr.cbegin(); ib != infoaddr.cend(); ib++)
										{
												  cleanMem<wchar_t>(*ib, 0, 256);
										}
										MedicinePrice = 0.0f;
										MedicineId = 0;
							  }
							  SQLLEN rowcount(0);
							  try
							  {
										throw SQLRowCount(stm1, &rowcount);
							  }
							  catch (SQLRETURN ret)
							  {
										if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
										{
												  std::cout << "[DATABASE SELECT STATUS]: 查询" << rowcount << "行数据成功!" << std::endl;
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE SELECT STATUS]: 数据库基本信息查询失败" << std::endl;
							  this->sqlErrorMsg();
					}
		  }
		  this->ReleaseStmt();
}

/*
*查询药品的基本信息
* @author：LPH
* @Para:
*		  target:需要查找的属性
*		  Find: 需要查找的内容
* Date：2021-10-14
*/
bool DataBaseOp::findMedicineBasicInfo(const wchar_t*target,const wchar_t *Find)	//查询药品的基本信息
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  int ind(0);		  //属性下标
		  for (; ind < 7; ind++)
		  {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))
					{
							  delete[]ptemp;
							  break;
					}
		  }
		  if (ind != 7)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[SEARCH_BASIC_INFO]);			//备份信息原始长度
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //字符串粘结
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], L"\'");
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], L"\'");
					this->basicInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //修改BasicInfo指针
					wprintf(L"%s", this->basicInfo);
					this->printBasicInfo();
					memset((this->sqlPatterns)[SEARCH_BASIC_INFO] + originInfoLength,
							  L'\0', sizeof(wchar_t) * (256 - originInfoLength ));
					return true;
		  }
		  else
		  {
					std::cout << "[DATABASE SELECT STATUS]: 输入的属性列错误" << std::endl;
					delete[]ptemp;
		  }
		  return false;
}

/*
*查询药品的采购信息	 
* @author：LPH
* * @Para:
*		  target:需要查找的属性
*		  Find: 需要查找的内容
* Date：2021-10-14
*/
bool DataBaseOp::findMedicinePurchaseInfo(const wchar_t* target, const wchar_t* Find)//查询药品的采购信息	  
{
		  const wchar_t* basic_types[]
		  {
					L"BuyingOrderNumber = ",L"MedicineId = ",L"MedicineName = ",
					L"TransActionAmmount = ",L"PriceInTotal = ",
					L"TransActionDate = ",L"OperatorName = "
		  };
		  int ind(0);		  //属性下标
		  for (; ind < 7; ind++)
		  {
					if (!lstrcmpW(basic_types[ind], target))		   break;
		  }
		  //if (ind != 7)
		  //{
				//	::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], basic_types[ind]);	  //字符串粘结
				//	::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
				//	this->printInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //修改BasicInfo指针
				//	this->printBasicInfo();
		  //}
		  //else
		  //{
				//	std::cout << "[DATABASE SELECT STATUS]: 输入的属性列错误" << std::endl;
		  //}
		  return false;
}

/*
*查询药品的销售信息
* @author：LPH
* * @Para:
*		  target:需要查找的属性
*		  Find: 需要查找的内容
* Date：2021-10-14
*/
bool DataBaseOp::findMedicineSalingInfo(const wchar_t*, const wchar_t*)	  //查询药品的销售信息	  
{
		  //const wchar_t* basic_types[]
		  //{
				//	L"MedicineId = ",L"MedicineName = ",
				//	L"MedicineType = ",L"Manufacture = ",
				//	L"MedicinePrice = ",L"MedicineValidateDate = ",
				//	L"AdditionInfo = "
		  //};
		  //int ind(0);		  //属性下标
		  //for (; ind < 7; ind++)
		  //{
				//	if (!lstrcmpW(basic_types[ind], target))		   break;
		  //}
		  //if (ind != 7)
		  //{
				//	::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], basic_types[ind]);	  //字符串粘结
				//	::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
				//	this->printInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //修改BasicInfo指针
				//	this->printBasicInfo();
		  //}
		  //else
		  //{
				//	std::cout << "[DATABASE SELECT STATUS]: 输入的属性列错误" << std::endl;
		  //}
		  return false;
}
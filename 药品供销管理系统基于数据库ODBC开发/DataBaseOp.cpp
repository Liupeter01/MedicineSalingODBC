#include "DataBaseOp.h"
/*
* 动态获取枚举体内查询语句参数
* @author：LPH
* Date：2021-10-13
*/
int DataBaseOp::getInitQuerySize()
{
		  int querysize(0);
		  for (enum sqlquery temp = (enum sqlquery)sqlquery::INIT_BASIC_INFO;
					temp != sqlquery::OTHER; temp = (enum sqlquery)(temp + 1)
					)
		  {
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
		  wsprintf((this->sqlPatterns)[INIT_BASIC_INFO],
					L"INSERT INTO MedicineManagmentSys.dbo.MedicineWareBase values(?,?,?,?,?,?,?) ");
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
		  if (this->ConnectionSatus)
		  {
					this->stm1 = new HSTMT;
					SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//生成stmt
					SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, *hdbc, reinterpret_cast<SQLHANDLE*>(&stm1));
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  std::cout << "[DATABASE STATUS]: 数据库句柄分配成功" << std::endl;
					}
					else
					{
							  std::cout << "[DATABASE STATUS]: 数据库句柄分配失败" << std::endl;
					}
					this->sqlInitQueryParttern();

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
}

void DataBaseOp::menu()
{
		  if (this->ConnectionSatus)
		  {
					this->initMedcineBasicInfo();
		  }
}

/*
*录入商品的基本信息
* @author：LPH
* Date：2021-9-21
*/
void DataBaseOp::initMedcineBasicInfo()
{
		  int MedicineId(0);
		  std::string MedicineName{ 0 };
		  std::string MedicineType{ 0 };
		  std::string Manufacture{ 0 };
		  float MedicinePrice(0.0f);
		  std::string MedicineValidateDate{ 0 };
		  std::string AdditionInfo{ 0 }; 
		  std::cout << "MedicineID:";
		  std::cin >> MedicineId;
		  std::cout << "MedicineName:";
		  std::cin >> MedicineName;
		  std::cout << "MedicineType:";
		  std::cin >> MedicineType;
		  std::cout << "Manufacture:";
		  std::cin >> Manufacture;
		  std::cout << "MedicinePrice:";
		  std::cin >> MedicinePrice;
		  std::cout << "MedicineValidateDate:";
		  std::cin >> MedicineValidateDate;
		  std::cout << "AdditionInfo:";
		  std::cin >> AdditionInfo;
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
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName.c_str(), strlen(MedicineName.c_str()), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)MedicineType.c_str(), strlen(MedicineType.c_str()), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)Manufacture.c_str(), strlen(Manufacture.c_str()), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT,  SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&MedicinePrice, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)MedicineValidateDate.c_str(), strlen(MedicineValidateDate.c_str()), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)AdditionInfo.c_str(), strlen(AdditionInfo.c_str()), &strLength);
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: 数据库参数绑定操作失败" << std::endl;
					}
		  }
		  try
		  {
					throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
		  }
		  catch (SQLRETURN retcode)
		  {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  std::cout << "[DATABASE STATUS]: 数据库插入操作成功" << std::endl;
					}
					else
					{
							  std::cout << "[DATABASE STATUS]: 数据库插入操作失败" << std::endl;
							  SQLLEN numRecs = 0;
							  SQLGetDiagField(SQL_HANDLE_STMT, reinterpret_cast<SQLHSTMT>(stm1), 0, SQL_DIAG_NUMBER, &numRecs, 0, 0);
							  SQLSMALLINT i = 1, MsgLen;
							  SQLWCHAR SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
							  SQLINTEGER NativeError;
							  while (i <= numRecs && (SQLGetDiagRec(SQL_HANDLE_STMT, reinterpret_cast<SQLHSTMT>(stm1), i, SqlState, &NativeError, Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA)
							  {
										
										std::wcout << L"SQLSTATE " << SqlState << L" " << Msg << std::endl;
										++i;
							  }
					}
		  }
}
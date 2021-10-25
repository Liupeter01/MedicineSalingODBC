#include "DataBaseOp.h"
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
					(this->sqlPatterns)[i] = new SQLWCHAR[512]{ 0 };
		  }
		  wsprintf((this->sqlPatterns)[INIT_BASIC_INFO],L"INSERT INTO MedicineManagmentSys.dbo.MedicineWareBase values(?,?,?,?,?,?,?) ");	//7参数
		  wsprintf((this->sqlPatterns)[MODIFIY_BASIC_INFO], L"UPDATE MedicineManagmentSys.dbo.MedicineWareBase SET ");	//7参数
		  wsprintf((this->sqlPatterns)[MEDICINE_BUYING], L"INSERT INTO MedicineManagmentSys.dbo.MedicineBuying values(?,?,?,?,?,?,?) ");	//7参数
		  wsprintf((this->sqlPatterns)[MEDICINE_SALING], L"INSERT INTO MedicineManagmentSys.dbo.MedicineSaling values(?,?,?,?,?,?,?,?) ");	//8参数
		  wsprintf((this->sqlPatterns)[DISPLAY_ALL_BASIC_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineWareBase");	
		  wsprintf((this->sqlPatterns)[SEARCH_BASIC_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineWareBase WHERE ");
		  wsprintf((this->sqlPatterns)[SEARCH_BUYING_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineBuying WHERE ");
		  wsprintf((this->sqlPatterns)[SEARCH_SALING_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineSaling WHERE ");
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
		  try{
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

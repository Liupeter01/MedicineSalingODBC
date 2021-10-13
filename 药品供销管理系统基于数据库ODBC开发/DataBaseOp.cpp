#include "DataBaseOp.h"
/*
* 动态获取枚举体内查询语句参数
* @author：LPH
* Date：2021-10-13
*/
int DataBaseOp::getInitQuerySize()
{
		  int querysize(0);
		  for (enum sqlquery temp = sqlquery::INIT_BASIC_INFO; temp != sqlquery::OTHER; temp = (enum sqlquery)(temp + 1))
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
		  this->sqlPatterns = new SQLCHAR * [this->getInitQuerySize()];			//动态分配查询语句的大小
		  for (int i = 0; i < this->getInitQuerySize(); ++i)
		  {
					(this->sqlPatterns)[i] = new SQLCHAR[256]{ 0 };
		  }
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
					SQLRETURN retcode = SQLFreeHandle(SQL_HANDLE_STMT, reinterpret_cast<SQLHANDLE>(stm1));
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  std::cout << "[DATABASE STATUS]: 数据库句柄释放成功" << std::endl;
					}
					else
					{
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
	/*	  std::cout << "MedicineID:";
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
		  sprintf(reinterpret_cast<char*>((this->sqlPatterns)[INIT_BASIC_INFO]),
					"INSERT INTO MedicineWareBase values(%d,\'%s\',\'%s\',\'%s\',%f,\'%s\',\'%s\')",MedicineId, 
					MedicineName.c_str(),MedicineType.c_str(),Manufacture.c_str(), 
					MedicinePrice, MedicineValidateDate.c_str(), AdditionInfo.c_str());

		  RETCODE retcode = SQLExecDirectW(stm1, reinterpret_cast<SQLWCHAR*>((this->sqlPatterns)[INIT_BASIC_INFO]), SQL_NTS);
		  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		  {
					std::cout << "[DATABASE STATUS]: 数据库插入操作成功" << std::endl;
		  }
		  else
		  {
					std::cout << "[DATABASE STATUS]: 数据库插入操作失败" << std::endl;
		  }*/

}


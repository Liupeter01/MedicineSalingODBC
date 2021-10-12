#include "DataBaseOp.h"

/*
* 初始化SQL查询语句结构
* @author：LPH
* Date：2021-10-12
*/
void DataBaseOp::SQLInitQueryParttern()
{
		  this->sqlPatterns = new SQLCHAR * [30];
		  (this->sqlPatterns)[INIT_BASIC_INFO] = new SQLCHAR[]{ "INSERT INTO MedicineWareBase values(" };
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
		  this->stm1 = new HSTMT;
		  SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//生成stmt
		  SQLInitQueryParttern();
}

/*
* SQL查询语句析构函数
* @author：LPH
* Date：2021-9-16
* Date:   2021-10-12 修复指针的引用级别不匹配的问题
*/
DataBaseOp::~DataBaseOp()
{
		  if (stm1 != nullptr)
		  {
					SQLFreeStmt(stm1, SQL_DROP);			//释放stmt
					delete stm1;
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
		  RETCODE retcode = SQLExecDirectA(stm1, sqlQuery, SQL_NTS);
}


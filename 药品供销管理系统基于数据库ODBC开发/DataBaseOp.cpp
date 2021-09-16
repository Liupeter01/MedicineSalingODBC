#include "DataBaseOp.h"

/*
* SQL查询语句初始化函数
* @author：LPH
* Date：2021-9-16
*/
void DataBaseOp::sqlQueryInit()
{
		  this->sqlQuery.push_back("Select From Where");
		  this->sqlQuery.push_back("Select From Where");
}

/*
* SQL查询语句构造函数
* @author：LPH
* Date：2021-9-16
*/
DataBaseOp::DataBaseOp()
{
		  if (stm1 == nullptr)
		  {
					stm1 = new HSTMT;	//创建对象
					SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//生成stmt
					sqlQueryInit();				      //SQL查询语句初始化函数
		  }
}

/*
* SQL查询语句析构函数
* @author：LPH
* Date：2021-9-16
*/
DataBaseOp::~DataBaseOp()
{
		  if (stm1 != nullptr)
		  {
					SQLFreeStmt(*stm1, SQL_DROP);			//释放stmt
					delete stm1;
		  }
}
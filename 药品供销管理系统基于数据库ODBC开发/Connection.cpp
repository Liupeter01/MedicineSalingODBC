#include "Connection.h"
/*
*构造函数
*@author:LPH
*@Date:2021-9-15
* @Date:2021-10-12 更新trycatch逻辑问题
*/
DataBaseConnect::Connection::Connection()
{
		  setlocale(LC_ALL, "zh-CN");
		  henv = new HENV;
		  hdbc = new HDBC;
		  SQLWCHAR* pszd(new SQLWCHAR[30]{ L"MedicineManagementSysDSN" });
		  SQLWCHAR* puid(new SQLWCHAR[15]{ L"MedicineOp" });
		  SQLWCHAR* pass(new SQLWCHAR[25]{ L"MedicineOp" });
		  this->szdsninfo = pszd;
		  this->uid = puid;
		  this->szauthstr = pass;
		  try
		  {			
					throw this->dataBaseOpenConnection();
		  }
		  catch (RETCODE errcode)				//数据库连接错误
		  {
					if (errcode == SQL_SUCCESS_WITH_INFO || errcode == SQL_SUCCESS)
					{
							  std::cout << "[COMMAND LINE STATUS]:数据库连接成功" << std::endl;
							  ConnectionSatus = true;				   //数据库连接状态成功
					}
					else				 //数据库连接错误
					{
							  std::cout << "[COMMAND LINE STATUS]: 数据库连接错误" << std::endl;
					}  
		  }
}

/*
*析构函数
*@author:LPH
*@Date:2021-9-15
*/
DataBaseConnect::Connection::~Connection()
{
		  std::cout << "[COMMAND LINE STATUS]: 数据库访问程序即将关闭..." << std::endl;
		  this->dataBaseCloseConnection();					//关闭数据库的连接
		  delete henv;
		  delete hdbc;
		  delete[]this->szdsninfo;
		  delete[]this->uid;
		  delete []this->szauthstr;
}

/*
*打开数据库的连接
*@author:LPH
*@Date:2021-9-15
*@Date:2021-10-13 更换函数实现和函数返回值
*/
RETCODE DataBaseConnect::Connection::dataBaseOpenConnection()
{
		  SQLRETURN errcode(-1);		//赋予返回值初值
		  if ((errcode = SQLAllocEnv(reinterpret_cast<SQLHENV*>(this->henv))) != SQL_SUCCESS)
		  {
					return errcode;
		  }
		  if ((errcode = SQLAllocConnect(static_cast<SQLHENV>(*(this->henv)), reinterpret_cast<SQLHDBC*>(this->hdbc)))!=SQL_SUCCESS)
		  {
					return errcode;
		  }
		  errcode = SQLConnectW(
					static_cast<SQLHDBC>(*(this->hdbc)), this->szdsninfo,SQL_NTS, this->uid, SQL_NTS, this->szauthstr, SQL_NTS
		  );
		  return errcode;
}

/*
* 关闭数据库的连接
*@author:LPH
*@Date:2021-9-15
* @Date:2021-10-12	修复返回值逻辑
*/
void DataBaseConnect::Connection::dataBaseCloseConnection()
{
		  SQLDisconnect(static_cast<SQLHDBC>((*this->hdbc)));
		  SQLFreeConnect(static_cast<SQLHDBC>((*this->hdbc)));
		  SQLFreeEnv(static_cast<SQLHENV>((*this->henv)));
}
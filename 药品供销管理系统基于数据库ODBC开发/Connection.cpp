#include "Connection.h"
/*
*构造函数
*@author:LPH
*@Date:2021-9-15
*/
DataBaseConnect::Connection::Connection(std::string m_szdsninfo, std::string m_uid, std::string m_szauthstr)
{
		  henv = new HENV;
		  hdbc = new HDBC;
		  int szdsninfo_length = m_szdsninfo.length();	  //szdsninfo长度的赋值
		  int uid_length = m_uid.length();						 //uid长度赋值
		  int szauthstr_length = m_szauthstr.length();			 //szauthstr的长度
		  
		  this->szdsninfo = new SQLCHAR[sizeof(SQLCHAR) * (szdsninfo_length + 1)];
		  this->uid = new SQLCHAR[sizeof(SQLCHAR) * (uid_length + 1)];
		  this->szauthstr = new SQLCHAR[sizeof(SQLCHAR) * (szauthstr_length + 1)];

		  memcpy(this->szdsninfo, m_szdsninfo.c_str(), sizeof(SQLCHAR) * (szdsninfo_length));
		  memcpy(this->uid, m_uid.c_str(), sizeof(SQLCHAR) * (uid_length));
		  memcpy(this->szauthstr, m_szauthstr.c_str(), sizeof(SQLCHAR) * (szauthstr_length));
		  try
		  {
					RETCODE error_code = this->dataBaseOpenConnection();		//尝试连接数据库
		  }
		  catch (RETCODE code)
		  {
					std::cout << "[COMMAND LINE STATUS]: 数据库出现错误，错误代码为：" << static_cast<int>(code) << std::endl;
					this->dataBaseCloseConnection();				  //关闭数据库并销毁数据结构
		  }
		  std::cout << "[COMMAND LINE STATUS]:数据库连接成功" << std::endl;
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
}

/*
*打开数据库的连接
*@author:LPH
*@Date:2021-9-15
*/
RETCODE DataBaseConnect::Connection::dataBaseOpenConnection()
{
		  SQLAllocEnv(reinterpret_cast<SQLHENV*>(this->henv));
		  SQLAllocConnect(static_cast<SQLHENV>(*(this->henv)), reinterpret_cast<SQLHDBC*>(this->hdbc));
		  RETCODE errocode = SQLConnectA(
					static_cast<SQLHENV>(*(this->henv)),
					this->szdsninfo,
					SQL_NTS,
					this->uid,
					SQL_NTS,
					this->szauthstr,
					SQL_NTS);
		  return errocode;
}

/*
* 关闭数据库的连接
*@author:LPH
*@Date:2021-9-15
*/
void DataBaseConnect::Connection::dataBaseCloseConnection()
{
		  SQLDisconnect(static_cast<SQLHDBC>((*this->hdbc)));
		  SQLFreeConnect(static_cast<SQLHDBC>((*this->hdbc)));
		  SQLFreeEnv(static_cast<SQLHENV>((*this->henv)));
}

/*
* 数据库的初始化
*@author:LPH
*@Date:2021-9-15
*/
//void DataBaseConnect::Connection::DataBaseInit()
//{
//
//}
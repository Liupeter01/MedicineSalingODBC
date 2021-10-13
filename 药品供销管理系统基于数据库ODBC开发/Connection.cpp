#include "Connection.h"
/*
*���캯��
*@author:LPH
*@Date:2021-9-15
* @Date:2021-10-12 ����trycatch�߼�����
*/
DataBaseConnect::Connection::Connection()
{
		  std::string m_szdsninfo;
		  std::string m_uid;
		  std::string m_szauthstr;
		  std::cout << "dsn:";
		  std::cin >> m_szdsninfo;
		  std::cout << "uid:";
		  std::cin >> m_uid;
		  std::cout << "authstr:";
		  std::cin >> m_szauthstr;
		  henv = new HENV;
		  hdbc = new HDBC;
		  int szdsninfo_length = m_szdsninfo.length();	  //szdsninfo���ȵĸ�ֵ
		  int uid_length = m_uid.length();						 //uid���ȸ�ֵ
		  int szauthstr_length = m_szauthstr.length();			 //szauthstr�ĳ���
		  
		  this->szdsninfo = new SQLCHAR[sizeof(SQLCHAR) * (szdsninfo_length + 1)];
		  this->uid = new SQLCHAR[sizeof(SQLCHAR) * (uid_length + 1)];
		  this->szauthstr = new SQLCHAR[sizeof(SQLCHAR) * (szauthstr_length + 1)];

		  memcpy(this->szdsninfo, m_szdsninfo.c_str(), sizeof(SQLCHAR) * (szdsninfo_length));
		  memcpy(this->uid, m_uid.c_str(), sizeof(SQLCHAR) * (uid_length));
		  memcpy(this->szauthstr, m_szauthstr.c_str(), sizeof(SQLCHAR) * (szauthstr_length));
		  try
		  {
					RETCODE code = this->dataBaseOpenConnection();		//�����������ݿ�
					if (code != SQL_SUCCESS)
					{
							  throw 1;			  //���ݿ����Ӵ���
					}
		  }
		  catch (int error)				//���ݿ����Ӵ���
		  {
					std::cout << "[COMMAND LINE STATUS]: ���ݿ����Ӵ���"  << std::endl;
					this->dataBaseCloseConnection();				  //�ر����ݿⲢ�������ݽṹ
					ConnectionSatus = false;	  //���ݿ�����״̬ʧ��
					return;
		  }
		  std::cout << "[COMMAND LINE STATUS]:���ݿ����ӳɹ�" << std::endl;
		  ConnectionSatus = true;				   //���ݿ�����״̬�ɹ�
}

/*
*��������
*@author:LPH
*@Date:2021-9-15
*/
DataBaseConnect::Connection::~Connection()
{
		  std::cout << "[COMMAND LINE STATUS]: ���ݿ���ʳ��򼴽��ر�..." << std::endl;
		  this->dataBaseCloseConnection();					//�ر����ݿ������
		  delete henv;
		  delete hdbc;
}

/*
*�����ݿ������
*@author:LPH
*@Date:2021-9-15
*@Date:2021-10-12 ������������
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
* �ر����ݿ������
*@author:LPH
*@Date:2021-9-15
* @Date:2021-10-12	�޸�����ֵ�߼�
*/
void DataBaseConnect::Connection::dataBaseCloseConnection()
{
		  SQLDisconnect(static_cast<SQLHDBC>((*this->hdbc)));
		  SQLFreeConnect(static_cast<SQLHDBC>((*this->hdbc)));
		  SQLFreeEnv(static_cast<SQLHENV>((*this->henv)));
}
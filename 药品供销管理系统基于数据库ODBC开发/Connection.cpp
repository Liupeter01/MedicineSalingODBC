#include "Connection.h"
/*
*���캯��
*@author:LPH
*@Date:2021-9-15
* @Date:2021-10-12 ����trycatch�߼�����
*/
DataBaseConnect::Connection::Connection()
{
		  henv = new HENV;
		  hdbc = new HDBC;
		  SQLWCHAR* ptemp(new SQLWCHAR[6]{ L"sql01" });
		  this->szdsninfo = ptemp;
		  try{			
					if (this->dataBaseOpenConnection() != SQL_SUCCESS_WITH_INFO)
							  throw 1;			  //���ݿ����Ӵ���
		  }
		  catch (int error)				//���ݿ����Ӵ���
		  {
					if (error) std::cout << "[COMMAND LINE STATUS]: ���ݿ����Ӵ���" << std::endl;
					return;						  //����
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
*@Date:2021-10-13 ��������ʵ�ֺͺ�������ֵ
*/
RETCODE DataBaseConnect::Connection::dataBaseOpenConnection()
{
		  SQLRETURN errcode(-1);		//���践��ֵ��ֵ
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
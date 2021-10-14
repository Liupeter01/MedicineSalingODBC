#include "Connection.h"
/*
*���캯��
*@author:LPH
*@Date:2021-9-15
* @Date:2021-10-12 ����trycatch�߼�����
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
		  catch (RETCODE errcode)				//���ݿ����Ӵ���
		  {
					if (errcode == SQL_SUCCESS_WITH_INFO || errcode == SQL_SUCCESS)
					{
							  std::cout << "[COMMAND LINE STATUS]:���ݿ����ӳɹ�" << std::endl;
							  ConnectionSatus = true;				   //���ݿ�����״̬�ɹ�
					}
					else				 //���ݿ����Ӵ���
					{
							  std::cout << "[COMMAND LINE STATUS]: ���ݿ����Ӵ���" << std::endl;
					}  
		  }
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
		  delete[]this->szdsninfo;
		  delete[]this->uid;
		  delete []this->szauthstr;
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
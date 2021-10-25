#include"DataBaseOp.h"

/*
* ��̬��ȡö�����ڲ�ѯ������
* @author��LPH
* Date��2021-10-13
*/
int DataBaseOp::getInitQuerySize()
{
		  int querysize(0);
		  for (enum sqlquery temp = (enum DataBaseOp::sqlquery)sqlquery::INIT_BASIC_INFO;
					temp != sqlquery::OTHER; temp = (enum DataBaseOp::sqlquery)(temp + 1)) {
					querysize++;
		  }
		  return querysize;
}

/*
* ����ִ�й���
* @author��LPH
* Date��2021-10-25
*/
void DataBaseOp::instructExecute()
{
		  this->AllocateStmt();
		  try {
					throw SQLExecDirectW(stm1, this->BasicMedicineInfo, SQL_NTS);
		  }
		  catch (SQLRETURN retcode) {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  std::cout << "[DATABASE SELECT STATUS]: ���ݿ���Ϣ�޸ĳɹ�" << std::endl;
					}
					else
					{
							  std::cout << "[DATABASE SELECT STATUS]: ���ݿ���Ϣ�޸�ʧ��" << std::endl;
							  this->sqlErrorMsg();
					}
		  }
		  this->ReleaseStmt();
}

/*
*������Ϣ�������
* @author��LPH
* Date��2021-10-14
*/
void DataBaseOp::sqlErrorMsg()
{
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
#include"DataBaseOp.h"

void DataBaseOp::menu()
{
		  if (this->ConnectionSatus)
		  {
					//this->initMedicineBasicInfo();
					//this->initMedicinePurchase();
					this->displayAllBasicInfo();
					this->findMedicineBasicInfo(L"MedicineType", L"Һ��");
					this->findMedicineBasicInfo(L"Manufacture", L"ǿ����˾");
		  }
}

/*
*���ȫ��ҩƷ������Ϣ
* @author��LPH
* Date��2021-10-14
*/
void DataBaseOp::displayAllBasicInfo()
{
		  this->basicInfo = (this->sqlPatterns)[DISPLAY_ALL_BASIC_INFO];			  //�޸�BasicInfoָ��
		  this->printBasicInfo();
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
#include "DataBaseOp.h"
/*
* ��ʼ��SQL��ѯ���ṹ
* @author��LPH
* Date��2021-10-12
*/
void DataBaseOp::sqlInitQueryParttern()
{
		  this->sqlPatterns = new SQLWCHAR * [this->getInitQuerySize()];			//��̬�����ѯ���Ĵ�С
		  for (int i = 0; i < this->getInitQuerySize(); ++i)
		  {
					(this->sqlPatterns)[i] = new SQLWCHAR[512]{ 0 };
		  }
		  wsprintf((this->sqlPatterns)[INIT_BASIC_INFO],L"INSERT INTO MedicineManagmentSys.dbo.MedicineWareBase values(?,?,?,?,?,?,?) ");	//7����
		  wsprintf((this->sqlPatterns)[MODIFIY_BASIC_INFO], L"UPDATE MedicineManagmentSys.dbo.MedicineWareBase SET ");	//7����
		  wsprintf((this->sqlPatterns)[MEDICINE_BUYING], L"INSERT INTO MedicineManagmentSys.dbo.MedicineBuying values(?,?,?,?,?,?,?) ");	//7����
		  wsprintf((this->sqlPatterns)[MEDICINE_SALING], L"INSERT INTO MedicineManagmentSys.dbo.MedicineSaling values(?,?,?,?,?,?,?,?) ");	//8����
		  wsprintf((this->sqlPatterns)[DISPLAY_ALL_BASIC_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineWareBase");	
		  wsprintf((this->sqlPatterns)[SEARCH_BASIC_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineWareBase WHERE ");
		  wsprintf((this->sqlPatterns)[SEARCH_BUYING_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineBuying WHERE ");
		  wsprintf((this->sqlPatterns)[SEARCH_SALING_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineSaling WHERE ");
}

/*
* SQL��ѯ��乹�캯��
* @author��LPH
* @descrition:
* Date��2021-9-16
* Date:   2021-10-12 �������ݿ��ѯ���ṹ�ĳ�ʼ��
*/
DataBaseOp::DataBaseOp()
{
		  this->sqlInitQueryParttern();
}

/*
* STMT���亯��
* @author��LPH
* Date��2021-10-21
*/
void DataBaseOp::AllocateStmt()
{
		  if (this->ConnectionSatus)
		  {
					this->stm1 = new HSTMT;
					SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//����stmt
					try
					{
							  throw  SQLAllocHandle(SQL_HANDLE_STMT, *hdbc, reinterpret_cast<SQLHANDLE*>(&stm1));;
					}
					catch (SQLRETURN retcode)
					{
							  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
							  {
										std::cout << "[DATABASE STATUS]: ���ݿ�������ɹ�" << std::endl;
							  }
							  else
							  {
										std::cout << "[DATABASE STATUS]: ���ݿ�������ʧ��" << std::endl;
							  }
					}
		  }
}

/*
* STMT�ͷź���
* @author��LPH
* Date��2021-10-21
*/
void DataBaseOp::ReleaseStmt()
{
		  try{
					throw SQLFreeHandle(SQL_HANDLE_STMT, reinterpret_cast<SQLHANDLE>(stm1));
		  }
		  catch (SQLRETURN retcode)
		  {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
							  std::cout << "[DATABASE STATUS]: ���ݿ����ͷųɹ�" << std::endl;
					else
							  std::cout << "[DATABASE STATUS]: ���ݿ����ͷ�ʧ��" << std::endl;
		  }
		  if (stm1 != nullptr)
		  {
					SQLFreeStmt(stm1, SQL_DROP);			//�ͷ�stmt
		  }
}

/*
* SQL��ѯ�����������
* @author��LPH
* Date��2021-9-16
* Date:   2021-10-12
		  1���޸�ָ������ü���ƥ�������
		  2������SQL��ѯ���û�б��ͷ��ڴ�ռ������
*/
DataBaseOp::~DataBaseOp()
{
		  if (this->ConnectionSatus)
		  {
					for (int i = 0; i < this->getInitQuerySize(); ++i)
					{
							  delete  (this->sqlPatterns)[i];
					}
					delete []this->sqlPatterns;		//�ͷ�SQL��ѯ���
		  }
}

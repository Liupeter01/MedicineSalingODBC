#include "DataBaseOp.h"
/*
* ��̬��ȡö�����ڲ�ѯ������
* @author��LPH
* Date��2021-10-13
*/
int DataBaseOp::getInitQuerySize()
{
		  int querysize(0);
		  for (enum sqlquery temp = sqlquery::INIT_BASIC_INFO; temp != sqlquery::OTHER; temp = (enum sqlquery)(temp + 1))
		  {
					querysize++;
		  }
		  return querysize;
}

/*
* ��ʼ��SQL��ѯ���ṹ
* @author��LPH
* Date��2021-10-12
*/
void DataBaseOp::sqlInitQueryParttern()
{
		  this->sqlPatterns = new SQLCHAR * [this->getInitQuerySize()];			//��̬�����ѯ���Ĵ�С
		  for (int i = 0; i < this->getInitQuerySize(); ++i)
		  {
					(this->sqlPatterns)[i] = new SQLCHAR[256]{ 0 };
		  }
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
		  if (this->ConnectionSatus)
		  {
					this->stm1 = new HSTMT;
					SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//����stmt
					SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, *hdbc, reinterpret_cast<SQLHANDLE*>(&stm1));
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  std::cout << "[DATABASE STATUS]: ���ݿ�������ɹ�" << std::endl;
					}
					else
					{
							  std::cout << "[DATABASE STATUS]: ���ݿ�������ʧ��" << std::endl;
					}
					this->sqlInitQueryParttern();
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
					SQLRETURN retcode = SQLFreeHandle(SQL_HANDLE_STMT, reinterpret_cast<SQLHANDLE>(stm1));
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  std::cout << "[DATABASE STATUS]: ���ݿ����ͷųɹ�" << std::endl;
					}
					else
					{
							  std::cout << "[DATABASE STATUS]: ���ݿ����ͷ�ʧ��" << std::endl;
					}
					if (stm1 != nullptr)
					{
							  SQLFreeStmt(stm1, SQL_DROP);			//�ͷ�stmt
					}
		  }
}

void DataBaseOp::menu()
{
		  if (this->ConnectionSatus)
		  {
					this->initMedcineBasicInfo();
		  }
}

/*
*¼����Ʒ�Ļ�����Ϣ
* @author��LPH
* Date��2021-9-21
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
	/*	  std::cout << "MedicineID:";
		  std::cin >> MedicineId;
		  std::cout << "MedicineName:";
		  std::cin >> MedicineName;
		  std::cout << "MedicineType:";
		  std::cin >> MedicineType;
		  std::cout << "Manufacture:";
		  std::cin >> Manufacture;
		  std::cout << "MedicinePrice:";
		  std::cin >> MedicinePrice;
		  std::cout << "MedicineValidateDate:";
		  std::cin >> MedicineValidateDate;
		  std::cout << "AdditionInfo:";
		  std::cin >> AdditionInfo;
		  sprintf(reinterpret_cast<char*>((this->sqlPatterns)[INIT_BASIC_INFO]),
					"INSERT INTO MedicineWareBase values(%d,\'%s\',\'%s\',\'%s\',%f,\'%s\',\'%s\')",MedicineId, 
					MedicineName.c_str(),MedicineType.c_str(),Manufacture.c_str(), 
					MedicinePrice, MedicineValidateDate.c_str(), AdditionInfo.c_str());

		  RETCODE retcode = SQLExecDirectW(stm1, reinterpret_cast<SQLWCHAR*>((this->sqlPatterns)[INIT_BASIC_INFO]), SQL_NTS);
		  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		  {
					std::cout << "[DATABASE STATUS]: ���ݿ��������ɹ�" << std::endl;
		  }
		  else
		  {
					std::cout << "[DATABASE STATUS]: ���ݿ�������ʧ��" << std::endl;
		  }*/

}


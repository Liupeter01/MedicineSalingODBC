#include "DataBaseOp.h"

/*
* ��ʼ��SQL��ѯ���ṹ
* @author��LPH
* Date��2021-10-12
*/
void DataBaseOp::SQLInitQueryParttern()
{
		  this->sqlPatterns = new SQLCHAR * [30];
		  (this->sqlPatterns)[INIT_BASIC_INFO] = new SQLCHAR[]{ "INSERT INTO MedicineWareBase values(" };
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
		  this->stm1 = new HSTMT;
		  SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//����stmt
		  SQLInitQueryParttern();
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
		  for (int i = 0; i < 30; ++i)
		  {
					delete  (this->sqlPatterns)[INIT_BASIC_INFO];
		  }
		  delete this->sqlPatterns;		//�ͷ�SQL��ѯ���
		  if (stm1 != nullptr)
		  {
					SQLFreeStmt(stm1, SQL_DROP);			//�ͷ�stmt
					delete stm1;
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
		  RETCODE retcode = SQLExecDirectA(stm1, sqlQuery, SQL_NTS);
}


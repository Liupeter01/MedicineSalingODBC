#include "DataBaseOp.h"

/*
* SQL��ѯ����ʼ������
* @author��LPH
* Date��2021-9-16
*/
void DataBaseOp::sqlQueryInit()
{
		  this->sqlQuery.push_back("Select From Where");
		  this->sqlQuery.push_back("Select From Where");
}

/*
* SQL��ѯ��乹�캯��
* @author��LPH
* Date��2021-9-16
*/
DataBaseOp::DataBaseOp()
{
		  if (stm1 == nullptr)
		  {
					stm1 = new HSTMT;	//��������
					SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//����stmt
					sqlQueryInit();				      //SQL��ѯ����ʼ������
		  }
}

/*
* SQL��ѯ�����������
* @author��LPH
* Date��2021-9-16
*/
DataBaseOp::~DataBaseOp()
{
		  if (stm1 != nullptr)
		  {
					SQLFreeStmt(*stm1, SQL_DROP);			//�ͷ�stmt
					delete stm1;
		  }
}
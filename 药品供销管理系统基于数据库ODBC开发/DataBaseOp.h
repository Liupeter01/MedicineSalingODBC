#pragma once
#include"Connection.h"
/*
* ���ݿ����ģ��
* @author��LPH
* Date��2021-9-15
*/
class DataBaseOp :public DataBaseConnect::Connection
{
public:
		  DataBaseOp();
		  ~DataBaseOp();
private:
		  void sqlQueryInit();					  //SQL��ѯ����ʼ������
private:
		  HSTMT *stm1;					//���Ӿ��
		  std::vector<std::string> sqlQuery;			//SQL��������ڶ��ֲ�ѯ���
};


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
		  void SQLInitQueryParttern();	//��ʼ��SQL��ѯ���ṹ
		  void initMedcineBasicInfo();	//��ʼ��ҩƷ�Ļ�����Ϣ
		  void findMedcineBasicInfo();	//��ѯҩƷ�Ļ�����Ϣ
		  void statisticMedcineBasicInfo();		  //ͳ��ҩƷ�Ļ�����Ϣ

private:
		  HSTMT *stm1;					//���Ӿ��
		  SQLCHAR sqlQuery[1024] = { 0 };
		  SQLCHAR** sqlPatterns;				  //��ѯģʽ

private:
		  enum sqlquery {
					INIT_BASIC_INFO,	//¼��ҩƷ������Ϣ
					MEDICINE_BUYING,	//ҩƷ������Ϣ�����
					MEDICINE_SALING,	//ҩƷ������Ϣ������
					MODIFIY_BASIC_INFO,	//�޸�ҩƷ������Ϣ
					DISPLAY_ALL,	//���ȫ��ҩƷ�Ļ�����Ϣ
					SEARCH_BASIC_INFO,	//��ѯ��������Ϣ
					SEARCH_BUYING_INFO,//��ѯ������Ϣ
					SEARCH_SALING_INFO,//��ѯ���۵���Ϣ
					STATISTICS_BASIC_INFO,	//ͳ�ƻ�������Ϣ
					STATISTICS_BUYING_INFO,//ͳ��������Ϣ
					STATISTICS_SALING_INFO,//ͳ�����۵���Ϣ
					OTHER	  //Ԥ���ӿ�
		  };
};


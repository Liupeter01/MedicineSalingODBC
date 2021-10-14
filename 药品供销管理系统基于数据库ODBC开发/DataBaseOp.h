#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
public:
		  void menu();
		  template<typename T>
		  void cleanMem(T* memzone, T data, int size);		//�ڴ����
		  template<typename T>
		  void eraseSpace(T* str);		//ɾ������ո�
private:
		  /*ҵ���߼�*/
		  int getInitQuerySize();
		  void sqlInitQueryParttern();	//��ʼ��SQL��ѯ���ṹ
		  void initMedicineBasicInfo();	//��ʼ��ҩƷ�Ļ�����Ϣ
		  void initMedicinePurchase();	//��ʼ��ҩƷ�ɹ���Ϣ
		  void initMedicineSaling();	    //��ʼ��ҩƷ������Ϣ

		  void displayAllBasicInfo();	    //���ȫ��ҩƷ������Ϣ
		  void findMedicineBasicInfo();	//��ѯҩƷ�Ļ�����Ϣ
		  void statisticMedicineBasicInfo();		  //ͳ��ҩƷ�Ļ�����Ϣ

private:
		  /*������Ϣ���*/
		  void sqlErrorMsg();					  //������Ϣ�������

private:
		  HSTMT *stm1;					//���Ӿ��
		  SQLWCHAR sqlQuery[1024] = { 0 };
		  SQLWCHAR** sqlPatterns;				  //��ѯģʽ

private:
		  enum sqlquery {
					INIT_BASIC_INFO,	//¼��ҩƷ������Ϣ
					MEDICINE_BUYING,	//ҩƷ������Ϣ�Ĳɹ�
					MEDICINE_SALING,	//ҩƷ������Ϣ������
					MODIFIY_BASIC_INFO,	//�޸�ҩƷ������Ϣ
					DISPLAY_ALL_BASIC_INFO,	//���ȫ��ҩƷ�Ļ�����Ϣ
					SEARCH_BASIC_INFO,	//��ѯ��������Ϣ
					SEARCH_BUYING_INFO,//��ѯ������Ϣ
					SEARCH_SALING_INFO,//��ѯ���۵���Ϣ
					STATISTICS_BASIC_INFO,	//ͳ�ƻ�������Ϣ
					STATISTICS_BUYING_INFO,//ͳ��������Ϣ
					STATISTICS_SALING_INFO,//ͳ�����۵���Ϣ
					OTHER	  //Ԥ���ӿ�
		  };
};


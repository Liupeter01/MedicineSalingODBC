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
		  void sqlErrorMsg();					  //������Ϣ�������

private:
		  void BasicDBExecute();				  //���ݿ������Ϣ��������
		  int getInitQuerySize();
		  void sqlInitQueryParttern();	//��ʼ��SQL��ѯ���ṹ
		  void AllocateStmt();			//STMT�ķ��亯��
		  void ReleaseStmt();			//STMT���ͷź���
		  template<typename T>  void eraseSpace(T* str)	{[&]() {/*ɾ������ո�*/	
							  T* ptemp = str;
							  while (*ptemp++ != ' ');
							  *ptemp = ((!strcmp(typeid(T*).name(), "wchar_t*")) ? L'\0' : '\0');
		 };}
		  template<typename T>  void cleanMem(T* memzone, T data, int size){[&]() {		  /*�ڴ���պ���*/
					for (int i = 0; i < size; ++i)		  *(memzone + i) = data;};
		  }

private:
		  /*ҵ���߼�*/
		  void initMedicineBasicInfo();	//��ʼ��ҩƷ�Ļ�����Ϣ
		  void initMedicinePurchase();	//��ʼ��ҩƷ�ɹ���Ϣ
		  void initMedicineSaling();	    //��ʼ��ҩƷ������Ϣ

		  void printBasicInfo();				  //���������Ϣ�Ӻ���
		  void printPurchaseInfo();				  //����ɹ���Ϣ�Ӻ���
		  void printSalingInfo();				  //���������Ϣ�Ӻ���
		  void displayAllBasicInfo();	    //���ȫ��ҩƷ������Ϣ
		  bool findMedicineBasicInfo(const wchar_t* target, const wchar_t* Find);//��ѯҩƷ�Ļ�����Ϣ
		  bool findMedicinePurchaseInfo(const wchar_t* target, const wchar_t* Find);	//��ѯҩƷ�Ĳɹ���Ϣ	  
		  bool findMedicineSalingInfo(const wchar_t* target, const wchar_t* Find);		  //��ѯҩƷ��������Ϣ

		  bool modifyMedicineBasicInfo(const wchar_t* target, const wchar_t* expired, const wchar_t* uptodate);	  //�޸�ҩƷ�Ļ�����Ϣ
		  bool modifyMedicinePurchaseInfo(const wchar_t* target);	  //�޸Ĳɹ���Ϣ(�Ƿ�����޸���ˮ)	
		  bool modifyMedicineSalingInfo(const wchar_t* target);		  //�޸�������Ϣ(�Ƿ�����޸���ˮ)

		  bool deleteMedicineBasicInfo(const wchar_t* target, const wchar_t* deleteitem); //ɾ��ҩƷ�Ļ�����Ϣ
		  bool deleteMedicinePurchaseInfo(const wchar_t* target, const wchar_t* deleteitem); //ɾ��ҩƷ�Ĳɹ���Ϣ(�Ƿ�����޸���ˮ)	
		  bool deleteMedicineSalingInfo(const wchar_t* target, const wchar_t* deleteitem); //ɾ��ҩƷ��������Ϣ(�Ƿ�����޸���ˮ)	

		  void statisticMedicineBasicInfo();		  //ͳ��ҩƷ�Ļ�����Ϣ

private:
		  /*����ר��SQL���ָ��*/
		  SQLWCHAR* BasicMedicineInfo;		//printBasicInfo�������ָ��
		  SQLWCHAR* PurchaseInfo;					  //printBuyingInfo�������ָ��
		  SQLWCHAR* SalingInfo;					  //printSalingInfo�������ָ��

		  const wchar_t* QueryBasicMedicineInfo[7]
		  {
					L"MedicineId = ",L"MedicineName = ",
					L"MedicineType = ",L"Manufacture = ",
					L"MedicinePrice = ",L"MedicineValidateDate = ",
					L"AdditionInfo = "
		  };
		  const wchar_t* QueryPurchaseMedicine[7]
		  {
					L"BuyingOrderNumber = ",L"MedicineId = ",L"MedicineName = ",
					L"TransActionAmmount = ",L"PriceInTotal = ",
					L"TransActionDate = ",L"OperatorName = "
		  };
		  const wchar_t* QuerySalingMedicine[8]
		  {
					L"SalingOrderNumber = ",L"MedicineId = ",L"MedicineName = ",
					L"MedicinePrice = ",L"TransActionAmmount = ",L"PriceInTotal = ",
					L"TransActionDate = ",L"BuyerName = "
		  };
private:
		  HSTMT *stm1;					//���Ӿ��
		  SQLWCHAR sqlQuery[1024] = { 0 };
		  SQLWCHAR** sqlPatterns;				  //��ѯģʽ

private:
		  enum sqlquery {
					/*������Ϣ  DBInsert.cpp*/
					INIT_BASIC_INFO,	//¼��ҩƷ������Ϣ
					MEDICINE_BUYING,	//ҩƷ������Ϣ�Ĳɹ�
					MEDICINE_SALING,	//ҩƷ������Ϣ������

					/*�޸���Ϣ*/
					MODIFIY_BASIC_INFO,	//�޸�WareBase�еĻ�����Ϣ
					MODIFIY_BUYING_INFO,	//�޸�������Ϣ
					MODIFIY_SALING_INFO,	//�޸����۵���Ϣ

					/*��ѯ��Ϣ*/
					DISPLAY_ALL_BASIC_INFO,	//���ȫ��ҩƷ�Ļ�����Ϣ
					SEARCH_BASIC_INFO,	//��ѯWareBase�е���Ϣ
					SEARCH_BUYING_INFO,//��ѯ������Ϣ
					SEARCH_SALING_INFO,//��ѯ���۵���Ϣ

					/*ɾ����Ϣ*/
					DELETE_BASIC_INFO,		//ɾ��WareBase�е���Ϣ
					DELETE_BUYING_INFO,//ɾ��������Ϣ
					DELETE_SALING_INFO,//ɾ�����۵���Ϣ

					STATISTICS_BASIC_INFO,	//ͳ�ƻ�������Ϣ
					STATISTICS_BUYING_INFO,//ͳ��������Ϣ
					STATISTICS_SALING_INFO,//ͳ�����۵���Ϣ
					OTHER	  //Ԥ���ӿ�
		  };
};
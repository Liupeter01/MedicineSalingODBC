#include"DataBaseOp.h"

void DataBaseOp::menu()
{
		  if (this->ConnectionSatus)
		  {
				//this->initMedicineBasicInfo();
				//this->initMedicinePurchase();
				//this->displayAllBasicInfo();
				//this->findMedicineBasicInfo(L"MedicineType", L"Һ��");
		  }
}

/*
*���ȫ��ҩƷ������Ϣ
* @author��LPH
* Date��2021-10-14
*/
void DataBaseOp::displayAllBasicInfo()
{
		  this->BasicMedicineInfo = (this->sqlPatterns)[DISPLAY_ALL_BASIC_INFO];			  //�޸�BasicInfoָ��
		  this->printBasicInfo();
}
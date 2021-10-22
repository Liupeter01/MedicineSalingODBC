#include"DataBaseOp.h"

void DataBaseOp::menu()
{
		  if (this->ConnectionSatus)
		  {
				//this->initMedicineBasicInfo();
				//this->initMedicinePurchase();
				//this->displayAllBasicInfo();
				//this->findMedicineBasicInfo(L"MedicineType", L"液体");
		  }
}

/*
*输出全部药品基本信息
* @author：LPH
* Date：2021-10-14
*/
void DataBaseOp::displayAllBasicInfo()
{
		  this->BasicMedicineInfo = (this->sqlPatterns)[DISPLAY_ALL_BASIC_INFO];			  //修改BasicInfo指针
		  this->printBasicInfo();
}
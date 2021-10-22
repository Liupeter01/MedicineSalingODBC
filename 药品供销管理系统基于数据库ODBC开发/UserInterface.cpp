#include"DataBaseOp.h"

void DataBaseOp::menu()
{
		  if (this->ConnectionSatus)
		  {
				this->initMedicineBasicInfo();
				this->initMedicinePurchase();
				this->initMedicineSaling();
				//this->displayAllBasicInfo();
				//this->findMedicineBasicInfo(L"MedicineType", L"Ò÷Ìו");
		  }
}
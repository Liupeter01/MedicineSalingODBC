#include"DataBaseOp.h"

void DataBaseOp::menu()
{
		  if (this->ConnectionSatus)
		  {
					/*信息插入*/
				this->initMedicineBasicInfo();
				//this->initMedicinePurchase();
				//this->initMedicineSaling();
				
					/* 信息的搜索*/
				//this->displayAllBasicInfo();
				//this->findMedicineBasicInfo(L"MedicineType", L"液体");
				//this->findMedicinePurchaseInfo()7
			     //this->findMedicineSalingInfo();
				  
				 /*信息的修改*/
				//this->modifyMedicineBasicInfo(L"MedicineName", L"地奥心血康", L"我不知道");
					//std::vector<const char*>info{ 
					//		  "1 InsertMeidicineBasicInfo",
					//		  "2 InsertMeidicinePurchase",
					//		  "3 InsertMeidicineSaling",
					//		  "4 FindMeidicineBasicInfo",
					//		  "5 FindMeidicinePurchaseInfo",
					//		  "6 FindMeidicineSalingInfo",
					//		  "7 DisplayAllBasicInfo",

					//};
					//for (auto i : info)
					//{
					//		  std::cout << i << std::endl;
					//}

		  }
}
#include"DataBaseOp.h"

void DataBaseOp::menu()
{
		  if (this->ConnectionSatus)
		  {
					/*��Ϣ����*/
				this->initMedicineBasicInfo();
				//this->initMedicinePurchase();
				//this->initMedicineSaling();
				
					/* ��Ϣ������*/
				//this->displayAllBasicInfo();
				//this->findMedicineBasicInfo(L"MedicineType", L"Һ��");
				//this->findMedicinePurchaseInfo()7
			     //this->findMedicineSalingInfo();
				  
				 /*��Ϣ���޸�*/
				//this->modifyMedicineBasicInfo(L"MedicineName", L"�ذ���Ѫ��", L"�Ҳ�֪��");
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
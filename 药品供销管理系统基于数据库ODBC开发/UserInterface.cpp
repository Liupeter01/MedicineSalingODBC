#include"DataBaseOp.h"

void DataBaseOp::menu()
{
		  std::vector<const char*>info{
			"0 quit",
			"1 InsertMeidicineBasicInfo",
			"2 InsertMeidicinePurchase",
			"3 InsertMeidicineSaling",
			"4 FindMeidicineBasicInfo",
			"5 FindMeidicinePurchaseInfo",
			"6 FindMeidicineSalingInfo",
			"7 DisplayAllBasicInfo",
		  };
		  if (this->ConnectionSatus)
		  {
					//while (1)
					//{
					//		  for (auto i : info)
					//		  {
					//					std::cout << i << std::endl;
					//		  }
					//		  int choose(0);
					//		  std::cout << "������ѡ��:";
					//		  std::cin >> choose;
					//		  switch (choose)
					//		  {
					//					/*��Ϣ����*/
					//		  case 1:this->initMedicineBasicInfo(); break;
					//		  case 2:this->initMedicinePurchase(); break;
					//		  case 3:this->initMedicineSaling(); break;
					//		  case 4:
					//		  {
					//					std::wstring row;
					//					std::cout << "��������Ҫ��ѯ�������У�";
					//					std::wcin >> row;
					//					std::wstring info;
					//					std::cout << "��������Ҫ��ѯ�����ݣ�";
					//					std::wcin >> info;
					//					this->findMedicineBasicInfo(row.c_str(), info.c_str());
					//		  }
					//		  break;
					//		  case 5:
					//		  {
					//					std::wstring row;
					//					std::cout << "��������Ҫ��ѯ�������У�";
					//					std::wcin >> row;
					//					std::wstring info;
					//					std::cout << "��������Ҫ��ѯ�����ݣ�";
					//					std::wcin >> info;
					//					this->findMedicinePurchaseInfo(row.c_str(), info.c_str());
					//		  }
					//		  break;
					//		  case 6:
					//		  {
					//					std::wstring row;
					//					std::cout << "��������Ҫ��ѯ�������У�";
					//					std::wcin >> row;
					//					std::wstring info;
					//					std::cout << "��������Ҫ��ѯ�����ݣ�";
					//					std::wcin >> info;
					//					this->findMedicineSalingInfo(row.c_str(), info.c_str());
					//		  }
					//		  break;
					//		  case 7:this->displayAllBasicInfo(); break;
					//		  default:exit(0); break;
					//		  }

					//		   /*��Ϣ���޸�*/
					//		  this->modifyMedicineBasicInfo(L"MedicineName", L"�Ҳ�֪��", L"����");
					//}
					this->modifyMedicineBasicInfo(L"MedicineName", L"�Ҳ�֪��", L"����");
		  }
}
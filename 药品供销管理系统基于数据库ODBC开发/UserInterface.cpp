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
					//		  std::cout << "请输入选择:";
					//		  std::cin >> choose;
					//		  switch (choose)
					//		  {
					//					/*信息插入*/
					//		  case 1:this->initMedicineBasicInfo(); break;
					//		  case 2:this->initMedicinePurchase(); break;
					//		  case 3:this->initMedicineSaling(); break;
					//		  case 4:
					//		  {
					//					std::wstring row;
					//					std::cout << "请输入需要查询的属性列：";
					//					std::wcin >> row;
					//					std::wstring info;
					//					std::cout << "请输入需要查询的内容：";
					//					std::wcin >> info;
					//					this->findMedicineBasicInfo(row.c_str(), info.c_str());
					//		  }
					//		  break;
					//		  case 5:
					//		  {
					//					std::wstring row;
					//					std::cout << "请输入需要查询的属性列：";
					//					std::wcin >> row;
					//					std::wstring info;
					//					std::cout << "请输入需要查询的内容：";
					//					std::wcin >> info;
					//					this->findMedicinePurchaseInfo(row.c_str(), info.c_str());
					//		  }
					//		  break;
					//		  case 6:
					//		  {
					//					std::wstring row;
					//					std::cout << "请输入需要查询的属性列：";
					//					std::wcin >> row;
					//					std::wstring info;
					//					std::cout << "请输入需要查询的内容：";
					//					std::wcin >> info;
					//					this->findMedicineSalingInfo(row.c_str(), info.c_str());
					//		  }
					//		  break;
					//		  case 7:this->displayAllBasicInfo(); break;
					//		  default:exit(0); break;
					//		  }

					//		   /*信息的修改*/
					//		  this->modifyMedicineBasicInfo(L"MedicineName", L"我不知道", L"测试");
					//}
					this->modifyMedicineBasicInfo(L"MedicineName", L"我不知道", L"测试");
		  }
}
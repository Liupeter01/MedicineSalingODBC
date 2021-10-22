#include"DataBaseOp.h"

/*
*查询药品的基本信息
* @author：LPH
* @Para:
*		  target:需要查找的属性
*		  Find: 需要查找的内容
* Date：2021-10-14
*/
bool DataBaseOp::findMedicineBasicInfo(const wchar_t* target, const wchar_t* Find)	//查询药品的基本信息
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  int ind(0);		  //属性下标
		  for (; ind < 7; ind++) {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != 8)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[SEARCH_BASIC_INFO]);			//备份信息原始长度
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //字符串粘结
					if (ind != 0 && ind != 4)
					{
							  ::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], L"\'");
							  ::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
							  ::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], L"\'");
					}
					else
					{
							  ::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
					}
					this->BasicMedicineInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //修改BasicInfo指针
					this->printBasicInfo();
					memset((this->sqlPatterns)[SEARCH_BASIC_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (256 - originInfoLength));					//将sqlPatterns恢复初始状态
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: 输入的属性列错误" << std::endl;
		  return false;
}

/*
*查询药品的采购信息
* @author：LPH
* * @Para:
*		  target:需要查找的属性
*		  Find: 需要查找的内容
* Date：2021-10-14
*/
bool DataBaseOp::findMedicinePurchaseInfo(const wchar_t* target, const wchar_t* Find)//查询药品的采购信息	  
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  int ind(0);		  //属性下标
		  for (; ind < 7; ind++) {
					if (!lstrcmpW(this->QueryPurchaseMedicine[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != 8)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[SEARCH_BUYING_INFO]);			//备份信息原始长度
					::wcscat((this->sqlPatterns)[SEARCH_BUYING_INFO], this->QueryPurchaseMedicine[ind]);	  //字符串粘结
					if (ind != 0 && ind != 3 && ind != 4)
					{
							  ::wcscat((this->sqlPatterns)[SEARCH_BUYING_INFO], L"\'");
							  ::wcscat((this->sqlPatterns)[SEARCH_BUYING_INFO], Find);
							  ::wcscat((this->sqlPatterns)[SEARCH_BUYING_INFO], L"\'");
					}
					else
					{
							  ::wcscat((this->sqlPatterns)[SEARCH_BUYING_INFO], Find);
					}
					this->PurchaseInfo = (this->sqlPatterns)[SEARCH_BUYING_INFO];			  //修改BasicInfo指针
					this->printPurchaseInfo();
					memset((this->sqlPatterns)[SEARCH_BUYING_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (256 - originInfoLength));					//将sqlPatterns恢复初始状态
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: 输入的属性列错误" << std::endl;
		  return false;
}

/*
*查询药品的销售信息
* @author：LPH
* * @Para:
*		  target:需要查找的属性
*		  Find: 需要查找的内容
* Date：2021-10-14
*/
bool DataBaseOp::findMedicineSalingInfo(const wchar_t* target, const wchar_t* Find)	  //查询药品的销售信息	  
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");

		  int ind(0);		  //属性下标
		  for (; ind < 8; ind++) {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != 9)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[SEARCH_BASIC_INFO]);			//备份信息原始长度
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //字符串粘结
					if (ind != 0 && ind != 4)
					{
							  ::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], L"\'");
							  ::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
							  ::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], L"\'");
					}
					else
					{
							  ::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
					}
					this->BasicMedicineInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //修改BasicInfo指针
					this->printBasicInfo();
					memset((this->sqlPatterns)[SEARCH_BASIC_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (256 - originInfoLength));					//将sqlPatterns恢复初始状态
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: 输入的属性列错误" << std::endl;
		  return false;
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
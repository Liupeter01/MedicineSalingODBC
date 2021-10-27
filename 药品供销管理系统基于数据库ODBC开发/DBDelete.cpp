#include"DataBaseOp.h"

/*
*删除药品的基本信息
* @author：LPH
* 		  target:需要删除的属性
*		  Find: 需要删除的内容
* Date：2021-10-25
*/
bool DataBaseOp::deleteMedicineBasicInfo(const wchar_t* target, const wchar_t* deleteitem)
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  int ind(0);		  //属性下标
		  for (; ind < sizeof(this->QueryBasicMedicineInfo) / sizeof(const wchar_t*); ind++) {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != sizeof(this->QueryBasicMedicineInfo) / sizeof(const wchar_t*) + 1)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[DELETE_BASIC_INFO]);			//备份信息原始长度
					::wcscat((this->sqlPatterns)[DELETE_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //字符串粘结
					if (ind != 0 && ind != 4)
					{
							  ::wcscat((this->sqlPatterns)[DELETE_BASIC_INFO], L"\'");
							  ::wcscat((this->sqlPatterns)[DELETE_BASIC_INFO], deleteitem);
							  ::wcscat((this->sqlPatterns)[DELETE_BASIC_INFO], L"\'");
					}
					else
					{
							  ::wcscat((this->sqlPatterns)[DELETE_BASIC_INFO], deleteitem);
					}
					this->BasicMedicineInfo = (this->sqlPatterns)[DELETE_BASIC_INFO];			  //修改BasicInfo指针
					this->BasicDBExecute();
					memset((this->sqlPatterns)[DELETE_BASIC_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (512 - originInfoLength));					//将sqlPatterns恢复初始状态
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: 输入的属性列错误" << std::endl;
		  return false;
}
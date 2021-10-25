#include"DataBaseOp.h"

/*
*修改商品的基本信息
* @author：LPH
* * @Para:
*		  target:需要查找的属性
*		  expired:查找的旧数据
*		  uptodate:新数据
* Date：2021-10-25
*/
bool DataBaseOp::modifyMedicineBasicInfo(const wchar_t* target,const wchar_t *expired,const wchar_t *uptodate)		  //修改药品的基本信息
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  wchar_t* condition(new wchar_t[wcslen(L" WHERE ") + wcslen(ptemp) + wcslen(expired) + 3 * wcslen(L"\'")]);	//包含两个'和一个'\0'
		  ::wcscpy(condition, L" WHERE ");
		  ::wcscat(condition, ptemp);
		  int ind(0);		  //属性下标
		  for (; ind < sizeof(this->QueryBasicMedicineInfo) / sizeof(const wchar_t*); ind++) {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))			    break;
		  }
		  if (ind != sizeof(this->QueryBasicMedicineInfo) / sizeof(const wchar_t*) + 1)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[MODIFIY_BASIC_INFO]);			//备份信息原始长度
					::wcscat((this->sqlPatterns)[MODIFIY_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //字符串粘结
					if (ind != 0 && ind != 4)
					{
							  ::wcscat((this->sqlPatterns)[MODIFIY_BASIC_INFO], L"\'");	  //操作SET内容
							  ::wcscat(condition, L"\'");				  //操作WHERE条件内容

							  ::wcscat((this->sqlPatterns)[MODIFIY_BASIC_INFO], uptodate);
							  ::wcscat(condition, expired);

							  ::wcscat((this->sqlPatterns)[MODIFIY_BASIC_INFO], L"\'");
							  ::wcscat(condition, L"\'");
					}
					else
					{
							  ::wcscat((this->sqlPatterns)[MODIFIY_BASIC_INFO], uptodate);
							  ::wcscat(condition, expired);
					}
					wcscat((this->sqlPatterns)[MODIFIY_BASIC_INFO], condition);
					this->BasicMedicineInfo = (this->sqlPatterns)[MODIFIY_BASIC_INFO];			  //修改BasicInfo指针
					this->instructExecute();	  //执行SQL语句
					memset((this->sqlPatterns)[MODIFIY_BASIC_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (512 - originInfoLength));					//将sqlPatterns恢复初始状态
					delete[]ptemp;
					delete[]condition;
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: 输入的属性列错误" << std::endl;
		  return false;
}
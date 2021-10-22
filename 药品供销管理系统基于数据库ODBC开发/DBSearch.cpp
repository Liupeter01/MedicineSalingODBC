#include"DataBaseOp.h"

/*
*��ѯҩƷ�Ļ�����Ϣ
* @author��LPH
* @Para:
*		  target:��Ҫ���ҵ�����
*		  Find: ��Ҫ���ҵ�����
* Date��2021-10-14
*/
bool DataBaseOp::findMedicineBasicInfo(const wchar_t* target, const wchar_t* Find)	//��ѯҩƷ�Ļ�����Ϣ
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  int ind(0);		  //�����±�
		  for (; ind < 7; ind++) {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != 8)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[SEARCH_BASIC_INFO]);			//������Ϣԭʼ����
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //�ַ���ճ��
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
					this->BasicMedicineInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //�޸�BasicInfoָ��
					this->printBasicInfo();
					memset((this->sqlPatterns)[SEARCH_BASIC_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (256 - originInfoLength));					//��sqlPatterns�ָ���ʼ״̬
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: ����������д���" << std::endl;
		  return false;
}

/*
*��ѯҩƷ�Ĳɹ���Ϣ
* @author��LPH
* * @Para:
*		  target:��Ҫ���ҵ�����
*		  Find: ��Ҫ���ҵ�����
* Date��2021-10-14
*/
bool DataBaseOp::findMedicinePurchaseInfo(const wchar_t* target, const wchar_t* Find)//��ѯҩƷ�Ĳɹ���Ϣ	  
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  int ind(0);		  //�����±�
		  for (; ind < 7; ind++) {
					if (!lstrcmpW(this->QueryPurchaseMedicine[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != 8)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[SEARCH_BUYING_INFO]);			//������Ϣԭʼ����
					::wcscat((this->sqlPatterns)[SEARCH_BUYING_INFO], this->QueryPurchaseMedicine[ind]);	  //�ַ���ճ��
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
					this->PurchaseInfo = (this->sqlPatterns)[SEARCH_BUYING_INFO];			  //�޸�BasicInfoָ��
					this->printPurchaseInfo();
					memset((this->sqlPatterns)[SEARCH_BUYING_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (256 - originInfoLength));					//��sqlPatterns�ָ���ʼ״̬
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: ����������д���" << std::endl;
		  return false;
}

/*
*��ѯҩƷ��������Ϣ
* @author��LPH
* * @Para:
*		  target:��Ҫ���ҵ�����
*		  Find: ��Ҫ���ҵ�����
* Date��2021-10-14
*/
bool DataBaseOp::findMedicineSalingInfo(const wchar_t* target, const wchar_t* Find)	  //��ѯҩƷ��������Ϣ	  
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");

		  int ind(0);		  //�����±�
		  for (; ind < 8; ind++) {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != 9)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[SEARCH_BASIC_INFO]);			//������Ϣԭʼ����
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //�ַ���ճ��
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
					this->BasicMedicineInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //�޸�BasicInfoָ��
					this->printBasicInfo();
					memset((this->sqlPatterns)[SEARCH_BASIC_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (256 - originInfoLength));					//��sqlPatterns�ָ���ʼ״̬
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: ����������д���" << std::endl;
		  return false;
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
#include"DataBaseOp.h"

/*
*�޸���Ʒ�Ļ�����Ϣ
* @author��LPH
* * @Para:
*		  target:��Ҫ���ҵ�����
*		  expired:���ҵľ�����
*		  uptodate:������
* Date��2021-10-25
*/
bool DataBaseOp::modifyMedicineBasicInfo(const wchar_t* target,const wchar_t *expired,const wchar_t *uptodate)		  //�޸�ҩƷ�Ļ�����Ϣ
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  wchar_t* condition(new wchar_t[wcslen(L" WHERE ") + wcslen(ptemp) + wcslen(expired) + 3 * wcslen(L"\'")]);	//��������'��һ��'\0'
		  ::wcscpy(condition, L" WHERE ");
		  ::wcscat(condition, ptemp);
		  int ind(0);		  //�����±�
		  for (; ind < sizeof(this->QueryBasicMedicineInfo) / sizeof(const wchar_t*); ind++) {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))			    break;
		  }
		  if (ind != sizeof(this->QueryBasicMedicineInfo) / sizeof(const wchar_t*) + 1)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[MODIFIY_BASIC_INFO]);			//������Ϣԭʼ����
					::wcscat((this->sqlPatterns)[MODIFIY_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //�ַ���ճ��
					if (ind != 0 && ind != 4)
					{
							  ::wcscat((this->sqlPatterns)[MODIFIY_BASIC_INFO], L"\'");	  //����SET����
							  ::wcscat(condition, L"\'");				  //����WHERE��������

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
					this->BasicMedicineInfo = (this->sqlPatterns)[MODIFIY_BASIC_INFO];			  //�޸�BasicInfoָ��
					this->instructExecute();	  //ִ��SQL���
					memset((this->sqlPatterns)[MODIFIY_BASIC_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (512 - originInfoLength));					//��sqlPatterns�ָ���ʼ״̬
					delete[]ptemp;
					delete[]condition;
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: ����������д���" << std::endl;
		  return false;
}
#include"DataBaseOp.h"

/*
*ɾ��ҩƷ�Ļ�����Ϣ
* @author��LPH
* 		  target:��Ҫɾ��������
*		  Find: ��Ҫɾ��������
* Date��2021-10-25
*/
bool DataBaseOp::deleteMedicineBasicInfo(const wchar_t* target, const wchar_t* deleteitem)
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  int ind(0);		  //�����±�
		  for (; ind < sizeof(this->QueryBasicMedicineInfo) / sizeof(const wchar_t*); ind++) {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != sizeof(this->QueryBasicMedicineInfo) / sizeof(const wchar_t*) + 1)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[DELETE_BASIC_INFO]);			//������Ϣԭʼ����
					::wcscat((this->sqlPatterns)[DELETE_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //�ַ���ճ��
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
					this->BasicMedicineInfo = (this->sqlPatterns)[DELETE_BASIC_INFO];			  //�޸�BasicInfoָ��
					this->BasicDBExecute();
					memset((this->sqlPatterns)[DELETE_BASIC_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (512 - originInfoLength));					//��sqlPatterns�ָ���ʼ״̬
					return true;
		  }
		  std::cout << "[DATABASE SELECT STATUS]: ����������д���" << std::endl;
		  return false;
}
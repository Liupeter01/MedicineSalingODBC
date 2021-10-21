#include "DataBaseOp.h"

/*
* �ڴ���պ���
* @author��LPH
* Date��2021-10-14
*/
template<typename T>
void DataBaseOp::cleanMem(T* memzone, T data, int size)	//�ڴ����
{
		  for (int i = 0; i < size; ++i)
		  {
					*(memzone + i) = data;
		  }
}

/*
*ɾ������ո�
* @author��LPH
* Date��2021-10-14
*/
template<typename T>
void DataBaseOp::eraseSpace(T* str)				  //ɾ������ո�
{
		  T* ptemp = str;
		  while (*ptemp++ != ' ');
		  *ptemp = ((!strcmp(typeid(T*).name(), "wchar_t*")) ? L'\0' : '\0');
}

/*
* ��̬��ȡö�����ڲ�ѯ������
* @author��LPH
* Date��2021-10-13
*/
int DataBaseOp::getInitQuerySize()
{
		  int querysize(0);
		  for (enum sqlquery temp = (enum DataBaseOp::sqlquery)sqlquery::INIT_BASIC_INFO;
					temp != sqlquery::OTHER; temp = (enum DataBaseOp::sqlquery)(temp + 1)){
					querysize++;
		  }
		  return querysize;
}

/*
* ��ʼ��SQL��ѯ���ṹ
* @author��LPH
* Date��2021-10-12
*/
void DataBaseOp::sqlInitQueryParttern()
{
		  this->sqlPatterns = new SQLWCHAR * [this->getInitQuerySize()];			//��̬�����ѯ���Ĵ�С
		  for (int i = 0; i < this->getInitQuerySize(); ++i)
		  {
					(this->sqlPatterns)[i] = new SQLWCHAR[256]{ 0 };
		  }
		  //INIT_BASIC_INFO	¼��ҩƷ������Ϣ
		  //MEDICINE_BUYING	ҩƷ������Ϣ�Ĳɹ�
		  //MEDICINE_SALING	ҩƷ������Ϣ������
		  //DISPLAY_ALL_BASIC_INFO				���ȫ��ҩƷ������Ϣ
		  //SEARCH_BASIC_INFO	��ѯ��������Ϣ
		  wsprintf((this->sqlPatterns)[INIT_BASIC_INFO],L"INSERT INTO MedicineManagmentSys.dbo.MedicineWareBase values(?,?,?,?,?,?,?) ");	//7����
		  wsprintf((this->sqlPatterns)[MEDICINE_BUYING], L"INSERT INTO MedicineManagmentSys.dbo.MedicineBuying values(?,?,?,?,?,?,?) ");	//7����
		  wsprintf((this->sqlPatterns)[MEDICINE_SALING], L"INSERT INTO MedicineManagmentSys.dbo.MedicineSaling values(?,?,?,?,?,?,?,?) ");	//8����
		  wsprintf((this->sqlPatterns)[DISPLAY_ALL_BASIC_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineWareBase");	
		  wsprintf((this->sqlPatterns)[SEARCH_BASIC_INFO], L"SELECT * FROM MedicineManagmentSys.dbo.MedicineWareBase WHERE ");
}

/*
* SQL��ѯ��乹�캯��
* @author��LPH
* @descrition:
* Date��2021-9-16
* Date:   2021-10-12 �������ݿ��ѯ���ṹ�ĳ�ʼ��
*/
DataBaseOp::DataBaseOp()
{
		  this->sqlInitQueryParttern();
}

/*
* STMT���亯��
* @author��LPH
* Date��2021-10-21
*/
void DataBaseOp::AllocateStmt()
{
		  if (this->ConnectionSatus)
		  {
					this->stm1 = new HSTMT;
					SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//����stmt
					try
					{
							  throw  SQLAllocHandle(SQL_HANDLE_STMT, *hdbc, reinterpret_cast<SQLHANDLE*>(&stm1));;
					}
					catch (SQLRETURN retcode)
					{
							  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
							  {
										std::cout << "[DATABASE STATUS]: ���ݿ�������ɹ�" << std::endl;
							  }
							  else
							  {
										std::cout << "[DATABASE STATUS]: ���ݿ�������ʧ��" << std::endl;
							  }
					}
		  }
}

/*
* STMT�ͷź���
* @author��LPH
* Date��2021-10-21
*/
void DataBaseOp::ReleaseStmt()
{
		  try
		  {
					throw SQLFreeHandle(SQL_HANDLE_STMT, reinterpret_cast<SQLHANDLE>(stm1));
		  }
		  catch (SQLRETURN retcode)
		  {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
							  std::cout << "[DATABASE STATUS]: ���ݿ����ͷųɹ�" << std::endl;
					else
							  std::cout << "[DATABASE STATUS]: ���ݿ����ͷ�ʧ��" << std::endl;
		  }
		  if (stm1 != nullptr)
		  {
					SQLFreeStmt(stm1, SQL_DROP);			//�ͷ�stmt
		  }
}



/*
* SQL��ѯ�����������
* @author��LPH
* Date��2021-9-16
* Date:   2021-10-12
		  1���޸�ָ������ü���ƥ�������
		  2������SQL��ѯ���û�б��ͷ��ڴ�ռ������
*/
DataBaseOp::~DataBaseOp()
{
		  if (this->ConnectionSatus)
		  {
					for (int i = 0; i < this->getInitQuerySize(); ++i)
					{
							  delete  (this->sqlPatterns)[i];
					}
					delete []this->sqlPatterns;		//�ͷ�SQL��ѯ���
		  }
}

/*
*¼����Ʒ�Ļ�����Ϣ
* @author��LPH
* Date��2021-9-21
*/
void DataBaseOp::initMedicineBasicInfo()
{
		  int MedicineId(0);
		  wchar_t MedicineName[256] = { 0 };
		  wchar_t MedicineType[256] = { 0 };
		  wchar_t Manufacture[256] = { 0 };
		  float MedicinePrice(0.0f);
		  wchar_t MedicineValidateDate[256] = { 0 };
		  wchar_t AdditionInfo[256] = { 0 };
		  std::cout << "MedicineID:";
		  std::cin >> MedicineId;
		  std::cout << "MedicineName:";
		  std::wcin >> MedicineName;
		  std::cout << "MedicineType:";
		  std::wcin >> MedicineType;
		  std::cout << "Manufacture:";
		  std::wcin >> Manufacture;
		  std::cout << "MedicinePrice:";
		  std::cin >> MedicinePrice;
		  std::cout << "MedicineValidateDate:";
		  std::wcin >> MedicineValidateDate;
		  std::cout << "AdditionInfo:";
		  std::wcin.getline(AdditionInfo, 256);
		  std::wcin.get();

		  //std::regex					�������ڽ��������ж�
		  try
		  {
					throw SQLPrepareW(reinterpret_cast<SQLHSTMT>(stm1), (this->sqlPatterns)[INIT_BASIC_INFO], SQL_NTS);
		  }
		  catch (SQLRETURN retcode)
		  {
					if(retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN strLength = SQL_NTS;
							  //��SQL���Ĳ���
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&MedicineId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName, wcslen(MedicineName), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)MedicineType, wcslen(MedicineType), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)Manufacture, wcslen(Manufacture), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT,  SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&MedicinePrice, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)MedicineValidateDate, wcslen(MedicineValidateDate), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)AdditionInfo, wcslen(AdditionInfo), &strLength);
							  try
							  {
										throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
							  }
							  catch (SQLRETURN retcode)
							  {
										if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE INSERT STATUS]: ������Ϣ��������ɹ�" << std::endl;
										else
										{
												  std::cout << "[DATABASE INSERT STATUS]: ������Ϣ�������ʧ��" << std::endl;
												  this->sqlErrorMsg();
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: ���ݿ�����󶨲���ʧ��" << std::endl;
					}
		  }
}

/*
*¼��ҩƷ�ɹ���Ϣ
* @author��LPH
* Date��2021-10-14
*/
void DataBaseOp::initMedicinePurchase()	//��ʼ��ҩƷ�ɹ���Ϣ
{
		  try
		  {
					throw SQLPrepareW(reinterpret_cast<SQLHSTMT>(stm1), (this->sqlPatterns)[MEDICINE_BUYING], SQL_NTS);
		  }
		  catch (SQLRETURN retcode)
		  {
					int OrderId(0);
					int MedicineId(0);
					int TransactAmmount(0);
					float pricetotal(0.0);
					wchar_t MedicineName[256] = { 0 };
					wchar_t TransActionDate[256] = { 0 };
					wchar_t OperatorName[256] = { 0 };
					std::cout << "BuyingOrderId:";
					std::cin >> OrderId;
					std::cout << "MedicineID:";
					std::cin >> MedicineId;
					std::cout << "MedicineName:";
					std::wcin >> MedicineName;
					std::cout << "TransactAmmount:";
					std::cin >> TransactAmmount;
					std::cout << "TransActionDate:";
					std::wcin >> TransActionDate;
					std::cout << "OperatorName:";
					std::wcin.getline(OperatorName, 256);
					std::wcin.get();

					//std::regex					�������ڽ��������ж�

					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN strLength = SQL_NTS;
							  //��SQL���Ĳ���
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&OrderId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&MedicineId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName, wcslen(MedicineName), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&TransactAmmount, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&pricetotal, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)TransActionDate, wcslen(TransActionDate), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)OperatorName, wcslen(OperatorName), &strLength);
							  try
							  {
										throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
							  }
							  catch (SQLRETURN retcode)
							  {
										if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE INSERT STATUS]: �ɹ����������ɹ�" << std::endl;
										else
										{
												  std::cout << "[DATABASE INSERT STATUS]: �ɹ���������ʧ��" << std::endl;
												  this->sqlErrorMsg();
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: ���ݿ�����󶨲���ʧ��" << std::endl;
					}
		  }
}

/*
*¼��ҩƷ������Ϣ
* @author��LPH
* Date��2021-10-14
*/
void DataBaseOp::initMedicineSaling()	    //��ʼ��ҩƷ������Ϣ
{
		  this->AllocateStmt();
		  try
		  {
					throw SQLPrepareW(reinterpret_cast<SQLHSTMT>(stm1), (this->sqlPatterns)[MEDICINE_SALING], SQL_NTS);
		  }
		  catch (SQLRETURN retcode)
		  {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  int OrderId(0);
							  int MedicineId(0);
							  int TransactAmmount(0);
							  float MedicinePrice(0.0);
							  wchar_t MedicineName[256] = { 0 };
							  wchar_t TransActionDate[256] = { 0 };
							  wchar_t BuyerName[256] = { 0 };
							  std::cout << "SalingOrderId:";
							  std::cin >> OrderId;
							  std::cout << "MedicineID:";
							  std::cin >> MedicineId;
							  std::cout << "MedicineName:";
							  std::wcin >> MedicineName;
							  std::cout << "MedicinePrice:";
							  std::cin >> MedicinePrice;
							  std::cout << "TransactAmmount:";
							  std::cin >> TransactAmmount;
							  std::cout << "TransActionDate:";
							  std::wcin >> TransActionDate;
							  std::cout << "BuyerName:";
							  std::wcin.getline(BuyerName, 256);
							  std::wcin.get();
							  float pricetotal(TransactAmmount * MedicinePrice);

							  //std::regex					�������ڽ��������ж�

							  SQLLEN strLength = SQL_NTS;
							  //��SQL���Ĳ���
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&OrderId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&MedicineId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName, wcslen(MedicineName), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&MedicinePrice, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&TransactAmmount, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&pricetotal, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)TransActionDate, wcslen(TransActionDate), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 8, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)BuyerName, wcslen(BuyerName), &strLength);
							  try
							  {
										throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
							  }
							  catch (SQLRETURN retcode)
							  {
										if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE INSERT STATUS]: ���۱��������ɹ�" << std::endl;
										else
										{
												  std::cout << "[DATABASE INSERT STATUS]: ���۱�������ʧ��" << std::endl;
												  this->sqlErrorMsg();
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: ���ݿ�����󶨲���ʧ��" << std::endl;
					}
		  }
		  this->ReleaseStmt();
}

/*
*���ȫ��������Ϣ�Ӻ���
* @author��LPH
* Date��2021-10-14
*/
void DataBaseOp::printBasicInfo()
{
		  this->AllocateStmt();
		  try
		  {
					throw SQLExecDirectW(stm1, this->basicInfo, SQL_NTS);
		  }
		  catch (SQLRETURN retcode)
		  {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN sqlLength = SQL_NTS;
							  int MedicineId(0);
							  wchar_t MedicineName[256] = { 0 };
							  wchar_t MedicineType[256] = { 0 };
							  wchar_t Manufacture[256] = { 0 };
							  float MedicinePrice(0.0f);
							  wchar_t MedicineValidateDate[256] = { 0 };
							  wchar_t AdditionInfo[256] = { 0 };
							  int size[] = { 0,0,0,0,0 };
							  std::vector<wchar_t*>infoaddr{ MedicineName,MedicineType,Manufacture,MedicineValidateDate,AdditionInfo };
							  SQLBindCol(stm1, 1, SQL_C_LONG, &MedicineId, sizeof(MedicineId), 0);
							  SQLBindCol(stm1, 2, SQL_C_WCHAR, MedicineName, sizeof(MedicineName), &sqlLength);
							  SQLBindCol(stm1, 3, SQL_C_WCHAR, MedicineType, sizeof(MedicineType), &sqlLength);
							  SQLBindCol(stm1, 4, SQL_C_WCHAR, Manufacture, sizeof(Manufacture), &sqlLength);
							  SQLBindCol(stm1, 5, SQL_C_FLOAT, &MedicinePrice, sizeof(MedicinePrice), 0);
							  SQLBindCol(stm1, 6, SQL_C_WCHAR, MedicineValidateDate, sizeof(MedicineValidateDate), &sqlLength);
							  SQLBindCol(stm1, 7, SQL_C_WCHAR, AdditionInfo, sizeof(AdditionInfo), &sqlLength);
							  SQLRETURN ret(0);
							  while ((ret = SQLFetch(stm1)) != SQL_NO_DATA)
							  {
										eraseSpace<wchar_t>(MedicineName);
										eraseSpace<wchar_t>(MedicineType);
										eraseSpace<wchar_t>(Manufacture);
										eraseSpace<wchar_t>(MedicineValidateDate);
										eraseSpace<wchar_t>(AdditionInfo);
										std::wcout << MedicineId << " " << MedicineName << " " <<
												  MedicineType << " " << Manufacture << " " << MedicinePrice << " " <<
												  MedicineValidateDate << " " << AdditionInfo << " " << std::endl;

										for (auto ib = infoaddr.cbegin(); ib != infoaddr.cend(); ib++)
										{
												  cleanMem<wchar_t>(*ib, 0, 256);
										}
										MedicinePrice = 0.0f;
										MedicineId = 0;
							  }
							  SQLLEN rowcount(0);
							  try
							  {
										throw SQLRowCount(stm1, &rowcount);
							  }
							  catch (SQLRETURN ret)
							  {
										if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
										{
												  std::cout << "[DATABASE SELECT STATUS]: ��ѯ" << rowcount << "�����ݳɹ�!" << std::endl;
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE SELECT STATUS]: ���ݿ������Ϣ��ѯʧ��" << std::endl;
							  this->sqlErrorMsg();
					}
		  }
		  this->ReleaseStmt();
}

/*
*��ѯҩƷ�Ļ�����Ϣ
* @author��LPH
* @Para:
*		  target:��Ҫ���ҵ�����
*		  Find: ��Ҫ���ҵ�����
* Date��2021-10-14
*/
bool DataBaseOp::findMedicineBasicInfo(const wchar_t*target,const wchar_t *Find)	//��ѯҩƷ�Ļ�����Ϣ
{
		  wchar_t* ptemp(new wchar_t[wcslen(target) + wcslen(L" = ") + 1]);
		  wcscpy(ptemp, target);
		  wcscat(ptemp, L" = ");
		  int ind(0);		  //�����±�
		  for (; ind < 7; ind++)
		  {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))
					{
							  delete[]ptemp;
							  break;
					}
		  }
		  if (ind != 7)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[SEARCH_BASIC_INFO]);			//������Ϣԭʼ����
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], this->QueryBasicMedicineInfo[ind]);	  //�ַ���ճ��
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], L"\'");
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
					::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], L"\'");
					this->basicInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //�޸�BasicInfoָ��
					wprintf(L"%s", this->basicInfo);
					this->printBasicInfo();
					memset((this->sqlPatterns)[SEARCH_BASIC_INFO] + originInfoLength,
							  L'\0', sizeof(wchar_t) * (256 - originInfoLength ));
					return true;
		  }
		  else
		  {
					std::cout << "[DATABASE SELECT STATUS]: ����������д���" << std::endl;
					delete[]ptemp;
		  }
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
		  const wchar_t* basic_types[]
		  {
					L"BuyingOrderNumber = ",L"MedicineId = ",L"MedicineName = ",
					L"TransActionAmmount = ",L"PriceInTotal = ",
					L"TransActionDate = ",L"OperatorName = "
		  };
		  int ind(0);		  //�����±�
		  for (; ind < 7; ind++)
		  {
					if (!lstrcmpW(basic_types[ind], target))		   break;
		  }
		  //if (ind != 7)
		  //{
				//	::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], basic_types[ind]);	  //�ַ���ճ��
				//	::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
				//	this->printInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //�޸�BasicInfoָ��
				//	this->printBasicInfo();
		  //}
		  //else
		  //{
				//	std::cout << "[DATABASE SELECT STATUS]: ����������д���" << std::endl;
		  //}
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
bool DataBaseOp::findMedicineSalingInfo(const wchar_t*, const wchar_t*)	  //��ѯҩƷ��������Ϣ	  
{
		  //const wchar_t* basic_types[]
		  //{
				//	L"MedicineId = ",L"MedicineName = ",
				//	L"MedicineType = ",L"Manufacture = ",
				//	L"MedicinePrice = ",L"MedicineValidateDate = ",
				//	L"AdditionInfo = "
		  //};
		  //int ind(0);		  //�����±�
		  //for (; ind < 7; ind++)
		  //{
				//	if (!lstrcmpW(basic_types[ind], target))		   break;
		  //}
		  //if (ind != 7)
		  //{
				//	::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], basic_types[ind]);	  //�ַ���ճ��
				//	::wcscat((this->sqlPatterns)[SEARCH_BASIC_INFO], Find);
				//	this->printInfo = (this->sqlPatterns)[SEARCH_BASIC_INFO];			  //�޸�BasicInfoָ��
				//	this->printBasicInfo();
		  //}
		  //else
		  //{
				//	std::cout << "[DATABASE SELECT STATUS]: ����������д���" << std::endl;
		  //}
		  return false;
}
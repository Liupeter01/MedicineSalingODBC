#include"DataBaseOp.h"

/*
*输出基本信息子函数
* @author：LPH
* Date：2021-10-14
*/
void DataBaseOp::printBasicInfo()
{
		  this->AllocateStmt();
		  try {
					throw SQLExecDirectW(stm1, this->BasicMedicineInfo, SQL_NTS);
		  }
		  catch (SQLRETURN retcode) {
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
							 // int size[] = { 0,0,0,0,0 };
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
										this->eraseSpace<wchar_t>(MedicineName);
										this->eraseSpace<wchar_t>(MedicineType);
										this->eraseSpace<wchar_t>(Manufacture);
										this->eraseSpace<wchar_t>(MedicineValidateDate);
										this->eraseSpace<wchar_t>(AdditionInfo);
										std::wcout << MedicineId << L" " << MedicineName << L" " <<
												  MedicineType << L" " << Manufacture << L" " << MedicinePrice << L" " <<
												  MedicineValidateDate << L" " << AdditionInfo << L" " << std::endl;

										for (auto ib = infoaddr.cbegin(); ib != infoaddr.cend(); ib++)
										{
												  cleanMem<wchar_t>(*ib, 0, 256);
										}
										MedicinePrice = 0.0f;
										MedicineId = 0;
							  }
							  SQLLEN rowcount(0);
							  try {
										throw SQLRowCount(stm1, &rowcount);
							  }
							  catch (SQLRETURN ret) {
										if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE SELECT STATUS]: 查询" << rowcount << "行数据成功!" << std::endl;
							  }
					}
					else
					{
							  std::cout << "[DATABASE SELECT STATUS]: 数据库基本信息查询失败" << std::endl;
							  this->sqlErrorMsg();
					}
		  }
		  this->ReleaseStmt();
}

/*
*输出采购信息子函数
* @author：LPH
* Date：2021-10-22
*/
void DataBaseOp::printPurchaseInfo()
{
		  this->AllocateStmt();
		  try {
					throw SQLExecDirectW(stm1, this->PurchaseInfo, SQL_NTS);
		  }
		  catch (SQLRETURN retcode) {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN sqlLength = SQL_NTS;
							  int OrderNumber(0);
							  int MedicineId(0);
							  wchar_t MedicineName[256] = { 0 };
							  int TransactionAmmount(0);
							  float PriceInTotal(0.0f);
							  wchar_t TransactionDate[256] = { 0 };
							  wchar_t OperatorName[256] = { 0 };
							  std::vector<wchar_t*>infoaddr{ MedicineName,TransactionDate,OperatorName };
							  SQLBindCol(stm1, 1, SQL_C_LONG, &OrderNumber, sizeof(OrderNumber), 0);
							  SQLBindCol(stm1, 2, SQL_C_LONG, &MedicineId, sizeof(MedicineId), 0);
							  SQLBindCol(stm1, 3, SQL_C_WCHAR, MedicineName, sizeof(MedicineName), &sqlLength);
							  SQLBindCol(stm1, 4, SQL_C_LONG, &TransactionAmmount, sizeof(TransactionAmmount), 0);
							  SQLBindCol(stm1, 5, SQL_C_FLOAT, &PriceInTotal, sizeof(PriceInTotal), 0);
							  SQLBindCol(stm1, 6, SQL_C_WCHAR, TransactionDate, sizeof(TransactionDate), &sqlLength);
							  SQLBindCol(stm1, 7, SQL_C_WCHAR, OperatorName, sizeof(OperatorName), &sqlLength);
							  SQLRETURN ret(0);
							  while ((ret = SQLFetch(stm1)) != SQL_NO_DATA)
							  {
										this->eraseSpace<wchar_t>(MedicineName);
										this->eraseSpace<wchar_t>(TransactionDate);
										this->eraseSpace<wchar_t>(OperatorName);
										std::wcout << OrderNumber << L" " << MedicineId << L" " <<
												 MedicineName << L" " << TransactionAmmount << L" " << PriceInTotal << L" " <<
												  TransactionDate << L" " << OperatorName << L" " << std::endl;

										for (auto ib = infoaddr.cbegin(); ib != infoaddr.cend(); ib++)
										{
												  cleanMem<wchar_t>(*ib, 0, 256);
										}
										OrderNumber =0;
										MedicineId = 0;
										TransactionAmmount = 0;
										PriceInTotal = 0.0f;
							  }
							  SQLLEN rowcount(0);
							  try {
										throw SQLRowCount(stm1, &rowcount);
							  }
							  catch (SQLRETURN ret) {
										if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE SELECT STATUS]: 查询" << rowcount << "行数据成功!" << std::endl;
							  }
					}
					else
					{
							  std::cout << "[DATABASE SELECT STATUS]: 数据库基本信息查询失败" << std::endl;
							  this->sqlErrorMsg();
					}
		  }
		  this->ReleaseStmt();
}

/*
*输出销售信息子函数
* @author：LPH
* Date：2021-10-22
*/
void DataBaseOp::printSalingInfo()
{
		  this->AllocateStmt();
		  try {
					throw SQLExecDirectW(stm1, this->SalingInfo, SQL_NTS);
		  }
		  catch (SQLRETURN retcode) {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN sqlLength = SQL_NTS;
							  int OrderNumber(0);
							  int MedicineId(0);
							  wchar_t MedicineName[256] = { 0 };
							  float MedicinePrice(0.0f);
							  int TransactionAmmount(0);
							  float PriceInTotal(0.0f);
							  wchar_t TransactionDate[256] = { 0 };
							  wchar_t BuyerName[256] = { 0 };
							  std::vector<wchar_t*>infoaddr{ MedicineName,TransactionDate,BuyerName };
							  SQLBindCol(stm1, 1, SQL_C_LONG, &OrderNumber, sizeof(OrderNumber), 0);
							  SQLBindCol(stm1, 2, SQL_C_LONG, &MedicineId, sizeof(MedicineId), 0);
							  SQLBindCol(stm1, 3, SQL_C_WCHAR, MedicineName, sizeof(MedicineName), &sqlLength);
							  SQLBindCol(stm1, 4, SQL_C_FLOAT, &MedicinePrice, sizeof(MedicinePrice), 0);
							  SQLBindCol(stm1, 5, SQL_C_LONG, &TransactionAmmount, sizeof(TransactionAmmount), 0);
							  SQLBindCol(stm1, 6, SQL_C_FLOAT, &PriceInTotal, sizeof(PriceInTotal), 0);
							  SQLBindCol(stm1, 7, SQL_C_WCHAR, TransactionDate, sizeof(TransactionDate), &sqlLength);
							  SQLBindCol(stm1, 8, SQL_C_WCHAR, BuyerName, sizeof(BuyerName), &sqlLength);
							  SQLRETURN ret(0);
							  while ((ret = SQLFetch(stm1)) != SQL_NO_DATA)
							  {
										this->eraseSpace<wchar_t>(MedicineName);
										this->eraseSpace<wchar_t>(TransactionDate);
										this->eraseSpace<wchar_t>(BuyerName);
										std::wcout << OrderNumber << L" " << MedicineId << L" " <<
												  MedicineName << L" " << TransactionAmmount << L" " << PriceInTotal << L" " <<
												  TransactionDate << L" " << BuyerName << L" " << std::endl;

										for (auto ib = infoaddr.cbegin(); ib != infoaddr.cend(); ib++)
										{
												  cleanMem<wchar_t>(*ib, 0, 256);
										}
										int OrderNumber = 0;
										int MedicineId = 0;
										float MedicinePrice = 0.0f;
										int TransactionAmmount = 0;
										float PriceInTotal = 0.0f;
							  }
							  SQLLEN rowcount(0);
							  try {
										throw SQLRowCount(stm1, &rowcount);
							  }
							  catch (SQLRETURN ret) {
										if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE SELECT STATUS]: 查询" << rowcount << "行数据成功!" << std::endl;
							  }
					}
					else
					{
							  std::cout << "[DATABASE SELECT STATUS]: 数据库基本信息查询失败" << std::endl;
							  this->sqlErrorMsg();
					}
		  }
		  this->ReleaseStmt();
}

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
		  for (; ind < sizeof(this->QueryBasicMedicineInfo)/sizeof(const wchar_t*); ind++) {
					if (!lstrcmpW(this->QueryBasicMedicineInfo[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != sizeof(this->QueryBasicMedicineInfo) / sizeof(const wchar_t*)+1)
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
					memset((this->sqlPatterns)[SEARCH_BASIC_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (512 - originInfoLength));					//将sqlPatterns恢复初始状态
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
		  for (; ind < sizeof(this->QueryPurchaseMedicine)/sizeof(const wchar_t*); ind++) {
					if (!lstrcmpW(this->QueryPurchaseMedicine[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != sizeof(this->QueryPurchaseMedicine) / sizeof(const wchar_t*)+1)
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
					memset((this->sqlPatterns)[SEARCH_BUYING_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (512 - originInfoLength));					//将sqlPatterns恢复初始状态
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
		  for (; ind < sizeof(this->QuerySalingMedicine) / sizeof(const wchar_t*); ind++)  {
					if (!lstrcmpW(this->QuerySalingMedicine[ind], ptemp))			    break;
		  }
		  delete[]ptemp;
		  if (ind != sizeof(this->QuerySalingMedicine) / sizeof(const wchar_t*) + 1)
		  {
					int originInfoLength = (int)wcslen((this->sqlPatterns)[SEARCH_SALING_INFO]);			//备份信息原始长度
					::wcscat((this->sqlPatterns)[SEARCH_SALING_INFO], this->QuerySalingMedicine[ind]);	  //字符串粘结
					if (ind > 2 && ind != 4 && ind != 5)
					{
							  ::wcscat((this->sqlPatterns)[SEARCH_SALING_INFO], L"\'");
							  ::wcscat((this->sqlPatterns)[SEARCH_SALING_INFO], Find);
							  ::wcscat((this->sqlPatterns)[SEARCH_SALING_INFO], L"\'");
					}
					else
					{
							  ::wcscat((this->sqlPatterns)[SEARCH_SALING_INFO], Find);
					}
					this->SalingInfo = (this->sqlPatterns)[SEARCH_SALING_INFO];			  //修改BasicInfo指针
					this->printSalingInfo();
					memset((this->sqlPatterns)[SEARCH_SALING_INFO] + originInfoLength, L'\0', sizeof(wchar_t) * (512 - originInfoLength));					//将sqlPatterns恢复初始状态
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
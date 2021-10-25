#include"DataBaseOp.h"

/*
*录入商品的基本信息
* @author：LPH
* Date：2021-9-21
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

		  //std::regex					对于日期进行正则判断
		  this->AllocateStmt();
		  try {
					throw SQLPrepareW(reinterpret_cast<SQLHSTMT>(stm1), (this->sqlPatterns)[INIT_BASIC_INFO], SQL_NTS);
		  }
		  catch (SQLRETURN retcode) {
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN strLength = SQL_NTS;
							  //绑定SQL语句的参数
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&MedicineId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName, wcslen(MedicineName), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)MedicineType, wcslen(MedicineType), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)Manufacture, wcslen(Manufacture), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&MedicinePrice, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)MedicineValidateDate, wcslen(MedicineValidateDate), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)AdditionInfo, wcslen(AdditionInfo), &strLength);
							  try
							  {
										throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
							  }
							  catch (SQLRETURN retcode)
							  {
										if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE INSERT STATUS]: 基本信息插入操作成功" << std::endl;
										else
										{
												  std::cout << "[DATABASE INSERT STATUS]: 基本信息插入操作失败" << std::endl;
												  this->sqlErrorMsg();
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: 数据库参数绑定操作失败" << std::endl;
					}
		  }
		  this->ReleaseStmt();
}

/*
*录入药品销售信息
* @author：LPH
* Date：2021-10-14
*/
void DataBaseOp::initMedicineSaling()	    //初始化药品销售信息
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

							  //std::regex					对于日期进行正则判断

							  SQLLEN strLength = SQL_NTS;
							  //绑定SQL语句的参数
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&OrderId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&MedicineId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName, wcslen(MedicineName), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&MedicinePrice, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&TransactAmmount, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&pricetotal, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)TransActionDate, wcslen(TransActionDate), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 8, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)BuyerName, wcslen(BuyerName), &strLength);
							  try {
										throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
							  }
							  catch (SQLRETURN retcode) {
										if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE INSERT STATUS]: 销售表插入操作成功" << std::endl;
										else
										{
												  std::cout << "[DATABASE INSERT STATUS]: 销售表插入操作失败" << std::endl;
												  this->sqlErrorMsg();
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: 数据库参数绑定操作失败" << std::endl;
					}
		  }
		  this->ReleaseStmt();
}

/*
*录入药品采购信息
* @author：LPH
* Date：2021-10-14
*/
void DataBaseOp::initMedicinePurchase()	//初始化药品采购信息
{
		  this->AllocateStmt();
		  try {
					throw SQLPrepareW(reinterpret_cast<SQLHSTMT>(stm1), (this->sqlPatterns)[MEDICINE_BUYING], SQL_NTS);
		  }
		  catch (SQLRETURN retcode) {
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

					//std::regex					对于日期进行正则判断

					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
							  SQLLEN strLength = SQL_NTS;
							  //绑定SQL语句的参数
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&OrderId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&MedicineId, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)MedicineName, wcslen(MedicineName), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 100, 0, (SQLPOINTER)&TransactAmmount, sizeof(int), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 8, 0, (SQLPOINTER)&pricetotal, sizeof(float), NULL);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 6, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)TransActionDate, wcslen(TransActionDate), &strLength);
							  ::SQLBindParameter(reinterpret_cast<SQLHSTMT>(stm1), 7, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLPOINTER)OperatorName, wcslen(OperatorName), &strLength);
							  try {
										throw SQLExecute(reinterpret_cast<SQLHSTMT>(stm1));
							  }
							  catch (SQLRETURN retcode) {
										if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
												  std::cout << "[DATABASE INSERT STATUS]: 采购表插入操作成功" << std::endl;
										else
										{
												  std::cout << "[DATABASE INSERT STATUS]: 采购表插入操作失败" << std::endl;
												  this->sqlErrorMsg();
										}
							  }
					}
					else
					{
							  std::cout << "[DATABASE PARAMETER BIND STATUS]: 数据库参数绑定操作失败" << std::endl;
					}
		  }
		  this->ReleaseStmt();
}
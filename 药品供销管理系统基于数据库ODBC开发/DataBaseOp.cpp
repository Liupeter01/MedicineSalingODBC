#include "DataBaseOp.h"

/*
* 初始化SQL查询语句结构
* @author：LPH
* Date：2021-10-12
*/
void DataBaseOp::SQLInitQueryParttern()
{
		  this->sqlPatterns = new SQLCHAR * [30];
		  (this->sqlPatterns)[INIT_BASIC_INFO] = new SQLCHAR[256]{ 0 };
}

/*
* SQL查询语句构造函数
* @author：LPH
* @descrition:
* Date：2021-9-16
* Date:   2021-10-12 增加数据库查询语句结构的初始化
*/
DataBaseOp::DataBaseOp()
{
		  if (this->ConnectionSatus)
		  {
					this->stm1 = new HSTMT;
					SQLAllocStmt(static_cast<SQLHDBC>(*(this->hdbc)), stm1);	//生成stmt
					SQLInitQueryParttern();
		  }
}

/*
* SQL查询语句析构函数
* @author：LPH
* Date：2021-9-16
* Date:   2021-10-12
		  1、修复指针的引用级别不匹配的问题
		  2、增加SQL查询语句没有被释放内存空间的问题
*/
DataBaseOp::~DataBaseOp()
{
		  if (this->ConnectionSatus)
		  {
					for (int i = 0; i < 30; ++i)
					{
							  delete  (this->sqlPatterns)[i];
					}
					delete this->sqlPatterns;		//释放SQL查询语句
					if (stm1 != nullptr)
					{
							  SQLFreeStmt(stm1, SQL_DROP);			//释放stmt
							  delete stm1;
					}
		  }
}

void DataBaseOp::menu()
{
		  if (this->ConnectionSatus)
		  {
					this->initMedcineBasicInfo();
		  }
}

/*
*录入商品的基本信息
* @author：LPH
* Date：2021-9-21
*/
void DataBaseOp::initMedcineBasicInfo()
{
		  int MedicineId(0);
		  std::string MedicineName{ 0 };
		  std::string MedicineType{ 0 };
		  std::string Manufacture{ 0 };
		  float MedicinePrice(0.0f);
		  std::string MedicineValidateDate{ 0 };
		  std::string AdditionInfo{ 0 }; 
		  std::cout << "MedicineID:";
		  std::cin >> MedicineId;
		  std::cout << "MedicineName:";
		  std::cin >> MedicineName;
		  std::cout << "MedicineType:";
		  std::cin >> MedicineType;
		  std::cout << "Manufacture:";
		  std::cin >> Manufacture;
		  std::cout << "MedicinePrice:";
		  std::cin >> MedicinePrice;
		  std::cout << "MedicineValidateDate:";
		  std::cin >> MedicineValidateDate;
		  std::cout << "AdditionInfo:";
		  std::cin >> AdditionInfo;
		  sprintf(reinterpret_cast<char*>((this->sqlPatterns)[INIT_BASIC_INFO]),
					"INSERT INTO MedicineWareBase values(%d,\'%s\',\'%s\',\'%s\',%f,\'%s\',\'%s\'"
										, MedicineId, MedicineName.c_str(),MedicineType.c_str(),
					Manufacture.c_str(), MedicinePrice, MedicineValidateDate.c_str(), AdditionInfo.c_str());
		  RETCODE retcode = SQLExecDirectA(stm1, (this->sqlPatterns)[INIT_BASIC_INFO], SQL_NTS);
}


#include"Connection.h"
#include"DataBaseOp.h"

int main()
{
		  std::string dsn;
		  std::string uid;
		  std::string authstr;
		  std::cout << "dsn:";
		  std::cin >> dsn;
		  std::cout << "uid:";
		  std::cin >> uid;
		  std::cout << "authstr:";
		  std::cin >> authstr;
		  DataBaseConnect::Connection m_connect(dsn, uid, authstr);
		  DataBaseOp dbop;
		  
		  return 0;
}
/*
* ���ݿ�����ģ��
* @author��LPH
* Date��2021-9-15
*/
#pragma once
#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<locale>
#include<regex>

/*����C����ODBC��ͷ�ļ�*/
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdlib.h>
#include <sal.h>
#pragma comment(lib,"odbc32.lib")
#pragma warning(disable:6386)

/*
*�����޸���SQLConnect�������ݿ����ӷ���ֵ=-2   -------  OK
*/
namespace DataBaseConnect
{
		  class Connection
		  {
		  public:
					Connection();
					~Connection();
		  public:
					void DataBaseInit() = delete;		  //�Ѿ����������ݿ�ĳ�ʼ������
		  protected:
					/*������Ա������*/
					HDBC* hdbc;
					bool ConnectionSatus = false;
		  private:
					/*˽�г�Ա������*/
					RETCODE dataBaseOpenConnection();
					void dataBaseCloseConnection();
		  private:
					/*˽�г�Ա������*/
					HENV *henv;
					SQLWCHAR* szdsninfo = nullptr;			//��������
					SQLWCHAR* uid = nullptr;						//����UID
					SQLWCHAR* szauthstr = nullptr;			//������֤
		  };
}
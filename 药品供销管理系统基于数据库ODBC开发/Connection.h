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

/*����C����ODBC��ͷ�ļ�*/
extern "C"
{
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdlib.h>
#include <sal.h>
}

namespace DataBaseConnect
{
		  class Connection
		  {
		  public:
					Connection() = default;
					Connection(std::string m_szdsninfo, std::string m_uid, std::string m_szauthstr);
					~Connection();
		  public:
					void DataBaseInit() = delete;		  //�Ѿ����������ݿ�ĳ�ʼ������
		  protected:
					/*������Ա������*/
					HDBC* hdbc;
		  private:
					/*˽�г�Ա������*/
					RETCODE dataBaseOpenConnection();
					void dataBaseCloseConnection();
		  private:
					/*˽�г�Ա������*/
					HENV *henv;
					SQLCHAR* szdsninfo;			//��������
					SQLCHAR* uid;						//����UID
					SQLCHAR* szauthstr;			//������֤
		  };
}


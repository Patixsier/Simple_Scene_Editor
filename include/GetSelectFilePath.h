//************************************
// Method:          GetSelectFilePath
// Access:          public 
// Returns:         string
// CreateTime:      December 18, 2020
// Author:          Patixsier
// Describe:        �����ļ���Դ����������ȡѡ���ļ�(��)·��
//************************************
#pragma once
#pragma comment(lib, "Comdlg32.lib")

#include <windows.h>
#include <ShlObj.h>
#include <stdio.h>
#include <stdlib.h>
#include <atlstr.h>
#include <string>
#include <iostream>

// string ת��Ϊ·�����õ� char*
char* String2FilePath(std::string src)
{
	char* dst = new char[255];
	int i;
	for (i = 0; i <= src.length(); i++)
		dst[i] = src[i];
	dst[i] = '\0';
	return dst;
}

// �����ļ���Դ����������ȡѡ���ļ�·��
std::string GetSelectFilePath_string()
{
	std::string FilePath = "";
	CString path;
	OPENFILENAME open;// �����Ի���ṹ��
	char file[MAX_PATH];// ���������ȡ�ļ����ƵĻ������� 
	ZeroMemory(&open, sizeof(OPENFILENAME)); // ��ʼ��ѡ���ļ��Ի���
	open.lStructSize = sizeof(OPENFILENAME);//ָ������ṹ�Ĵ�С�����ֽ�Ϊ��λ��
	open.lpstrFile = file;//�򿪵��ļ���ȫ·��
	open.lpstrFile[0] = '\0'; //��һ���ַ����ǹ�������������ʾ�ַ���
	open.nMaxFile = MAX_PATH;  //ָ��lpstrFile����Ĵ�С����TCHARsΪ��λ
	open.lpstrFilter = "�����ļ�(*.*)\0*.*\0\0";  //���ļ�����
	open.nFilterIndex = 1;  //ָ�����ļ����Ϳؼ��е�ǰѡ��Ĺ�����������
	open.lpstrFileTitle = NULL; // ָ�����ѡ����ļ����ļ�������չ���Ļ��壨����·����Ϣ���������Ա������NULL��
	open.nMaxFileTitle = 0;  //ָ��lpstrFileTitle����Ĵ�С����TCHARsΪ��λ
	open.lpstrInitialDir = NULL;  //ָ���Կ��ַ��������ַ���������������ַ�����ָ����ʼĿ¼��
	open.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;//λ��ǵ����ã������ʹ������ʼ���Ի���
	//GetOpenFileName (&open) ;//���ļ��Ի���
	//GetSaveFileName(&open);//�����ļ��Ի���
	if (GetOpenFileName(&open))  // ��ʾ��ѡ���ļ��Ի���  
		path = file;
	else {
		std::cout << "û��ѡ���ļ���\n\n";
		return FilePath;
	}
	FilePath = path.GetBuffer(0);
	return FilePath;
}

// �����ļ���Դ����������ȡѡ���ļ�·��
char* GetSelectFilePath() {
	char* path = String2FilePath(GetSelectFilePath_string());
	return path;
}

// �����ļ���Դ����������ȡѡ���ļ���·��
std::string GetSelectFolderPath_string()
{
	std::string FolderPath = "";

	TCHAR           szFolderPath[MAX_PATH] = { 0 };
	CString         strFolderPath = TEXT("");

	BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("��ѡ��һ���ļ��У�");
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn = NULL;

	// ��ʾ�ļ���ѡ��Ի���  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// ȡ���ļ�����  
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
		}
	}
	else {
		std::cout << "û��ѡ���ļ��С�\n\n";
		return FolderPath;
	}

	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}

	FolderPath = strFolderPath.GetBuffer(0);
	return FolderPath;

}

// �����ļ���Դ����������ȡѡ���ļ���·��
char* GetSelectFolderPath() {
	char* path = String2FilePath(GetSelectFolderPath_string());
	return path;
}
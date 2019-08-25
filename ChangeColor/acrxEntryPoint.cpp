// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "CCreateEnt.h"
#include "CModifyEnt.h"
#include "CCalculation.h"
#include "CAuxiliary.h"
#include <vector> 
#include"acedCmdNF.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("asdk")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CChangeColorApp : public AcRxArxApp {

public:
	CChangeColorApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the CChangeColorApp class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	
	//�ڳ�������֮ǰ��Ҫȷ����strLayer����͡����ߡ����͵Ĵ���

	static void asdkMyGroupAddLine () {//����ʵ�����ɫ
		// Put your command code here
		// ����ֱ��
		AcGePoint3d ptStart(0, 0, 0);
		AcGePoint3d ptEnd(100, 100, 0);
		AcDbObjectId lineId;
		lineId = CCreateEnt::CreateLine(ptStart,ptEnd);
		// �޸�ֱ�ߵ���ɫΪ��ɫ
		CModifyEnt::ChangeColor(lineId, 1);
		// �޸�ֱ�ߵ�ͼ��ΪstrLayer
		CModifyEnt::ChangeLayer(lineId, _T("strLayer"));
		// �޸�ֱ�ߵ�����Ϊ����
		CModifyEnt::ChangeLinetype(lineId, _T("����"));
	}

	static void asdkMyGroupAddCircle() {
		// Put your command code here
		// ����Բ
		AcGePoint3d ptCenter(0, 0, 0);//Բ�����꣬�뾶100
		CCreateEnt::CreateCircle(ptCenter, 100);
		CCreateEnt::CreatePolyCircle(CCalculation::Pt3dTo2d(ptCenter), 200);
	}

	static void asdkMyGroupAddArc() {
	// Put your command code here
		// ����Բ��
		AcGePoint2d ptCenter(0, 0);
		CCreateEnt::CreateArc(ptCenter, 1000, 0, CCalculation::dutohudu(145));
		CCreateEnt::CreatePolyArc(ptCenter, 500, 0, CCalculation::dutohudu(145));
	}

	static void asdkMyGroupAddPolyline() {
		// Put your command code here
		//�û�������������
		CCreateEnt::CreatePoly();
	}

	static void asdkMyGroupAddRect()
	{
		ads_point ptStart; // ���
		ads_point ptEnd; // �յ�

		if (RTNORM != acedGetPoint(NULL, _T("\n�����һ��:"), ptStart))
		{
			return;
		}
		acutPrintf(_T("\n������������(%.2f, %.2f, %.2f)"), ptStart[X], ptStart[Y], ptStart[Z]);

		if (RTNORM != acedGetPoint(NULL, _T("\n����ڶ���:"), ptEnd))
		{
			return;
		}
		acutPrintf(_T("\n������������(%.2f, %.2f, %.2f)"), ptEnd[X], ptEnd[Y], ptEnd[Z]);

		CCreateEnt::CreateRect(asPnt2d(ptStart), asPnt2d(ptEnd)
);
	}

	static void asdkMyGroupAddPolygon() {
		// Put your command code here
		// �����������
		CCreateEnt::CreatePolygon(AcGePoint2d::kOrigin, 6, 100, 0, 1);
		//�������Ϊ���ġ����������Բ�뾶����ת�Ƕȣ�����ֵ�����߿�
	}

	static void asdkMyGroupEntInfo()
	{
		// ��ʾ�û�ѡ��ʵ��
		ads_name entName;
		ads_point pt;
		if (acedEntSel(_T("\nѡ��ʵ��:"), entName, pt) != RTNORM)
			return;
		struct resbuf *rbEnt; // ����ʵ�����ݵĽ��������
		struct resbuf *rb; // ���ڱ���rbEnt�Ľ��������
		// ��entName��ñ���ʵ�����ݵĽ��������
		rbEnt = acdbEntGet(entName);
		rb = rbEnt;
		while (rb != NULL)
		{
			switch (rb->restype)
			{
			case -1: // ͼԪ��
				acutPrintf(_T("\nͼԪ��: %x"), rb->resval.rstring);
				break;
			case 0: // ͼԪ����
				acutPrintf(_T("\nͼԪ����: %s"), rb->resval.rstring);
				break;
			case 8: // ͼ��
				acutPrintf(_T("\nͼ��:%s"), rb->resval.rstring);
				break;
			case 10: // Բ��
				acutPrintf(_T("\nԲ��:(%.2f, %.2f, %.2f)"),
					rb->resval.rpoint[X],
					rb->resval.rpoint[Y],
					rb->resval.rpoint[Z]);
				break;
			case 40: // �뾶
				acutPrintf(_T("\n�뾶:%.4f"), rb->resval.rreal);
				break;
			case 210: // Բ����ƽ��ķ���ʸ��
				acutPrintf(_T("\nƽ��ķ���ʸ��:(%.2f, %.2f, %.2f)"),
					rb->resval.rpoint[X],
					rb->resval.rpoint[Y],
					rb->resval.rpoint[Z]);
				break;
			default:
				break;
			} // switch
			rb = rb->rbnext; // �л�����һ���ڵ�
		} // while
		if (rbEnt != NULL)
		{
			acutRelRb(rbEnt);
		}
		/*���û��ʹ��
		������ָ��rb ���������нڵ㣬����ֱ��ʹ��rbEnt �����ʣ������޷�ͨ��acutRelRb ��
		���ͷŽ�������������Ĵ洢�ռ䣨rbEnt ��δָ��������ͷ�ڵ㣩������ڴ�й©��*/
	}

	static void asdkMyGroupAddText()
	{
		// ������������
		AcGePoint3d ptInsert(0, 12, 0);
		CCreateEnt::CreateText(ptInsert, _T("CAD����"));
		// ������������
		ptInsert.set(0, 0, 0);
		CCreateEnt::CreateMText(ptInsert, _T("http://www.cadhelp.net\n����"));
	}

	static void asdkMyGroupNewLayer()
	{
		CCreateEnt::NewLayer();
	}

	static void asdkMyGroupSetLayer()
	{
		CCreateEnt::SetLayer();
	}

	static void asdkMyGroupDelLayer()
	{
		CString layerName;
		layerName = CCreateEnt::DelLayer();
		if (layerName == _T("0"))
		{
			acutPrintf(_T("����������ѡ���ͼ�㣡"));
		}
		else
		{
			acutPrintf(_T("���ղ�ɾ����ͼ�㣺") + layerName);
		}
	}

	static void asdkMyGroupOpenFile1()
	{
		CAuxiliary::vec_pt.clear();//�������������

		const ACHAR* title = _T("ѡ�������ļ�");
		const ACHAR* path = _T("G:\\");
		struct resbuf *fileName;
		fileName = acutNewRb(RTSTR);
		if (acedGetFileD(title, path, _T("txt;bat"), 0, fileName) == RTNORM)
		{
			//acedAlert(fileName->resval.rstring);//�Ի�����ʾ�ļ�·��
			CStdioFile file(fileName->resval.rstring, CFile::modeRead | CFile::typeText);
			CString strLine, strTemp;
			int row = 0;
			try
			{
				while (file.ReadString(strLine))//ÿ�ζ�ȡһ��
				{
					CMyPoint point;
					int n = strLine.Find(_T(","));//���ص�һ�γ��ֵ�λ�ã�����λ�ã���0��ʼ�������û�У�����-1
					strTemp = strLine.Left(n);
					point.ptName = strTemp;
					strLine = strLine.Right(strLine.GetLength() - n - 1);//ȥ����һ�����ż�֮ǰ������
					n = strLine.Find(_T(","));
					/*strLine = strLine.Right(strLine.GetLength() - n - 1);//�ѵڶ���û���ݵĶ���ȥ��
					n = strLine.Find(_T(","));*/

					float* num = new float[3];//�洢����ֵ
					int i = 0;
					while (-1 != n)
					{
						strTemp = strLine.Left(n);
						//num[i] = (float)atof((char *)(LPTSTR)(LPCTSTR)strTemp);//����ǿ��ת����ʧ����
						num[i] = (float)_ttof(strTemp);
						i++;
						strLine = strLine.Right(strLine.GetLength() - n - 1);
						n = strLine.Find(_T(","));
					}
					if (strLine.GetLength() > 0)//���һ������
					{
						num[i] = (float)_ttof(strLine);
					}
					point.pt.x = num[1];//��������ϵ��x��y���껥��
					point.pt.y = num[0];
					point.pt.z = num[2];
					CAuxiliary::vec_pt.push_back(point);//Ϊ��̬������ֵ
					row++;
				}
			}
			catch (...)//���������쳣
			{
				acedAlert(_T("�����ļ��е������Ƿ���ȷ��\n���ݵ���ʧ�ܣ�"));
				return;
			}
			file.Close();
		}
		acutRelRb(fileName);
		//acedAlert(_T("�ļ��򿪳ɹ���"));

		AcDbObjectId textId;
		CString layerName;
		//layerName = CCreateEnt::NewLayer();//���û��½�һ��ͼ��
		layerName = CCreateEnt::ChooseLayer();//���û�ѡ��ͼ������

		for (int i = 0; i < CAuxiliary::vec_pt.size(); i++)
		{
			CCreateEnt::CreatePoint(CAuxiliary::vec_pt[i].pt);

			//CString תCStringA תstring ��ת const char*
			/*CStringA strA(CAuxiliary::vec_pt[i].ptName.GetBuffer(0));
			CAuxiliary::vec_pt[i].ptName.ReleaseBuffer();
			string s = strA.GetBuffer(0);
			const char* pc = s.c_str();*/

			textId = CCreateEnt::CreateText(CAuxiliary::vec_pt[i].pt, CAuxiliary::vec_pt[i].ptName);
			CModifyEnt::ChangeLayer(textId,layerName);//��������ע�ǵ�ͼ��

			/*ads_point pt = {CAuxiliary::vec_pt[i].pt.x, CAuxiliary::vec_pt[i].pt.y, CAuxiliary::vec_pt[i].pt.z};
			acedCommandS(RTSTR, "POINT", // ����
				RTPOINT, pt, // λ��
				RTNONE); // ��������*/
		}
		/*CString str = "";
		acedAlert(CAuxiliary::vec_pt[0].ptName);
		str.Format(_T("%.2f"), (float)CAuxiliary::vec_pt[0].pt.x);
		acedAlert(str);
		str.Format(_T("%.2f"), (float)CAuxiliary::vec_pt[0].pt.y);
		acedAlert(str);
		str.Format(_T("%.2f"), (float)CAuxiliary::vec_pt[0].pt.z);
		acedAlert(str);*/

		//CCreateEnt::CreateTriangle(CAuxiliary::vec_pt[0].pt, CAuxiliary::vec_pt[1].pt, CAuxiliary::vec_pt[2].pt);

		// ��������
		acedCommandS(RTSTR, _T("Zoom"), RTSTR, _T("E"), RTNONE);

		acdbCurDwg()->setPdmode(34); //���õ���ʽ

		//acdbCurDwg()->setPdsize(3); //���ô�С
	}

	static void asdkMyGroupDrawTriange()
	{
		if (CAuxiliary::vec_pt.size() == 0)
		{
			acedAlert(_T("���ȴ��ļ���"));
			return;
		}

		CString layerName;
		//layerName = CCreateEnt::NewLayer();//���û��½�һ��ͼ��
		layerName = CCreateEnt::ChooseLayer();//���û�ѡ��ͼ������

		CAuxiliary::drawTriangle(CAuxiliary::vec_pt, layerName);
	}

	static void asdkMyGroupCaculateV()
	{
		if (CAuxiliary::vec_tri.size() == 0)
		{
			acedAlert(_T("���ȹ���TIN��"));
			return;
		}

		int gaocheng;
		acedGetInt(_T("�������׼�߳�: "), &gaocheng);
		CAuxiliary::result = CAuxiliary::calculateV(CAuxiliary::vec_tri, gaocheng);
	}

	static void asdkMyGroupSaveFile()
	{
		if (CAuxiliary::result == "")
		{
			acedAlert(_T("���ȼ��������"));
			return;
		}

		//acedAlert(CAuxiliary::result);

		CFileDialog fileDlg(FALSE);//�ļ�����
		fileDlg.m_ofn.lpstrTitle = _T("�ļ�����");
		fileDlg.m_ofn.lpstrFilter = _T("Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0");
		fileDlg.m_ofn.lpstrDefExt = _T("txt");
		if (IDOK == fileDlg.DoModal())
		{
			CFile file(fileDlg.GetPathName()/*_T("G:\\")*/, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
			// | CFile::typeBinary�����ö�����ģʽ��д�����ܶ�ȡ�س����з�
			//CStdioFile  file(_T("Report.txt"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

			//���ļ�����Ϊunicode��ʽ
			//Ϊ��unicode�����CStringд��unicode������ļ�֮����������ʾ����������
			//��Ҫ���ļ��Ŀ�ͷд��0xFEFF
			WORD unicode = 0xFEFF; //�����Ҫ
			file.Write(&unicode, 2); //�����Ҫ

			file.Write(CAuxiliary::result, CAuxiliary::result.GetLength() * 2);//�������2Ӧ������ansi���뷽ʽ������
			file.Close();
			AfxMessageBox(_T("�ļ�����ɹ���"));
		}
	}

	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void asdkMyGroupMyPickFirst () {
		ads_name result;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM )
		{
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else
		{
			// There are no selected entities
			// Put your command code here
		}
	}

	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void asdkMyGroupMySessionCmd () {
		// Put your command code here
	}

	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the CChangeColorApp class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(CChangeColorApp, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}
	
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CChangeColorApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, AddLine, AddLine, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, AddCircle, AddCircle, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, AddArc, AddArc, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, AddPolyline, AddPolyline, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, AddRect, AddRect, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, AddPolygon, AddPolygon, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, EntInfo, EntInfo, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, AddText, AddText, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, NewLayer, NewLayer, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, SetLayer, SetLayer, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, DelLayer, DelLayer, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, OpenFile1, OpenFile1, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, DrawTriange, DrawTriange, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, CaculateV, CaculateV, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, SaveFile, SaveFile, ACRX_CMD_MODAL, NULL)

ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CChangeColorApp, asdkMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
ACED_ADSSYMBOL_ENTRY_AUTO(CChangeColorApp, MyLispFunction, false)

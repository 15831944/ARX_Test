#include "stdafx.h"
#include "CCreateEnt.h"
#include "CCalculation.h"
#include "CModifyEnt.h"
#include "CAuxiliary.h"

CCreateEnt::CCreateEnt()
{
}


CCreateEnt::~CCreateEnt()
{
}
//������
AcDbObjectId CCreateEnt::CreatePoint(AcGePoint3d pt)
{

	AcDbPoint *pPoint = new AcDbPoint(pt);

	// ��ʵ�����ӵ�ͼ�����ݿ�
	AcDbObjectId pointId;
	pointId = CCreateEnt::PostToModelSpace(pPoint);
	return pointId;
}

// ����ֱ��
AcDbObjectId CCreateEnt::CreateLine(AcGePoint3d ptStart,AcGePoint3d ptEnd)
{

	AcDbLine *pLine = new AcDbLine(ptStart, ptEnd);

	// ��ʵ�����ӵ�ͼ�����ݿ�
	AcDbObjectId lineId;
	lineId = CCreateEnt::PostToModelSpace(pLine);
	return lineId;
}

//����Բ
AcDbObjectId CCreateEnt::CreateCircle(AcGePoint3d ptCenter, double radius)
{
	AcGeVector3d vec(0, 0, 1);//����һ������λ��XOY ƽ���ϵ�Բ

	AcDbCircle *pCircle = new AcDbCircle(ptCenter, vec, radius);

	// ��ʵ�����ӵ�ͼ�����ݿ�
	AcDbObjectId circleId;
	circleId = CCreateEnt::PostToModelSpace(pCircle);
	return circleId;
}
//���ߵķ�ʽ����Բ
AcDbObjectId CCreateEnt::CreatePolyCircle(AcGePoint2d ptCenter,double radius, double width)
{
	// ���㶥���λ��
	AcGePoint2d pt1, pt2, pt3;
	pt1.x = ptCenter.x + radius;
	pt1.y = ptCenter.y;
	pt2.x = ptCenter.x - radius;
	pt2.y = ptCenter.y;
	pt3.x = ptCenter.x + radius;
	pt3.y = ptCenter.y;
	// ���������
	AcDbPolyline *pPoly = new AcDbPolyline(3);
	pPoly->addVertexAt(0, pt1, 1, width, width);
	pPoly->addVertexAt(1, pt2, 1, width, width);
	pPoly->addVertexAt(2, pt3, 1, width, width);
	pPoly->setClosed(Adesk::kTrue);
	// ����������ӵ�ģ�Ϳռ�
	AcDbObjectId polyId;
	polyId = CCreateEnt::PostToModelSpace(pPoly);
	return polyId;
}

//��Բ�ļӰ뾶�����յ�Ƕȵķ�������һ��Բ��
AcDbObjectId CCreateEnt::CreateArc(AcGePoint2d ptCenter, double radius, double startAngle, double endAngle)
{
	AcGeVector3d vec(0, 0, 1);//����һ������λ��XOY ƽ���ϵ�Բ
	AcGePoint3d pt3dCenter = CCalculation::Pt2dTo3d(ptCenter);

	AcDbArc *pArc = new AcDbArc(pt3dCenter, vec, radius, startAngle, endAngle);

	// ��ʵ�����ӵ�ͼ�����ݿ�
	AcDbObjectId arcId;
	arcId = CCreateEnt::PostToModelSpace(pArc);
	return arcId;
}
//�ô������ߵķ�ʽ����Բ��
AcDbObjectId CCreateEnt::CreatePolyArc(AcGePoint2d ptCenter, double radius,
	double angleStart, double angleEnd, double width)
{
	// ���㶥���λ��
	AcGePoint2d pt1, pt2;
	pt1.x = ptCenter.x + radius * cos(angleStart);
	pt1.y = ptCenter.y + radius * sin(angleStart);
	pt2.x = ptCenter.x + radius * cos(angleEnd);
	pt2.y = ptCenter.y + radius * sin(angleEnd);
	// ���������
	AcDbPolyline *pPoly = new AcDbPolyline(3);

	pPoly->addVertexAt(0, pt1, tan((angleEnd - angleStart) / 4), width,
		width);
	pPoly->addVertexAt(1, pt2, 0, width, width);
	// ����������ӵ�ģ�Ϳռ�
	AcDbObjectId polyId;
	polyId = CCreateEnt::PostToModelSpace(pPoly);
	return polyId;
}
//���ݶ�ά���б���������
AcDbObjectId CCreateEnt::CreatePolyline(AcGePoint2dArray points, double width)
{
	int numVertices = points.length();
	AcDbPolyline *pPoly = new AcDbPolyline(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		pPoly->addVertexAt(i, points.at(i), 0, width, width);
	}
	// ��ʵ�����ӵ�ͼ�����ݿ�
	AcDbObjectId polyId;
	polyId = CCreateEnt::PostToModelSpace(pPoly);
	return polyId;
}

//������ά����
AcDbObjectId CCreateEnt::CreateRect(AcGePoint2d pt1, AcGePoint2d pt2, double width)
{
	// ��ȡ�����ǵ������ֵ
	double x1 = pt1.x, x2 = pt2.x;
	double y1 = pt1.y, y2 = pt2.y;

	// ������εĽǵ�
	AcGePoint2d ptLeftBottom(CCalculation::Min(x1, x2),
		CCalculation::Min(y1, y2));
	AcGePoint2d ptRightBottom(CCalculation::Max(x1, x2),
		CCalculation::Min(y1, y2));
	AcGePoint2d ptRightTop(CCalculation::Max(x1, x2),
		CCalculation::Max(y1, y2));
	AcGePoint2d ptLeftTop(CCalculation::Min(x1, x2),
		CCalculation::Max(y1, y2));

	// ������Ӧ�Ķ����
	AcDbPolyline *pPloy = new AcDbPolyline(4);
	pPloy->addVertexAt(0, ptLeftBottom, 0, width, width);
	pPloy->addVertexAt(1, ptRightBottom, 0, width, width);
	pPloy->addVertexAt(2, ptRightTop, 0, width, width);
	pPloy->addVertexAt(3, ptLeftTop, 0, width, width);
	pPloy->setClosed(Adesk::kTrue);

	// ����������ӵ�ģ�Ϳռ�
	AcDbObjectId polyId;
	polyId = CCreateEnt::PostToModelSpace(pPloy);
	return polyId;
}

//������ά������
AcDbObjectId CCreateEnt::CreateTriangle(AcGePoint3d pt1, AcGePoint3d pt2, AcGePoint3d pt3, double width)
{
	AcGePoint3dArray points;
	points.append(pt1);
	points.append(pt2);
	points.append(pt3);

	// ������Ӧ�Ķ����
	AcDb3dPolyline *p3dPloy = new AcDb3dPolyline(AcDb::k3dSimplePoly,points,true);//�պ϶��߶�

	// ����������ӵ�ģ�Ϳռ�
	AcDbObjectId polyId;
	polyId = CCreateEnt::PostToModelSpace(p3dPloy);
	return polyId;
}
//�û�������������
void CCreateEnt::CreatePoly()
{
	int colorIndex = 0; // ��ɫ����ֵ
	ads_real width_begin = 0; // ����ߵ�����߿�
	ads_real width_end = 0; // ����ߵ��յ��߿�
	int nIndex = 2; // ��ǰ�����Ĵ���
	ads_point ptStart; // ���
	ads_point ptPrevious;// ǰһ���ο���
	ads_point ptCurrent; //��ǰʰȡ�ĵ�
	AcDbObjectId polyId; //�����ID

	// ��ʾ�û��������
	if (RTNORM != acedGetPoint(NULL, _T("\n�����һ��:"), ptStart))
	{
		return;
	}
	acdbPointSet(ptStart, ptPrevious);//������������ֵ
	// ����ڶ���
	acedInitGet(NULL, _T("W C B F"));//�޶����������

	int rc = acedGetPoint(ptPrevious, _T("\n������һ�� [����(W)/��ɫ(C)/�պ�(B)]<���(F)>:"), ptCurrent);

	while (rc == RTNORM || rc == RTKWORD)//����ֵΪ�ɹ������û������˹ؼ���
	{
		if (RTKWORD == rc) // ����û������˹ؼ���
		{
			ACHAR kword[20];//����Ҫ��ACHAR����ؼ���
			if (acedGetInput(kword) != RTNORM)//��ȡ�û�����Ĺؼ��֣����ɹ��ͷ���
				return;
			if (0 == _tcscmp(kword, _T("W")))//�жϹؼ���
			{
				CAuxiliary::GetWidth(&width_begin,&width_end);//��ȡ����
			}
			else if (0 == _tcscmp(kword, _T("C")))
			{
				colorIndex = CAuxiliary::GetColorIndex(); //��ȡ��ɫ����

				AcDbEntity *pEnt;
				acdbOpenAcDbEntity(pEnt, polyId, AcDb::kForWrite);//���ݶ���id��ȡ���ݿ��е�ʵ���ָ��

				if (pEnt->isKindOf(AcDbPolyline::desc()) == Adesk::kTrue)//
				{
					AcDbPolyline *pPoly = AcDbPolyline::cast(pEnt);//����ת��Ϊָ��AcDbPolyline ��ָ��
					if (pPoly != NULL)
					{
						pPoly->setColorIndex(colorIndex);
					}
				}
				pEnt->close();
			}
			else if (0 == _tcscmp(kword, _T("B")))
			{
				if (nIndex < 3)
				{
					acutPrintf(_T("\n�����������㣬����ִ�бպϲ���"));
					return;
				}

				AcDbEntity *pEnt;
				acdbOpenAcDbEntity(pEnt, polyId, AcDb::kForWrite);//���ݶ���id��ȡ���ݿ��е�ʵ���ָ��

				if (pEnt->isKindOf(AcDbPolyline::desc()) == Adesk::kTrue)//
				{
					AcDbPolyline *pPoly = AcDbPolyline::cast(pEnt);//����ת��Ϊָ��AcDbPolyline ��ָ��
					if (pPoly != NULL)
					{
						pPoly->setClosed(Adesk::kTrue);
					}
				}
				pEnt->close();

				return;
			}
			else if (0 == _tcscmp(kword, _T("F")))
			{
				return;
			}
		}
		else if (RTNORM == rc)  // �û������˵�
		{
			acutPrintf(_T("\n������������(%.2f, %.2f, %.2f)"), ptCurrent[X], ptCurrent[Y], ptCurrent[Z]);

			if (2 == nIndex)
			{
				// ���������
				AcDbPolyline *pPoly = new AcDbPolyline(2);
				AcGePoint2d ptGe1, ptGe2; // �����ڵ�
				ptGe1[X] = ptPrevious[X];
				ptGe1[Y] = ptPrevious[Y];
				ptGe2[X] = ptCurrent[X];
				ptGe2[Y] = ptCurrent[Y];
				pPoly->addVertexAt(0, ptGe1, 0, width_begin, width_end);
				pPoly->addVertexAt(1, ptGe2, 0, width_begin, width_end);

				// �޸Ķ���ߵ���ɫ���߿�
				//pPoly->setConstantWidth(width);
				//pPoly->setColorIndex(colorIndex);
				// ���ӵ�ģ�Ϳռ�
				polyId = PostToModelSpace(pPoly);
			}
			else if (nIndex > 2)
			{
				// �޸Ķ���ߣ��������һ������
				AcDbPolyline *pPoly;
				acdbOpenObject(pPoly, polyId, AcDb::kForWrite);//��ȡ���ݿ��еĶ���
				AcGePoint2d ptGe; // ���ӵĽڵ�
				ptGe[X] = ptCurrent[X];
				ptGe[Y] = ptCurrent[Y];
				pPoly->addVertexAt(nIndex - 1, ptGe, 0, width_begin, width_end);
				// �޸Ķ���ߵ���ɫ���߿�
				//pPoly->setConstantWidth(width);
				//pPoly->setColorIndex(colorIndex);
				pPoly->close();
			}

			++nIndex;
			acdbPointSet(ptCurrent, ptPrevious);//acdbPointSet�꣺ ads_point ����ֵ�ĸ���
		}
		// ��ʾ�û������µĽڵ�
		acedInitGet(NULL, _T("W C B F"));//�޶����������
		rc = acedGetPoint(ptPrevious, _T("\n������һ�� [����(W)/��ɫ(C)/�պ�(B)]<���(F)>:"), ptCurrent);
	}
}

//�����������
AcDbObjectId CCreateEnt::CreatePolygon(AcGePoint2d ptCenter, int number,
	double radius, double rotation, double width)
{
	AcGePoint2dArray points;
	double angle = 2 * CCalculation::PI() / (double)number;

	for (int i = 0; i < number; i++)
	{
		AcGePoint2d pt;
		pt.x = ptCenter.x + radius * cos(i * angle);//������еĶ�������������
		pt.y = ptCenter.y + radius * sin(i * angle);
		points.append(pt);
	}

	AcDbObjectId polyId = CCreateEnt::CreatePolyline(points, width);

	// ����պ�
	AcDbEntity *pEnt;
	acdbOpenAcDbEntity(pEnt, polyId, AcDb::kForWrite);//���ݶ���id��ȡ���ݿ��е�ʵ���ָ��

	if (pEnt->isKindOf(AcDbPolyline::desc()) == Adesk::kTrue)//
	{
		AcDbPolyline *pPoly = AcDbPolyline::cast(pEnt);//����ת��Ϊָ��AcDbPolyline ��ָ��
		if (pPoly != NULL)
		{
			pPoly->setClosed(Adesk::kTrue);
		}
	}
	
	pEnt->close();
	CModifyEnt::Rotate(polyId, ptCenter, rotation);//��ת
	return polyId;
}

//������������
AcDbObjectId CCreateEnt::CreateText(const AcGePoint3d& ptInsert,
	const ACHAR* text, AcDbObjectId style,
	double height, double rotation)
{
	AcDbText *pText = new AcDbText(ptInsert, text, style, height, rotation);
	return CCreateEnt::PostToModelSpace(pText);
}
AcDbObjectId CCreateEnt::CreateMText(const AcGePoint3d& ptInsert,
	const ACHAR* text, AcDbObjectId style,
	double height, double width)
{
	AcDbMText *pMText = new AcDbMText();
	// ���ö������ֵ�����
	pMText->setTextStyle(style);
	pMText->setContents(text);
	pMText->setLocation(ptInsert);
	pMText->setTextHeight(height);
	pMText->setWidth(width);
	pMText->setAttachment(AcDbMText::kBottomLeft);//�޸����ֶ��뷽ʽ

	return CCreateEnt::PostToModelSpace(pMText);
}

CString CCreateEnt::NewLayer()//�½�һ��ͼ��
{
	// ��ʾ�û������½�ͼ�������
	ACHAR layerName[100];
	if (acedGetString(Adesk::kFalse, _T("\n������ͼ������ƣ�"), layerName) != RTNORM)
	{
		return _T("0");
	}
	// ��õ�ǰͼ�εĲ��
	AcDbLayerTable *pLayerTbl;
	acdbHostApplicationServices()->workingDatabase()
		->getLayerTable(pLayerTbl, AcDb::kForWrite);//��д��ķ�ʽ�򿪲��

	// �Ƿ��Ѿ�����ָ���Ĳ����¼
	if (pLayerTbl->has(layerName))
	{
		pLayerTbl->close();
		return _T("0");
	}

	// �����µĲ����¼
	AcDbLayerTableRecord *pLayerTblRcd;
	pLayerTblRcd = new AcDbLayerTableRecord();
	pLayerTblRcd->setName(layerName);//��������

	// ���½��Ĳ����¼���ӵ�����з���ͼ��id
	AcDbObjectId layerTblRcdId;
	pLayerTbl->add(layerTblRcdId, pLayerTblRcd);

	acdbHostApplicationServices()->workingDatabase()
		->setClayer(layerTblRcdId);//����ͼ�εĵ�ǰͼ�㣬���Ǻ���ûʲô��

	pLayerTblRcd->close();
	pLayerTbl->close();

	return layerName;
}
CString CCreateEnt::SetLayer()//����ͼ������
{
	// ��ʾ�û�����Ҫ�޸ĵ�ͼ������
	ACHAR layerName[100];
	if (acedGetString(Adesk::kFalse, _T("\n����ͼ������ƣ�"),
		layerName) != RTNORM)
	{
		return _T("0");
	}

	// ��õ�ǰͼ�εĲ��
	AcDbLayerTable *pLayerTbl;
	acdbHostApplicationServices()->workingDatabase()
		->getLayerTable(pLayerTbl, AcDb::kForRead);

	// �ж��Ƿ����ָ�����ƵĲ����¼
	if (!pLayerTbl->has(layerName))
	{
		pLayerTbl->close();
		return _T("0");
	}

	// ���ָ�������¼��ָ��
	AcDbLayerTableRecord *pLayerTblRcd;
	pLayerTbl->getAt(layerName, pLayerTblRcd, AcDb::kForWrite);

	// ��������ɫ���Ի���
	AcCmColor oldColor = pLayerTblRcd->color();
	int nCurColor = oldColor.colorIndex(); // ͼ���޸�ǰ����ɫ
	int nNewColor = oldColor.colorIndex(); // �û�ѡ�����ɫ
	if (acedSetColorDialog(nNewColor, Adesk::kFalse, nCurColor))
	{
		AcCmColor color;
		color.setColorIndex(nNewColor);
		pLayerTblRcd->setColor(color);//����ͼ����ɫ
	}


	// ��������
	ACHAR lineType[100];
	if (acedGetString(Adesk::kFalse, _T("\n�������ε����ƣ��㻬�� CENTER������ DASHED����"),
		lineType) != RTNORM)
	{
		return _T("0");
	}

	AcDbLinetypeTable *pLinetypeTbl;
	AcDbObjectId linetypeId;
	//��ȡ��ǰ�����ͱ�
	acdbHostApplicationServices()->workingDatabase()
		->getLinetypeTable(pLinetypeTbl, AcDb::kForRead);

	if (pLinetypeTbl->has(lineType))
	{
		pLinetypeTbl->getAt(lineType, linetypeId);
	}
	else
	{
		acutPrintf(_T("����������Ͳ����ڣ�"));
		pLinetypeTbl->getAt(_T("Continuous"), linetypeId);//�������û�ѡ������ξ�ѡ��ʵ��
	}
	pLayerTblRcd->setLinetypeObjectId(linetypeId);
	pLinetypeTbl->close();

	// �����߿�
	ACHAR linewidth[10];
	if (acedGetString(Adesk::kFalse, _T("\n�����߿���"), linewidth) != RTNORM)
	{
		return _T("0");
	}
	AcDb::LineWeight lineWeight = (AcDb::LineWeight)_ttol(linewidth);
	pLayerTblRcd->setLineWeight(lineWeight);

	pLayerTblRcd->close();
	pLayerTbl->close();

	return layerName;
}

CString CCreateEnt::ChooseLayer()//ѡ��ͼ��
{
	// ��ʾ�û�����Ҫ�޸ĵ�ͼ������
	ACHAR layerName[100];
	if (acedGetString(Adesk::kFalse, _T("\n����ͼ������ƣ�"),
		layerName) != RTNORM)
	{
		return _T("0");
	}

	// ��õ�ǰͼ�εĲ��
	AcDbLayerTable *pLayerTbl;
	acdbHostApplicationServices()->workingDatabase()
		->getLayerTable(pLayerTbl, AcDb::kForRead);

	// �ж��Ƿ����ָ�����ƵĲ����¼
	if (!pLayerTbl->has(layerName))
	{
		pLayerTbl->close();
		acutPrintf(_T("�������ͼ�㲻���ڣ�"));
		return _T("0");
	}
	else
	{
		return layerName;
	}
	pLayerTbl->close();
}

CString CCreateEnt::DelLayer()//ɾ��ͼ��
{
	// ��ʾ�û�����Ҫ�޸ĵ�ͼ������
	ACHAR layerName[100];
	if (acedGetString(Adesk::kFalse, _T("\n����ͼ������ƣ�"), layerName) != RTNORM)
	{
		return  _T("0");
	}
	// ��õ�ǰͼ�εĲ��
	AcDbLayerTable *pLayerTbl;
	acdbHostApplicationServices()->workingDatabase()
		->getLayerTable(pLayerTbl, AcDb::kForRead);
	// �ж��Ƿ����ָ�����ƵĲ����¼
	if (!pLayerTbl->has(layerName))
	{
		pLayerTbl->close();
		return  _T("0");
	}
	// ���ָ�������¼��ָ��
	AcDbLayerTableRecord *pLayerTblRcd;
	pLayerTbl->getAt(layerName, pLayerTblRcd, AcDb::kForWrite);

	pLayerTblRcd->erase(); // Ϊ�����á�ɾ�������
	pLayerTblRcd->close();
	pLayerTbl->close();

	return layerName;
}

// ��ʵ�����ӵ�ͼ�����ݿ��ģ�Ϳռ�
AcDbObjectId CCreateEnt::PostToModelSpace(AcDbEntity* pEnt)
{
	//ͼ�����ݿ���
	AcDbBlockTable *pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getBlockTable(pBlockTable, AcDb::kForRead);

	//��ȡ������ض��ļ�¼
	AcDbBlockTableRecord *pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
		AcDb::kForWrite);

	//��ʵ�����ӵ������¼
	AcDbObjectId entId;
	pBlockTableRecord->appendAcDbEntity(entId, pEnt);

	//�رտ���������¼��ʵ��
	pBlockTable->close();
	pBlockTableRecord->close();
	pEnt->close();

	return entId;
}
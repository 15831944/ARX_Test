#pragma once
class CCreateEnt
{
public:
	CCreateEnt();
	~CCreateEnt();
	static AcDbObjectId CreatePoint(AcGePoint3d pt); //创建点

	static AcDbObjectId CreateLine(AcGePoint3d ptStart, AcGePoint3d ptEnd); //创建直线

	static AcDbObjectId CreateCircle(AcGePoint3d ptCenter, double radius);//创建圆
	static AcDbObjectId CreatePolyCircle(AcGePoint2d ptCenter, double radius, double width = 0);//多线的方式创建圆

	static AcDbObjectId CreateArc(AcGePoint2d ptCenter, double radius, double startAngle, double endAngle);//创建圆弧
	static AcDbObjectId CreatePolyArc(AcGePoint2d ptCenter, double radius,
		double angleStart, double angleEnd, double width = 0);//以多线的方式创建圆弧

	static AcDbObjectId CreatePolyline(AcGePoint2dArray points, double width = 0);//通过二维点列表创建多线

	static void CreatePoly();//通过用户交互绘制多线

	static AcDbObjectId CreateRect(AcGePoint2d pt1, AcGePoint2d pt2, double width = 0);//创建矩形
	static AcDbObjectId CreateTriangle(AcGePoint3d pt1, AcGePoint3d pt2, AcGePoint3d pt3, double width = 0);//创建三角形
	 
	static AcDbObjectId CreatePolygon(AcGePoint2d ptCenter, int number,
		double radius, double rotation, double width);//创建正多边形，输入参数为中心、边数、外接圆半径、旋转角度（弧度值）和线宽

	static AcDbObjectId CreateText(const AcGePoint3d& ptInsert,//创建文字
		const ACHAR* text, AcDbObjectId style = AcDbObjectId::kNull,
		double height = 1, double rotation = 0);
	static AcDbObjectId CreateMText(const AcGePoint3d& ptInsert,//创建多行文字
		const ACHAR* text, AcDbObjectId style = AcDbObjectId::kNull,
		double height = 2.5, double width = 10);

	static CString NewLayer();//新建一个图层
	static CString SetLayer();//更改图层特性
	static CString ChooseLayer();//选择图层（让用户选择实体添加到指定的图层）
	static CString DelLayer();//删除图层

	static AcDbObjectId CCreateEnt::PostToModelSpace(AcDbEntity* pEnt);//将实体添加到图形数据库
};


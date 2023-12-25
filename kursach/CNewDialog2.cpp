// CNewDialog2.cpp : implementation file
//

#include "pch.h"
#include "kursach.h"
#include "afxdialogex.h"
#include "CNewDialog2.h"
#include <cmath>

#include "math.h"
#include "D:\компас\SDK\Include\ksConstants.h"
#include "D:\компас\SDK\Include\ksConstants3D.h"

#define PI 4*atan(1)
#import "D:\компас\SDK\lib\kAPI5.tlb"


using namespace Kompas6API5;

KompasObjectPtr pKompasApp55;

ksPartPtr pPart2;
ksDocument3DPtr pDoc2;



// CNewDialog2 dialog

//IMPLEMENT_DYNAMIC(CNewDialog2, CDialog)

CNewDialog2::CNewDialog2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CNewDialog2, pParent)
	, D(53)
	, D1(50)
	, D2(26)
	, d(12)
	, L(81)
	, L1(48)
	, l(15)
	, l1(28)
	, l2(10)
	, B(10)
	, b1(5)
	, R(1.6)
	, lDeep(30)
	, B1(14)
	, d_star(26)
	, H(15)
{

}

CNewDialog2::~CNewDialog2()
{
}

void CNewDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, D);
	DDX_Text(pDX, IDC_EDIT13, D1);
	DDX_Text(pDX, IDC_EDIT14, D2);
	DDX_Text(pDX, IDC_EDIT15, d);
	DDX_Text(pDX, IDC_EDIT16, L);
	DDX_Text(pDX, IDC_EDIT17, L1);
	DDX_Text(pDX, IDC_EDIT18, l);
	DDX_Text(pDX, IDC_EDIT19, l1);
	DDX_Text(pDX, IDC_EDIT20, l2);
	DDX_Text(pDX, IDC_EDIT21, B);
	DDX_Text(pDX, IDC_EDIT22, b1);
	DDX_Text(pDX, IDC_EDIT23, R);
	DDX_Control(pDX, IDC_COMBO1, execution2);
	DDX_Text(pDX, IDC_EDIT24, lDeep);
	DDX_Text(pDX, IDC_EDIT25, B1);
	DDX_Text(pDX, IDC_EDIT2, d_star);
	DDX_Text(pDX, IDC_EDIT3, H);
}


BEGIN_MESSAGE_MAP(CNewDialog2, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CNewDialog2::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDOK, &CNewDialog2::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewDialog2 message handlers

void CNewDialog2::OnCbnSelchangeCombo2()
{
	// Получаем индекс выбранного элемента
	int selectedIndex = execution2.GetCurSel();

	// Проверяем выбранный элемент и устанавливаем значения переменных соответственно
	if (selectedIndex == 0) // Выбрано "1"
	{
		D = 53;
		D1 = 50;
		D2 = 26;
		d = 12;
		L = 81;
		L1 = 48;
		l = 15;
		l1 = 28;
		l2 = 10;
		B = 10;
		b1 = 5;
		R = 1.6;
		lDeep = 30;
		B1 = 14;
		d_star = 26;
		H = 15;
	}
	else if (selectedIndex == 1) // Выбрано "2"
	{
		D = 71;
		D1 = 70;
		D2 = 30;
		d = 16;
		L = 101;
		L1 = 58;
		l = 15;
		l1 = 28;
		l2 = 10;
		B = 12;
		b1 = 6;
		R = 1.6;
		lDeep = 40;
		B1 = 16;
		d_star = 30;
		H = 15;
	}
	else if (selectedIndex == 2) // Выбрано "3"
	{
		D = 85;
		D1 = 80;
		D2 = 36;
		d = 20;
		L = 128;
		L1 = 75;
		l = 22;
		l1 = 40;
		l2 = 12;
		B = 14;
		b1 = 7;
		R = 2;
		lDeep = 50;
		B1 = 16;
		d_star = 30;
		H = 22;
	}
	else if (selectedIndex == 3) // Выбрано "4"
	{
		D = 105;
		D1 = 100;
		D2 = 45;
		d = 25;
		L = 148;
		L1 = 85;
		l = 22;
		l1 = 40;
		l2 = 12;
		B = 16;
		b1 = 8;
		R = 2;
		lDeep = 60;
		B1 = 25;
		d_star = 36;
		H = 22;
	}
	else if (selectedIndex == 4) // Выбрано "5"
	{
		D = 135;
		D1 = 130;
		D2 = 55;
		d = 32;
		L = 191;
		L1 = 108;
		l = 25;
		l1 = 48;
		l2 = 12;
		B = 18;
		b1 = 9;
		R = 3;
		lDeep = 80;
		B1 = 32;
		d_star = 45;
		H = 25;
	}
	else if (selectedIndex == 5) // Выбрано "6"
	{
		D = 166;
		D1 = 160;
		D2 = 63;
		d = 38;
		L = 196;
		L1 = 113;
		l = 30;
		l1 = 56;
		l2 = 12;
		B = 20;
		b1 = 10;
		R = 3;
		lDeep = 80;
		B1 = 38;
		d_star = 56;
		H = 30;
	}


	// Обновляем данные на диалоговом окне
	UpdateData(FALSE);
}


void CNewDialog2::OnBnClickedOk()
{
	BeginWaitCursor();

	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!pKompasApp55)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp55 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp55 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp55);
		if (FAILED(hRes)) {
			return;
		}
	}

	// делаем Компас видимым
	pKompasApp55->Visible = true;
	pDoc2 = pKompasApp55->Document3D();
	pDoc2->Create(false, true);
	pPart2 = pDoc2->GetPart(pTop_Part);
	ksEntityPtr pSketch = pPart2->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart2->GetDefaultEntity(o3d_planeXOY));
	pSketch->Create();
	ksDocument2DPtr p2DDoc = pSketchDef->BeginEdit();
	UpdateData();
	double star_D1 = D1;
	double star_r = R;
	double star_H = H;
	double star_d = d_star;
	double star_B = B;

	//создаем вспомогательный эскиз круга для создания звезды 
	p2DDoc->ksCircle(0, 0, star_d / 2, 1);
	pSketchDef->EndEdit();

	//выдавливаем эскиз
	ksEntityPtr pExtrudeDowel_st = pPart2->NewEntity(o3d_baseExtrusion);
	ksBaseExtrusionDefinitionPtr pBaseDef_st = pExtrudeDowel_st->GetDefinition();
	pBaseDef_st->directionType = dtNormal;
	pBaseDef_st->SetSketch(pSketch);
	pBaseDef_st->SetSideParam(true, etBlind, star_H, 0, false);
	pExtrudeDowel_st->Create();

	//смещенная плоскость для создания лучиков звезды
	ksEntityPtr pPlane_st = pPart2->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr pPlaneDef_st = pPlane_st->GetDefinition();
	pPlaneDef_st->direction = true;
	pPlaneDef_st->offset = star_H;
	pPlaneDef_st->SetPlane(pPart2->GetDefaultEntity(o3d_planeXOY));
	pPlane_st->Create();

	//создание эскиза луча звезды (прямоугольник)
	ksEntityPtr pSketch_st = pPart2->NewEntity(o3d_sketch);
	pSketchDef = pSketch_st->GetDefinition();
	pSketchDef->SetPlane(pPlane_st);
	pSketch_st->Create();
	p2DDoc = pSketchDef->BeginEdit();

	p2DDoc->ksLineSeg(0, star_B / 2, star_D1, star_B / 2, 1);
	p2DDoc->ksLineSeg(star_D1, star_B / 2, star_D1, -star_B / 2, 1);
	p2DDoc->ksLineSeg(star_D1, -star_B / 2, 0, -star_B / 2, 1);
	p2DDoc->ksLineSeg(0, star_B / 2, 0, -star_B / 2, 1);
	pSketchDef->EndEdit();

	//выдавливание эскиза луча
	ksEntityPtr pExtrudeDowel_st1 = pPart2->NewEntity(o3d_baseExtrusion);
	ksBaseExtrusionDefinitionPtr pBaseDef_st1 = pExtrudeDowel_st1->GetDefinition();
	pBaseDef_st1->directionType = dtReverse;
	pBaseDef_st1->SetSketch(pSketch_st);
	pBaseDef_st1->SetSideParam(false, etBlind, star_H, 0, false);
	pExtrudeDowel_st1->Create();

	//круговой массив 
	ksEntityPtr pEx1 = pPart2->NewEntity(o3d_circularCopy);
	//Получаем интерфейс параметрова операции
	ksCircularCopyDefinitionPtr CircularCopyDefinition = pEx1->GetDefinition();
	//Количество копий в радиальном направлении
	CircularCopyDefinition->count1 = 1;
	//Устанавливаем ось операции
	CircularCopyDefinition->SetAxis(pPart2->GetDefaultEntity(o3d_axisOZ));
	//Устанавливаем параметры копирования
	CircularCopyDefinition->SetCopyParamAlongDir(6, 60, FALSE, FALSE);
	//Получаем массив копируемых элементов
	ksEntityCollectionPtr EntityCollection = CircularCopyDefinition->GetOperationArray();
	EntityCollection->Clear();
	//Заполняем массив копируемыъ элементов
	EntityCollection->Add(pExtrudeDowel_st1);
	//Создаем операцию
	pEx1->Create();

	//создание на ранее созданной смещенной плоскости эскизов кругов для дальнейшего обрезание лучей и их скругления
	ksEntityPtr pSketch_st1 = pPart2->NewEntity(o3d_sketch);
	pSketchDef = pSketch_st1->GetDefinition();
	pSketchDef->SetPlane(pPlane_st);
	pSketch_st1->Create();
	p2DDoc = pSketchDef->BeginEdit();

	p2DDoc->ksCircle(0, 0, star_D1 / 2, 1);
	p2DDoc->ksCircle(0, 0, star_D1 * 2, 1);
	pSketchDef->EndEdit();

	//вырезаем выдавливанием эскиз кругов
	ksEntityPtr pExtrude_st = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef_st = pExtrude_st->GetDefinition();
	pCutDef_st->directionType = dtNormal;
	pCutDef_st->SetSketch(pSketch_st1);
	pCutDef_st->SetSideParam(true, etThroughAll, 0, 0, false);
	pExtrude_st->Create();

	//получившиеся скругленные края называем circle для дальнейшего применения соосности
	ksEntityCollectionPtr flFaces = pPart2->EntityCollection(o3d_face);
	for (int i = 0; i < flFaces->GetCount(); i++)
	{
		ksEntityPtr face = flFaces->GetByIndex(i);
		ksFaceDefinitionPtr def = face->GetDefinition();
		if (def->GetOwnerEntity() == pExtrude_st)
		{
			face->Putname("circle");
			face->Update();
		}
	}

	//создаем необходимые скругления
	ksEntityCollectionPtr fledges1 = pPart2->EntityCollection(o3d_edge);
	ksEntityPtr pFillet = pPart2->NewEntity(o3d_fillet);
	ksFilletDefinitionPtr pFilletDef = pFillet->GetDefinition();
	pFilletDef->radius = R;
	ksEntityCollectionPtr fl1 = pFilletDef->array();
	fl1->Clear();
	int k = 0;
	int k2 = 0;
	int k3 = 0;
	for (int i = 0; i < fledges1->GetCount(); i++)
	{
		ksEntityPtr ed = fledges1->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();


		if (def->IsStraight())
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			if (p1 && p2)
			{
				p1->GetPoint(&x1, &y1, &z1);
				p2->GetPoint(&x2, &y2, &z2);
				if (abs(z1) == l && ceil(abs(x1)) == D1 / 2 && abs(int(y1)) != B / 2 && k == 0)
				{
					//называем верхнюю грань
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("starTOP");
					face->Update();
					k++;
				}
				if (abs(x1 - x2) < 0.0001 && abs(y1 - y2) < 0.0001)
				{
					if (z1 == 0 && int(y1) == -B / 2 && k3 == 1 && ceil(abs(x1)) == D1 / 2) {
						//называем внутреннюю часть зуба
						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Putname("star_tor2");
						face->Update();
						k3++;
					}
				}
				if (abs(x1 - x2) < 0.0001 && abs(y1 - y2) < 0.0001)
				{
					fl1->Add(ed);
					if (z1 == 0 && k2 == 0) {
						//называем другую внутреннюю часть зуба
						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Putname("star_tor");
						face->Update();
						k2++;
						k3 = 1;
					}
				}
			}
		}
	}

	pFillet->Create();

	//сохраняем звезду
	pDoc2->SaveAs("D:\\kursachTEST\\star2.m3d");

	//создаем новый документ, где будем строить муфту
	pDoc2 = pKompasApp55->Document3D();
	pDoc2->Create(false, true);
	pPart2 = pDoc2->GetPart(pTop_Part);
	pSketch = pPart2->NewEntity(o3d_sketch);
	pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart2->GetDefaultEntity(o3d_planeXOY));
	pSketch->Create();
	p2DDoc = pSketchDef->BeginEdit();
	UpdateData();

	double mufta_2isp_B1 = B1;
	double mufta_2isp_D = D;
	double mufta_2isp_D1 = D1;
	double mufta_2isp_D2 = D2;
	double mufta_2isp_d = d;
	double mufta_2isp_L1 = L1;
	double mufta_2isp_l = lDeep;
	double mufta_2isp_B = B/2;
	double mufta_2isp_L = L;
	double mufta_2isp_l_deep = lDeep;

	//эскиз для муфты
	p2DDoc->ksLineSeg(0, -mufta_2isp_B1 / 2, 0, -mufta_2isp_D / 2, 1);
	p2DDoc->ksLineSeg(0, -mufta_2isp_D / 2, mufta_2isp_l, -mufta_2isp_D / 2, 1);
	p2DDoc->ksLineSeg(mufta_2isp_l, -mufta_2isp_D / 2, mufta_2isp_l, -mufta_2isp_D2 / 2, 1);
	p2DDoc->ksLineSeg(mufta_2isp_l, -mufta_2isp_D2 / 2, mufta_2isp_L1, -mufta_2isp_D2 / 2, 1);
	p2DDoc->ksLineSeg(mufta_2isp_L1, -mufta_2isp_D2 / 2, mufta_2isp_L1, -mufta_2isp_d / 2, 1);
	p2DDoc->ksLineSeg(mufta_2isp_L1, -mufta_2isp_d / 2, mufta_2isp_L1 - mufta_2isp_l_deep, -mufta_2isp_d / 2, 1);
	p2DDoc->ksLineSeg(mufta_2isp_L1 - mufta_2isp_l_deep, -mufta_2isp_d / 2, mufta_2isp_L1 - mufta_2isp_l_deep, -mufta_2isp_B1 / 2, 1);
	p2DDoc->ksLineSeg(mufta_2isp_L1 - mufta_2isp_l_deep, -mufta_2isp_B1 / 2, 0, -mufta_2isp_B1 / 2, 1);
	p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);
	pSketchDef->EndEdit();

	//выдавливаем вращением полученный эскиз
	ksEntityPtr pRotate2 = pPart2->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotDef2 = pRotate2->GetDefinition();
	pRotDef2->SetSketch(pSketch);
	pRotDef2->SetSideParam(TRUE, 360);
	pRotate2->Create();

	//создание эскиза двух треугольников с углом 60 градусов для вырезания зубьев муфты
	ksEntityPtr pSketch_muft_pl7 = pPart2->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl7 = pSketch_muft_pl7->GetDefinition();
	pSketchDef_muft_pl7->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl7->Create();
	p2DDoc = pSketchDef_muft_pl7->BeginEdit();
	UpdateData();
	double angle_BAC_degrees = 60;  // Угол BAC
	double length_BC2 = mufta_2isp_D * 5;  // Длина стороны BC2
	double y_A2 = 0;
	double x_B2 = length_BC2 * cos(angle_BAC_degrees * PI / 180.0);
	double y_B2 = length_BC2 * sin(angle_BAC_degrees * PI / 180.0);
	double x_C2 = -length_BC2 * cos(angle_BAC_degrees * PI / 180.0);
	double y_C2 = length_BC2 * sin(angle_BAC_degrees * PI / 180.0);
	double length_BC = mufta_2isp_D * 3;  // Длина стороны BC
	// Координаты точки A (начальная точка)
	double x_A = 0;
	double y_A = B;
	double y_A3 = -B;
	// Координаты точки B (конечная точка первой линии)
	double x_B = length_BC * cos(angle_BAC_degrees * PI / 180.0);
	double y_B = y_A + length_BC * sin(angle_BAC_degrees * PI / 180.0);
	double y_B3 = -y_A + length_BC * sin(angle_BAC_degrees * PI / 180.0);
	// Координаты точки C (конечная точка второй линии)
	double x_C = -length_BC * cos(angle_BAC_degrees * PI / 180.0);
	double y_C = y_A + length_BC * sin(angle_BAC_degrees * PI / 180.0);
	double y_C3 = -y_A + length_BC * sin(angle_BAC_degrees * PI / 180.0);

	p2DDoc->ksLineSeg(x_A, y_A, x_B, y_B, 1);
	p2DDoc->ksLineSeg(x_A, y_A, x_C, y_C, 1);
	p2DDoc->ksLineSeg(x_B, y_B, x_C, y_C, 1);

	p2DDoc->ksLineSeg(x_A, y_A2, x_B2, y_B2, 1);
	p2DDoc->ksLineSeg(x_A, y_A2, x_C2, y_C2, 1);
	p2DDoc->ksLineSeg(x_B2, y_B2, x_C2, y_C2, 1);

	pSketchDef_muft_pl7->EndEdit();

	//вырезаем полученные эскизы
	ksEntityPtr pExtrude9 = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef9 = pExtrude9->GetDefinition();
	pCutDef9->directionType = dtNormal;
	pCutDef9->SetSketch(pSketchDef_muft_pl7);
	pCutDef9->SetSideParam(true, etBlind, H, 0, false);
	pExtrude9->Create();


	
	//строим два треугольника для создания выступов у зубьев
	double glubina_tre4 =  H+(L1-lDeep-H);
	ksEntityPtr pSketch_muft_pl5 = pPart2->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl5 = pSketch_muft_pl5->GetDefinition();
	pSketchDef_muft_pl5->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl5->Create();
	p2DDoc = pSketchDef_muft_pl5->BeginEdit();
	UpdateData();

	double length_BC69 = mufta_2isp_D * 5;  // Длина стороны BC
	double length_BC77 = mufta_2isp_D * 3;  // Длина стороны BC

	// Координаты точки A (начальная точка)
	double x_A69 = 0;
	double y_A69 = -sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2));
	double y_A77 = 0;
	// Координаты точки B (конечная точка первой линии)
	double x_B69 = length_BC69 * cos(angle_BAC_degrees * PI / 180.0);
	double y_B69 = y_A69 + length_BC69 * sin(angle_BAC_degrees * PI / 180.0);
	double x_B77 = length_BC77 * cos(angle_BAC_degrees * PI / 180.0);
	double y_B77 = length_BC77 * sin(angle_BAC_degrees * PI / 180.0);
	// Координаты точки C (конечная точка второй линии)
	double x_C69 = -length_BC69 * cos(angle_BAC_degrees * PI / 180.0);
	double y_C69 = y_A69 + length_BC69 * sin(angle_BAC_degrees * PI / 180.0);
	double x_C77 = -length_BC77 * cos(angle_BAC_degrees * PI / 180.0);
	double y_C77 = y_A77 + length_BC77 * sin(angle_BAC_degrees * PI / 180.0);

	// Рисование линий
	p2DDoc->ksLineSeg(x_A69, y_A69, x_B69, y_B69, 1);
	p2DDoc->ksLineSeg(x_A69, y_A69, x_C69, y_C69, 1);
	p2DDoc->ksLineSeg(x_B69, y_B69, x_C69, y_C69, 1);

	p2DDoc->ksLineSeg(x_A69, y_A77, x_B77, y_B77, 1);
	p2DDoc->ksLineSeg(x_A69, y_A77, x_C77, y_C77, 1);
	p2DDoc->ksLineSeg(x_B77, y_B77, x_C77, y_C77, 1);

	pSketchDef_muft_pl5->EndEdit();

	//вырезаем эскизы
	ksEntityPtr pExtrude11 = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef11 = pExtrude11->GetDefinition();
	pCutDef11->directionType = dtNormal;
	pCutDef11->SetSketch(pSketchDef_muft_pl5);
	pCutDef11->SetSideParam(true, etBlind, glubina_tre4, 0, false);
	pExtrude11->Create();

	//создаем эскиз треугольников для удаления лишних элементов, получившися в итоге предыдущих операций
	ksEntityPtr pSketch_muft_pl174 = pPart2->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl174 = pSketch_muft_pl174->GetDefinition();
	pSketchDef_muft_pl174->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl174->Create();
	p2DDoc = pSketchDef_muft_pl174->BeginEdit();
	double length_BC174 = mufta_2isp_D * 4;  // Длина стороны BC
	// Координаты точки A (начальная точка)
	double x_A174 = 0;
	double y_A174 = 0;
	// Координаты точки B (конечная точка первой линии)
	double x_B174 = length_BC174 * cos(angle_BAC_degrees * PI / 180.0);
	double y_B174 = length_BC174 * sin(angle_BAC_degrees * PI / 180.0);
	// Координаты точки C (конечная точка второй линии)
	double x_C174 = -length_BC174 * cos(angle_BAC_degrees * PI / 180.0);
	double y_C174 = length_BC174 * sin(angle_BAC_degrees * PI / 180.0);
	double angle_shift_degrees = 60;  // Угол смещения
	// Преобразование угла смещения в радианы
	double angle_shift_radians = angle_shift_degrees * PI / 180.0;
	// Новые координаты точек B и C с учетом смещения
	double x_B174_shifted = x_B174 * cos(angle_shift_radians) - y_B174 * sin(angle_shift_radians);
	double y_B174_shifted = x_B174 * sin(angle_shift_radians) + y_B174 * cos(angle_shift_radians);
	double x_C174_shifted = x_C174 * cos(angle_shift_radians) - y_C174 * sin(angle_shift_radians);
	double y_C174_shifted = x_C174 * sin(angle_shift_radians) + y_C174 * cos(angle_shift_radians);

	// Рисование смещенных линий
	p2DDoc->ksLineSeg(x_A174, y_A174, x_B174_shifted, y_B174_shifted, 1);
	p2DDoc->ksLineSeg(x_A174, y_A174, x_C174_shifted, y_C174_shifted, 1);
	p2DDoc->ksLineSeg(x_B174_shifted, y_B174_shifted, x_C174_shifted, y_C174_shifted, 1);

	pSketchDef_muft_pl174->EndEdit();

	//вырезаем полученный эскиз
	ksEntityPtr pExtrude174 = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef174 = pExtrude174->GetDefinition();
	pCutDef174->directionType = dtNormal;
	pCutDef174->SetSketch(pSketchDef_muft_pl174);
	pCutDef174->SetSideParam(true, etBlind, glubina_tre4, 0, false);
	pExtrude174->Create();

	//создаем эскиз для выдавливания прямоугольника, который выпрямляет внутренние части зубьев
	ksEntityPtr pSketch_muft_pl777 = pPart2->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl777 = pSketch_muft_pl777->GetDefinition();
	pSketchDef_muft_pl777->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl777->Create();
	p2DDoc = pSketchDef_muft_pl777->BeginEdit();
	// Координаты вершин прямоугольника относительно его центра
	double y_A777 = 0;
	double x_A777 = -300;
	double y_B777 = 0;
	double x_B777 = 300;
	double y_C777 = B1;
	double x_C777 = 300;
	double y_D777 = B1;
	double x_D777 = -300;

	// Рисование прямоугольника
	p2DDoc->ksLineSeg(x_A777, y_A777, x_B777, y_B777, 1);
	p2DDoc->ksLineSeg(x_B777, y_B777, x_C777, y_C777, 1);
	p2DDoc->ksLineSeg(x_C777, y_C777, x_D777, y_D777, 1);
	p2DDoc->ksLineSeg(x_D777, y_D777, x_A777, y_A777, 1);

	pSketchDef_muft_pl777->EndEdit();

	//вырезаем полученный прямоугольник
	ksEntityPtr pExtrude777 = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef777 = pExtrude777->GetDefinition();
	pCutDef777->directionType = dtNormal;
	pCutDef777->SetSketch(pSketchDef_muft_pl777);
	pCutDef777->SetSideParam(true, etBlind, glubina_tre4, 0, false);
	pExtrude777->Create();

	//создаем круговой массив для повторения (3 раза) операций создания зубьев, выступов и прямоугольника
	ksEntityPtr pEx2 = pPart2->NewEntity(o3d_circularCopy);
	//Получаем интерфейс параметрова операции
	ksCircularCopyDefinitionPtr CircularCopyDefinition2 = pEx2->GetDefinition();
	//Количество копий в радиальном направлении
	CircularCopyDefinition2->count1 = 1;
	//Устанавливаем ось операции
	CircularCopyDefinition2->SetAxis(pPart2->GetDefaultEntity(o3d_axisOX));
	//Устанавливаем параметры копирования
	CircularCopyDefinition2->SetCopyParamAlongDir(3, 120, FALSE, FALSE);
	//Получаем массив копируемых элементов
	ksEntityCollectionPtr EntityCollection2 = CircularCopyDefinition2->GetOperationArray();
	EntityCollection2->Clear();
	//Заполняем массив копируемыъ элементов
	EntityCollection2->Add(pExtrude11);
	EntityCollection2->Add(pExtrude9);
	EntityCollection2->Add(pExtrude174);
	EntityCollection2->Add(pExtrude777);
	//Создаем операцию
	pEx2->Create();

	//называем плоскости, создаем фаски
	ksEntityCollectionPtr fledges = pPart2->EntityCollection(o3d_edge);
	ksEntityPtr pChamfer = pPart2->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamferDef = pChamfer->GetDefinition();
	pChamferDef->SetChamferParam(false, 1, 1);
	ksEntityCollectionPtr fl = pChamferDef->array();
	fl->Clear();
	int j = 0;
	int m = 0;
	for (int i = 0; i < fledges->GetCount(); i++)
	{
		ksEntityPtr ed = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();
		if (def->IsCircle())
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			if (p1 && p2)
			{
				p1->GetPoint(&x1, &y1, &z1);
				p2->GetPoint(&x2, &y2, &z2);
				if (abs(z1) < 0.001)
				{
					//создаем фаски
					fl->Add(ed);
				}
			}
		}
		if (def->IsStraight()) {
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			if (p1 && p2)
			{
				p1->GetPoint(&x1, &y1, &z1);
				p2->GetPoint(&x2, &y2, &z2);
				if (x1==l) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					if (f->IsPlanar() && j ==0) {
						//называем боковую грань зуба
						face->Putname("Face4Assembly");
						face->Update();
						j++;
					}
					if (!f->IsPlanar()){
						//называем внешнюю цилиндрическую часть муфты
						face->Putname("Face174Assembly");
						face->Update();
					}
				}
				if (x1 == 0 && m ==0) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					if (f->IsPlanar()) {
						//называем верхнюю плоскость зуба
						face->Putname("Face777Assembly");
						face->Update();
						m++;
					}
				}
			}
		}
	}
	pChamfer->Create();
	//сохраняем муфту
	pDoc2->SaveAs("D:\\kursachTEST\\mufta2.m3d");

	// создание нового документы сборки
	pDoc2 = pKompasApp55->Document3D();
	pDoc2->Create(false, false);
	pPart2 = pDoc2->GetPart(pTop_Part);
	ksPartPtr pBoss, pGear1, pGear2;
	//добавляем в сборку ранее созданные детали
	pDoc2->SetPartFromFile("D:\\kursachTEST\\star2.m3d", pPart2, true);
	pDoc2->SetPartFromFile("D:\\kursachTEST\\mufta2.m3d", pPart2, true);
	pDoc2->SetPartFromFile("D:\\kursachTEST\\mufta2.m3d", pPart2, true);
	pBoss = pDoc2->GetPart(0);
	pGear1 = pDoc2->GetPart(1);
	pGear2 = pDoc2->GetPart(2);

	//присваиваем граням переменные для создания зависимостей
	ksEntityCollectionPtr col2 = pBoss->EntityCollection(o3d_face);
	ksEntityPtr BossFace4Assemly0 = col2->GetByName("star_tor", true, true);
	ksEntityPtr BossFace4Assemly1 = col2->GetByName("starTOP", true, true);
	ksEntityPtr BossFace4Assemly2 = col2->GetByName("circle", true, true);
	ksEntityPtr BossFace4Assemly3 = col2->GetByName("star_tor2", true, true);

	col2 = pGear1->EntityCollection(o3d_face);
	ksEntityPtr Gear1Face4Assemly = col2->GetByName("Face4Assembly", true, true);
	ksEntityPtr Gear1Face4Assemly1 = col2->GetByName("Face174Assembly", true, true);
	ksEntityPtr Gear1Face4Assemly2 = col2->GetByName("Face777Assembly", true, true);

	col2 = pGear2->EntityCollection(o3d_face);
	ksEntityPtr Gear2Face4Assemly = col2->GetByName("Face4Assembly", true, true);
	ksEntityPtr Gear2Face4Assemly1 = col2->GetByName("Face174Assembly", true, true);
	ksEntityPtr Gear2Face4Assemly2 = col2->GetByName("Face777Assembly", true, true);
	
	//создаем зависимости (соосность)
	pDoc2->AddMateConstraint(mc_Concentric, BossFace4Assemly2, Gear1Face4Assemly1, -1, 1, 0);
	pDoc2->AddMateConstraint(mc_Concentric, BossFace4Assemly2, Gear2Face4Assemly1, 1, 0, 0);

	//создаем зависимости (совпадение)
	pDoc2->AddMateConstraint(mc_Coincidence, Gear1Face4Assemly, BossFace4Assemly0, -1, 1, 0);
	pDoc2->AddMateConstraint(mc_Coincidence, Gear2Face4Assemly, BossFace4Assemly3, -1, 1, 0);
	pDoc2->AddMateConstraint(mc_Coincidence, Gear2Face4Assemly2, BossFace4Assemly1, 1, 0, 0);

	pDoc2->RebuildDocument();
	//сохраняем документ сборки
	pDoc2->SaveAs("D:\\kursachTEST\\Assembly.a3d");
}

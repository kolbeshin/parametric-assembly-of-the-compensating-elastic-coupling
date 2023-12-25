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
	//circle 
	p2DDoc->ksCircle(0, 0, star_d / 2, 1);
	pSketchDef->EndEdit();

	//extrude
	ksEntityPtr pExtrudeDowel_st = pPart2->NewEntity(o3d_baseExtrusion);
	ksBaseExtrusionDefinitionPtr pBaseDef_st = pExtrudeDowel_st->GetDefinition();
	pBaseDef_st->directionType = dtNormal;
	pBaseDef_st->SetSketch(pSketch);
	pBaseDef_st->SetSideParam(true, etBlind, star_H, 0, false);
	pExtrudeDowel_st->Create();



	//tails star plane
	ksEntityPtr pPlane_st = pPart2->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr pPlaneDef_st = pPlane_st->GetDefinition();

	pPlaneDef_st->direction = true;
	pPlaneDef_st->offset = star_H;
	pPlaneDef_st->SetPlane(pPart2->GetDefaultEntity(o3d_planeXOY));
	pPlane_st->Create();

	//skatch tail
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

	//extrud one tail
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

	//округлость хвоста
	ksEntityPtr pPlane_st1 = pPart2->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr pPlaneDef_st1 = pPlane_st1->GetDefinition();
	pPlaneDef_st1->direction = true;
	pPlaneDef_st1->offset = star_H;
	pPlaneDef_st1->SetPlane(pPart2->GetDefaultEntity(o3d_planeXOY));
	pPlane_st1->Create();

	

	//skatch tail
	ksEntityPtr pSketch_st1 = pPart2->NewEntity(o3d_sketch);
	pSketchDef = pSketch_st1->GetDefinition();
	pSketchDef->SetPlane(pPlane_st1);
	pSketch_st1->Create();
	p2DDoc = pSketchDef->BeginEdit();

	p2DDoc->ksCircle(0, 0, star_D1 / 2, 1);
	p2DDoc->ksCircle(0, 0, star_D1 * 2, 1);
	pSketchDef->EndEdit();

	//срез округлостей
	ksEntityPtr pExtrude_st = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef_st = pExtrude_st->GetDefinition();
	pCutDef_st->directionType = dtNormal;
	pCutDef_st->SetSketch(pSketch_st1);
	pCutDef_st->SetSideParam(true, etThroughAll, 0, 0, false);
	pExtrude_st->Create();




	//скругления

	//ksEntityCollectionPtr fledges2 = pPart2->EntityCollection(o3d_edge);
	///*ksEntityCollectionPtr col = pPart2->EntityCollection(o3d_face);*/

	//ksEntityPtr pFillet2 = pPart2->NewEntity(o3d_fillet);

	//ksFilletDefinitionPtr pFilletDef2 = pFillet2->GetDefinition();
	//pFilletDef2->radius = plus_R;
	//ksEntityCollectionPtr fl2 = pFilletDef2->array();
	//fl2->Clear();
	//fl2->Add(pEx1);
	//fl2->Add(pExtrudeDowel_st1);
	//fl2->Add(pExtrudeDowel_st);

	//for (int i = 0; i < fledges2->GetCount(); i++)
	//{
	//	ksEntityPtr ed = fledges2->GetByIndex(i);
	//	ksEdgeDefinitionPtr def = ed->GetDefinition();
	//	if (def->GetOwnerEntity() == fl2)
	//	{
	//		if (def->IsCircle())
	//		{
	//			fl2->Add(ed);
	//		}
	//	}

	//}
	//for (int i = 0; i < fledges2->GetCount(); i++)
	//{
	//	ksEntityPtr ed = fledges2->GetByIndex(i);
	//	ksEdgeDefinitionPtr def = ed->GetDefinition();


	//	if (def->IsCircle())
	//	{

	//		ksVertexDefinitionPtr p1 = def->GetVertex(true);
	//		ksVertexDefinitionPtr p2 = def->GetVertex(false);
	//		double x1, y1, z1, x2, y2, z2;
	//		if (p1 && p2)
	//		{
	//			p1->GetPoint(&x1, &y1, &z1);
	//			p2->GetPoint(&x2, &y2, &z2);
	//			//((x1 > 0 && y1 > 0) || (x2 > 0 && y2 < 0)) && 
	//			if (abs(x1 - x2) < 0.0001 && abs(y1 - y2) < 0.0001)
	//			{
	//				//ed->Putname("LoftEdge");
	//				fl1->Add(ed);
	//			}

	//		}

	//	}
	//}

	//ksEntityCollectionPtr fledges2 = pPart2->EntityCollection(o3d_edge);
	//ksEntityPtr pFillet2 = pPart2->NewEntity(o3d_fillet);

	//ksFilletDefinitionPtr pFilletDef2 = pFillet2->GetDefinition();
	//pFilletDef2->radius = R;
	//ksEntityCollectionPtr fl2 = pFilletDef2->array();
	//fl2->Clear();

	//for (int i = 0; i < fledges2->GetCount(); i++)
	//{
	//	ksEntityPtr ed = fledges2->GetByIndex(i);
	//	ksEdgeDefinitionPtr def = ed->GetDefinition();
	//	if (def->GetOwnerEntity() == pExtrudeDowel_st1)
	//	{
	//		ksVertexDefinitionPtr p1 = def->GetVertex(true);
	//		ksVertexDefinitionPtr p2 = def->GetVertex(false);
	//		double x1, y1, z1, x2, y2, z2;
	//		p1->GetPoint(&x1, &y1, &z1);
	//		p2->GetPoint(&x2, &y2, &z2);

	//		if (z1 == B) { // l = 10.5;
	//			ksFaceDefinitionPtr f_star1_1 = def->GetAdjacentFace(true);
	//			ksEntityPtr face_star1_1 = f_star1_1->GetEntity();
	//			face_star1_1->Putname("star_plane_1");
	//			face_star1_1->Update();
	//		}

	//		if (z1 == 0 && z2 == 0) {
	//			ksFaceDefinitionPtr f_star1_2 = def->GetAdjacentFace(false);
	//			ksEntityPtr face_star1_2 = f_star1_2->GetEntity();
	//			face_star1_2->Putname("star_plane_2");
	//			face_star1_2->Update();
	//		}
	//	}
	//}
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
	//pFillet2->Create();
	ksEntityCollectionPtr fledges1 = pPart2->EntityCollection(o3d_edge);
	/*ksEntityCollectionPtr col = pPart->EntityCollection(o3d_face);*/

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
				/*if (ceil(abs(x1)) == D1 / 2)
				{
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);

					ksEntityPtr face = f->GetEntity();
					if (f->IsCylinder()) {
						face->Putname("XXX");

						face->Update();
					}
				}*/
				
				if (abs(z1) == l && ceil(abs(x1)) == D1 / 2 && abs(int(y1)) != B / 2 && k == 0)
				{
					
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);

					ksEntityPtr face = f->GetEntity();

					face->Putname("starTOP");

					face->Update();
					k++;
					
					

				}
				if (abs(x1 - x2) < 0.0001 && abs(y1 - y2) < 0.0001)
				{
					if (z1 == 0 && int(y1) == -B / 2 && k3 == 1 && ceil(abs(x1)) == D1 / 2) {
						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);

						ksEntityPtr face = f->GetEntity();

						face->Putname("star_tor2");

						face->Update();
						k3++;
					}
				}
				/*if (ceil(abs(x1)) == D1 / 2 && abs(int(y1)) != B / 2 && k == 0)
				{


					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);

					ksEntityPtr face = f->GetEntity();

					face->Putname("starCIRC");

					face->Update();
					k++;


				}*/
				//((x1 > 0 && y1 > 0) || (x2 > 0 && y2 < 0)) && 
				if (abs(x1 - x2) < 0.0001 && abs(y1 - y2) < 0.0001)
				{
					//ed->Putname("LoftEdge");
					fl1->Add(ed);
					if (z1 == 0 && k2 == 0) {

						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);

						ksEntityPtr face = f->GetEntity();

						face->Putname("star_tor");

						face->Update();
						k2++;
						k3 = 1;

					}
					
					
					
					/*if (z1 == H) {

						ksFaceDefinitionPtr f2 = def->GetAdjacentFace(true);

						ksEntityPtr face2 = f2->GetEntity();

						face2->Putname("star_tor");

						face2->Update();

					}*/
				}

			}

		}
	}

	pFillet->Create();


	pDoc2->SaveAs("D:\\kursachTEST\\star.m3d");

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
	/*double mufta_2isp_d1 = D2;*/
	/*double mufta_2isp_R = R;*/
	double mufta_2isp_D = D;
	double mufta_2isp_D1 = D1;
	double mufta_2isp_D2 = D2;
	/*double mufta_2isp_b = 4;*/
	double mufta_2isp_d = d;
	double mufta_2isp_L1 = L1;
	double mufta_2isp_l = lDeep;
	double mufta_2isp_B = B/2;
	double mufta_2isp_L = L;
	double mufta_2isp_l_deep = lDeep;

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

	ksEntityPtr pRotate2 = pPart2->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotDef2 = pRotate2->GetDefinition();
	pRotDef2->SetSketch(pSketch);
	pRotDef2->SetSideParam(TRUE, 360);

	pRotate2->Create();


	////эскиз для выреза поломуфтья
	//ksEntityPtr pSketch_muft_f2 = pPart2->NewEntity(o3d_sketch);
	//ksSketchDefinitionPtr pSketchDef_muft_f2 = pSketch_muft_f2->GetDefinition();
	//pSketchDef_muft_f2->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	//pSketch_muft_f2->Create();
	//p2DDoc = pSketchDef_muft_f2->BeginEdit();
	//UpdateData();

	///*p2DDoc->ksLineSeg(mufta_1isp_B1 / 2 * cos(PI / 4), mufta_1isp_B1 / 2 * sin(PI / 4),  1);*/

	//p2DDoc->ksLineSeg(-30, mufta_2isp_B1 / 2, 30, mufta_2isp_B1 / 2, 1);
	//p2DDoc->ksLineSeg(30, mufta_2isp_B1 / 2, 30, -mufta_2isp_B1 / 2, 1);
	//p2DDoc->ksLineSeg(30, -mufta_2isp_B1 / 2, -30, -mufta_2isp_B1 / 2, 1);
	//p2DDoc->ksLineSeg(-30, -mufta_2isp_B1 / 2, -30, mufta_2isp_B1 / 2, 1);

	//pSketchDef_muft_f2->EndEdit();



	//double glubina_rect3 = mufta_2isp_L1 - mufta_2isp_l;
	//ksEntityPtr pExtrude8 = pPart2->NewEntity(o3d_cutExtrusion);
	//ksCutExtrusionDefinitionPtr pCutDef8 = pExtrude8->GetDefinition();
	//pCutDef8->directionType = dtNormal;
	//pCutDef8->SetSketch(pSketchDef_muft_f2);
	//pCutDef8->SetSideParam(true, etBlind, glubina_rect3, 0, false);
	//pExtrude8->Create();


	//строем вырез под полумуфты



	//пальцы

	//palec 1

	//double x2 = 0;
	//double y2 = 0;
	//int k = 0;
	//for (double x = 0; x < 100; x+=0.1) {
	//	for (double y = 0; y < 100; y+=0.1) {
	//		if (atan((x-0)/ (y - sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2)))) == 30) {
	//			k = 1;
	//			x2 = x;
	//			y2 = y;
	//			break;
	//		}
	//	}
	//	if (k == 1)
	//		break;
	//	
	//}

	//ksEntityPtr pSketch_muft_pl7 = pPart2->NewEntity(o3d_sketch);
	//ksSketchDefinitionPtr pSketchDef_muft_pl7 = pSketch_muft_pl7->GetDefinition();
	//pSketchDef_muft_pl7->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	//pSketch_muft_pl7->Create();
	//p2DDoc = pSketchDef_muft_pl7->BeginEdit();
	//UpdateData();

	//double angle_BAC_degrees = 60;  // Угол BAC

	//double length_BC2 = mufta_2isp_D * 5;  // Длина стороны BC

	//double y_A2 = 0;

	//double x_B2 = length_BC2 * cos(angle_BAC_degrees * PI / 180.0);
	//double y_B2 = length_BC2 * sin(angle_BAC_degrees * PI / 180.0);

	//double x_C2 = -length_BC2 * cos(angle_BAC_degrees * PI / 180.0);
	//double y_C2 = length_BC2 * sin(angle_BAC_degrees * PI / 180.0);


	//double length_BC = mufta_2isp_D * 3;  // Длина стороны BC

	//// Координаты точки A (начальная точка)
	//double x_A = 0;
	//double y_A = B*2;
	//double y_A3 = -B * 2;
	//// Координаты точки B (конечная точка первой линии)
	//double x_B = length_BC * cos(angle_BAC_degrees * PI / 180.0);
	//double y_B = y_A + length_BC * sin(angle_BAC_degrees * PI / 180.0);
	//double y_B3 = -y_A + length_BC * sin(angle_BAC_degrees * PI / 180.0);
	//// Координаты точки C (конечная точка второй линии)
	//double x_C = -length_BC * cos(angle_BAC_degrees * PI / 180.0);
	//double y_C = y_A - length_BC * sin(angle_BAC_degrees * PI / 180.0);
	//double y_C3 = -y_A + length_BC * sin(angle_BAC_degrees * PI / 180.0);
	//// Рисование линий
	//p2DDoc->ksLineSeg(x_A, y_A, x_B, y_B, 1);
	//p2DDoc->ksLineSeg(x_A, y_A, x_C, y_C, 1);
	//p2DDoc->ksLineSeg(x_B, y_B, x_C, y_C, 1);

	//p2DDoc->ksLineSeg(x_A, y_A2, x_B2, y_B2, 1);
	//p2DDoc->ksLineSeg(x_A, y_A2, x_C2, y_C2, 1);
	//p2DDoc->ksLineSeg(x_B2, y_B2, x_C2, y_C2, 1);
	
	
	//double angle_BAC_degrees = 60;  // Угол BAC
	//double length_BC_outer = mufta_2isp_D * 5;  // Длина стороны BC внешнего треугольника
	//double distance_between_triangles = 10;  // Желаемое расстояние между сторонами

	//// Координаты точек внешнего треугольника
	//double x_A_outer = 0;
	//double y_A_outer = 0;

	//double x_B_outer = length_BC_outer * cos(angle_BAC_degrees * PI / 180.0);
	//double y_B_outer = length_BC_outer * sin(angle_BAC_degrees * PI / 180.0);

	//double x_C_outer = -length_BC_outer * cos(angle_BAC_degrees * PI / 180.0);
	//double y_C_outer = length_BC_outer * sin(angle_BAC_degrees * PI / 180.0);

	//// Рисование внешнего треугольника
	//p2DDoc->ksLineSeg(x_A_outer, y_A_outer, x_B_outer, y_B_outer, 1);
	//p2DDoc->ksLineSeg(x_B_outer, y_B_outer, x_C_outer, y_C_outer, 1);
	//p2DDoc->ksLineSeg(x_C_outer, y_C_outer, x_A_outer, y_A_outer, 1);

	//// Найдем точку D для внутреннего треугольника
	//double x_D_inner = x_A_outer;
	//double y_D_inner = y_A_outer + distance_between_triangles;

	//// Координаты точек внутреннего треугольника
	//double x_A_inner = x_D_inner;
	//double y_A_inner = y_D_inner;

	//double x_B_inner = x_B_outer;
	//double y_B_inner = y_B_outer + distance_between_triangles;

	//double x_C_inner = x_C_outer;
	//double y_C_inner = y_C_outer + distance_between_triangles;

	//// Рисование внутреннего треугольника
	//p2DDoc->ksLineSeg(x_A_inner, y_A_inner, x_B_inner, y_B_inner, 1);
	//p2DDoc->ksLineSeg(x_B_inner, y_B_inner, x_C_inner, y_C_inner, 1);
	//p2DDoc->ksLineSeg(x_C_inner, y_C_inner, x_A_inner, y_A_inner, 1);


	/*pSketchDef_muft_pl7->EndEdit();*/
	ksEntityPtr pSketch_muft_pl7 = pPart2->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl7 = pSketch_muft_pl7->GetDefinition();
	pSketchDef_muft_pl7->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl7->Create();
	p2DDoc = pSketchDef_muft_pl7->BeginEdit();
	UpdateData();

	//внутренний
	/*p2DDoc->ksLineSeg(0, sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2)), -(mufta_2isp_D * 3 * sin(60)), -(mufta_2isp_D * 3 * cos(60) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), 1);
	p2DDoc->ksLineSeg(0, sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2)), mufta_2isp_D * 3 * sin(60),-( mufta_2isp_D * 3 * cos(60) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), 1);
	p2DDoc->ksLineSeg(-mufta_2isp_D * 3 * sin(60), -(mufta_2isp_D * 3 * cos(60) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), mufta_2isp_D * 3 * sin(60),- (mufta_2isp_D * 3 * cos(60) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), 1);*/

	double angle_BAC_degrees = 60;  // Угол BAC
	//double length_BC = mufta_2isp_D * 3;  // Длина стороны BC
	double length_BC2 = mufta_2isp_D * 5;  // Длина стороны BC
	//// Координаты точки A (начальная точка)
	//double x_A = 0;
	//double y_A = sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2));
	double y_A2 = 0;
	//// Координаты точки B (конечная точка первой линии)
	//double x_B = length_BC * cos(angle_BAC_degrees * PI / 180.0);
	//double y_B = length_BC * sin(angle_BAC_degrees * PI / 180.0) + y_A;
	double x_B2 = length_BC2 * cos(angle_BAC_degrees * PI / 180.0);
	double y_B2 = length_BC2 * sin(angle_BAC_degrees * PI / 180.0);
	//// Координаты точки C (конечная точка второй линии)
	//double x_C = -length_BC * cos(angle_BAC_degrees * PI / 180.0);
	//double y_C = length_BC * sin(angle_BAC_degrees * PI / 180.0);
	double x_C2 = -length_BC2 * cos(angle_BAC_degrees * PI / 180.0);
	double y_C2 = length_BC2 * sin(angle_BAC_degrees * PI / 180.0);
	//// Рисование линий
	//p2DDoc->ksLineSeg(x_A, y_A, x_B, y_B, 1);
	//p2DDoc->ksLineSeg(x_A, y_A, x_C, y_C, 1);
	//p2DDoc->ksLineSeg(x_B, y_B, x_C, y_C, 1);





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




	//p2DDoc->ksLineSeg(100, 0, -100, 0, 1);
	//p2DDoc->ksLineSeg(100, 0, 100, 100, 1);
	//p2DDoc->ksLineSeg(100, 100, -100, 100, 1);
	//p2DDoc->ksLineSeg(-100, 100, -100, 0, 1);

	//внешний 
	//p2DDoc->ksLineSeg(0, 0, -mufta_2isp_D * 5 * sin(60), -mufta_2isp_D * 5  * cos(60) , 1);
	//p2DDoc->ksLineSeg(0,0, mufta_2isp_D * 5 * sin(60), -mufta_2isp_D * 5 * cos(60), 1);
	//p2DDoc->ksLineSeg(-mufta_2isp_D * 5 * sin(60), -mufta_2isp_D * 5 * cos(60), mufta_2isp_D * 5 * sin(60), -mufta_2isp_D * 5 * cos(60), 1);

	p2DDoc->ksLineSeg(x_A, y_A2, x_B2, y_B2, 1);
	p2DDoc->ksLineSeg(x_A, y_A2, x_C2, y_C2, 1);
	p2DDoc->ksLineSeg(x_B2, y_B2, x_C2, y_C2, 1);

	pSketchDef_muft_pl7->EndEdit();


	ksEntityPtr pExtrude9 = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef9 = pExtrude9->GetDefinition();
	pCutDef9->directionType = dtNormal;
	pCutDef9->SetSketch(pSketchDef_muft_pl7);
	pCutDef9->SetSideParam(true, etBlind, H, 0, false);
	pExtrude9->Create();


	////palec 2
	//ksEntityPtr pSketch_muft_pl8 = pPart2->NewEntity(o3d_sketch);
	//ksSketchDefinitionPtr pSketchDef_muft_pl8 = pSketch_muft_pl8->GetDefinition();
	//pSketchDef_muft_pl8->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	//pSketch_muft_pl8->Create();
	//p2DDoc = pSketchDef_muft_pl8->BeginEdit();
	//UpdateData();


	//p2DDoc->ksLineSeg(0, -sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2)), -100 * cos(45), -(100 * cos(45) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), 1);
	//p2DDoc->ksLineSeg(0, -sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2)), 100 * cos(45), -(100 * cos(45) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), 1);
	//p2DDoc->ksLineSeg(-100 * cos(45), -(100 * cos(45) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), 100 * cos(45), -(100 * cos(45) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), 1);

	//p2DDoc->ksLineSeg(100, 0, -100, 0, 1);
	//p2DDoc->ksLineSeg(100, 0, 100, -100, 1);
	//p2DDoc->ksLineSeg(100, -100, -100, -100, 1);
	//p2DDoc->ksLineSeg(-100, -100, -100, 0, 1);


	//pSketchDef_muft_pl8->EndEdit();


	//ksEntityPtr pExtrude10 = pPart2->NewEntity(o3d_cutExtrusion);
	//ksCutExtrusionDefinitionPtr pCutDef10 = pExtrude10->GetDefinition();
	//pCutDef10->directionType = dtNormal;
	//pCutDef10->SetSketch(pSketchDef_muft_pl8);
	//pCutDef10->SetSideParam(true, etBlind, l, 0, false);
	//pExtrude10->Create();



	//пальцы редизайн первый



	double glubina_tre4 =  H+(L1-lDeep-H);
	ksEntityPtr pSketch_muft_pl5 = pPart2->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl5 = pSketch_muft_pl5->GetDefinition();
	pSketchDef_muft_pl5->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl5->Create();
	p2DDoc = pSketchDef_muft_pl5->BeginEdit();
	UpdateData();


	//p2DDoc->ksLineSeg(0, 0, -300, 300, 1);
	//p2DDoc->ksLineSeg(0, 0, 300, 300, 1);
	//p2DDoc->ksLineSeg(-300, 300, 300, 300, 1);
	//внутренний
	//p2DDoc->ksLineSeg(x_A, -y_A, x_B2, y_B3, 1);S
	//p2DDoc->ksLineSeg(x_A, -y_A, x_C2, y_C3, 1);
	//p2DDoc->ksLineSeg(x_B2, y_B3, x_C2, y_C3, 1);
	 // Угол BAC
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

	//1-ая вертикаль  2-ая горизонталь
	/*p2DDoc->ksLineSeg(0, sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2)), -(200 * sin(60) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2)))  , -(200 * cos(60)), 1);
	p2DDoc->ksLineSeg(0, sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2)), (200 * sin(60) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), -(200 * cos(60)), 1);
	p2DDoc->ksLineSeg((200 * sin(60) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), -(200 * cos(60)), -(200 * sin(60) + sqrt(pow(mufta_2isp_B, 2) + pow(mufta_2isp_B, 2))), -(200 * cos(60)), 1);*/

	/*p2DDoc->ksLineSeg(x_A, y_A2, x_B, y_B, 1);
	p2DDoc->ksLineSeg(x_A, y_A2, x_C, y_C, 1);
	p2DDoc->ksLineSeg(x_B, y_B, x_C, y_C, 1);*/
	pSketchDef_muft_pl5->EndEdit();


	ksEntityPtr pExtrude11 = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef11 = pExtrude11->GetDefinition();
	pCutDef11->directionType = dtNormal;
	pCutDef11->SetSketch(pSketchDef_muft_pl5);
	pCutDef11->SetSideParam(true, etBlind, glubina_tre4, 0, false);
	pExtrude11->Create();



	////пальцы редизайн второй
	//ksEntityPtr pSketch_muft_pl6 = pPart2->NewEntity(o3d_sketch);
	//ksSketchDefinitionPtr pSketchDef_muft_pl6 = pSketch_muft_pl6->GetDefinition();
	//pSketchDef_muft_pl6->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	//pSketch_muft_pl6->Create();
	//p2DDoc = pSketchDef_muft_pl6->BeginEdit();
	//UpdateData();

	//p2DDoc->ksLineSeg(0, 0, -80, -80, 1);
	//p2DDoc->ksLineSeg(0, 0, 80, -80, 1);
	//p2DDoc->ksLineSeg(-80, -80, 80, -80, 1);

	//p2DDoc->ksLineSeg(100, 1, -100, 1, 1);
	//p2DDoc->ksLineSeg(100, 1, 100, -100, 1);
	//p2DDoc->ksLineSeg(100, -100, -100, -100, 1);
	//p2DDoc->ksLineSeg(-100, -100, -100, 1, 1);


	//pSketchDef_muft_pl6->EndEdit();


	//ksEntityPtr pExtrude12 = pPart2->NewEntity(o3d_cutExtrusion);
	//ksCutExtrusionDefinitionPtr pCutDef12 = pExtrude12->GetDefinition();
	//pCutDef12->directionType = dtNormal;
	//pCutDef12->SetSketch(pSketchDef_muft_pl6);
	//pCutDef12->SetSideParam(true, etBlind, glubina_tre4, 0, false);
	//pExtrude12->Create();




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

	//// Рисование линий
	//p2DDoc->ksLineSeg(x_A174, y_A174, x_B174, y_B174, 1);
	//p2DDoc->ksLineSeg(x_A174, y_A174, x_C174, y_C174, 1);
	//p2DDoc->ksLineSeg(x_B174, y_B174, x_C174, y_C174, 1);
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





	ksEntityPtr pExtrude174 = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef174 = pExtrude174->GetDefinition();
	pCutDef174->directionType = dtNormal;
	pCutDef174->SetSketch(pSketchDef_muft_pl174);
	pCutDef174->SetSideParam(true, etBlind, glubina_tre4, 0, false);
	pExtrude174->Create();




	ksEntityPtr pSketch_muft_pl777 = pPart2->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl777 = pSketch_muft_pl777->GetDefinition();
	pSketchDef_muft_pl777->SetPlane(pPart2->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl777->Create();
	p2DDoc = pSketchDef_muft_pl777->BeginEdit();

	//double angle_degrees = 60;  // Угол между сторонами треугольника
	//double rotation_degrees = 0;  // Угол поворота треугольника
	//double height = 48.5;         // Расстояние от центра до стороны треугольника

	//// Преобразование углов в радианы
	//double angle_radians = angle_degrees * PI / 180.0;
	//double rotation_radians = rotation_degrees * PI / 180.0;

	//// Координаты вершин треугольника относительно его центра
	//double x_A777_relative = 0;
	//double y_A777_relative = -height / sqrt(3);

	//double x_B777_relative = height / 2;
	//double y_B777_relative = height / (2 * sqrt(3));

	//double x_C777_relative = -height / 2;
	//double y_C777_relative = height / (2 * sqrt(3));

	//// Поворот треугольника на угол rotation_degrees
	//double x_A777_rotated = x_A777_relative * cos(rotation_radians) - y_A777_relative * sin(rotation_radians);
	//double y_A777_rotated = x_A777_relative * sin(rotation_radians) + y_A777_relative * cos(rotation_radians);

	//double x_B777_rotated = x_B777_relative * cos(rotation_radians) - y_B777_relative * sin(rotation_radians);
	//double y_B777_rotated = x_B777_relative * sin(rotation_radians) + y_B777_relative * cos(rotation_radians);

	//double x_C777_rotated = x_C777_relative * cos(rotation_radians) - y_C777_relative * sin(rotation_radians);
	//double y_C777_rotated = x_C777_relative * sin(rotation_radians) + y_C777_relative * cos(rotation_radians);

	//// Перемещение координат вершин треугольника в центр
	//double x_center = 0;
	//double y_center = 0;

	//x_A777_rotated += x_center;
	//y_A777_rotated += y_center;

	//x_B777_rotated += x_center;
	//y_B777_rotated += y_center;

	//x_C777_rotated += x_center;
	//y_C777_rotated += y_center;

	//// Рисование треугольника
	//p2DDoc->ksLineSeg(x_A777_rotated, y_A777_rotated, x_B777_rotated, y_B777_rotated, 1);
	//p2DDoc->ksLineSeg(x_B777_rotated, y_B777_rotated, x_C777_rotated, y_C777_rotated, 1);
	//p2DDoc->ksLineSeg(x_C777_rotated, y_C777_rotated, x_A777_rotated, y_A777_rotated, 1);

	//pSketchDef_muft_pl777->EndEdit();

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

	ksEntityPtr pExtrude777 = pPart2->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef777 = pExtrude777->GetDefinition();
	pCutDef777->directionType = dtNormal;
	pCutDef777->SetSketch(pSketchDef_muft_pl777);
	pCutDef777->SetSideParam(true, etBlind, glubina_tre4, 0, false);
	pExtrude777->Create();








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
			//def->Get
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);

			double x1, y1, z1, x2, y2, z2;
			if (p1 && p2)
			{
				p1->GetPoint(&x1, &y1, &z1);
				p2->GetPoint(&x2, &y2, &z2);

				if (abs(z1) < 0.001)
				{
					//ed->Putname("LoftEdge");
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

					ksFaceDefinitionPtr f =

						def->GetAdjacentFace(true);

					ksEntityPtr face = f->GetEntity();
					if (f->IsPlanar() && j ==0) {
						face->Putname("Face4Assembly");

						face->Update();
						j++;

					}
					if (!f->IsPlanar()){
						face->Putname("Face174Assembly");

						face->Update();
					}
					

				}
				if (x1 == 0 && m ==0) {

					ksFaceDefinitionPtr f =

						def->GetAdjacentFace(true);

					ksEntityPtr face = f->GetEntity();
					if (f->IsPlanar()) {
						face->Putname("Face777Assembly");

						face->Update();
						m++;

					}
					


				}
			}
		}
	}
	pChamfer->Create();



	pDoc2->SaveAs("D:\\kursachTEST\\mufta2.m3d");

	// сборка
	pDoc2 = pKompasApp55->Document3D();

	pDoc2->Create(false, false);

	pPart2 = pDoc2->GetPart(pTop_Part);

	ksPartPtr pBoss, pGear1, pGear2;
	pDoc2->SetPartFromFile("D:\\kursachTEST\\star.m3d", pPart2, true);
	pDoc2->SetPartFromFile("D:\\kursachTEST\\mufta2.m3d", pPart2, true);
	pDoc2->SetPartFromFile("D:\\kursachTEST\\mufta2.m3d", pPart2, true);
	
	pBoss = pDoc2->GetPart(0);
	pGear1 = pDoc2->GetPart(1);
	pGear2 = pDoc2->GetPart(2);

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
	

	pDoc2->AddMateConstraint(mc_Concentric, BossFace4Assemly2, Gear1Face4Assemly1, -1, 1, 0);
	pDoc2->AddMateConstraint(mc_Concentric, BossFace4Assemly2, Gear2Face4Assemly1, 1, 0, 0);

	/*pDoc2->AddMateConstraint(mc_Parallel, BossFace4Assemly1, Gear1Face4Assemly, -1, 1, 0);*/
	pDoc2->AddMateConstraint(mc_Coincidence, Gear1Face4Assemly, BossFace4Assemly0, -1, 1, 0);
	pDoc2->AddMateConstraint(mc_Coincidence, Gear2Face4Assemly, BossFace4Assemly3, -1, 1, 0);
	pDoc2->AddMateConstraint(mc_Coincidence, Gear2Face4Assemly2, BossFace4Assemly1, 1, 0, 0);

	pDoc2->RebuildDocument();

	pDoc2->SaveAs("D:\\kursachTEST\\Assembly.a3d");
}

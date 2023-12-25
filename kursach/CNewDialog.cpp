// CNewDialog.cpp : implementation file
//

#include "pch.h"
#include "kursach.h"
#include "afxdialogex.h"
#include "CNewDialog.h"
#include <cmath>

#include "math.h"
#include "D:\компас\SDK\Include\ksConstants.h"
#include "D:\компас\SDK\Include\ksConstants3D.h"

#define PI 4*atan(1)
#import "D:\компас\SDK\lib\kAPI5.tlb"


using namespace Kompas6API5;

KompasObjectPtr pKompasApp5;

ksPartPtr pPart;
ksDocument3DPtr pDoc;

// CNewDialog dialog

IMPLEMENT_DYNAMIC(CNewDialog, CDialog)

CNewDialog::CNewDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CNewDialog, pParent)
	, D(32)
	, D1(30)
	, D2(20)
	, d(6)
	, L(45.5)
	, L1(28)
	, l(10.5)
	, l1(16)
	, l2(6)
	, B(8)
	, b1(4)
	, R(1.2)
	, lDeep(16)
	, B1(16)
{

}

CNewDialog::~CNewDialog()
{
}

void CNewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, D);
	DDX_Text(pDX, IDC_EDIT2, D1);
	DDX_Text(pDX, IDC_EDIT3, D2);
	DDX_Text(pDX, IDC_EDIT4, d);
	DDX_Text(pDX, IDC_EDIT5, L);
	DDX_Text(pDX, IDC_EDIT6, L1);
	DDX_Text(pDX, IDC_EDIT7, l);
	DDX_Text(pDX, IDC_EDIT8, l1);
	DDX_Text(pDX, IDC_EDIT9, l2);
	DDX_Text(pDX, IDC_EDIT10, B);
	DDX_Text(pDX, IDC_EDIT11, b1);
	DDX_Text(pDX, IDC_EDIT12, R);
	DDX_Control(pDX, IDC_COMBO1, execution);
	DDX_Text(pDX, IDC_EDIT24, lDeep);
	DDX_Text(pDX, IDC_EDIT25, B1);
}


BEGIN_MESSAGE_MAP(CNewDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CNewDialog::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CNewDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewDialog message handlers
void CNewDialog::OnCbnSelchangeCombo1()
{
	// Получаем индекс выбранного элемента
	int selectedIndex = execution.GetCurSel();

	// Проверяем выбранный элемент и устанавливаем значения переменных соответственно
	if (selectedIndex == 0) // Выбрано "1"
	{
		D = 32;
		D1 = 30;
		D2 = 20;
		d = 6;
		L = 45.5;
		L1 = 28;
		l = 10.5;
		l1 = 16;
		l2 = 6;
		B = 8;
		b1 = 4;
		R = 1.2;
		lDeep = 16;
		B1 = 16;
	}
	else if (selectedIndex == 1) // Выбрано "2"
	{
		D = 45;
		D1 = 42;
		D2 = 22;
		d = 10;
		L = 59.5;
		L1 = 35;
		l = 10.5;
		l1 = 16;
		l2 = 8;
		B = 10;
		b1 = 5;
		R = 1.6;
		lDeep = 23;
		B1 = 20;
	}

	// Обновляем данные на диалоговом окне
	UpdateData(FALSE);
}

void CNewDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	/*CDialog::OnOK();*/
	BeginWaitCursor();

	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
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
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	// делаем Компас видимым
	pKompasApp5->Visible = true;

	pDoc = pKompasApp5->Document3D();

	pDoc->Create(false, true);

	pPart = pDoc->GetPart(pTop_Part);

	ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch);

	ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));

	pSketch->Create();
	ksDocument2DPtr p2DDoc = pSketchDef->BeginEdit();
	UpdateData();

	//создаем эскиз для звездочки муфты
	double plus_B = B;
	double plus_D1 = D1;
	double plus_R = R;
	p2DDoc->ksLineSeg(-plus_D1 / 2, 0, -plus_D1 / 2, plus_B / 2, 1);
	p2DDoc->ksLineSeg(-plus_D1 / 2, plus_B / 2, -plus_B / 2, plus_B / 2, 1);
	p2DDoc->ksLineSeg(-plus_B / 2, plus_B / 2, -plus_B / 2, plus_D1 / 2, 1);
	p2DDoc->ksLineSeg(-plus_B / 2, plus_D1 / 2, plus_B / 2, plus_D1 / 2, 1);
	p2DDoc->ksLineSeg(plus_B / 2, plus_D1 / 2, plus_B / 2, plus_B / 2, 1);
	p2DDoc->ksLineSeg(plus_B / 2, plus_B / 2, plus_D1 / 2, plus_B / 2, 1);
	p2DDoc->ksLineSeg(plus_D1 / 2, plus_B / 2, plus_D1 / 2, 0, 1);

	p2DDoc->ksLineSeg(plus_D1 / 2, 0, plus_D1 / 2, -plus_B / 2, 1);
	p2DDoc->ksLineSeg(plus_D1 / 2, -plus_B / 2, plus_B / 2, -plus_B / 2, 1);
	p2DDoc->ksLineSeg(plus_B / 2, -plus_B / 2, plus_B / 2, -plus_D1 / 2, 1);
	p2DDoc->ksLineSeg(plus_B / 2, -plus_D1 / 2, -plus_B / 2, -plus_D1 / 2, 1);
	p2DDoc->ksLineSeg(-plus_B / 2, -plus_D1 / 2, -plus_B / 2, -plus_B / 2, 1);
	p2DDoc->ksLineSeg(-plus_B / 2, -plus_B / 2, -plus_D1 / 2, -plus_B / 2, 1);
	p2DDoc->ksLineSeg(-plus_D1 / 2, -plus_B / 2, -plus_D1 / 2, 0, 1);
	
	pSketchDef->EndEdit();

	//выдавливание эскиза звездочки
	ksEntityPtr pExtrudeDowel = pPart->NewEntity(o3d_baseExtrusion);
	ksBaseExtrusionDefinitionPtr pBaseDef = pExtrudeDowel->GetDefinition();
	pBaseDef->directionType = dtNormal;
	pBaseDef->SetSketch(pSketch);
	pBaseDef->SetSideParam(true, etBlind, l, 0, false);
	pExtrudeDowel->Create();

	//смещенная плоскость для скругления краев
	ksEntityPtr pPlane = pPart->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr pPlaneDef = pPlane->GetDefinition();
	pPlaneDef->direction = true;
	pPlaneDef->offset = l;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pPlane->Create();

	//эскиз окружности для скругления краев
	ksEntityPtr pSketch1 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch1->GetDefinition();
	pSketchDef->SetPlane(pPlane);
	pSketch1->Create();
	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(0, 0, plus_D1 / 2, 1);
	p2DDoc->ksCircle(0, 0, plus_D1, 1);
	pSketchDef->EndEdit();

	//вырезание ПЕРЕСЕЧЕНИЕМ для скругления краев звездочки
	ksEntityPtr pExtrude2 = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef = pExtrude2->GetDefinition();
	pCutDef->directionType = dtNormal;
	pCutDef->SetSketch(pSketch1);
	pCutDef->SetSideParam(true, etThroughAll, 0, 0, false);
	pExtrude2->Create();


	//получившиеся скругленные края называем circle для дальнейшего применения соосности
	ksEntityCollectionPtr flFaces = pPart->EntityCollection(o3d_face);
	for (int i = 0; i < flFaces->GetCount(); i++)
	{
		ksEntityPtr face = flFaces->GetByIndex(i);
		ksFaceDefinitionPtr def = face->GetDefinition();
		if (def->GetOwnerEntity() == pExtrude2)
		{
			face->Putname("circle");
			face->Update();
		}
	}

	//создаем скругление радиусом R, обзываем оставшиеся грани звезды
	ksEntityCollectionPtr fledges1 = pPart->EntityCollection(o3d_edge);
	ksEntityPtr pFillet = pPart->NewEntity(o3d_fillet);
	ksFilletDefinitionPtr pFilletDef = pFillet->GetDefinition();
	pFilletDef->radius = plus_R;
	ksEntityCollectionPtr fl1 = pFilletDef->array();
	fl1->Clear();

	int ng = 0;
	int ng2 = 0;
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

				if (abs(z1) == l && abs(int(x1)) == B/2 && abs(int(y1))==B/2)
				{
					//называем верхнюю грань
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("starTOP");
					face->Update();
				}
				if (abs(x1 - x2) < 0.0001 && abs(y1 - y2) < 0.0001)
				{
					//скругления
					fl1->Add(ed);
					if (z1 == 0 && int(y1) == -B / 2 && (ceil(abs(x1)) == D1 / 2) && ng==0) {
						//называем внутреннюю часть зуба
						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Putname("star_tor2");
						face->Update();
						ng++;
					}
				}
				if (abs(x1 - x2) < 0.0001 && abs(y1 - y2) < 0.0001)
				{
					fl1->Add(ed);
					if (z1 == 0 && int(y1) == B / 2 && (ceil(abs(x1)) == D1 / 2) && ng2 == 0) {
						//называем другую внутреннюю часть зуба
						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Putname("star_tor");
						face->Update();
						ng2++;
					}
				}
			}
		}
	}

	pFillet->Create();

	//сохраняем звезду
	pDoc->SaveAs("D:\\kursachTEST\\star1.m3d");


	//создаем новый документ c муфтой 1 исполнения (2 зуба)
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);
	pSketch = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch->Create();
	p2DDoc = pSketchDef->BeginEdit();
	UpdateData();
	double mufta_1isp_B1 = B1;
	double mufta_1isp_d1 = D2;
	double mufta_1isp_R = R;
	double mufta_1isp_D = D;
	double mufta_1isp_D1 = D1;
	double mufta_1isp_D2 = D2;
	double mufta_1isp_b = 2;
	double mufta_1isp_d = d;
	double mufta_1isp_L1 = L1;
	double mufta_1isp_l = lDeep;
	double mufta_1isp_B = B/2;
	double mufta_1isp_L = L;
	double mufta_1isp_l_deep = lDeep;

	//эскиз для муфты
	p2DDoc->ksLineSeg(0, -mufta_1isp_B1 / 2, 0, -mufta_1isp_D / 2, 1);
	p2DDoc->ksLineSeg(0, -mufta_1isp_D / 2, mufta_1isp_l, -mufta_1isp_D / 2, 1);
	p2DDoc->ksLineSeg(mufta_1isp_l, -mufta_1isp_D / 2, mufta_1isp_l, -mufta_1isp_D2 / 2, 1);
	p2DDoc->ksLineSeg(mufta_1isp_l, -mufta_1isp_D2 / 2, mufta_1isp_L1, -mufta_1isp_D2 / 2, 1);
	p2DDoc->ksLineSeg(mufta_1isp_L1, -mufta_1isp_D2 / 2, mufta_1isp_L1, -mufta_1isp_d / 2, 1);
	p2DDoc->ksLineSeg(mufta_1isp_L1, -mufta_1isp_d / 2, mufta_1isp_L1 - mufta_1isp_l_deep, -mufta_1isp_d / 2, 1);
	p2DDoc->ksLineSeg(mufta_1isp_L1 - mufta_1isp_l_deep, -mufta_1isp_d / 2, mufta_1isp_L1 - mufta_1isp_l_deep, -mufta_1isp_B1 / 2, 1);
	p2DDoc->ksLineSeg(mufta_1isp_L1 - mufta_1isp_l_deep, -mufta_1isp_B1 / 2, 0, -mufta_1isp_B1 / 2, 1);
	p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);
	pSketchDef->EndEdit();

	//выдавливаем вращением полученный эскиз
	ksEntityPtr pRotate = pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotDef = pRotate->GetDefinition();
	pRotDef->SetSketch(pSketch);
	pRotDef->SetSideParam(TRUE, 360);
	pRotate->Create();

	//эскиз для образования зубов муфты
	ksEntityPtr pSketch_muft_f = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_f = pSketch_muft_f->GetDefinition();
	pSketchDef_muft_f->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_f->Create();
	p2DDoc = pSketchDef_muft_f->BeginEdit();
	UpdateData();

	p2DDoc->ksLineSeg(-30, mufta_1isp_B1 / 2, 30, mufta_1isp_B1 / 2, 1);
	p2DDoc->ksLineSeg(30, mufta_1isp_B1 / 2, 30, -mufta_1isp_B1 / 2, 1);
	p2DDoc->ksLineSeg(30, -mufta_1isp_B1 / 2, -30, -mufta_1isp_B1 / 2, 1);
	p2DDoc->ksLineSeg(-30, -mufta_1isp_B1 / 2, -30, mufta_1isp_B1 / 2, 1);

	pSketchDef_muft_f->EndEdit();

	//вырезаем выдавливанием ранее созданный эскиз
	double glubina_rect = mufta_1isp_L1 - mufta_1isp_l;
	ksEntityPtr pExtrude3 = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef3 = pExtrude3->GetDefinition();
	pCutDef3->directionType = dtNormal;
	pCutDef3->SetSketch(pSketchDef_muft_f);
	pCutDef3->SetSideParam(true, etBlind, glubina_rect, 0, false);
	pExtrude3->Create();

	//создаем эскиз для дальейшего выреза зуба муфты под 45 градусов
	ksEntityPtr pSketch_muft_pl = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl = pSketch_muft_pl->GetDefinition();
	pSketchDef_muft_pl->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl->Create();
	p2DDoc = pSketchDef_muft_pl->BeginEdit();
	UpdateData();

	p2DDoc->ksLineSeg(0, sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2)), -100*cos(45), 100 * cos(45) + sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2)), 1);
	p2DDoc->ksLineSeg(0, sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2)), 100 * cos(45), 100 * cos(45) + sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2)), 1);
	p2DDoc->ksLineSeg(-100 * cos(45), 100 * cos(45) + sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2)), 100 * cos(45), 100 * cos(45) + sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2)), 1);
	p2DDoc->ksLineSeg(0, 0, -150 * cos(45), 150 * cos(45), 1);
	p2DDoc->ksLineSeg(0, 0, 150 * cos(45), 150 * cos(45), 1);
	p2DDoc->ksLineSeg(-150 * cos(45), 150 * cos(45), 150 * cos(45), 150 * cos(45), 1);

	pSketchDef_muft_pl->EndEdit();

	//вырезаем эскиз зубов
	ksEntityPtr pExtrude4 = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef4 = pExtrude4->GetDefinition();
	pCutDef4->directionType = dtNormal;
	pCutDef4->SetSketch(pSketchDef_muft_pl);
	pCutDef4->SetSideParam(true, etBlind, l, 0, false);
	pExtrude4->Create();

	//аналогично создаем эскиз для другого зуба
	ksEntityPtr pSketch_muft_pl2 = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl2 = pSketch_muft_pl2->GetDefinition();
	pSketchDef_muft_pl2->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl2->Create();
	p2DDoc = pSketchDef_muft_pl2->BeginEdit();
	UpdateData();

	p2DDoc->ksLineSeg(0, -sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2)), -100 * cos(45), -(100 * cos(45) + sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2))), 1);
	p2DDoc->ksLineSeg(0, -sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2)), 100 * cos(45), -(100 * cos(45) + sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2))), 1);
	p2DDoc->ksLineSeg(-100 * cos(45), -(100 * cos(45) + sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2))), 100 * cos(45), -(100 * cos(45) + sqrt(pow(mufta_1isp_B, 2) + pow(mufta_1isp_B, 2))), 1);

	p2DDoc->ksLineSeg(100, 0, -100, 0, 1);
	p2DDoc->ksLineSeg(100, 0, 100, -100, 1);
	p2DDoc->ksLineSeg(100, -100, -100, -100, 1);
	p2DDoc->ksLineSeg(-100, -100, -100, 0, 1);

	pSketchDef_muft_pl2->EndEdit();

	//вырезаем полученный зуб
	ksEntityPtr pExtrude5 = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef5 = pExtrude5->GetDefinition();
	pCutDef5->directionType = dtNormal;
	pCutDef5->SetSketch(pSketchDef_muft_pl2);
	pCutDef5->SetSideParam(true, etBlind, l, 0, false);
	pExtrude5->Create();

	//для первого зуба создаем выступы для звезды
	double glubina_tre2 = mufta_1isp_L1 - mufta_1isp_l;
	ksEntityPtr pSketch_muft_pl3 = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl3 = pSketch_muft_pl3->GetDefinition();
	pSketchDef_muft_pl3->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl3->Create();
	p2DDoc = pSketchDef_muft_pl3->BeginEdit();
	UpdateData();

	p2DDoc->ksLineSeg(0, 0, -80, 80, 1);
	p2DDoc->ksLineSeg(0, 0, 80, 80, 1);
	p2DDoc->ksLineSeg(-80, 80, 80, 80, 1);

	p2DDoc->ksLineSeg(100, -1, -100, -1, 1);
	p2DDoc->ksLineSeg(100, -1, 100, 100, 1);
	p2DDoc->ksLineSeg(100, 100, -100, 100, 1);
	p2DDoc->ksLineSeg(-100, 100, -100, -1, 1);

	pSketchDef_muft_pl3->EndEdit();

	//вырезаем, чтобы появились выступы для звезды
	ksEntityPtr pExtrude6 = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef6 = pExtrude6->GetDefinition();
	pCutDef6->directionType = dtNormal;
	pCutDef6->SetSketch(pSketchDef_muft_pl3);
	pCutDef6->SetSideParam(true, etBlind, glubina_tre2, 0, false);
	pExtrude6->Create();

	//аналогично для второго зуба (эскиз)
	ksEntityPtr pSketch_muft_pl4 = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef_muft_pl4 = pSketch_muft_pl4->GetDefinition();
	pSketchDef_muft_pl4->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pSketch_muft_pl4->Create();
	p2DDoc = pSketchDef_muft_pl4->BeginEdit();
	UpdateData();

	p2DDoc->ksLineSeg(0, 0, -80, -80, 1);
	p2DDoc->ksLineSeg(0, 0, 80, -80, 1);
	p2DDoc->ksLineSeg(-80, -80, 80, -80, 1);

	p2DDoc->ksLineSeg(100, 1, -100, 1, 1);
	p2DDoc->ksLineSeg(100, 1, 100, -100, 1);
	p2DDoc->ksLineSeg(100, -100, -100, -100, 1);
	p2DDoc->ksLineSeg(-100, -100, -100, 1, 1);

	pSketchDef_muft_pl4->EndEdit();

	//аналогично для второго зуба (вырез)
	ksEntityPtr pExtrude7 = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutDef7 = pExtrude7->GetDefinition();
	pCutDef7->directionType = dtNormal;
	pCutDef7->SetSketch(pSketchDef_muft_pl4);
	pCutDef7->SetSideParam(true, etBlind, glubina_tre2, 0, false);
	pExtrude7->Create();

	////создаем фаски и обзываем грани для создания сборки
	ksEntityPtr pLoft = pPart->NewEntity(o3d_bossLoft);
	ksBossLoftDefinitionPtr pLoftDef = pLoft->GetDefinition();
	pLoftDef->SetLoftParam(FALSE, TRUE, TRUE);
	ksEntityCollectionPtr sk = pLoftDef->Sketchs();
	sk->Clear();
	sk->Add(pExtrude2);
	sk->Add(pExtrude3);
	sk->Add(pExtrude4);
	sk->Add(pExtrude5);
	sk->Add(pExtrude6);
	sk->Add(pExtrude7);
	pLoft->Create();

	ksEntityCollectionPtr fledges = pPart->EntityCollection(o3d_edge);
	ksEntityPtr pChamfer = pPart->NewEntity(o3d_chamfer);
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
					//создание фасок
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
				if (x1 == l && y1<-B) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					if (f->IsPlanar() && j == 0) {
						//называем боковую грань зуба
						face->Putname("Face4Assembly");
						face->Update();
						j++;
					}
					if (!f->IsPlanar()) {
						//называем внешнюю цилиндрическую часть муфты
						face->Putname("Face174Assembly");
						face->Update();
					}
				}
				if (x1 == 0 && m == 0) {
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
	pDoc->SaveAs("D:\\kursachTEST\\mufta.m3d");


	// создание нового документы сборки
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, false);
	pPart = pDoc->GetPart(pTop_Part);
	ksPartPtr pBoss, pGear1, pGear2;
	//добавляем в сборку ранее созданные детали
	pDoc->SetPartFromFile("D:\\kursachTEST\\star1.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\kursachTEST\\mufta.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\kursachTEST\\mufta.m3d", pPart, true);

	pBoss = pDoc->GetPart(0);
	pGear1 = pDoc->GetPart(1);
	pGear2 = pDoc->GetPart(2);

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
	pDoc->AddMateConstraint(mc_Concentric, BossFace4Assemly2, Gear1Face4Assemly1, -1, 1, 0);
	pDoc->AddMateConstraint(mc_Concentric, BossFace4Assemly2, Gear2Face4Assemly1, 1, 0, 0);
	//создаем зависимости (совпадение)
	pDoc->AddMateConstraint(mc_Coincidence, Gear1Face4Assemly, BossFace4Assemly0, -1, 1, 0);
	pDoc->AddMateConstraint(mc_Coincidence, Gear2Face4Assemly, BossFace4Assemly3, -1, 1, 0);
	pDoc->AddMateConstraint(mc_Coincidence, Gear2Face4Assemly2, BossFace4Assemly1, 1, 0, 0);

	pDoc->RebuildDocument();
	//сохраняем документ сборки
	pDoc->SaveAs("D:\\kursachTEST\\Assembly.3d");
}

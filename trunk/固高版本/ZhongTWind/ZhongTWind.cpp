// ZhongTWind.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ZhongTWind.h"
#include "ZhongTWindDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZhongTWindApp

BEGIN_MESSAGE_MAP(CZhongTWindApp, CWinApp)
	//{{AFX_MSG_MAP(CZhongTWindApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZhongTWindApp construction

CZhongTWindApp::CZhongTWindApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CZhongTWindApp object

CZhongTWindApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CZhongTWindApp initialization

BOOL CZhongTWindApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	ProgramInitial();
	CZhongTWindDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CZhongTWindApp::ProgramInitial()
{
	
	GlobalParam.m_fAcceleration = 1;
	GlobalParam.m_fAccelerationFactor =1;
	GlobalParam.m_fCarDistancePerRound = 424.115001;
	GlobalParam.m_fCarMaxSpeed = 3000;
	GlobalParam.m_fCarSpeedDownP = 11;
	GlobalParam.m_fMainAxeLevelFactor[0] = 23;
	GlobalParam.m_fMainAxeLevelFactor[1] = 47.31428571;
	GlobalParam.m_fMainAxeLevelFactor[2] = 23;
	GlobalParam.m_fMainAxeLevelFactor[3] = 23;
	GlobalParam.m_fMainAxeLevelFactor[4] = 23;
	GlobalParam.m_fMainAxeLevelFactor[5] = 23;
	GlobalParam.m_fMainAxeMaxSpeed = 1460;
	GlobalParam.m_fZeroPitch = 80;
	GlobalParam.m_iCarPulses = 10000;
    GlobalParam.m_iMainAxePulses = 2000;
}

// �����ļ��༭��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�����ļ��༭��.h"
#include "�����ļ��༭��Dlg.h"
#include ".\�����ļ��༭��dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDlg �Ի���



CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMyDlg::~CMyDlg()
{

	for (int i=0;i<m_ButtonList.size();i++)
	{
		delete m_ButtonList[i];
	}
	m_ButtonList.clear();

	for (int i=0;i<m_StaticList.size();i++)
	{
		delete m_StaticList[i];
	}
	m_StaticList.clear();

	for (int i=0;i<m_EditList.size();i++)
	{
		delete m_EditList[i];
	}
	m_EditList.clear();

}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_COMMAND_RANGE(IDC_MYBUTTON1,IDC_MYBUTTON1+999,OnMyButton)			//��ഴ��999���ؼ�
	ON_COMMAND_RANGE(IDC_MYSTATIC1,IDC_MYSTATIC1+999,OnMyStatic)
	ON_COMMAND_RANGE(IDC_MYEDIT1,IDC_MYEDIT1+999,OnMyEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMyDlg ��Ϣ�������

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//DLGSCROLL
	SetScrollRange(SB_HORZ, 0, 100);   
	SetScrollRange(SB_VERT, 0, 100);  
	
	//��ť������ʼ�� 
	m_myFont.CreatePointFont(100,"����") ;
	m_ButtonCount = 0;
	m_StaticCount = 0;
	m_EditCount = 0;
	

	CreateDynControl(CTRLT_BUTTON,"���ǰ�ť",10,20,100,40,NULL);
	CreateDynControl(CTRL_STATIC,"���Ǿ�̬�ı�",150,20,100,45,NULL);
	CreateDynControl(CTRL_EDIT,"���Ǳ༭��",10,100,120,40,NULL);
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ������̬�ؼ�����
CWnd* CMyDlg::CreateDynControl(
	int nCtrlType,   CString strCaption,
	LONG nStartX,  LONG nStartY,
	LONG nWidth,  LONG nHeight,    int nStyle
	)
{
	CWnd* lpCwnd = NULL;
	CRect rct = CRect(nStartX,nStartY,nStartX+nWidth,nStartY+nHeight);
	if (CTRLT_BUTTON == nCtrlType )
	{
		CButton *p_Button = new CButton();
		ASSERT_VALID(p_Button);
		if( !p_Button->Create( strCaption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | nStyle, rct, this, IDC_MYBUTTON1+m_ButtonCount ) )
		{
			return NULL;
		}
		lpCwnd = (CWnd*)p_Button;
		m_ButtonList.push_back(p_Button);
		m_ButtonCount++;
	}
	else if (CTRL_STATIC == nCtrlType)
	{
		CStatic *p_Static = new CStatic();
		ASSERT_VALID(p_Static);
		if( !p_Static->Create( strCaption, WS_CHILD | WS_VISIBLE | SS_LEFT | nStyle, rct, this, IDC_MYSTATIC1+m_StaticCount ) )
		{
			return NULL;
		}
		p_Static->SetFont(&m_myFont);
		
		lpCwnd = (CWnd*)p_Static;
		m_StaticList.push_back(p_Static);
		m_StaticCount++;
	}
	else  if (CTRL_EDIT == nCtrlType)
	{
		CEdit *p_Edit = new CEdit();
		ASSERT_VALID(p_Edit);
		if( !p_Edit->Create( WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | nStyle, rct, this, IDC_MYEDIT1+m_EditCount ) )
		{
			return NULL;
		}
		p_Edit->SetWindowText(strCaption);
		lpCwnd = (CWnd*)p_Edit;
		m_EditList.push_back(p_Edit);
		m_EditCount++;
	}
	
	return lpCwnd;
}


void CMyDlg::OnMyButton(UINT nId)
{
	int nIndex = nId - IDC_MYBUTTON1;
	CString strFmt;
	strFmt.Format("%d",nIndex);
	AfxMessageBox(strFmt);
}

void CMyDlg::OnMyStatic(UINT nId)
{
	int nIndex = nId - IDC_MYSTATIC1;
	
	CString strFmt;
	strFmt.Format("%d",nIndex);
	AfxMessageBox(strFmt);
}

void CMyDlg::OnMyEdit(UINT nId)
{
	int nIndex = nId - IDC_MYEDIT1;

	CString strFmt;
	strFmt.Format("%d",nIndex);
	AfxMessageBox(strFmt);
}



//////////////////////////////////////////////////////////////////////////
void CMyDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	SCROLLINFO scrollinfo;  

	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
	switch (nSBCode)  
	{  
	case SB_LEFT:  
		ScrollWindow((scrollinfo.nPos-scrollinfo.nMin)*10,0);  
		scrollinfo.nPos = scrollinfo.nMin;  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		break;  
	case SB_RIGHT:  
		ScrollWindow((scrollinfo.nPos-scrollinfo.nMax)*10,0);  
		scrollinfo.nPos = scrollinfo.nMax;  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		break;  
	case SB_LINELEFT:  
		scrollinfo.nPos -= 1;  
		if (scrollinfo.nPos)
		{  
			scrollinfo.nPos = scrollinfo.nMin;  
			break;  
		}  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		ScrollWindow(10,0);  
		break;  
	case SB_LINERIGHT:  
		scrollinfo.nPos += 1;  
		if (scrollinfo.nPos>scrollinfo.nMax)  
		{  
			scrollinfo.nPos = scrollinfo.nMax;  
			break;  
		}  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		ScrollWindow(-10,0);  
		break;  
	case SB_PAGELEFT:  
		scrollinfo.nPos -= 5;  
		if (scrollinfo.nPos)
		{  
			scrollinfo.nPos = scrollinfo.nMin;  
			break;  
		}  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		ScrollWindow(10*5,0);  
		break;  
	case SB_PAGERIGHT:  
		scrollinfo.nPos += 5;  
		if (scrollinfo.nPos>scrollinfo.nMax)  
		{  
			scrollinfo.nPos = scrollinfo.nMax;  
			break;  
		}  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		ScrollWindow(-10*5,0);  
		break;  
	case SB_THUMBPOSITION:  
		break;  
	case SB_THUMBTRACK:  
		ScrollWindow((scrollinfo.nPos-nPos)*10,0);  
		scrollinfo.nPos = nPos;  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		break;  
	case SB_ENDSCROLL:  
		break;  
	}  

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMyDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	SCROLLINFO scrollinfo;

	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	switch (nSBCode)  
	{  
	case SB_BOTTOM:  
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMax)*10);  
		scrollinfo.nPos = scrollinfo.nMax;  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		break;  
	case SB_TOP:  
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMin)*10);  
		scrollinfo.nPos = scrollinfo.nMin;  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		break;  
	case SB_LINEUP:  
		scrollinfo.nPos -= 1;  
		if (scrollinfo.nPos)
		{  
			scrollinfo.nPos = scrollinfo.nMin;  
			break;  
		}  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		ScrollWindow(0,10);  
		break;  
	case SB_LINEDOWN:  
		scrollinfo.nPos += 1;  
		if (scrollinfo.nPos>scrollinfo.nMax)  
		{  
			scrollinfo.nPos = scrollinfo.nMax;  
			break;  
		}  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		ScrollWindow(0,-10);  
		break;  
	case SB_PAGEUP:  
		scrollinfo.nPos -= 5;  
		if (scrollinfo.nPos)
		{  
			scrollinfo.nPos = scrollinfo.nMin;  
			break;  
		}  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		ScrollWindow(0,10*5);  
		break;  
	case SB_PAGEDOWN:  
		scrollinfo.nPos += 5;  
		if (scrollinfo.nPos>scrollinfo.nMax)  
		{  
			scrollinfo.nPos = scrollinfo.nMax;  
			break;  
		}  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		ScrollWindow(0,-10*5);  
		break;  
	case SB_ENDSCROLL:  
		// MessageBox("SB_ENDSCROLL");  
		break;  
	case SB_THUMBPOSITION:  
		// ScrollWindow(0,(scrollinfo.nPos-nPos)*10);  
		// scrollinfo.nPos = nPos;  
		// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		break;  
	case SB_THUMBTRACK:  
		ScrollWindow(0,(scrollinfo.nPos-nPos)*10);  
		scrollinfo.nPos = nPos;  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		break;  
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}




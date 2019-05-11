// 复盘文件编辑器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "复盘文件编辑器.h"
#include "复盘文件编辑器Dlg.h"
#include ".\复盘文件编辑器dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDlg 对话框



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
	ON_COMMAND_RANGE(IDC_MYBUTTON1,IDC_MYBUTTON1+999,OnMyButton)			//最多创建999个控件
	ON_COMMAND_RANGE(IDC_MYSTATIC1,IDC_MYSTATIC1+999,OnMyStatic)
	ON_COMMAND_RANGE(IDC_MYEDIT1,IDC_MYEDIT1+999,OnMyEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMyDlg 消息处理程序

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//DLGSCROLL
	SetScrollRange(SB_HORZ, 0, 100);   
	SetScrollRange(SB_VERT, 0, 100);  
	
	//按钮数量初始化 
	m_myFont.CreatePointFont(100,"宋体") ;
	m_ButtonCount = 0;
	m_StaticCount = 0;
	m_EditCount = 0;
	

	CreateDynControl(CTRLT_BUTTON,"我是按钮",10,20,100,40,NULL);
	CreateDynControl(CTRL_STATIC,"我是静态文本",150,20,100,45,NULL);
	CreateDynControl(CTRL_EDIT,"我是编辑框",10,100,120,40,NULL);
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 创建动态控件方法
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




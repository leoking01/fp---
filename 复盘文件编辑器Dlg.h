// 复盘文件编辑器Dlg.h : 头文件
//

#pragma once


// CMyDlg 对话框
class CMyDlg : public CDialog
{
// 构造
public:
	CMyDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMyDlg();

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnMyButton(UINT nId);
	afx_msg void OnMyStatic(UINT nId);
	afx_msg void OnMyEdit(UINT nId);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	enum ControlType
	{
		CTRLT_NULL,										
		CTRLT_BUTTON,						//按钮
		CTRL_STATIC,						//静态文本
		CTRL_EDIT,							//编辑框
		CTRLT_COUNT
	};
	// 创建动态控件方法
	CWnd* CreateDynControl(int nCtrlType,CString strCaption,LONG nStartX,LONG nStartY,LONG nWidth,LONG nHeight, int nStyle);

private:
	CFont m_myFont;							//定义成成员变量
	int m_ButtonCount;						//按钮数量
	int m_StaticCount;						//静态文本数量
	int m_EditCount;						//编辑框数量

	vector<CButton*> m_ButtonList;			//按钮记录列表
	vector<CStatic*> m_StaticList;			//按钮记录列表
	vector<CEdit*> m_EditList;			//按钮记录列表

};

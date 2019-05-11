// �����ļ��༭��Dlg.h : ͷ�ļ�
//

#pragma once


// CMyDlg �Ի���
class CMyDlg : public CDialog
{
// ����
public:
	CMyDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CMyDlg();

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnMyButton(UINT nId);
	afx_msg void OnMyStatic(UINT nId);
	afx_msg void OnMyEdit(UINT nId);

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	enum ControlType
	{
		CTRLT_NULL,										
		CTRLT_BUTTON,						//��ť
		CTRL_STATIC,						//��̬�ı�
		CTRL_EDIT,							//�༭��
		CTRLT_COUNT
	};
	// ������̬�ؼ�����
	CWnd* CreateDynControl(int nCtrlType,CString strCaption,LONG nStartX,LONG nStartY,LONG nWidth,LONG nHeight, int nStyle);

private:
	CFont m_myFont;							//����ɳ�Ա����
	int m_ButtonCount;						//��ť����
	int m_StaticCount;						//��̬�ı�����
	int m_EditCount;						//�༭������

	vector<CButton*> m_ButtonList;			//��ť��¼�б�
	vector<CStatic*> m_StaticList;			//��ť��¼�б�
	vector<CEdit*> m_EditList;			//��ť��¼�б�

};

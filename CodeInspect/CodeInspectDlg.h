
// CodeInspectDlg.h : ͷ�ļ�
//

#pragma once


// CCodeInspectDlg �Ի���
class CCodeInspectDlg : public CDialogEx
{
// ����
public:
	CCodeInspectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CODEINSPECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	cv::Mat m_MatSrc;
	cv::Mat m_MatTemplate;
	CString m_strSrcImgPath;
	CString m_strTemplateImagePath;
public:
	afx_msg void OnBnClickedButtonLoadimg();

	int PaintOnIDC(const uchar* pbuffer,int nWidth,int nHeight, UINT nIDC);
	void LoadMemImage(uchar *pImgBuf, CImage &DesImg, int nWidth, int nHeight);

	afx_msg void OnBnClickedButtonProcess();
	afx_msg void OnBnClickedButtonGetroi();
	afx_msg void OnBnClickedButtonPcolor();
	afx_msg void OnBnClickedButtonArctest();
	afx_msg void OnBnClickedButtonLoadtemplate();
	afx_msg void OnBnClickedButtonTemplatematch();
};

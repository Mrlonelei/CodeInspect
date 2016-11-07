
// CodeInspectDlg.h : 头文件
//

#pragma once


// CCodeInspectDlg 对话框
class CCodeInspectDlg : public CDialogEx
{
// 构造
public:
	CCodeInspectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CODEINSPECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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


// CodeInspectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CodeInspect.h"
#include "CodeInspectDlg.h"
#include "afxdialogex.h"
#include "math.h"
#include "GraphUtils.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCodeInspectDlg �Ի���



CCodeInspectDlg::CCodeInspectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCodeInspectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodeInspectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCodeInspectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOADIMG, &CCodeInspectDlg::OnBnClickedButtonLoadimg)
	ON_BN_CLICKED(IDC_BUTTON_PROCESS, &CCodeInspectDlg::OnBnClickedButtonProcess)
	ON_BN_CLICKED(IDC_BUTTON_GETROI, &CCodeInspectDlg::OnBnClickedButtonGetroi)
	ON_BN_CLICKED(IDC_BUTTON_PCOLOR, &CCodeInspectDlg::OnBnClickedButtonPcolor)
	ON_BN_CLICKED(IDC_BUTTON_ARCTEST, &CCodeInspectDlg::OnBnClickedButtonArctest)
	ON_BN_CLICKED(IDC_BUTTON_LOADTEMPLATE, &CCodeInspectDlg::OnBnClickedButtonLoadtemplate)
	ON_BN_CLICKED(IDC_BUTTON_TEMPLATEMATCH, &CCodeInspectDlg::OnBnClickedButtonTemplatematch)
END_MESSAGE_MAP()


// CCodeInspectDlg ��Ϣ�������

BOOL CCodeInspectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCodeInspectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCodeInspectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCodeInspectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCodeInspectDlg::OnBnClickedButtonLoadimg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);

	if (dlg.DoModal() == IDOK)
	{
		this->m_strSrcImgPath = dlg.GetPathName(); //�ļ�����������FilePathName��
	}
	else
	{
		return;
	}
	if (this->m_MatSrc.data == NULL)
	{
		this->m_MatSrc = cv::imread(this->m_strSrcImgPath.GetBuffer(), 0);
		this->m_strSrcImgPath.ReleaseBuffer();
	}
	else
	{
		this->m_MatSrc.release();
		this->m_MatSrc = cv::imread(this->m_strSrcImgPath.GetBuffer(), 0);
		this->m_strSrcImgPath.ReleaseBuffer();
	}
	PaintOnIDC(this->m_MatSrc.data, this->m_MatSrc.cols, this->m_MatSrc.rows, IDC_STATIC_SRCIMG);
}

int CCodeInspectDlg::PaintOnIDC(const uchar* pbuffer,int nWidth,int nHeight, UINT nIDC)
{
	CRect rect;
	GetDlgItem(nIDC)->GetClientRect(&rect);
	cv::Mat srcbuff(cvSize(nWidth, nHeight), CV_8U);
	cv::Mat resizeMat;
	memcpy(srcbuff.data, pbuffer, nWidth*nHeight*sizeof(uchar));
	if (pbuffer == NULL)
		return 0;
	if (rect.Width() != nWidth || rect.Height() != nHeight)
	{
		cv::resize(srcbuff, resizeMat, cvSize(rect.Width(), rect.Height()));
	}
	else
	{
		resizeMat = srcbuff;
	}

	CDC * pDC = GetDlgItem(nIDC)->GetDC();
	HDC pHDC = pDC->GetSafeHdc();

	cv::imwrite("resizeMat.bmp", resizeMat);
	CImage dstcimg;
	LoadMemImage(resizeMat.data, dstcimg, rect.Width(), rect.Height());
	dstcimg.Draw(pHDC, 0, 0);
	ReleaseDC(pDC);
	dstcimg.Destroy();

	OnPaint();
	return 0;
}

void CCodeInspectDlg::LoadMemImage(uchar *pImgBuf, CImage &DesImg, int nWidth, int nHeight)
{
	if (!DesImg.IsNull())
	{
		DesImg.ReleaseGDIPlus();
		DesImg.Destroy();
	}

	//DesImg.Create(nWidth,nHeight,8);

	while (DesImg.IsNull())
	{
		DesImg.Create(nWidth, nHeight, 8);
		Sleep(20);
	}

	RGBQUAD* ColorTable;
	int MaxColors = 256;
	//�������ͨ��Img.GetMaxColorTableEntries()�õ���С(�������Img.Load����ͼ��Ļ�)
	ColorTable = new RGBQUAD[MaxColors];
	DesImg.GetColorTable(0, MaxColors, ColorTable);//������ȡ��ָ��
	for (int i = 0; i < MaxColors; i++)
	{
		ColorTable[i].rgbBlue = (BYTE)i;
		ColorTable[i].rgbGreen = (BYTE)i;
		ColorTable[i].rgbRed = (BYTE)i;
	}
	DesImg.SetColorTable(0, MaxColors, ColorTable);
	delete[]ColorTable;
	ColorTable = NULL;

	BYTE* q;
	for (int y = 0; y < nHeight; y++)
	{
		q = (byte*)DesImg.GetPixelAddress(0, y);
		memcpy(q, &pImgBuf[nWidth*y], nWidth);
	}
}

void CCodeInspectDlg::OnBnClickedButtonProcess()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	cv::Mat threImg,matSobelX16S,matSobelY16S;
	cv::Mat matSobelX, matSobelY,matSobel;
	cv::Mat MatProcess;
	cv::blur(this->m_MatSrc, MatProcess, cvSize(10,10));
	PaintOnIDC(MatProcess.data, MatProcess.cols, MatProcess.rows, IDC_STATIC_PROCESSIMG);
	cv::threshold(MatProcess, threImg, 70, 255, cv::THRESH_BINARY);
	cv::imwrite("threimg.bmp", threImg);
	cv::Mat dstimg(this->m_MatSrc.rows,this->m_MatSrc.cols,this->m_MatSrc.type());
	
	cv::Sobel(threImg, matSobelX16S, CV_16S, 2, 0);
	cv::Sobel(threImg, matSobelY16S, CV_16S, 0, 2);
	cv::convertScaleAbs(matSobelX16S, matSobelX, 1, 0);
	cv::convertScaleAbs(matSobelY16S, matSobelY, 1, 0);
	matSobel = matSobelX + matSobelY;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(threImg, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cv::Point(-1, -1));
	std::vector<std::vector<cv::Point>> ::iterator itcContours,itcEarse;
	std::vector < std::vector < std::vector<cv::Point >>> ControusClass;

	itcContours = contours.begin();
	itcEarse = itcContours;
	dstimg.setTo(255);
	cv::Point2f boxPts[4];
	int contoursClassType;
	int MinWH = this->m_MatSrc.cols > this->m_MatSrc.rows ? this->m_MatSrc.rows : this->m_MatSrc.cols;
	int MaxWH = this->m_MatSrc.cols > this->m_MatSrc.rows ? this->m_MatSrc.cols : this->m_MatSrc.rows;
	while (itcContours != contours.end())
	{
		cv::RotatedRect rcBoxBlob = cv::minAreaRect(*itcContours);
		rcBoxBlob.points(boxPts);
		if ((rcBoxBlob.size.width < 400 && rcBoxBlob.size.height < 100) || (fabs(rcBoxBlob.size.width - MinWH)<10 || fabs(rcBoxBlob.size.height - MaxWH)<10))
			itcContours = contours.erase(itcContours);
		else
		{
			cv::line(dstimg, cvPoint((int)boxPts[0].x, (int)boxPts[0].y), cvPoint((int)boxPts[1].x, (int)boxPts[1].y), cvScalar(0));
			cv::line(dstimg, cvPoint((int)boxPts[1].x, (int)boxPts[1].y), cvPoint((int)boxPts[2].x, (int)boxPts[2].y), cvScalar(0));
			cv::line(dstimg, cvPoint((int)boxPts[2].x, (int)boxPts[2].y), cvPoint((int)boxPts[3].x, (int)boxPts[3].y), cvScalar(0));
			cv::line(dstimg, cvPoint((int)boxPts[3].x, (int)boxPts[3].y), cvPoint((int)boxPts[0].x, (int)boxPts[0].y), cvScalar(0));
			uchar* ptr = dstimg.ptr<uchar>((int)rcBoxBlob.center.y);
			*(ptr + (int)rcBoxBlob.center.x) = 0;
			++itcContours;
		}
	}
	itcContours = contours.begin();
	while (itcContours != contours.end())
	{
		cv::RotatedRect rcBoxBlob = cv::minAreaRect(*itcContours);
		cv::Mat affMatrix = cv::getRotationMatrix2D(rcBoxBlob.center, rcBoxBlob.angle, 1);
		
		cv::Mat matRotedSrc(this->m_MatSrc.cols,this->m_MatSrc.rows,this->m_MatSrc.type());
		cv::warpAffine(this->m_MatSrc, matRotedSrc, affMatrix, cvSize(this->m_MatSrc.cols, this->m_MatSrc.rows));
		PaintOnIDC(matRotedSrc.data, matRotedSrc.cols, matRotedSrc.rows, IDC_STATIC_DSTIMG);
		cv::Rect barCodeRoi;
		barCodeRoi.x = (int)(rcBoxBlob.center.x - rcBoxBlob.size.width / 2.0);
		barCodeRoi.y = (int)(rcBoxBlob.center.y - rcBoxBlob.size.height / 2.0);
		barCodeRoi.width = (int)rcBoxBlob.size.width;
		barCodeRoi.height = (int)rcBoxBlob.size.height;
		//cv::rectangle(matRotedSrc, barCodeRoi, cvScalar(255, 255, 255));
		cv::imwrite("RotatedSrc.bmp", matRotedSrc);
		float* verticleProject = new float[barCodeRoi.width];
		memset(verticleProject, 0,sizeof(float)* barCodeRoi.width);
		for (int i = barCodeRoi.y; i < barCodeRoi.height + barCodeRoi.y;i++)
		{
			uchar* ptrSrc = matRotedSrc.ptr<uchar>(i);
			for (int j = barCodeRoi.x; j < barCodeRoi.width + barCodeRoi.x;j++)
			{
				verticleProject[j - barCodeRoi.x] += ptrSrc[j];
			}
		}
		for (int i = 0; i < barCodeRoi.width;i++)
		{
			verticleProject[i] /= barCodeRoi.height;
		}
		showFloatGraph("Verticle project", verticleProject, barCodeRoi.width);
		++itcContours;
	}
	
	cv::imwrite("dstimg.bmp", dstimg);
	//PaintOnIDC(dstimg.data, dstimg.cols, dstimg.rows, IDC_STATIC_DSTIMG);
	

}


void CCodeInspectDlg::OnBnClickedButtonGetroi()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	cv::Mat threImg, matSobelX16S, matSobelY16S;
	cv::Mat matSobelX, matSobelY, matSobel;
	cv::Mat MatProcess;
	//cv::blur(this->m_MatSrc, MatProcess, cvSize(10, 10));
	MatProcess = this->m_MatSrc.clone();
	PaintOnIDC(MatProcess.data, MatProcess.cols, MatProcess.rows, IDC_STATIC_PROCESSIMG);
	cv::threshold(MatProcess, threImg, 70, 255, cv::THRESH_BINARY);
	cv::imwrite("threimg.bmp", threImg);
	cv::Mat dstimg(this->m_MatSrc.rows, this->m_MatSrc.cols, this->m_MatSrc.type());

	cv::Sobel(threImg, matSobelX16S, CV_16S, 2, 0);
	cv::Sobel(threImg, matSobelY16S, CV_16S, 0, 2);
	cv::convertScaleAbs(matSobelX16S, matSobelX, 1, 0);
	cv::convertScaleAbs(matSobelY16S, matSobelY, 1, 0);
	matSobel = matSobelX + matSobelY;
	PaintOnIDC(matSobel.data, matSobel.cols, matSobel.rows, IDC_STATIC_PROCESSIMG);
	cv::imwrite("edge.bmp", matSobel);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(threImg, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cv::Point(-1, -1));
	std::vector<std::vector<cv::Point>> ::iterator itcContours, itcEarse;
	std::vector < std::vector < std::vector<cv::Point >>> ControusClass;

	itcContours = contours.begin();
	itcEarse = itcContours;
	dstimg.setTo(255);
	cv::Point2f boxPts[4];
	int contoursClassType;
	int MinWH = this->m_MatSrc.cols > this->m_MatSrc.rows ? this->m_MatSrc.rows : this->m_MatSrc.cols;
	int MaxWH = this->m_MatSrc.cols > this->m_MatSrc.rows ? this->m_MatSrc.cols : this->m_MatSrc.rows;

	while (itcContours != contours.end())
	{
		double contoursArea = cv::contourArea(*itcContours);
		cv::RotatedRect rcBoxBlob = cv::minAreaRect(*itcContours);
		rcBoxBlob.points(boxPts);
		if (contoursArea/(rcBoxBlob.size.width*rcBoxBlob.size.height)<0.5)
			itcContours = contours.erase(itcContours);
		else
		{
			//cv::line(dstimg, cvPoint((int)boxPts[0].x, (int)boxPts[0].y), cvPoint((int)boxPts[1].x, (int)boxPts[1].y), cvScalar(0));
			cv::line(dstimg, cvPoint((int)boxPts[1].x, (int)boxPts[1].y), cvPoint((int)boxPts[2].x, (int)boxPts[2].y), cvScalar(0));
			//cv::line(dstimg, cvPoint((int)boxPts[2].x, (int)boxPts[2].y), cvPoint((int)boxPts[3].x, (int)boxPts[3].y), cvScalar(0));
			cv::line(dstimg, cvPoint((int)boxPts[3].x, (int)boxPts[3].y), cvPoint((int)boxPts[0].x, (int)boxPts[0].y), cvScalar(0));
			uchar* ptr = dstimg.ptr<uchar>((int)rcBoxBlob.center.y);
			*(ptr + (int)rcBoxBlob.center.x) = 0;
			++itcContours;
		}
	}
	//itcContours = contours.begin();
	//while (itcContours != contours.end())
	//{
	//	cv::RotatedRect rcBoxBlob = cv::minAreaRect(*itcContours);
	//	cv::Mat affMatrix = cv::getRotationMatrix2D(rcBoxBlob.center, rcBoxBlob.angle, 1);

	//	cv::Mat matRotedSrc(this->m_MatSrc.cols, this->m_MatSrc.rows, this->m_MatSrc.type());
	//	cv::warpAffine(this->m_MatSrc, matRotedSrc, affMatrix, cvSize(this->m_MatSrc.cols, this->m_MatSrc.rows));
	//	PaintOnIDC(matRotedSrc.data, matRotedSrc.cols, matRotedSrc.rows, IDC_STATIC_DSTIMG);
	//	cv::Rect barCodeRoi;
	//	barCodeRoi.x = (int)(rcBoxBlob.center.x - rcBoxBlob.size.width / 2.0);
	//	barCodeRoi.y = (int)(rcBoxBlob.center.y - rcBoxBlob.size.height / 2.0);
	//	barCodeRoi.width = (int)rcBoxBlob.size.width;
	//	barCodeRoi.height = (int)rcBoxBlob.size.height;
	//	//cv::rectangle(matRotedSrc, barCodeRoi, cvScalar(255, 255, 255));
	//	cv::imwrite("RotatedSrc.bmp", matRotedSrc);
	//	float* verticleProject = new float[barCodeRoi.width];
	//	memset(verticleProject, 0, sizeof(float)* barCodeRoi.width);
	//	for (int i = barCodeRoi.y; i < barCodeRoi.height + barCodeRoi.y; i++)
	//	{
	//		uchar* ptrSrc = matRotedSrc.ptr<uchar>(i);
	//		for (int j = barCodeRoi.x; j < barCodeRoi.width + barCodeRoi.x; j++)
	//		{
	//			verticleProject[j - barCodeRoi.x] += ptrSrc[j];
	//		}
	//	}
	//	for (int i = 0; i < barCodeRoi.width; i++)
	//	{
	//		verticleProject[i] /= barCodeRoi.height;
	//	}
	//	showFloatGraph("Verticle project", verticleProject, barCodeRoi.width);
	//	++itcContours;
	//}

	cv::imwrite("dstimg.bmp", dstimg);
	PaintOnIDC(dstimg.data, dstimg.cols, dstimg.rows, IDC_STATIC_DSTIMG);
}


void CCodeInspectDlg::OnBnClickedButtonPcolor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	cv::Mat img = cv::imread(this->m_strSrcImgPath.GetBuffer(), 0);
	this->m_strSrcImgPath.ReleaseBuffer();
	unsigned short * p = img.ptr<unsigned short>(img.rows / 2);
	//const int n = img.type();
	int  n = 1 << CV_CN_SHIFT;
	CV_MAT_TYPE(img.flags);
	if (CV_16U == img.type())
		AfxMessageBox("OK");

}


void CCodeInspectDlg::OnBnClickedButtonArctest()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	cv::Mat img = cv::imread(this->m_strSrcImgPath.GetBuffer(), 0);
	cv::Mat thredst;
	this->m_strSrcImgPath.ReleaseBuffer();
	thredst.create(cvSize(img.cols, img.rows), CV_8U);
	try{
		cv::threshold(img, thredst, 70,255,CV_THRESH_BINARY);
	}
	catch (cv::Exception &e)
	{
		TRACE(e.err.c_str());
	}
	cv::imwrite("arcThre.bmp", thredst);
	PaintOnIDC(thredst.data, thredst.cols, thredst.rows, IDC_STATIC_PROCESSIMG);
}


void CCodeInspectDlg::OnBnClickedButtonLoadtemplate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);

	if (dlg.DoModal() == IDOK)
	{
		this->m_strTemplateImagePath = dlg.GetPathName(); //�ļ�����������FilePathName��
	}
	else
	{
		return;
	}
	if (this->m_MatTemplate.data == NULL)
	{
		this->m_MatTemplate = cv::imread(this->m_strTemplateImagePath.GetBuffer(), 0);
		this->m_strTemplateImagePath.ReleaseBuffer();
	}
	else
	{
		this->m_MatTemplate.release();
		this->m_MatTemplate = cv::imread(this->m_strTemplateImagePath.GetBuffer(), 0);
		this->m_strSrcImgPath.ReleaseBuffer();
	}
	PaintOnIDC(this->m_MatTemplate.data, this->m_MatTemplate.cols, this->m_MatSrc.rows, IDC_STATIC_TEMPLATEIMG);
}


void CCodeInspectDlg::OnBnClickedButtonTemplatematch()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if ((!this->m_MatSrc.data) || (!this->m_MatTemplate.data)||(this->m_MatSrc.cols<this->m_MatTemplate.cols)||(this->m_MatSrc.rows<this->m_MatTemplate.rows))
		return;

	cv::Mat resultMat(this->m_MatSrc.rows - this->m_MatTemplate.rows, this->m_MatSrc.cols - this->m_MatTemplate.cols, CV_32FC1);

	cv::matchTemplate(this->m_MatSrc, this->m_MatTemplate, resultMat, CV_TM_CCOEFF_NORMED);
	double fMax, fMin;
	cv::Point MaxLoc, MinLoc;
	cv::minMaxLoc(resultMat, &fMin, &fMax, &MinLoc, &MaxLoc);

}

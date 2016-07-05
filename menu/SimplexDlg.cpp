// SimplexDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimplexDlg.h"
#include "afxdialogex.h"
//#include "SimplexFunction.h"
#include "TransRevShare.h"
#include "SystemParameter.h"
#include "Framing.h"
#include "encode.h"
#include "menuDlg.h"


// CSimplexDlg �Ի���

IMPLEMENT_DYNAMIC(CSimplexDlg, CDialogEx)

CSimplexDlg::CSimplexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimplexDlg::IDD, pParent)
{

}

CSimplexDlg::~CSimplexDlg()
{
}

void CSimplexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LED1_STATIC, m_led1);
	DDX_Control(pDX, IDC_LED2_STATIC, m_led2);
	DDX_Control(pDX, IDC_LED3_STATIC, m_led3);
	DDX_Control(pDX, IDC_LED4_STATIC, m_led4);
	DDX_Control(pDX, IDC_LED5_STATIC, m_led5);
	DDX_Control(pDX, IDC_LED6_STATIC, m_led6);
	DDX_Control(pDX, IDC_LED7_STATIC, m_led7);
	DDX_Control(pDX, IDC_LED8_STATIC, m_led8);
	DDX_Control(pDX, IDC_LED9_STATIC, m_led9);
}


BEGIN_MESSAGE_MAP(CSimplexDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSimplexDlg ��Ϣ�������


void CSimplexDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������

	CPen pen; //���廭�ʶ���
	CBrush brush; //�����ˢ����
	pen.CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush.CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush); //����ˢѡ��dc
	dc.SelectObject(&pen);  //������ѡ��dc
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	dc.Rectangle(15, 20, 500, 430); //����һ��͸�����ı���

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}

int CSimplexDlg::StartRunSimplex(int a)
{
	state_inactiveS = 0;
	state_starthailS = 0;
	state_hailacquisitionS = 0;
	state_haildirectivesS = 0;
	state_hailtailS = 0;
	state_hailresponseS = 0;
	state_carrieronlyS = 0;
	state_acquisitionS = 0;
	state_simplexsonS = 0;
	state_lnmdendS = 0;
	state_simplexsendS = 0;
	state_terminatingtailS = 0;

	StopFlagS = 0;

	SetLedOff(1);
	Sleep(1000);
	state_inactiveS = 1;   //��ʼ״̬
	m_led1.SetBitmap(m_red);

	//hThread = CreateThread(NULL,
	//	0,
	//	(LPTHREAD_START_ROUTINE)ThreadFuncS,
	//	this,
	//	0,
	//	&ThreadID); //����һ���߳�
	CWinThread * m_pThread;
	m_pThread = AfxBeginThread(ThreadFuncS, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	if (NULL == m_pThread)
	{
		CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
		SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(_T("Error in Begin a Thread.\r\n"));
	}
	
	return 0; //��������з���ֵ�ĺ�����������Ҫreturn 0
}
int CSimplexDlg::SetLedOff(int a)
{
	m_led1.SetBitmap(m_grey);
	m_led2.SetBitmap(m_grey);
	m_led3.SetBitmap(m_grey);
	m_led4.SetBitmap(m_grey);
	m_led5.SetBitmap(m_grey);
	m_led6.SetBitmap(m_grey);
	m_led7.SetBitmap(m_grey);
	m_led8.SetBitmap(m_grey);
	m_led9.SetBitmap(m_grey);

	return 0;
}

//void ThreadFuncS(LPVOID lpParam)
UINT ThreadFuncS(LPVOID lpParam)
{
	CSimplexDlg *pDlg = (CSimplexDlg*)lpParam;
	CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;

	while (1)
	{
		if (endSystemFlag)
		{
			endSystemFlag = 0;
			pDlg->endSystem();
		}
		pDlg->state_starthailS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(_T("Start Hail Action.\r\n"));
		pDlg->m_led2.SetBitmap(pDlg->m_red);
		Sleep(1000);

		if (endSystemFlag)
		{
			endSystemFlag = 0;
			pDlg->endSystem();
		}
		pDlg->state_carrieronlyS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(_T("Radiate Carrier Only.\r\n"));
		pDlg->m_led3.SetBitmap(pDlg->m_red);
		Sleep(2000);

		if (endSystemFlag)
		{
			endSystemFlag = 0;
			pDlg->endSystem();
		}
		pDlg->state_hailacquisitionS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(_T("Carrier Only.\r\n"));
		pDlg->m_led4.SetBitmap(pDlg->m_red);

		if (endSystemFlag)
		{
			endSystemFlag = 0;
			pDlg->endSystem();
		}
		pDlg->state_acquisitionS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(_T("Send Hail Acquisition.\r\n"));
		pDlg->m_led5.SetBitmap(pDlg->m_red);		

		//����Ӧ����������ָ��
		HallCommond = 1;
		CarrierSend_T = 1;

		CommondGroup = SPDU_framing();
		encodecommond(CommondGroup);
		((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);

		HallCommond = 0;
		CarrierSend_T = 0;

		Sleep(1000);

		if (endSystemFlag)
		{
			endSystemFlag = 0;
			pDlg->endSystem();
		}
		pDlg->state_simplexsonS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(_T("Data Service Send.\r\n"));
		pDlg->m_led6.SetBitmap(pDlg->m_red);

		pDlg->dangongsend();
		pDlg->m_led6.SetBitmap(pDlg->m_red);

		if (endSystemFlag)
		{
			endSystemFlag = 0;
			pDlg->endSystem();
		}
		pDlg->state_lnmdendS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(_T("Receive LNMD.\r\n"));
		pDlg->m_led7.SetBitmap(pDlg->m_red);
		Sleep(2000);

		//����RNMDָ��
		SetControlParameters = 1;
		RNMD_T = 1;
		
		CommondGroup = SPDU_framing();
		encodecommond(CommondGroup);
		((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
		
		SetControlParameters = 0;
		RNMD_T = 0;

		if (endSystemFlag)
		{
			endSystemFlag = 0;
			pDlg->endSystem();
		}
		pDlg->state_simplexsendS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(_T("Data Service End.\r\n"));
		pDlg->m_led8.SetBitmap(pDlg->m_red);
		Sleep(2000);

		if (endSystemFlag)
		{
			endSystemFlag = 0;
			pDlg->endSystem();
		}
		pDlg->state_terminatingtailS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(_T("Terminating Tail.\r\n"));
		pDlg->m_led9.SetBitmap(pDlg->m_red);
		
		Sleep(2000);
		pDlg->SetLedOff(1);

		break;
	}

	
	return 0;
}


void CSimplexDlg::SystemTime()
{
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime(); //��ȡϵͳ��ǰʱ��
	strTime = tm.Format("%Y.%m.%d %X"); //��ʽת��
	CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
	//AfxGetMainWnd��Ӧ�ó������̵߳��ã����������Ϲ��򷵻�Ӧ�ó���������ڡ�����ú�����Ӧ�ó���Ĵ��̵߳��ã��ú�������������õ����߳����ӵ�������
	//		CmenuDlg *ppDlg = (CmenuDlg*)AfxGetMainWnd();
	ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	ppDlg->m_Hist.ReplaceSel(strTime + "\r\n");
	//	return strTime;
}

void CSimplexDlg::dangongsend()
{
	int *temp, *temp2;
	int *buffer; //����
	int h = 0;							//������Ч֡�Ĵ���
	int n;
	int allnumber = 0;			//����֡����
	//	char *temp;
	num_frame = 0; //֡���к�
	Error = 0;
	Num_Data = SendA.FrameLength * 8;			//��bit����FrameLength���ֽ�
	/*********ͨ��������ȥ��ÿؼ�ֵ���������д��룩
	CString strFilePath;
	psDlg->GetDlgItemText(IDC_SENDSOUCER_EDIT, strFilePath);
	CFile file(strFilePath, CFile::modeRead | CFile::typeBinary);
	*/
	// ����κ��壺��ȡԶ�̷����ļ�
	/****************����WideCharToMultiByte���ϵͳ������CStringת��char*��************************/
	//��ȡת�������Ŀ�껺���С
//	DWORD dBufSize_R = WideCharToMultiByte(CP_OEMCP, 0, ReceiveA.gRemoteDataPath, -1, NULL, 0, NULL, FALSE);
	//����Ŀ�껺��
//	char *strFilePath_R = new char[dBufSize_R + 1]; //new���������Ķѵ�һ��ռ䣬������Ӧ�������ͷţ�������������ڴ�й©
//	memset(strFilePath_R, 0, dBufSize_R);
	//ת����WideCharToMultiByte����������гɹ�������cchMultiByte��Ϊ�㣬����ֵ���� lpMultiByteStrָ��Ļ�������д����ֽ�����
//	int nRet_R = WideCharToMultiByte(CP_OEMCP, 0, ReceiveA.gRemoteDataPath, -1, strFilePath_R, dBufSize_R, NULL, FALSE);
	/******���Դ���
	if (nRet_R <= 0)
	{
	MessageBox(_T("ת��ʧ��\n"));
	}
	else
	{
	MessageBox(_T("ת���ɹ�\n"));
	}
	*/
//	FILE *fp_R;
//	errno_t err_R;
//	err_R = fopen_s(&fp_R, strFilePath_R, "r+"); //��ȫ��ʽ���ļ����ɹ��򿪷���0��δ�ɹ��򿪷���1
	/********���Դ���
	if (err_R == 0)
	{
	MessageBox(_T("The file  was opened!"));
	}
	else
	{
	MessageBox(_T("The file  was not opened"));
	}
	*/
	//fopen()������fseek��ftell������ļ��ĳ���
//	fseek(fp_R, 0, SEEK_END);		//��λ�ļ�ָ�뵽�ļ�ĩβ	�ɹ�����0�����ɹ�����-1
//	fileSize1 = ftell(fp_R);			//���ԣ�����Դ�ļ�1111.dat   filesize = 72
//	fseek(fp_R, 0, SEEK_SET);	//�ٶ�λ�ļ�ָ�뵽�ļ�ͷ
//	delete[]strFilePath_R; //�ͷţ����ɺ�ϰ��
//	strFilePath_R = NULL;

//	SourceFile = (int*)malloc(fileSize1*sizeof(int));//C���������ڴ�ռ亯��
//	for (int i = 0; i < fileSize1; i++)
//	{
//		fscanf_s(fp_R, "%1u", &SourceFile[i]);		//%u����ʽ�ַ�����%1u��Ҫ����������Ҷ���һλ
//	}

//	fclose(fp_R);//C���Ա���µĹر��ļ�

	// ����κ��壺��ȡ���ط����ļ�
	/****************����WideCharToMultiByte���ϵͳ������CStringת��char*��************************/
	//��ȡת�������Ŀ�껺���С
	DWORD dBufSize = WideCharToMultiByte(CP_OEMCP, 0, SendA.gSendDataPath, -1, NULL, 0, NULL, FALSE); //���ԣ�����Դ�ļ�1111.dat   dBufSize = 77
	//����Ŀ�껺��
	char *strFilePath = new char[dBufSize + 1]; //new���������Ķѵ�һ��ռ䣬������Ӧ�������ͷţ�������������ڴ�й©
	memset(strFilePath, 0, dBufSize);
	//ת����WideCharToMultiByte����������гɹ�������cchMultiByte��Ϊ�㣬����ֵ���� lpMultiByteStrָ��Ļ�������д����ֽ�����
	int nRet = WideCharToMultiByte(CP_OEMCP, 0, SendA.gSendDataPath, -1, strFilePath, dBufSize, NULL, FALSE);

	/*���Դ��� *****
	if (nRet <= 0)
	{
	MessageBox(_T("ת��ʧ��\n"));
	}
	else
	{
	MessageBox(_T("ת���ɹ�\n"));
	}
	*/
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, strFilePath, "r+"); //��ȫ��ʽ���ļ����ɹ��򿪷���0��δ�ɹ��򿪷���1
	/**********����
	if (err == 0)
	{
	MessageBox(_T("The file  was opened!"));
	}
	else
	{
	MessageBox(_T("The file  was not opened"));
	}*/
	//fopen()������fseek��ftell������ļ��ĳ���
	int filesize;
	fseek(fp, 0, SEEK_END);		//��λ�ļ�ָ�뵽�ļ�ĩβ	�ɹ�����0�����ɹ�����-1
	filesize = ftell(fp);			//���ԣ�����Դ�ļ�1111.dat   filesize = 72
	fseek(fp, 0, SEEK_SET);	//�ٶ�λ�ļ�ָ�뵽�ļ�ͷ
	delete[]strFilePath; //�ͷţ����ɺ�ϰ��
	strFilePath = NULL;

	temp = (int*)malloc(filesize*sizeof(int));//C���������ڴ�ռ亯��
	for (int i = 0; i < filesize; i++)
	{
		fscanf_s(fp, "%1u", &temp[i]);		//%u����ʽ�ַ�����%1u��Ҫ����������Ҷ���һλ
	}
	//�ж�Ҫ���͵Ĵ���n
	if (filesize % Num_Data)
	{
		n = filesize / Num_Data + 1;
	}
	else
	{
		n = filesize / Num_Data;
	}

	//��ɱ�׼֡�����㲹0
	temp2 = (int*)malloc(Num_Data*n*sizeof(int));
	for (int i = 0; i < Num_Data*n; i++)
	{
		if (i < filesize)
			temp2[i] = temp[i];
		else
			temp2[i] = 0;
	}
	while (1)
	{
		buffer = (int *)malloc(Num_Data*sizeof(int));
		for (int i = 0; i < Num_Data; i++)
		{
			buffer[i] = temp2[i + Num_Data*h];
		}
		h++;
		break;
	}

	CString	*str;
	str = new CString[Num_Data*n + 1];
	CString strDisplay;
	for (int i = 0; i < Num_Data; i++) //Ϊ�˴�int������תCString���������������
	{
		str[i].Format(_T("%d"), buffer[i]);
		strDisplay += str[i];	//����CString��������+=������
	} //���ݱ��浽strDisplay���������

	//��Ҫ���͵������͵�CStatusDisply�Ի������еķ������ݱ༭��
	d_sdSDlg->m_HistSendData.SetSel(d_sdSDlg->m_HistSendData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	d_sdSDlg->m_HistSendData.ReplaceSel(strDisplay); //�滻��ǰ�ı�
	//	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay);
	d_sdSDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //���������ܱ�������ʾ
	d_sdSDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//��ʾ��֡��


	while (1)
	{
		if (endSystemFlag)
		{
			break;
		}
		if (commondstate == 0)					 //�жϴ�ʱû��ָ���
		{
			messagestate = 1;						//��ʱ��������
			encode(buffer);


			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
			arqarray(num_frame);					//�����ݴ������飬�Է���arq
			break;
		}

	}
	messagestate = 0;
	/******���õ���˸��ʾ���ڷ�������*****/
	state_simplexsonS = 1;	
	m_led6.SetBitmap(m_red);
	Sleep(1000);
	state_simplexsonS = 0;
	m_led6.SetBitmap(m_grey);
	/*************************************/
	num_frame++;
	allnumber++;
	Sleep(4000);

	while (1)
	{
		/*		if (arqreceiveflag == 1)
		{
		arqreceiveflag = 0;
		d_sdDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //���������ܱ�������ʾ
		CString frame_resend;
		frame_resend.Format(_T("%d"), ResendNumber_R);
		d_sdDlg->m_ResendFrameNumEdit.SetSel(d_sdDlg->m_ResendFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		d_sdDlg->m_ResendFrameNumEdit.ReplaceSel(frame_resend); //�滻��ǰ�ı�
		d_sdDlg->m_ResendFrameNumEdit.SetSel(d_sdDlg->m_ResendFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		d_sdDlg->m_ResendFrameNumEdit.ReplaceSel(_T(",")); //�滻��ǰ�ı�
		while (1)
		{
		if (commondstate == 0)
		{
		messagestate = 1;
		arqsend(ResendNumber_R);					//�ӻ����ȡ�ش�֡
		Len_DataInProcess = Num_Data + 24 + 40 + 32;
		Sleep(1000);
		((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessage(P_Data_CC, Len_DataInProcess);
		break;
		}

		}
		messagestate = 0;
		d_sdDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, ResendNumber_R);//��ʾ��֡��

		state_senddataH = 1;
		CBitmap bitmap[2];
		HBITMAP hBmp[2];
		bitmap[0].LoadBitmap(IDB_BITMAP_RED);
		hBmp[0] = (HBITMAP)bitmap[0].GetSafeHandle();
		m_led11.SetBitmap(hBmp[0]);
		Sleep(1000);
		state_senddataH = 0;
		bitmap[1].LoadBitmap(IDB_BITMAP_GREY);
		hBmp[1] = (HBITMAP)bitmap[1].GetSafeHandle();
		m_led11.SetBitmap(hBmp[1]);

		allnumber++;
		h = ResendNumber_R + 1;
		num_frame = ResendNumber_R + 1;
		Sleep(4000);
		}*/
		if (endSystemFlag)
		{
			break;
		}
		if (n == h)
		{
			break;
		}
		Sleep(1000);
		while (1)
		{
			for (int i = 0; i < Num_Data; i++)
			{
				buffer[i] = temp2[i + Num_Data*h];
			}
			h++;
			break;
		}
		CString	*str;
		str = new CString[Num_Data*n + 1];
		CString strDisplay;
		for (int i = 0; i < Num_Data; i++) //Ϊ�˴�int������תCString���������������
		{
			str[i].Format(_T("%d"), buffer[i]);
			strDisplay += str[i];	//����CString��������+=������
		} //���ݱ��浽strDisplay���������

		//��Ҫ���͵������͵�CStatusDisply�Ի������еķ������ݱ༭��
		d_sdSDlg->m_HistSendData.SetSel(d_sdSDlg->m_HistSendData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		d_sdSDlg->m_HistSendData.ReplaceSel(strDisplay); //�滻��ǰ�ı�
		//	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay);
		d_sdSDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //���������ܱ�������ʾ
		d_sdSDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//��ʾ��֡��

		while (1)
		{
			if (commondstate == 0)					 //�жϴ�ʱû��ָ���
			{
				messagestate = 1;						//��ʱ��������
				encode(buffer);

				//				Sleep(4000);
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
				arqarray(num_frame);					//�����ݴ������飬�Է���arq
				break;
			}

		}
		messagestate = 0;
		/******���õ���˸��ʾ���ڷ�������*****/
		state_simplexsonS= 1;
		m_led6.SetBitmap(m_red);
		Sleep(1000);
		state_simplexsonS = 0;
		m_led9.SetBitmap(m_grey);
		/*************************************/
		num_frame++;
		allnumber++;
		Sleep(4000);
	}

	fclose(fp);//C���Ա���µĹر��ļ�
	free(temp); //�ͷ�ָ��ָ����ڴ�
	temp = NULL;//ָ���ڴ��ָ����Ϊ�գ���ֹ������治С��ʹ������

}


void CSimplexDlg::arqarray(int framecounter)
{
	int length = Num_Data + 24 + 40 + 32;

	switch (framecounter % 10)
	{
	case 0:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + i) = *(P_Data_CC + i);
		}
		break;
	case 1:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + length + i) = *(P_Data_CC + i);
		}
		break;
	case 2:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 2 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 3:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 3 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 4:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 4 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 5:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 5 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 6:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 6 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 7:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 7 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 8:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 8 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 9:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 9 * length + i) = *(P_Data_CC + i);
		}
		break;
	}

}

void CSimplexDlg::arqsend(int framecounter)
{
	int length = Num_Data + 24 + 40 + 32;
	P_Data_CC = (int *)malloc(length*sizeof(int));
	switch (framecounter % 10)
	{
	case 0:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[i];
		}
		break;
	case 1:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[length + i];
		}
		break;
	case 2:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[2 * length + i];
		}
		break;
	case 3:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[3 * length + i];
		}
		break;
	case 4:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[4 * length + i];
		}
		break;
	case 5:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[5 * length + i];
		}
		break;
	case 6:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[6 * length + i];
		}
		break;
	case 7:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[7 * length + i];
		}
		break;
	case 8:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[8 * length + i];
		}
		break;
	case 9:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[9 * length + i];
		}
		break;

	}
}


BOOL CSimplexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	font.CreatePointFont(110, _T("΢���ź�")); //����������ʽ������110����11������
	GetDlgItem(IDC_SIMPLEXPROCEDURES_STATIC)->SetFont(&font); //�����崫�ݸ���̬��

	m_grey = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_GREY));
	m_red = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_RED));
	//AfxGetInstanceHandle():This function allows you to retrieve (ȡ��) the instance handle of the current application.
	//MAKEINTRESOURCE macro (��):Converts an integer value to a resource type compatible with the resource-management functions. This macro is used in place of a string containing the name of the resource.
	/*********��ʼled��Ϊ��ɫ**********/
	m_led1.SetBitmap(m_grey);
	m_led2.SetBitmap(m_grey);
	m_led3.SetBitmap(m_grey);
	m_led4.SetBitmap(m_grey);
	m_led5.SetBitmap(m_grey);
	m_led6.SetBitmap(m_grey);
	m_led7.SetBitmap(m_grey);
	m_led8.SetBitmap(m_grey);
	m_led9.SetBitmap(m_grey);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CSimplexDlg::endSystem()
{
	SetLedOff(1);
	CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
	SystemTime();
	ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	ppDlg->m_Hist.ReplaceSel(_T("End the Thread.\r\n"));
	AfxEndThread(0, TRUE);	
}
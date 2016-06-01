// SimplexDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimplexDlg.h"
#include "afxdialogex.h"
#include "SimplexFunction.h"
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


// CSimplexDlg ��Ϣ��������


void CSimplexDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴�������Ϣ�����������

	CPen pen; //���廭�ʶ���
	CBrush brush; //�����ˢ����
	pen.CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush.CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush); //����ˢѡ��dc
	dc.SelectObject(&pen);  //������ѡ��dc
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	dc.Rectangle(15, 10, 500, 470); //����һ��͸�����ı���

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

	hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFuncS,
		this,
		0,
		&ThreadID); //����һ���߳�

	return 0; //��������з���ֵ�ĺ�����������Ҫreturn 0
}
int CSimplexDlg::SetLedOffS(int a)
{
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_GREY);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led1.SetBitmap(hBmp);
	m_led2.SetBitmap(hBmp);
	m_led3.SetBitmap(hBmp);
	m_led4.SetBitmap(hBmp);
	m_led5.SetBitmap(hBmp);
	m_led6.SetBitmap(hBmp);
	m_led7.SetBitmap(hBmp);
	m_led8.SetBitmap(hBmp);
	m_led9.SetBitmap(hBmp);

	return 0;
}

void ThreadFuncS(LPVOID lpParam)
{
	CSimplexDlg *pDlg = (CSimplexDlg*)lpParam;
	while (StopFlagS == 0)
	{
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_inactiveS = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led1.SetBitmap(hBmp);
			if (state_inactiveS == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_starthailS= 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led2.SetBitmap(hBmp);
			if (state_starthailS == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_starthailS = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led2.SetBitmap(hBmp);
			if (state_starthailS == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_hailacquisitionS = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led3.SetBitmap(hBmp);
			if (state_hailacquisitionS == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_carrieronlyS = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led4.SetBitmap(hBmp);
			if (state_carrieronlyS == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_acquisitionS = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led5.SetBitmap(hBmp);

			//�򱻶������������ź�
			HallCommond = 1;
			CarrierSend_T = 1;

			CommondGroup = SPDU_framing();
			encodecommond(CommondGroup);
			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessage(P_Data_CC, Len_DataInProcess);

			HallCommond = 0;
			CarrierSend_T = 0;

			if (state_acquisitionS == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);

			SystemTimeS();  //���û�ȡϵͳʱ�亯��
			CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("��������\r\n"));
			pDlg->dangongsend();

			state_simplexsonS = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led6.SetBitmap(hBmp);
			if (state_simplexsonS == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(4000);
			state_lnmdendS = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led7.SetBitmap(hBmp);

			SetControlParameters = 1;
			RNMD_T = 1;

			CommondGroup = SPDU_framing();
			encodecommond(CommondGroup);
			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessage(P_Data_CC, Len_DataInProcess);

			SetControlParameters = 0;
			RNMD_T = 0;

			if (state_lnmdendS == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_simplexsendS = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led8.SetBitmap(hBmp);
			if (state_simplexsendS == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_terminatingtailS = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led9.SetBitmap(hBmp);
			if (state_terminatingtailS == 1) break;
		}
		Sleep(2000);
		pDlg->SetLedOffS(1); //��LED���ú�
		break;
	}


}
void SystemTimeS()
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
		if (commondstate == 0)					 //�жϴ�ʱû��ָ���
		{
			messagestate = 1;						//��ʱ��������
			encode(buffer);


			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessage(P_Data_CC, Len_DataInProcess);
			arqarray(num_frame);					//�����ݴ������飬�Է���arq
			break;
		}

	}
	messagestate = 0;
	/******���õ���˸��ʾ���ڷ�������*****/
	state_simplexsonS = 1;
	CBitmap bitmap[2];
	HBITMAP hBmp[2];
	bitmap[0].LoadBitmap(IDB_BITMAP_RED);
	hBmp[0] = (HBITMAP)bitmap[0].GetSafeHandle();
	m_led6.SetBitmap(hBmp[0]);
	Sleep(1000);
	state_simplexsonS = 0;
	bitmap[1].LoadBitmap(IDB_BITMAP_GREY);
	hBmp[1] = (HBITMAP)bitmap[1].GetSafeHandle();
	m_led6.SetBitmap(hBmp[1]);
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
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessage(P_Data_CC, Len_DataInProcess);
				arqarray(num_frame);					//�����ݴ������飬�Է���arq
				break;
			}

		}
		messagestate = 0;
		/******���õ���˸��ʾ���ڷ�������*****/
		state_simplexsonS= 1;
		CBitmap bitmap[2];
		HBITMAP hBmp[2];
		bitmap[0].LoadBitmap(IDB_BITMAP_RED);
		hBmp[0] = (HBITMAP)bitmap[0].GetSafeHandle();
		m_led6.SetBitmap(hBmp[0]);
		Sleep(1000);
		state_simplexsonS = 0;
		bitmap[1].LoadBitmap(IDB_BITMAP_GREY);
		hBmp[1] = (HBITMAP)bitmap[1].GetSafeHandle();
		m_led9.SetBitmap(hBmp[1]);
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
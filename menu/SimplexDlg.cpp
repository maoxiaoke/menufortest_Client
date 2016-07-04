// SimplexDlg.cpp : 实现文件
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


// CSimplexDlg 对话框

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


// CSimplexDlg 消息处理程序


void CSimplexDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码

	CPen pen; //定义画笔对象
	CBrush brush; //定义笔刷对象
	pen.CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	brush.CreateStockObject(NULL_BRUSH); //初始化实心的空画刷（没有背景颜色）
	dc.SelectObject(&brush); //将画刷选入dc
	dc.SelectObject(&pen);  //将画笔选入dc
	dc.SetBkMode(TRANSPARENT); //设置背景模式为透明，也可以使用SetBkColor设置背景色
	dc.Rectangle(15, 20, 500, 430); //创建一个透明的文本框

	// 不为绘图消息调用 CDialogEx::OnPaint()
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
	state_inactiveS = 1;   //初始状态
	m_led1.SetBitmap(m_red);

	//hThread = CreateThread(NULL,
	//	0,
	//	(LPTHREAD_START_ROUTINE)ThreadFuncS,
	//	this,
	//	0,
	//	&ThreadID); //开辟一个线程

	/*HANDLE m_handle = (HANDLE)_beginthreadex(NULL, 0, ThreadFuncS, NULL, NULL, NULL);*/
	AfxBeginThread(ThreadFuncS, this, THREAD_PRIORITY_NORMAL,0,0,NULL);

	return 0; //定义的是有返回值的函数，所以需要return 0
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
		pDlg->state_starthailS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Start Hail Action.\r\n"));
		pDlg->m_led2.SetBitmap(pDlg->m_red);
		Sleep(1000);

		pDlg->state_carrieronlyS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Radiate Carrier Only.\r\n"));
		pDlg->m_led3.SetBitmap(pDlg->m_red);
		Sleep(2000);

		pDlg->state_hailacquisitionS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Carrier Only.\r\n"));
		pDlg->m_led4.SetBitmap(pDlg->m_red);

		pDlg->state_acquisitionS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Send Hail Acquisition.\r\n"));
		pDlg->m_led5.SetBitmap(pDlg->m_red);		

		//向响应方发送握手指令
		HallCommond = 1;
		CarrierSend_T = 1;

		CommondGroup = SPDU_framing();
		encodecommond(CommondGroup);
		((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);

		HallCommond = 0;
		CarrierSend_T = 0;

		Sleep(1000);

		pDlg->state_simplexsonS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Data Service Send.\r\n"));
		pDlg->m_led6.SetBitmap(pDlg->m_red);

		pDlg->dangongsend();
		pDlg->m_led6.SetBitmap(pDlg->m_red);

		pDlg->state_lnmdendS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Receive LNMD.\r\n"));
		pDlg->m_led7.SetBitmap(pDlg->m_red);
		Sleep(2000);

		//发送RNMD指令
		SetControlParameters = 1;
		RNMD_T = 1;
		
		CommondGroup = SPDU_framing();
		encodecommond(CommondGroup);
		((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
		
		SetControlParameters = 0;
		RNMD_T = 0;

		pDlg->state_simplexsendS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Data Service End.\r\n"));
		pDlg->m_led8.SetBitmap(pDlg->m_red);
		Sleep(2000);

		pDlg->state_terminatingtailS = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
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
	tm = CTime::GetCurrentTime(); //获取系统当前时间
	strTime = tm.Format("%Y.%m.%d %X"); //格式转换
	CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
	//AfxGetMainWnd被应用程序主线程调用，它根据以上规则返回应用程序的主窗口。如果该函数被应用程序的次线程调用，该函数返回与引起该调用线程连接的主窗口
	//		CmenuDlg *ppDlg = (CmenuDlg*)AfxGetMainWnd();
	ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
	ppDlg->m_Hist.ReplaceSel(strTime + "\r\n");
	//	return strTime;
}

void CSimplexDlg::dangongsend()
{
	int *temp, *temp2;
	int *buffer; //缓存
	int h = 0;							//发送有效帧的次数
	int n;
	int allnumber = 0;			//发送帧次数
	//	char *temp;
	num_frame = 0; //帧序列号
	Error = 0;
	Num_Data = SendA.FrameLength * 8;			//总bit数，FrameLength是字节
	/*********通过访问类去获得控件值（下面三行代码）
	CString strFilePath;
	psDlg->GetDlgItemText(IDC_SENDSOUCER_EDIT, strFilePath);
	CFile file(strFilePath, CFile::modeRead | CFile::typeBinary);
	*/
	// 代码段含义：读取远程发射文件
	/****************利用WideCharToMultiByte这个系统函数将CString转成char*型************************/
	//获取转换所需的目标缓存大小
//	DWORD dBufSize_R = WideCharToMultiByte(CP_OEMCP, 0, ReceiveA.gRemoteDataPath, -1, NULL, 0, NULL, FALSE);
	//分配目标缓存
//	char *strFilePath_R = new char[dBufSize_R + 1]; //new运算符申请的堆的一块空间，申请完应该立即释放，否则容易造成内存泄漏
//	memset(strFilePath_R, 0, dBufSize_R);
	//转换（WideCharToMultiByte这个函数运行成功，并且cchMultiByte不为零，返回值是由 lpMultiByteStr指向的缓冲区中写入的字节数）
//	int nRet_R = WideCharToMultiByte(CP_OEMCP, 0, ReceiveA.gRemoteDataPath, -1, strFilePath_R, dBufSize_R, NULL, FALSE);
	/******测试代码
	if (nRet_R <= 0)
	{
	MessageBox(_T("转换失败\n"));
	}
	else
	{
	MessageBox(_T("转换成功\n"));
	}
	*/
//	FILE *fp_R;
//	errno_t err_R;
//	err_R = fopen_s(&fp_R, strFilePath_R, "r+"); //安全方式打开文件，成功打开返回0，未成功打开返回1
	/********测试代码
	if (err_R == 0)
	{
	MessageBox(_T("The file  was opened!"));
	}
	else
	{
	MessageBox(_T("The file  was not opened"));
	}
	*/
	//fopen()可利用fseek和ftell来获得文件的长度
//	fseek(fp_R, 0, SEEK_END);		//定位文件指针到文件末尾	成功返回0，不成功返回-1
//	fileSize1 = ftell(fp_R);			//测试：发射源文件1111.dat   filesize = 72
//	fseek(fp_R, 0, SEEK_SET);	//再定位文件指针到文件头
//	delete[]strFilePath_R; //释放，养成好习惯
//	strFilePath_R = NULL;

//	SourceFile = (int*)malloc(fileSize1*sizeof(int));//C语言申请内存空间函数
//	for (int i = 0; i < fileSize1; i++)
//	{
//		fscanf_s(fp_R, "%1u", &SourceFile[i]);		//%u：格式字符串，%1u：要输出的数向右对齐一位
//	}

//	fclose(fp_R);//C语言编程下的关闭文件

	// 代码段含义：读取本地发射文件
	/****************利用WideCharToMultiByte这个系统函数将CString转成char*型************************/
	//获取转换所需的目标缓存大小
	DWORD dBufSize = WideCharToMultiByte(CP_OEMCP, 0, SendA.gSendDataPath, -1, NULL, 0, NULL, FALSE); //测试：发射源文件1111.dat   dBufSize = 77
	//分配目标缓存
	char *strFilePath = new char[dBufSize + 1]; //new运算符申请的堆的一块空间，申请完应该立即释放，否则容易造成内存泄漏
	memset(strFilePath, 0, dBufSize);
	//转换（WideCharToMultiByte这个函数运行成功，并且cchMultiByte不为零，返回值是由 lpMultiByteStr指向的缓冲区中写入的字节数）
	int nRet = WideCharToMultiByte(CP_OEMCP, 0, SendA.gSendDataPath, -1, strFilePath, dBufSize, NULL, FALSE);

	/*测试代码 *****
	if (nRet <= 0)
	{
	MessageBox(_T("转换失败\n"));
	}
	else
	{
	MessageBox(_T("转换成功\n"));
	}
	*/
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, strFilePath, "r+"); //安全方式打开文件，成功打开返回0，未成功打开返回1
	/**********测试
	if (err == 0)
	{
	MessageBox(_T("The file  was opened!"));
	}
	else
	{
	MessageBox(_T("The file  was not opened"));
	}*/
	//fopen()可利用fseek和ftell来获得文件的长度
	int filesize;
	fseek(fp, 0, SEEK_END);		//定位文件指针到文件末尾	成功返回0，不成功返回-1
	filesize = ftell(fp);			//测试：发射源文件1111.dat   filesize = 72
	fseek(fp, 0, SEEK_SET);	//再定位文件指针到文件头
	delete[]strFilePath; //释放，养成好习惯
	strFilePath = NULL;

	temp = (int*)malloc(filesize*sizeof(int));//C语言申请内存空间函数
	for (int i = 0; i < filesize; i++)
	{
		fscanf_s(fp, "%1u", &temp[i]);		//%u：格式字符串，%1u：要输出的数向右对齐一位
	}
	//判断要发送的次数n
	if (filesize % Num_Data)
	{
		n = filesize / Num_Data + 1;
	}
	else
	{
		n = filesize / Num_Data;
	}

	//组成标准帧，不足补0
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
	for (int i = 0; i < Num_Data; i++) //为了从int型数组转CString真是累死你爹地了
	{
		str[i].Format(_T("%d"), buffer[i]);
		strDisplay += str[i];	//利用CString类型重载+=的性质
	} //数据保存到strDisplay这个数组中

	//将要发送的数据送到CStatusDisply对话框类中的发送数据编辑框
	d_sdSDlg->m_HistSendData.SetSel(d_sdSDlg->m_HistSendData.GetWindowTextLength(), -1); //获取当前编辑框字符
	d_sdSDlg->m_HistSendData.ReplaceSel(strDisplay); //替换当前文本
	//	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay);
	d_sdSDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //发射数据总比特数显示
	d_sdSDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//显示总帧数


	while (1)
	{
		if (commondstate == 0)					 //判断此时没有指令发送
		{
			messagestate = 1;						//此时发送数据
			encode(buffer);


			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
			arqarray(num_frame);					//将数据存入数组，以发送arq
			break;
		}

	}
	messagestate = 0;
	/******设置灯闪烁表示正在发送数据*****/
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
		d_sdDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //发射数据总比特数显示
		CString frame_resend;
		frame_resend.Format(_T("%d"), ResendNumber_R);
		d_sdDlg->m_ResendFrameNumEdit.SetSel(d_sdDlg->m_ResendFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
		d_sdDlg->m_ResendFrameNumEdit.ReplaceSel(frame_resend); //替换当前文本
		d_sdDlg->m_ResendFrameNumEdit.SetSel(d_sdDlg->m_ResendFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
		d_sdDlg->m_ResendFrameNumEdit.ReplaceSel(_T(",")); //替换当前文本
		while (1)
		{
		if (commondstate == 0)
		{
		messagestate = 1;
		arqsend(ResendNumber_R);					//从缓存读取重传帧
		Len_DataInProcess = Num_Data + 24 + 40 + 32;
		Sleep(1000);
		((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessage(P_Data_CC, Len_DataInProcess);
		break;
		}

		}
		messagestate = 0;
		d_sdDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, ResendNumber_R);//显示总帧数

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
		for (int i = 0; i < Num_Data; i++) //为了从int型数组转CString真是累死你爹地了
		{
			str[i].Format(_T("%d"), buffer[i]);
			strDisplay += str[i];	//利用CString类型重载+=的性质
		} //数据保存到strDisplay这个数组中

		//将要发送的数据送到CStatusDisply对话框类中的发送数据编辑框
		d_sdSDlg->m_HistSendData.SetSel(d_sdSDlg->m_HistSendData.GetWindowTextLength(), -1); //获取当前编辑框字符
		d_sdSDlg->m_HistSendData.ReplaceSel(strDisplay); //替换当前文本
		//	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay);
		d_sdSDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //发射数据总比特数显示
		d_sdSDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//显示总帧数

		while (1)
		{
			if (commondstate == 0)					 //判断此时没有指令发送
			{
				messagestate = 1;						//此时发送数据
				encode(buffer);

				//				Sleep(4000);
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
				arqarray(num_frame);					//将数据存入数组，以发送arq
				break;
			}

		}
		messagestate = 0;
		/******设置灯闪烁表示正在发送数据*****/
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

	fclose(fp);//C语言编程下的关闭文件
	free(temp); //释放指针指向的内存
	temp = NULL;//指向内存的指针设为空，防止程序后面不小心使用了它

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
	font.CreatePointFont(110, _T("微软雅黑")); //创建字体样式，传递110请求11点字体
	GetDlgItem(IDC_SIMPLEXPROCEDURES_STATIC)->SetFont(&font); //将字体传递给静态框

	m_grey = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_GREY));
	m_red = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_RED));
	//AfxGetInstanceHandle():This function allows you to retrieve (取回) the instance handle of the current application.
	//MAKEINTRESOURCE macro (宏):Converts an integer value to a resource type compatible with the resource-management functions. This macro is used in place of a string containing the name of the resource.
	/*********初始led灯为灰色**********/
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

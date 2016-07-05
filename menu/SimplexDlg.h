#pragma once
#include "resource.h"
#include "afxwin.h"
#include "ParameterSet.h"
#include "StatusDisplayDlg.h"
//void ThreadFuncS(LPVOID lpParam); //���������̺߳���
// CSimplexDlg �Ի���
UINT ThreadFuncS(LPVOID lpParam);

class CSimplexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSimplexDlg)

public:
	CSimplexDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSimplexDlg();

// �Ի�������
	enum { IDD = IDD_SIMPLEX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CStatic m_led1;
	CStatic m_led2;
	CStatic m_led3;
	CStatic m_led4;
	CStatic m_led5;
	CStatic m_led6;
	CStatic m_led7;
	CStatic m_led8;
	CStatic m_led9;

	int SetLedOff(int a);
	int StartRunSimplex(int a);
	void dangongsend();

	void SystemTime(); //��ȡϵͳʱ��
	UINT oldtickcount, newtickcount;
	HBITMAP m_grey;  // ��Ӿ������
	HBITMAP m_red;
	CFont font;

	CParameterSet *psSDlg;
	CStatusDisplayDlg * d_sdSDlg;  //��˫��״̬�·���StatusDisplay�Ի���  d = duplex
	void arqarray(int framecounter);
	void arqsend(int framecounter);

protected:
	HANDLE hThread; //�߳̾��
	DWORD ThreadID; //�߳�ID

public:

	//����״̬�µ�ϵͳ��������
	int state_inactiveS;
	int state_starthailS;
	int state_hailacquisitionS;
	int state_haildirectivesS;
	int state_hailtailS;
	int state_hailresponseS;
	int state_carrieronlyS;
	int state_acquisitionS;
	int state_simplexsonS;
	int state_lnmdendS;
	int state_simplexsendS;
	int state_terminatingtailS;

	int StopFlagS;



	virtual BOOL OnInitDialog();
	inline void endSystem();
};

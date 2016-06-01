#pragma once

#include "StatusDisplayDlg.h"

// CClientSocket ����Ŀ��

class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	CStatusDisplayDlg * ds_sdDlg;
};



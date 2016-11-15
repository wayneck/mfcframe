// mousepose.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>  
#include<windows.h>    
using namespace std; 

int _tmain(int argc, _TCHAR* argv[])
{
	POINT point;      
    unsigned long rgb;  
    HDC scr;  
    while(1)  
    {  
        if(GetAsyncKeyState(VK_F8) & 0x8000)  //����F8  
        {  
            scr=GetDC(0);                     //��ȡ��Ļ�豸����  
            GetCursorPos(&point);             //��ȡ��ǰ���λ��  
            cout<<"X="<<point.x<<" Y="<<point.y<<endl;  
            rgb=GetPixel(scr,point.x,point.y);//��ȡ��굱ǰλ�õ���ɫ  
            printf("R=%d",rgb&0xff);  
            printf(" G=%d",(rgb>>8)&0xff);  
            printf(" B=%d\n",(rgb>>16)&0xff);  
            ReleaseDC(0,scr);                 //�ͷ���Ļ�豸����  
        }  
        Sleep(200);  
    }  
    return 0;  
}


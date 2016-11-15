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
        if(GetAsyncKeyState(VK_F8) & 0x8000)  //监视F8  
        {  
            scr=GetDC(0);                     //获取屏幕设备场景  
            GetCursorPos(&point);             //获取当前鼠标位置  
            cout<<"X="<<point.x<<" Y="<<point.y<<endl;  
            rgb=GetPixel(scr,point.x,point.y);//获取鼠标当前位置的颜色  
            printf("R=%d",rgb&0xff);  
            printf(" G=%d",(rgb>>8)&0xff);  
            printf(" B=%d\n",(rgb>>16)&0xff);  
            ReleaseDC(0,scr);                 //释放屏幕设备场景  
        }  
        Sleep(200);  
    }  
    return 0;  
}


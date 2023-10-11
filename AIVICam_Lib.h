#pragma once

#ifndef _AICAM_LIB_H_
#define _AICAM_LIB_H_
#include "pch.h"
#include "AIVICam_Err.h"
#include "AIVICam_Def.h"
#include <string.h>

#ifndef AIVI_NULL
#define AIVI_NULL    0
#endif


#ifdef AIVICAM_EXPORTS
#define AIVICAM_LIB_API __declspec(dllexport)
#else
#define AIVICAM_LIB_API __declspec(dllimport)
#endif


class AIVICAM_LIB_API AIVICam_Lib
{
public:
    AIVICam_Lib();
    ~AIVICam_Lib();

    int     GetCameraList(AIVI_DEVICE_INFO_LIST* pDeviceList);
    int     CameraInitialize(int Index);
    int     CameraClose();
    bool    CameraConnectionCheck();
    
    int     RegisterImageCallBack(void(__stdcall* cbOutput)(unsigned char* pData, AIVI_FRAME_OUT_INFO* pFrameInfo, void* pUser), void* pUser);
    int     StartGrabbing();
    int     StopGrabbing();
    int     GetImageBuffer(AIVI_FRAME_OUT* pFrame, int nMsec);
    int     FreeImageBuffer(AIVI_FRAME_OUT* pFrame);

    int     GetWdithHeight(int* pWidth, int* pHeight);
    int     GetPixelFormat(MvGvspPixelType* pPixelFormat);

private:
    void(__stdcall* originalCallback)(unsigned char*, AIVI_FRAME_OUT_INFO*, void*);

    void*       m_hAIVICamHandle;
    int			m_nValidCamNum;
};

extern "C" {
    AIVICAM_LIB_API AIVICam_Lib* CreateCamera();
    AIVICAM_LIB_API void DestroyCamera(AIVICam_Lib* camera);    
}


#endif//_AICAM_LIB_H_
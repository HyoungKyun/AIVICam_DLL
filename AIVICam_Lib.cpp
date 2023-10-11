#include "pch.h"
#include "AIVICam_Lib.h"
#include "CamFunction.h"

static MV_CC_DEVICE_INFO_LIST	g_stDevList;

AIVICam_Lib::AIVICam_Lib() {
    m_hAIVICamHandle = AIVI_NULL;
    m_nValidCamNum = 0;
}

AIVICam_Lib::~AIVICam_Lib() {
    if (m_hAIVICamHandle)
    {
        MV_CC_DestroyHandle(m_hAIVICamHandle);
        m_hAIVICamHandle = AIVI_NULL;
    }
}

int AIVICam_Lib::GetCameraList(AIVI_DEVICE_INFO_LIST* pDeviceList)
{
    memset((void*)&g_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    m_nValidCamNum = 0;
    int nRet = EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &g_stDevList);
    if (MV_OK != nRet || g_stDevList.nDeviceNum == 0)
    {        
        return AIVI_ERR_NODEVICE;
    }

	for (unsigned int i = 0; i < MAX_CAM_NUM; i++)
	{
		if (i < g_stDevList.nDeviceNum)
		{        
            pDeviceList->DeviceInfo[i].nMacAddrHigh = g_stDevList.pDeviceInfo[i]->nMacAddrHigh;
            pDeviceList->DeviceInfo[i].nMacAddrLow = g_stDevList.pDeviceInfo[i]->nMacAddrLow;
            pDeviceList->DeviceInfo[i].nMajorVer = g_stDevList.pDeviceInfo[i]->nMajorVer;
            pDeviceList->DeviceInfo[i].nMinorVer = g_stDevList.pDeviceInfo[i]->nMinorVer;
            pDeviceList->DeviceInfo[i].nTLayerType = g_stDevList.pDeviceInfo[i]->nTLayerType;
            memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chDeviceGUID, (void*)g_stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chDeviceGUID, sizeof(AIVI_USB3_DEVICE_INFO));
           /* memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chDeviceGUID, (void*) stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chDeviceGUID, 64);
            memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chDeviceVersion, (void*)stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chDeviceVersion, 64);
            memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chFamilyName, (void*)stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chFamilyName, 64);
            memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chManufacturerName, (void*)stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chManufacturerName, 64);
            memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chModelName, (void*)stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chModelName, 64);
            memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chSerialNumber, (void*)stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chSerialNumber, 64);
            memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chUserDefinedName, (void*)stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chUserDefinedName, 64);
            memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chVendorName, (void*)stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chVendorName, 64);*/
            m_nValidCamNum++;
		}		
	}
    pDeviceList->nDeviceNum = m_nValidCamNum;
    return AIVI_OK;
}

int AIVICam_Lib::CameraInitialize(int Index)
{
    MV_CC_DEVICE_INFO* pstDeviceInfo;

    pstDeviceInfo = g_stDevList.pDeviceInfo[Index];
    if (AIVI_NULL == pstDeviceInfo)
    {
        return AIVI_ERR_PARAMETER;
    }

    if (m_hAIVICamHandle)
    {
        return AIVI_ERR_CALLORDER;
    }

    int nRet = MV_CC_CreateHandle(&m_hAIVICamHandle, pstDeviceInfo);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    nRet = MV_CC_OpenDevice(m_hAIVICamHandle);
    if (AIVI_OK != nRet)
    {
        MV_CC_DestroyHandle(m_hAIVICamHandle);
        m_hAIVICamHandle = AIVI_NULL;
        nRet = AIVI_ERR_INITIALFAIL;
    }

    return nRet;    
}

int AIVICam_Lib::CameraClose()
{
    if (AIVI_NULL == m_hAIVICamHandle)
    {
        return AIVI_ERR_HANDLE;
    }

    MV_CC_CloseDevice(m_hAIVICamHandle);

    int nRet = MV_CC_DestroyHandle(m_hAIVICamHandle);
    m_hAIVICamHandle = AIVI_NULL;

    if (nRet != AIVI_OK)
    {
        nRet = AIVI_ERR_CLOSE;
    }
    return nRet;
}

bool AIVICam_Lib::CameraConnectionCheck()
{
    return MV_CC_IsDeviceConnected(m_hAIVICamHandle);
}


void __stdcall WrapperCallback(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfoEx, void* pUser) {
    // pUser를 원래의 콜백 함수 포인터로 캐스팅
    auto originalCb = reinterpret_cast<void(__stdcall*)(unsigned char*, AIVI_FRAME_OUT_INFO*, void*)>(pUser);

    AIVI_FRAME_OUT_INFO* pFrameInfo = reinterpret_cast<AIVI_FRAME_OUT_INFO*>(pFrameInfoEx);
    originalCb(pData, pFrameInfo, pUser);  
}

int AIVICam_Lib::RegisterImageCallBack(void(__stdcall* cbOutput)(unsigned char* pData, AIVI_FRAME_OUT_INFO* pFrameInfo, void* pUser), void* pUser) {
    return MV_CC_RegisterImageCallBackEx(m_hAIVICamHandle, WrapperCallback, reinterpret_cast<void*>(cbOutput));  
}

int AIVICam_Lib::StartGrabbing()
{
    int nRet;
    nRet = MV_CC_StartGrabbing(m_hAIVICamHandle);
    if (nRet != AIVI_OK)
    {
        nRet = AIVI_ERR_GRABSTART;
    }
    return nRet;
}

int AIVICam_Lib::StopGrabbing()
{
    int nRet;
    nRet = MV_CC_StopGrabbing(m_hAIVICamHandle);
    if (nRet != AIVI_OK)
    {
        nRet = AIVI_ERR_GRABSTOP;
    }
    return nRet;
}

int AIVICam_Lib::GetImageBuffer(AIVI_FRAME_OUT* pFrame, int nMsec)
{
    return MV_CC_GetImageBuffer(m_hAIVICamHandle, reinterpret_cast<MV_FRAME_OUT*>(pFrame), nMsec);
}

int AIVICam_Lib::FreeImageBuffer(AIVI_FRAME_OUT* pFrame)
{
    return MV_CC_FreeImageBuffer(m_hAIVICamHandle, reinterpret_cast<MV_FRAME_OUT*>(pFrame));
}

int AIVICam_Lib::GetWdithHeight(int* pWidth, int* pHeight)
{
    int nRet;
    MVCC_INTVALUE_EX value;
    nRet = GetIntValue("Width", &value);
    if(nRet == AIVI_OK )
    {
        *pWidth = value.nCurValue;
    }
    else
    {
        return nRet;
    }

    nRet = GetIntValue("Height", &value);
    if (nRet == AIVI_OK)
    {
        *pHeight = value.nCurValue;
    }
    return nRet;    
}


int AIVICam_Lib::GetPixelFormat(MvGvspPixelType* pPixelFormat)
{
    int nRet;
    MVCC_ENUMVALUE value;
    nRet = GetEnumValue("PixelFormat", &value);
    if (nRet == AIVI_OK)
    {
        *pPixelFormat = (MvGvspPixelType)value.nCurValue;
    }
    return nRet;
}

extern "C" {
    __declspec(dllexport) AIVICam_Lib* CreateCamera() {
        return new AIVICam_Lib();
    }

    __declspec(dllexport) void DestroyCamera(AIVICam_Lib* camera) {
        delete camera;
    }   
}
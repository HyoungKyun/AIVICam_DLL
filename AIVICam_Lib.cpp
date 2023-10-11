#include "pch.h"
#include "AIVICam_Lib.h"
#include "CamFunction.h"

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
    MV_CC_DEVICE_INFO_LIST	stDevList;
    m_nValidCamNum = 0;
    int nRet = EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDevList);
    if (MV_OK != nRet || stDevList.nDeviceNum == 0)
    {        
        return AIVICAM_NODEVICE;
    }

	for (unsigned int i = 0; i < MAX_CAM_NUM; i++)
	{
		if (i < stDevList.nDeviceNum)
		{        
            pDeviceList->DeviceInfo[i].nMacAddrHigh = stDevList.pDeviceInfo[i]->nMacAddrHigh;
            pDeviceList->DeviceInfo[i].nMacAddrLow = stDevList.pDeviceInfo[i]->nMacAddrLow;
            pDeviceList->DeviceInfo[i].nMajorVer = stDevList.pDeviceInfo[i]->nMajorVer;
            pDeviceList->DeviceInfo[i].nMinorVer = stDevList.pDeviceInfo[i]->nMinorVer;
            pDeviceList->DeviceInfo[i].nTLayerType = stDevList.pDeviceInfo[i]->nTLayerType;
            memcpy((void*)pDeviceList->DeviceInfo[i].stUsb3VInfo.chDeviceGUID, (void*)stDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chDeviceGUID, sizeof(AIVI_USB3_DEVICE_INFO));
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
    return AIVICAM_OK;
}

int AIVICam_Lib::CameraInitialize(int Index)
{

}


extern "C" {
    __declspec(dllexport) AIVICam_Lib* CreateCamera() {
        return new AIVICam_Lib();
    }

    __declspec(dllexport) void DestroyCamera(AIVICam_Lib* camera) {
        delete camera;
    }   
}
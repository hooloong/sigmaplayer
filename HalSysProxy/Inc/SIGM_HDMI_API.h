#ifndef SIGM_HDMI_API_H
#define SIGM_HDMI_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "SIGM_Types.h"
#include "SIGM_HDMI_Types.h"

Error_Type_e HalSys_HDMI_Initialize(void);

Error_Type_e HalSys_HDMI_Deinit(void);

Error_Type_e HalSys_HDMI_Open(HDMI_Config_t* ptConfig, sigma_handle_t* ptInst);

Error_Type_e HalSys_HDMI_Start(sigma_handle_t ptInst, HDMI_PortConfig_t* ptConfig, sigma_handle_t* ptPort);

Error_Type_e HalSys_HDMI_Stop(sigma_handle_t ptPort);

Error_Type_e HalSys_HDMI_Close(sigma_handle_t ptInst);

//Error_Type_e HalSys_HDMI_SetParameter(sigma_handle_t ptPort, SIGM_PARAMETER_INDEX eParameter, datatype_ptr pData);

//Error_Type_e HalSys_HDMI_GetParameter(sigma_handle_t ptPort, SIGM_PARAMETER_INDEX eParameter, datatype_ptr pData);

//Error_Type_e HalSys_HDMI_InstallCallback(CallBackFuncsInfo_t* const cbInfo, sigm_callback_t pInfoRoutine, void* pUserParam);

//Error_Type_e HalSys_HDMI_UnInstallCallback(CallBackFuncsInfo_t* ptCallbackInfo);

#ifdef __cplusplus
}
#endif

#endif

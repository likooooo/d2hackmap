
#include "stdafx.h"


char* relayDlls[] = {"D2CLIENT.DLL", "D2COMMON.DLL", "D2GFX.DLL", "D2WIN.DLL", "D2LANG.DLL", "D2CMP.DLL", "D2MULTI.DLL", "BNCLIENT.DLL", "D2NET.DLL", "STORM.DLL", "FOG.DLL", "D2GAME.DLL","D2LAUNCH.dll","D2MCPCLIENT.dll"};
HMODULE d2hackmapHandle;
char  szPluginPath[MAX_PATH];


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		d2hackmapHandle = hModule;
		DisableThreadLibraryCalls(d2hackmapHandle);
		GetModuleFileNameA(d2hackmapHandle, szPluginPath, MAX_PATH);
		*(strrchr( szPluginPath, '\\' ) + 1)='\0';
		return Install();
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		UnLoadExtInfo();
		if (!lpReserved)
			Uninstall();
		break;
	}
	return TRUE;
}
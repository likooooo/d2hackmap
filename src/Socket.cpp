#include "stdafx.h"

#ifdef MODULE_SOCKET

RET_VOID_NAKE FixSocketTimeOut_ASM()
{
		__asm {
		mov eax , [dwSocketTimeOut]
		mov [esp+0x30] ,eax
		ret;
	}
}

RET_VOID_NAKE FixSocketErrRet_ASM()
{
		__asm {
		mov ebx , eax
		cmp eax, esi
		jle oldje
		mov ecx,[p_D2UnkNetFlag]
		mov ecx,[ecx]
		ret
oldje:
		add dword ptr [esp], 0x14
		ret;
	}
}




#endif
#include "stdafx.h"

#ifdef MODULE_ULCPATH


RET_VOID_NAKE ULCPatch_ASM()
{
		__asm {
			cmp [tULCMask.isOn],0
			je			org_code
			movzx		ecx,byte ptr [edi+6]
			cmp			ecx,197
			jne			org_code
			mov			byte ptr [edi+6],0	; modify the firestorm effect to normal attack effect
org_code:
			movzx   edx, byte ptr [edi+8]
			xor     ecx, ecx
			ret;
	}
}



#endif
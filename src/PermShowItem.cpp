#include "stdafx.h"

#ifdef MODULE_PERMSHOWITEM


BOOL PermShowItemsPatch1()
{
	//ALT �����Ƿ���Ч
	if ( tLockAltToggle.isOn || tPermShowItems.isOn || D2CheckUiStatus(UIVAR_SHOWITEMS)) return true ;
	return false;
}

BOOL PermShowItemsPatch2() {
	//�Ƿ���ʾ������false����ʾ true ��ʾ
	if( tLockAltToggle.isOn ) return false;

	if ( D2CheckUiStatus(UIVAR_SHOWITEMS) ){
		if ( tPermShowItems.isOn && tPermShowItems.value==3)return true;
		return false;
	}else{
		return tPermShowItems.isOn?true:false;
	}

}

BOOL PermShowItemsPatch3() {
	//�Ƿ���ʾ��Ʒ�� true ��ʾ  false ����ʾ
	if( tLockAltToggle.isOn ) return true;

	if ( D2CheckUiStatus(UIVAR_SHOWITEMS) ){
		if ( tPermShowItems.isOn==FALSE) return true ;
		return tPermShowItems.isOn && tPermShowItems.value==1 ;
	}else{
		return tPermShowItems.isOn?true:false;
	}

}

RET_VOID_NAKE PermShowItemsPatch1_ASM()
{
	__asm {
		call PermShowItemsPatch1
		test eax,eax
		ret
	}
}

RET_VOID_NAKE PermShowItemsPatch2_ASM()
{
	__asm {
		call PermShowItemsPatch2
		test eax,eax
		je orgcode
		ret
orgcode:
		mov eax, dword ptr [esp+0x20]
		test eax,eax
		ret
	}
}


RET_VOID_NAKE PermShowItemsPatch3_ASM()
{
	__asm {
		push ebp
		push esi
		call PermShowItemsPatch3
		test eax,eax
		pop esi
		pop ebp
		jz 	outcode
		cmp ebp, 0x20
		jge outcode
		ret
outcode:
		add dword ptr [esp], 0x38A  //to 6FB0DD89
		ret
	}
}

RET_VOID_NAKE PermShowItemsPatch4_ASM()
{
	__asm {
		push eax
		call PermShowItemsPatch1
		mov ecx, eax
		pop eax
		ret
	}
}



#endif
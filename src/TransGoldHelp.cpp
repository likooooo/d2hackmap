#include "stdafx.h"

#ifdef MODULE_TRANSGOLDHELP
int __fastcall SetGoldPatch(int iType){

	int gold = *p_D2GoldInTranBox;

	if ( iType==4 && gold >0){//������������ת�ƽ�Ǯ���ҽ�����0
		//�����Ƿ񳬹���ת�Ƶ����ֵ�����������ȡ���ֵ
		int goldstash = D2GetUnitStat(PLAYER, STAT_GOLD ,0);
		int lvl = D2GetUnitStat(PLAYER, STAT_LEVEL ,0);
		int maxgold = lvl*10000 - goldstash ;
		if ( gold>maxgold ) gold = maxgold ;
		*p_D2GoldInTranBox = gold;
	}
	return gold;
}

RET_VOID_NAKE SetGoldPatch_ASM()
{
	__asm{
		mov ecx ,eax
		call SetGoldPatch
		mov edx ,eax
		ret
	}
}

RET_VOID_NAKE SetDefaultGoldPatch_ASM()
{
	__asm{
		
		cmp ebx , 4
		je nojmp
		cmp ebx , 6
		je nojmp
		add dword ptr [esp] , 0x30
nojmp:
		ret
	}
}


#endif
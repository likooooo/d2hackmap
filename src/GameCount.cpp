#include "stdafx.h"

#ifdef MODULE_GAMECOUNT

//����ScreenHook.cpp�����
void ShowGameCount(){

	int xpos = SCREENSIZE.x/2 + 70;
	int ypos = SCREENSIZE.y - 50;
	DWORD dwOldFone = D2SetTextFont(1);

	if ( tGetHitCount.isOn ){	
		wchar_t wszTemp[512];
		DWORD dwColor = tGetHitCount.value-1 ;
		wcscpy( wszTemp , L"GetHits:" );
		D2DrawText(wszTemp, xpos,  ypos, dwColor, 0);

		wsprintfW(wszTemp ,L"%d" , dwGetHits );
		D2DrawText(wszTemp, xpos+65,  ypos, dwColor, 0);

		wsprintfW(wszTemp ,L"Total: %d" , dwGetHitSum );
		D2DrawText(wszTemp, xpos+105,  ypos, dwColor , 0);
		ypos = ypos-15;
	}

	if ( tKillCount.isOn ){	
		wchar_t wszTemp[512];
		DWORD dwColor = tKillCount.value-1 ;
		wcscpy( wszTemp , L"Kills:" );
		D2DrawText(wszTemp, xpos+20,  ypos, dwColor, 0);

		wsprintfW(wszTemp ,L"%d" , dwGameKills );
		D2DrawText(wszTemp, xpos+65,  ypos, dwColor, 0);

		wsprintfW(wszTemp ,L"Total: %d" , dwKillSum );
		D2DrawText(wszTemp, xpos+105,  ypos, dwColor, 0);
	}

	D2SetTextFont(dwOldFone);
}

void __fastcall SetKills( DWORD newKills ){

	if ( (int)newKills > (int)dwLastKills ) {
		dwKillSum++;
		dwGameKills++;
	}
	dwLastKills = newKills;

}
RET_VOID_NAKE KillCountPatch_ASM()
{
	//����һ�λ����һ��ɱ���������Կ��ܱ为��
	//��¼���ϴ�ֵ�����С���ϴΣ���Ϊ����~
	__asm{

		push esi
		push eax
		
		movsx ecx, si
		call SetKills

		pop eax
		pop esi
		test esi,0x8000
		ret 

	}
}

RET_VOID_NAKE UnitModeChangePatch_ASM()
{
	__asm{
		cmp edi , 4
		jne org

		mov edx, dword ptr [esi]
		cmp edx, 0
		jne org
		
		cmp [dwOrgMode] ,0
		je gocount
		mov [dwOrgMode] ,0
		jmp org
gocount:
		mov edx , dword ptr [esi+0x10] //�������������Σ���ս��ģʽ����,��¼����һ�ε��õ�ԭֵ������ȫ��ѭ��������
		mov [dwOrgMode] , edx 
		add [dwGetHits] , 1
		add [dwGetHitSum] , 1
org:
		mov edx, dword ptr [esi+0xC4]
		ret 
	}
}



#endif
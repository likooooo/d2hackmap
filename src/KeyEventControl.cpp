#include "stdafx.h"

//�����¼�

extern ToggleVar *tKeyEvent[100];
extern int nKeyCount;

void __fastcall KeydownPatch(BYTE keycode, BYTE repeat)
{
	//printMsg(" keycode == %x" ,keycode);
	if ((keycode == (BYTE)-1) || !keycode) return;	
	
	#ifdef MODULE_SCROLLLOCK
		
	if (keycode == VK_LEFT) SetScrollMapPos(-1, 0);
	if (keycode == VK_RIGHT) SetScrollMapPos(+1, 0);
	if (keycode == VK_UP) SetScrollMapPos(0, -1);
	if (keycode == VK_DOWN) SetScrollMapPos(0, +1);
	if (tDiagonalScroll.isOn) {
		if (keycode == VK_HOME) SetScrollMapPos(-1, -1);
		if (keycode == VK_END) SetScrollMapPos(-1, +1);
		if (keycode == VK_PRIOR) SetScrollMapPos(+1, -1);
		if (keycode == VK_NEXT) SetScrollMapPos(+1, +1);
	}

	#endif
	if (repeat) return;

	wchar_t wszbuf[512];
	memset(wszbuf , 0  , sizeof(wszbuf));
	wszbuf[0] = L'\0';

	for(int i=0;i<nKeyCount;i++){
		ToggleVar *tgKey = tKeyEvent[i];
		if( keycode==tgKey->key ){
			if(tgKey->type==1){

				tgKey->isOn = !tgKey->isOn;
				if (tgKey->funcVoid) (tgKey->funcVoid)();
				if (tgKey->desc){

					D2ShowPartyMessage( wsprintfW2(wszbuf, "<Hackmap>: %s %s.", tgKey->desc, tgKey->isOn ? "on" : "off" ) ,   0 );

				}

			}else if(tgKey->type==2){

				if (tgKey->funcVoid) (tgKey->funcVoid)();

			}else if(tgKey->type==3){

				if (tgKey->funcParam) (tgKey->funcParam)(tgKey->param);

			}
		}
	}
}



RET_VOID_NAKE KeydownPatch_ASM()
{
	__asm {
//edi = ptr to (hwnd, msg, wparam, lparam)
		mov cl,[edi+0x08] //nVirtKey (wparam)
		mov dl,[edi+0x0c+3] //lKeyData (lparam)
		and dl,0x40 //bit 30 of lKeyData (lparam)
		call KeydownPatch
//original code
		test byte ptr [edi+0x0c+3],0x40 //bit 30 of lKeyData (lparam)
		ret
	}
}

//�����ж��Ƿ񳤰�����
RET_VOID_NAKE KeyupPatch_ASM()
{
	// edi = ptr to (hwnd, msg, wparam, lparam)
	//esi = keycode
	__asm {
		cmp esi , [dwKeyDown]
		jne oldcode
		mov [fKeyRepeat],0
//original code
oldcode:
		movzx eax, word ptr [ecx+0x04]
		cmp eax, esi
		ret
	}
}


RET_VOID_NAKE MButtonDownPatch_ASM()
{
	__asm {
//[esp+08] = ptr to (hwnd, msg, wparam, lparam)
//���ﲶ�񵽵��м���Ϣ��0x10����Shift��ͻ��ǿ����0x04
//���ﲻ����ְ�ס��������Ϣ�����Բ�����ԭ��Ϣ�ṹ��
		mov cl,0x04
		mov dl,0
		call KeydownPatch
//original code
		mov eax ,[p_D2MButton]
		mov eax ,[eax]
		ret
	}
}






#include "stdafx.h"

#ifdef MODULE_QUICKSWAPITEM


void  MoveItem(D2MSG *pMsg ){
	
	static InventoryType invTypes[] = {   //left��bottom�Ѿ�ƫ���˸���һ���С
		{0, 430, 325, 10, 4, 29, 29}, // Inventory
		{4, 165, 152, 6, 8, 29, 29}, // Stash
		{3, 220, 220, 3, 4, 29, 29}, // Cube
		{4, 165, 345, 6, 4, 29, 29}, // Stash_Classic
		{2, 110, 325, 10, 4, 29, 29}, // Trade 1 for others trade
	};
	
	UnitAny *pItem = PLAYER->pInventory->pCursorItem;

	if (!pItem) return ;  //����û����
	
	int invtype = 0;
	if ( D2CheckUiStatus(UIVAR_STASH) ) {

		if ( EXPANSION ) invtype = 1; 
		else invtype = 3; //��������

	} else if ( D2CheckUiStatus(UIVAR_CUBE) ){

		invtype = 2;

	} else if ( D2CheckUiStatus(UIVAR_PPLTRADE) ) {

		invtype = 4; //���״���

	}

	if ( invtype>0 ) {//��߿�

		InventoryType *pInvType = (pMsg->xpos < SCREENSIZE.x/2) ? &invTypes[0] : &invTypes[invtype];

		if (pInvType) {

			DWORD dwBoxType = D2GetBoxType(PLAYER, pInvType->invType, EXPANSION);
			for (int x = 0; x < pInvType->nGridXs; ++x) {
				for (int y = 0; y < pInvType->nGridYs; ++y) {

					int xpos = pInvType->left + x*pInvType->nGridWidth;
					int ypos = pInvType->bottom + y*pInvType->nGridHeight;
					int gridcount = 0;
					int itemcount = 0;
					SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, MAKELONG(xpos, ypos));
					D2CheckInvLocation(PLAYER->pInventory, pItem, *p_D2CursorInvGridX, *p_D2CursorInvGridY, dwBoxType, &gridcount, &itemcount, pInvType->invType);
					if ( itemcount==0 ) {
						SendMessage(pMsg->hwnd, WM_LBUTTONDOWN, pMsg->wParam, MAKELONG(xpos, ypos));
						SendMessage(pMsg->hwnd, WM_LBUTTONUP, pMsg->wParam, MAKELONG(xpos, ypos));
						x = y = 1000; // break;
					}

				}

			}
	
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, pMsg->lParam);
		}

	}else if (tQuickDropToggle.isOn){
		
		if ( D2CheckUiStatus(UIVAR_INVENTORY) && 
			!D2CheckUiStatus(UIVAR_STATS) && 
			!D2CheckUiStatus(UIVAR_QUEST) && 
			!D2CheckUiStatus(UIVAR_PARTY) &&
			!D2CheckUiStatus(UIVAR_PET) &&
			!D2CheckUiStatus(UIVAR_QUESTSCROLL) ){

			int xpos = 230;
			int ypos = 200;
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, MAKELONG(xpos, ypos));
			SendMessage(pMsg->hwnd, WM_LBUTTONDOWN, pMsg->wParam, MAKELONG(xpos, ypos));
			SendMessage(pMsg->hwnd, WM_LBUTTONUP, pMsg->wParam, MAKELONG(xpos, ypos));
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, pMsg->lParam);

		}

	}

}

void __stdcall RButtonUpHandlerPatch(D2MSG *pMsg)
{

	if( fInGame==FALSE )return;

	if (tRightClickSwap.isOn && pMsg->dwMessage == WM_RBUTTONUP) {
		
		MoveItem( pMsg );

	}
	StopShake();
}


RET_VOID_NAKE RButtonUpHandlerPatch_ASM()
{
	__asm {
		push [esp+8];
		call RButtonUpHandlerPatch;
//oldcode:
		mov eax, p_D2InGame;
		mov eax, [eax];
		ret;
	}
}

RET_VOID_NAKE RButtonInTradePatch_ASM()
{
	__asm {
		push [esp+4];
		call RButtonUpHandlerPatch
		jmp D2Storm511
	}
}



//Ctrl+�������
//������ģʽ��������Ҫ�ȴ����ݰ����ز���������Ʒ��������ButtonUp�в�һ���ܴ����
//��������LButtonUp��ʼ��ʱ��������Ϸѭ���ж���ֱ���������


static int nClickStatus = 0;    //�Ƿ�Ctrl+����¼�
static BOOL fSwapProc = FALSE;  //�Ƿ��ѿ�ʼ����
static BOOL fSwapProcLoop = FALSE; //�Ƿ񽻸���Ϸѭ������
static D2MSG unDealMsg; //LButtonUp��Ϣ�ṹ����
static DWORD dwSwapTimer;//��ʱ��
void DealCtrlClick(){

	if ( fSwapProcLoop == TRUE ){
		
		if ( GetTickCount()-dwSwapTimer> PING +10 ) {
			UnitAny *pItem = PLAYER->pInventory->pCursorItem;
			if ( pItem){
				MoveItem( &unDealMsg );
				fSwapProc = FALSE;
				nClickStatus = 0;
				fSwapProcLoop = FALSE;
				dwSwapTimer = GetTickCount();
			}
		}
	}

}


RET_VOID_NAKE CtrlClickHandlerPatch_ASM()
{
	__asm {
		je noNpc 
		ret//���NPC����������
noNpc:
		cmp [tCtrlClickSwap.isOn] , 0
		jz orgjz

		cmp [fSwapProc] , 1  //������
		je orgjz

		mov [nClickStatus],1
		add dword ptr [esp] ,0x12D //ǿ��������Ʒ
		xor eax ,eax
		ret
orgjz:	
		add dword ptr [esp] ,0x141
		ret
	}
}


void __stdcall LButtonUpHandlerPatch(D2MSG *pMsg)
{
	
	if ( fSwapProc ) return ;
	if ( nClickStatus==0 ) return ;

	fSwapProc = TRUE;
	fSwapProcLoop = FALSE;
	
	dwSwapTimer = GetTickCount();
	fSwapProcLoop = TRUE;
	unDealMsg = *pMsg;

	/*UnitAny *pItem = PLAYER->pInventory->pCursorItem;
	if ( pItem){
		Sleep(150);
		MoveItem( pMsg );
	}else{
		fSwapProcLoop = TRUE;
		unDealMsg = *pMsg;
		return;
	}*/

	//fSwapProc = FALSE;
	//nClickStatus = 0;

}
RET_VOID_NAKE LButtonUpHandlerPatch_ASM()
{
	//esp+4  = pMsg
	__asm {
		push ebp
		push ebx

		push [esp+0xC]
		call D2Storm511    //ԭʼ���ã��ȵ��ý�LButtonUp��Ϣ�����

		push [esp+0xC]
		call LButtonUpHandlerPatch

		pop ebx
		pop ebp
		ret 4
	}
}


#endif
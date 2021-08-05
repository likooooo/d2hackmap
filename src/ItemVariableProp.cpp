#include "stdafx.h"


#ifdef MODULE_ITEMVARIABLEPROP

//������Χ��ʾ
/*

��һ������ʱ���ȳ�ʼ��������ɫ���������֮������Ա�
����ĳЩ��������Ҫ�������Ͳ������

short aItemPropInfo[3][500][30][4];
��һλ 0 ���� 1 ��ɫ 2 ���֮��
�ڶ�λ �����Ͷ�Ӧ��� set 128�� unique 397��  runeword 169��
����λ װ������  ��359������ , ֻ����ɱ��
����λ 0 ��¼statnoֵ 1 ��¼paramֵ 2 ��¼��Сֵ 3 ��¼���ֵ
(3*500*20*4*4)/1024 = 469K ;


���ڱ����д������ܣ�����ʱ�������ܣ�gethit��������3�����ԣ�����ȼ��ɱ䣬�㷨�Ƚ��鷳��ֱ��if elseά����

*/
/*
TEST
wchar_t wszTemp[512];
wsprintfW(wszTemp, L"[%d] [%d] [%d] [%d]" , mPropId ,  pItemProp[i].Param , pItemProp[i].MinVal,pItemProp[i].MaxVal);
D2ShowGameMessage(wszTemp,0);

*/


static int aItemPropInfo[3][500][20][4];
static int nStatCount = 0 ;

void SetPropInfo( int itemType , int index ,int propMax , ItemProp *pItemProp){

	if (!pItemProp)return;
	int nCount = 0 ;
	int (*pStat)[4] = &aItemPropInfo[itemType][index][0];

	for ( int i=0 ; i<propMax ; i++){//1

		int mPropId = pItemProp[i].PropId ;

		if ( mPropId>=0 && pItemProp[i].MinVal!= pItemProp[i].MaxVal ){//2

			PropertiesTxt *pPropertiesTxt = D2GetPropertiesTxt( mPropId );
			if ( !pPropertiesTxt ) continue;

			short *pStatNo = pPropertiesTxt->wStatNo;
			
			if ( mPropId==267 && pPropertiesTxt->nFunc[0]==36 ){
				continue;
			}
			//�������Բ��
			
			if ( pPropertiesTxt->nFunc[0]==21 ){
				//�ӽ�ɫ����
				pStat[nCount][0] = 83;
				pStat[nCount][1] = pPropertiesTxt->wVal[0];
				pStat[nCount][2] = pItemProp[i].MinVal ;
				pStat[nCount][3] = pItemProp[i].MaxVal ;
				nCount++;
				continue;
			}

			if ( mPropId == 29 ){
				//��ǿ�˺�
				pStat[nCount][0] = 17;
				pStat[nCount][1] = pItemProp[i].Param;
				pStat[nCount][2] = pItemProp[i].MinVal;
				pStat[nCount][3] = pItemProp[i].MaxVal;
				nCount++;
				pStat[nCount][0] = 18;
				pStat[nCount][1] = pItemProp[i].Param;
				pStat[nCount][2] = pItemProp[i].MinVal;
				pStat[nCount][3] = pItemProp[i].MaxVal;
				nCount++;
				continue;
			}
			//�������ԣ�ɾ��
			if ( mPropId>=134 && mPropId<=140)continue;  //���������˺�������
			if ( mPropId==248 )continue;  //������������˺�

			if ( mPropId <= 128 &&  mPropId >=126){
				//�����ʱ��������ʱ������ʱ��������

				if (pItemProp[i].MaxVal==0){

					int statno = -1 ;
					int min = -1 ;
					int max = -1;

					if ( mPropId == 126 ){
						if ( index==254 ) {
							statno = 195;
							min = 16;
							max = 20;
						}else if ( index==259 ) {
							statno = 195;
							min = 14;
							max = 20;
						}
					}
					if ( mPropId == 127 ){
						if ( index==136 ) {
							statno = 198;
							min = 13;
							max = 20;
						}
					}

					if ( mPropId == 128 ){
						if ( index==264 ) {
							statno = -1; //��Ϊ����Ҫ��̫�ߣ����ʵ�ʱ���˲��ɱ�
							min = 20;
							max = 20;
						}else if ( index==270 ) {
							statno = 201;
							min = 13;
							max = 19;
						}else if ( index==245 ) {
							statno = 201;
							min = 7;
							max = 19;
						}else if ( index==137 ) {
							statno = 201;
							min = 12;
							max = 20;
						}
					}
					if ( statno>=0 ){
						pStat[nCount][0] = statno;
						pStat[nCount][1] = pItemProp[i].Param ;
						pStat[nCount][2] = min ;
						pStat[nCount][3] = max ;
						nCount++;
					}

				}
				continue;
			}
				
			for( int j=0 ; j< 7; j++ ){//3  �����Բ��
		
				if ( pStatNo[j]>=0 ){//4

					pStat[nCount][0] = pStatNo[j];
					pStat[nCount][1] = pItemProp[i].Param;
					pStat[nCount][2] = pItemProp[i].MinVal ;
					pStat[nCount][3] = pItemProp[i].MaxVal ;
					
					nCount++;
				}//4

			}//3

		}//2
	}//1
	
	if ( nCount> nStatCount) nStatCount = nCount;

}

wchar_t *GetStatRange( wchar_t *wszStr , DWORD dwStatId , DWORD wParam = 0) {

	
	static BOOL fItemStatInit = FALSE;

	if ( fItemStatInit == FALSE ){

		memset(aItemPropInfo,	-1	,	sizeof(aItemPropInfo));
		nStatCount = 0 ;
		
		//����
		for ( int i =0  ; i < 500 ; i++ ){
			UniqueItemTxt *pUniqueTxt = D2GetUniqueItemTxt(i);
			if (!pUniqueTxt)break;
			SetPropInfo( 0 , i , 12 , pUniqueTxt->Prop );
		}
		
		//��ɫ
		for ( int i =0  ; i < 200 ; i++ ){
			SetItemTxt *pSetTxt = D2GetSetItemTxt(i);
			if (!pSetTxt)break;
			SetPropInfo( 1 , i , 9 , pSetTxt->Prop );
		}

		//���֮��
		for ( int i =0  ; i < 169 ; i++ ){
			RuneWordTxt *pRuneWordTxt = D2GetRuneWordTxt(i);
			if (!pRuneWordTxt)break;
			SetPropInfo( 2 , i , 7 ,pRuneWordTxt->Prop );
		}
		fItemStatInit = TRUE;
	}
	
	UnitAny *pUnit = VIEWITEMUNIT ;
	if (pUnit){
		
		DWORD dwQuality = pUnit->pItemData->dwQuality;
		int idx = -1;
		int fileindex = -1 ;
		if ( dwQuality==ITEM_QUALITY_UNIQUE ) {
			idx = 0 ;
			fileindex = D2GetItemFileIndex(pUnit);
		}else if (  dwQuality==ITEM_QUALITY_SET ){
			idx = 1 ;
			fileindex = D2GetItemFileIndex(pUnit);
		}else if ( D2CheckItemFlag(pUnit, ITEMFLAG_RUNEWORD, 0, "?") ){
			idx = 2 ;
			fileindex = D2GetRuneWordTxtIndex( pUnit->pItemData->wMagicPrefix[0] );
		}

		if ( idx>=0 && fileindex>=0 ){

			int (*pStat)[4] = &aItemPropInfo[idx][fileindex][0];
			for ( int i=0 ; i<nStatCount ; i++){

				if ( pStat[i][0]<0 ) break;
				if ( pStat[i][0]==dwStatId &&  pStat[i][1]==wParam ){
					

					if (dwStatId==194){
						ItemTxt *pItemTxt = D2GetItemTxt(pUnit->dwTxtFileNo);
						if ( pStat[i][3] > (pItemTxt->nSocket)){
							pStat[i][3] = (pItemTxt->nSocket);
						}
					}

					if ( dwStatId==216 ){
						int lvl = D2GetUnitStat(PLAYER, STAT_LEVEL, 0);
						wsprintfW(wszStr+wcslen(wszStr), L" \xFF\x63\x34(%d-%d)\xFF\x63\x33",pStat[i][2]*lvl/8 , pStat[i][3]*lvl/8 );
					}else{
						int extvalue = 0 ;
						if(idx==2){
							/*�������֮������ĵ�����Ҳ�ӵ�������Χ��*/
							UnitAny *pItem = D2GetFirstItemInInv(pUnit->pInventory);
							while (pItem) {
								extvalue = extvalue + D2GetUnitStat(pItem,dwStatId,0);
								pItem = D2GetNextItemInInv(pItem);
							}
						}
						wsprintfW(wszStr+wcslen(wszStr), L" \xFF\x63\x34(%d-%d)\xFF\x63\x33",pStat[i][2]+extvalue , pStat[i][3]+extvalue);
					}
					break;
				}

			}

		}
		
	}
	return wszStr;
}


DWORD __fastcall GetItemPropStringPatch( wchar_t *wszStr , StatEx * pStatEx ,DWORD flag){

	if ( tShowItemVariableProp.isOn && !flag ){
		//ShowGameMessage(pStatEx->wParam);

		DWORD dwStatId = pStatEx->wStatId;
		DWORD dwParam = pStatEx->wParam ;

		switch( dwStatId ){
			case 195:
			case 198:
			case 201:
				dwParam = dwParam>>6;
				break;
			case 188:
				{
					int chartype = dwParam/8;
					int skilltab = dwParam%8;
					dwParam = chartype*3+skilltab;
				}
				break;
			default:
				break;
		}
		GetStatRange( wszStr , dwStatId , dwParam );
	}
	return pStatEx->wStatId;

}

RET_VOID_NAKE GetItemPropStringPatch_ASM()
{
	// esp +4 +8*ebp+2D4 = pStatEx
	// ebx = dwStatNo
	// esi = wszPropStr
	__asm {
		lea edx , [esp+4+8*ebp+0x2D4]
		mov ecx , esi
		push [esp+0x10]
		call GetItemPropStringPatch
//org , eax from ebx
		sub eax, 0x17
		ret
	}
}

void __fastcall StrcatItemPropStringPatch( wchar_t *wszMainStr  , wchar_t *wszPropStr ,DWORD dwStatNo ){
	
	int len = wcslen(wszPropStr);
	if ( len == 0 ) return;
	wszPropStr [ len-1] = L'\0';//ȥ���س�
	if ( tShowItemVariableProp.isOn 
		#ifdef MODULE_ITEMDESC 
			&& tViewSocketBase.isOn == 0 
		#endif

	){
		
		GetStatRange( wszPropStr , dwStatNo );
	}
	wcscat( wszMainStr , wszPropStr );
	wcscat( wszMainStr , L"\n");

}

RET_VOID_NAKE StrcatItemPropStringPatch_ASM()
{
	__asm {
		push [esp+0xC]
		call StrcatItemPropStringPatch
		ret
	}
}

wchar_t * __fastcall StrcatSocketStringPatch( wchar_t *wszStr ){
	
	//ƴ�����ַ����ĵط�,��һ������ƴ�ӻس�

	if ( tShowItemVariableProp.isOn ){
		GetStatRange( wszStr , 194 );
	}
	return wszStr;
}

RET_VOID_NAKE StrcatSocketStringPatch_ASM()
{
	__asm {
		push edi

		mov ecx , eax
		call StrcatSocketStringPatch

		pop edi

		mov edx, dword ptr [esp+0x14]
		mov ecx, eax
		ret
	}
}


wchar_t * __fastcall StrcatDefenseStringPatch( wchar_t *wszStr ){
	
	//ƴ�����ַ����ĵط�,��һ������ƴ�ӻس�
	//����ETH��Ʒ Bug��ף����bug�����������ķ�bug���ֵ��С������Ϊ�Ƿ�bug
	if ( tShowItemVariableProp.isOn ){

		UnitAny *pUnit = VIEWITEMUNIT ;
		if (pUnit){

			ItemTxt *pItemTxt = D2GetItemTxt( pUnit->dwTxtFileNo );
			if( pItemTxt && pItemTxt->dwMinDef>0 ){

				int mDef = D2GetUnitBaseStat(pUnit, 31,0);
				int mMinDef = pItemTxt->dwMinDef;
				int mMaxDef = pItemTxt->dwMaxDef ;
				wchar_t wszPrep[256] = {L"\0"};
				wchar_t wszTemp[512] = {L"\0"};

				if ( D2CheckItemFlag(pUnit, ITEMFLAG_ETHEREAL, 0, "?") ){
					mMinDef = (int)(mMinDef * 1.5) ;
					mMaxDef = (int)(mMaxDef * 1.5) ;

					if ( mDef>mMaxDef && pUnit->pItemData->dwQuality==2 && D2CheckItemFlag(pUnit, ITEMFLAG_SOCKETED, 0, "?")  ){
						//��ͨ��Ʒ ,���ף�������������������ΪETH BUG
						mMinDef = (int)(mMinDef * 1.5) ;
						mMaxDef = (int)(mMaxDef * 1.5) ;
						wcscpy(wszPrep , L"(Bug)");
					}

				}

				if ( mDef > mMaxDef ){//������������˵��������ED�������Զ�max+1
					wsprintfW( wszTemp, L"%s(Min: %d, Max: %d, Now: %d+%d)\n" ,wszPrep, mMinDef , mMaxDef , mMaxDef ,mDef - mMaxDef );
				}else{
					wsprintfW( wszTemp, L"%s(Min: %d, Max: %d, Now: %d)\n" ,wszPrep, mMinDef , mMaxDef , mDef);
				}
				wcsrcat(wszStr,  wszTemp);
			}

		}

	}
	return wszStr;
}

RET_VOID_NAKE StrcatDefenseStringPatch_ASM()
{
	__asm {
		push ebx

		mov ecx , edi
		call StrcatDefenseStringPatch

		pop ebx

		mov edx, dword ptr [esp+0x1C]
		mov ecx, eax
		ret
	}
}


wchar_t * __fastcall StrcatDamageStringPatch( wchar_t *wszStr ){

	//ƴ�����ַ�����ֱ��ƴ��(����Ҳ�����)
	if ( tShowItemVariableProp.isOn ){
		UnitAny *pUnit = VIEWITEMUNIT ;
		if (pUnit){

			ItemTxt *pItemTxt = D2GetItemTxt( pUnit->dwTxtFileNo );
			if( pItemTxt &&  (int)(pUnit->dwTxtFileNo)< *p_D2WeaponsTxts ){
				wchar_t wszTemp[512] = {L"\0"};
				int Sockets = pItemTxt->nSocket;
				if ( pUnit->pItemData->dwQuality<=3){
					int maxSockets = 0;
					int iLevel = pUnit->pItemData->dwItemLevel;
					ItemTypeTxt *pItemTypeTxt = D2GetItemTypeTxt(pItemTxt->nType);
					if ( iLevel<=25){
						maxSockets = pItemTypeTxt->nMaxSock1;
					}else if ( iLevel<=40 ){
						maxSockets = pItemTypeTxt->nMaxSock25;
					}else{
						maxSockets = pItemTypeTxt->nMaxSock40;
					}
					if (Sockets>maxSockets)Sockets = maxSockets;
					wsprintfW2Colour( wszTemp, 0,"(Range: %d, Speed: %d, Sockets: 1-%d)\n" ,pItemTxt->nRangeAdder+1, pItemTxt->dwSpeed , Sockets);
				}else{
					wsprintfW2Colour( wszTemp, 0,"(Range: %d, Speed: %d)\n" ,pItemTxt->nRangeAdder+1, pItemTxt->dwSpeed);
				}
				wcsrcat(wszStr,  wszTemp);
			}

		}

	}
	
	return wszStr;
}
//һ����Ʒ����
RET_VOID_NAKE StrcatDamageStringPatch_ASM1()
{
	__asm {
		push ebx

		mov ecx , edi
		call StrcatDamageStringPatch

		pop ebx

		mov edx, eax
		lea ecx, dword ptr [esp+0x68]
		ret
	}
}
//��ɫ��������

RET_VOID_NAKE StrcatDamageStringPatch_ASM2()
{
	__asm {
		push ebp

		mov ecx , edi
		call StrcatDamageStringPatch

		pop ebp

		mov edx, eax
		lea ecx, dword ptr [esp+0x194C]
		ret
	}
}
#endif
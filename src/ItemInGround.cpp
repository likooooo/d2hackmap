#include "stdafx.h"

#ifdef MODULE_ITEMINGROUND

BOOL  CheckItemVisible(UnitAny *pItem){
	// false ����ʾ true ��ʾ
	if( tHiddenItems.isOn ) return TRUE;

	//�ѱ�ʶ��Ʒ�����ж�
	if( tShowIdentifiedItem.isOn && fPlayerInTown && pItem->pItemData->dwQuality>=3){
		if( D2CheckItemFlag(pItem, ITEMFLAG_IDENTIFIED, 0, "?") ) return TRUE;
	}

	//���֮�ﲻ����
	if ( D2CheckItemFlag(pItem, ITEMFLAG_RUNEWORD, 0, "?") ) return TRUE;

	BYTE nColour = GetItemColour( pItem , nItemShowMode );
	if ( nColour == 0xFE ) return FALSE;
	return TRUE;

}

#endif
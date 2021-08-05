#include "stdafx.h"

#ifdef MODULE_AUTOENCHANT

//����ǿ�����ݰ���ǿ��״̬����û���ϣ�����Ϊÿ��unitid���ü�ʱ�����ڼ�ʱ����ǰ���������ظ������ݰ�
//��ÿ����һ��ǿ����ȫ�ּ�ʱ����ʱ���������¿�ʼ�ж�ǿ����������Ч���ݰ��ķ���
//�˶ε��ú���֣�����������ֹȫ�ּ�ʱʧЧ

void AutoEnchantLoop( UnitAny *pUnit ){

	static int delays = 0 ;//��ʱ
	static int unitCount[2][1000] = {0,};  //1K

	if(fPlayerInTown){
		//���Ǻ󣬵ȻῪʼ
		delays = 1000;
		return;
	}
	
	if ( delays >0 ) {
		delays -- ;
		return;
	}
	
	DWORD dwUnitId = pUnit->dwUnitId ; 

	if ( pUnit->dwUnitType==UNITNO_PLAYER && dwUnitId == dwPlayerId) return; //�����Լ�ǿ��

	if ( PLAYER->pSkill->pRightSkill->pSkillInfo->wSkillId !=52 ) return;//��Ҫ�Ҽ�����ǿ��

	if ( pUnit->dwUnitType==UNITNO_MONSTER ){
		dwUnitId = D2GetMonsterOwner(pUnit->dwUnitId);
		if (dwUnitId == (DWORD)-1)return; //��������
	}
	
	if ( D2CheckUnitState(pUnit, 16) )return; //��ǿ��

	if ( unitCount[pUnit->dwUnitType][pUnit->dwUnitId] >0 ) {
		//ûǿ��״̬������ʱδ����������ǿ������
		unitCount[pUnit->dwUnitType][pUnit->dwUnitId] = unitCount[pUnit->dwUnitType][pUnit->dwUnitId] -1;
		return;
	}
	if ( TestPvpFlag( dwPlayerId, dwUnitId )>=2 ){
		//ֻ�ܸ�����
		unitCount[pUnit->dwUnitType][pUnit->dwUnitId] = 2000; //��ʼ��ʱ
		delays = 800 ; //���´η���ǰ��ȫ�ּ�ʱ

		BYTE castTP1[9] = {0x0D};
		*(DWORD*)&castTP1[1] = pUnit->dwUnitType;
		*(DWORD*)&castTP1[5] = pUnit->dwUnitId;
		D2SendPacket(sizeof(castTP1), 0, castTP1);		
	}
	return;
}

void AutoEnchant(UnitAny *pUnit) {
	
	static int lock = 0 ; 

	if( tAutoEnchant.isOn==0 ) return;

	if (lock==1)return;
	lock = 1;
	AutoEnchantLoop(pUnit);
    lock = 0;
	return ;

}


#endif
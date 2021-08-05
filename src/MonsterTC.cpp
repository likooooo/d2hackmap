#include "stdafx.h"

#ifdef MODULE_MONSTERLIFEBAR

/*
TC ����

struct TreasureClassItem {
	DWORD _1[2];		//+00
	DWORD dwIdx;		//+08
	union {
		DWORD dwProp;
		struct {
			DWORD _3:2;
			DWORD fTc:1;
		};				//+0C
	};
};

struct TreasureClass {			//size = 0x2C
	WORD wGroup;				//+00
	WORD wLevel;				//+02
	DWORD dwItems;				//+04
	DWORD _1[8];				//+08
	TreasureClassItem *pItems;	//+28
};


�ڵ�һ�ν���Ϸʱ��������TCֵ�����Ӧ��TC�ȼ�(ȡ����������ȼ�),TreasureClass���1012��
TreasureClassEx.txt�У��ӵ�һ����Ч�������1��ʼ��ţ��ټ���160����Ϊ��Ϸ�е�TC�ṹ����
��Ϸ������1-160Ϊ����TC�����������ָ��һ��itemtype(bow��weap��mele��armo��abow),��32��һ����,

ÿ��TreasureClass������TreasureClassItem����ָ��TreasureClass�����յݹ�ָ������itemtype
��ָ��itemtypeʱ�� dwIdxΪgptItemTables������,����Ϊһ��TC����

TreasureClass��group���Ե�һ�ν���ϷʱΪ0����ʵ��group+5���Ժ�ÿ��һ���µķ���+5  ;

tc ��3��ʼ��3������ʵ�����87 
runeTC  ÿ2��rune һ�飬��17�飬 33��ռһ��


TC��������
���mlvl>tc->level �� tc->group ��Ϊ0 , ��tc������ͬgroup��level��С��mlvl��tc��
*/


static MonTC anMonsterTCs[1014];
static BOOL fIsTcInit = FALSE ; 	

void CalculateHighestTC(int tcno , WORD offset)
{
	TreasureClass *pTc = D2GetTreasureClasses(tcno, 0);
	if(!pTc)return;

	anMonsterTCs[tcno].wLevel = pTc->wLevel;
	anMonsterTCs[tcno].wGroup = ( ( pTc->wGroup==0 ) ? 0 : pTc->wGroup-offset );
	anMonsterTCs[tcno].fInit = false;

	for (int i = 0; i < (int)pTc->dwItemNums; i++) {

		DWORD dwThingNo = pTc->pItems[i].dwThingNo;

		if (pTc->pItems[i].fTc) {
			if ( dwThingNo<= 160) {
				int groupno = (dwThingNo-1)/32;
				int tc = (((dwThingNo-1)%32)+1)*3;
				if (groupno==1 && tc>anMonsterTCs[tcno].nTc ) anMonsterTCs[tcno].nTc=tc;
			} else {
				if ( anMonsterTCs[ dwThingNo ].fInit==false ){
					CalculateHighestTC(dwThingNo , offset);
				}
				if ( anMonsterTCs[dwThingNo].nTc > anMonsterTCs[tcno].nTc ){
					anMonsterTCs[tcno].nTc = anMonsterTCs[dwThingNo].nTc;
				}
				if ( anMonsterTCs[dwThingNo].nRtc > anMonsterTCs[tcno].nRtc ){
					anMonsterTCs[tcno].nRtc = anMonsterTCs[dwThingNo].nRtc;
				}

			}
		} else {
			ItemTxt *itemtxt = D2GetItemTxt(dwThingNo);
			if (itemtxt && itemtxt->nType == 74) {
				int runeno = (itemtxt->szCode[1]-'0')*10+(itemtxt->szCode[2]-'0');
				int runetc = (int)(runeno/2)+runeno%2;
				if (runetc >anMonsterTCs[tcno].nRtc) anMonsterTCs[tcno].nRtc = runetc;
			}
		}
	}
	anMonsterTCs[tcno].fInit = true;
}

void InitTCList()
{	
	if(fIsTcInit) return ;
	memset( anMonsterTCs ,		0 ,			sizeof(anMonsterTCs) );
	int i;
	WORD offset;
	TreasureClass *pTc=D2GetTreasureClasses(262, 0) ;
	offset= pTc->wGroup - 2;//�������ֵ; 262 ΪAct 1 Melee A   group Ϊ2
	
	for (i = 1; i <1014; i++)
	{
		CalculateHighestTC(i ,offset );
	}
	fIsTcInit = true;
}


MonTC *GetTcLevel(WORD tcno , DWORD mlvl) {
	
	int tcidx = tcno;
	if (anMonsterTCs[tcidx].wGroup>0 && mlvl>(DWORD)anMonsterTCs[tcidx].wLevel) {
		WORD tempgroup = anMonsterTCs[tcidx].wGroup ;
		while ( anMonsterTCs[tcidx+1].wGroup == tempgroup){
			tcidx++;
			if ( mlvl<=(DWORD)anMonsterTCs[tcidx].wLevel )break;

		}
	}
	return &anMonsterTCs[tcidx];
}




#endif
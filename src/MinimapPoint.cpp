#include "stdafx.h"
//����AutomapCell,��RoomPatch������

#ifdef MODULE_MINIMAPPOINT

extern MinimapConfig aMinimapConfigs[140];
MinimapCell aMinimapCells[140][30];//��Ϸ�д��ڵĿ�ָ������
int mimimapCells[140] = {0} ;
MinimapPoint aMinimapPoints[140];//ʵ�����õ�ָ������

void AddMinimapCell( DrlgLevel* pDrlgLevel , short cellno ,short xpos , short ypos ){
	DWORD dwLevelNo = pDrlgLevel->dwLevelNo;
	if( dwLevelNo == 45 ) dwLevelNo = 44; // Change Valley of Snakes to Lost City
	if( dwLevelNo == 17 ) dwLevelNo = 3; // ���֮�ظ�Ϊ����֮ԭ
	if (cellno < 0 ) cellno = -cellno;
	if ( dwLevelNo==46 && pDrlgLevel->pDrlgMisc->dwStaffTombLvl == cellno)cellno=300 ;//����ָ���趨
	if ( dwLevelNo >=140 || mimimapCells[dwLevelNo] >= 30 ) return ;

	if ( (dwLevelNo == 4 && cellno == 314)) { 
		for ( int i = 0 ; i < mimimapCells[dwLevelNo] ; i++){
			if( aMinimapCells[dwLevelNo][i].cellno == cellno ) return;
		}
	}
	
	aMinimapCells[dwLevelNo][ mimimapCells[dwLevelNo] ].cellno = cellno;
	aMinimapCells[dwLevelNo][ mimimapCells[dwLevelNo] ].xpos = xpos;
	aMinimapCells[dwLevelNo][ mimimapCells[dwLevelNo] ].ypos = ypos;
	mimimapCells[dwLevelNo]++;
}

void ResetMiniCells(){
	memset( aMinimapCells ,				0	,		sizeof(aMinimapCells) );
	memset( mimimapCells ,				0	,		sizeof(mimimapCells) );
	memset( aMinimapPoints ,			0	,		sizeof(aMinimapPoints) );
}


void BuildMiniMapPoint( DWORD dwAct ){
	DWORD lvlfirst,lvlend;
	if ( dwAct==5 ) {
		lvlfirst = actlvls[0] ;
		lvlend = actlvls[5];
	}else{
		lvlfirst = actlvls[dwAct] ;
		lvlend = actlvls[dwAct+1] ;
	}

	for ( DWORD i=lvlfirst; i<lvlend; i++ ){
		aMinimapPoints[i].nPoints = 0 ;
		MinimapConfig *pConfig = &aMinimapConfigs[i];
		for ( int j=0 ; j < pConfig->nPoints; j++ ){
			for( int k=0; k<mimimapCells[i] ; k++){
				if( pConfig->aPoint[j].wPointNo==aMinimapCells[i][k].cellno  && pConfig->aPoint[j].fFlag ){
					if ( pConfig->aPoint[j].nColour ==(BYTE)-1 ){
						aMinimapPoints[i].aPoint[aMinimapPoints[i].nPoints].nColour = nMinimapCellCol ;
					}else{
						aMinimapPoints[i].aPoint[aMinimapPoints[i].nPoints].nColour = pConfig->aPoint[j].nColour ;
					}
					aMinimapPoints[i].aPoint[aMinimapPoints[i].nPoints].xpos = aMinimapCells[i][k].xpos ;
					aMinimapPoints[i].aPoint[aMinimapPoints[i].nPoints].ypos = aMinimapCells[i][k].ypos ;
					aMinimapPoints[i].nPoints++;
				}
			}
		}
	
	}

}


BOOL AdjustPosition(POINT *ptPlayer, POINT *ptObject, POINT *ptLine)
{
	//�յ�λ��Ϊ nMinimapSize/10 �� , ������1/15��
	int xDistance = ptObject->x-ptPlayer->x;
	int yDistance = ptObject->y-ptPlayer->y;
	
	if ( abs(xDistance)<15 && abs(yDistance)<15 ){
		return false;
	}else{
		
		ptObject->x = (LONG)( ptPlayer->x + nMinimapSize*xDistance/10);
		ptObject->y = (LONG)( ptPlayer->y + nMinimapSize*yDistance/10);

		ptLine->x = (LONG)( ptPlayer->x + 2*nMinimapSize*xDistance/30);
		ptLine->y = (LONG)( ptPlayer->y + 2*nMinimapSize*yDistance/30);
		return true;
	}
}


void DrawMinimapPoint(){
	if ( tMinimap.isOn ) {
		for ( int i=0 ; i<aMinimapPoints[LEVELNO].nPoints ; i ++){
			BYTE colour = aMinimapPoints[LEVELNO].aPoint[i].nColour;
			int xpos = aMinimapPoints[LEVELNO].aPoint[i].xpos*10;
			int ypos = aMinimapPoints[LEVELNO].aPoint[i].ypos*10;
			
			//�޸Ĵ˴���ʹָ����scrolllock�͵�ͼ�ƶ�Ӱ��
			POINT ptObj,ptPlayer , ptLine; 
			PreparePosForDraw(&ptPlayer,PLAYER->pMonPath->dwMapPosX,PLAYER->pMonPath->dwMapPosY);
			PreparePosForDraw(&ptObj , xpos, ypos);

			if ( AdjustPosition(&ptPlayer, &ptObj, &ptLine) ){

				if (pMinimapObjectCell) {
					DrawAutomapCell(pMinimapObjectCell, ptObj.x, ptObj.y,colour);
				}else{
					wchar_t temp[20] = {L'*'};
					ColourD2String(temp, colour);
					DrawCenterText(6, temp, ptObj.x, ptObj.y, colour);
				}
				D2DrawLine(ptPlayer.x, ptPlayer.y, ptLine.x, ptLine.y, colour, -1);

			}
		}
	}

	if ((tMousePosToggle.isOn == 1) && (tMousePosToggle.key == 3))
	{
		POINT tMP;
		PreparePosForDraw(&tMP,D2GetPlayerXOffset()+MOUSEPOS.y,MOUSEPOS.x+D2GetPlayerYOffset());
		DrawAutomapCell(pMousePosCell, tMP.x, tMP.y, (BYTE)tMousePosToggle.value);
	}

}

#endif
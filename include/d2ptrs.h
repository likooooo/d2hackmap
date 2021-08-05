#ifndef D2_PTR_H
  enum DllBase { //Ϊ���ҷ���෽��, ��ȫ��ַ��ʽ���庯����ַ��������Ҫע��˴���ֵ�뷴����ļ��ж�Ӧ
    DLLBASE_D2CLIENT = 0x6FAB0000,
    DLLBASE_D2COMMON = 0x6FD50000,
    DLLBASE_D2GFX = 0x6FA80000,
    DLLBASE_D2WIN = 0x6F8E0000,
    DLLBASE_D2LANG = 0x6FC00000,
    DLLBASE_D2CMP = 0x6FE10000,
    DLLBASE_D2MULTI = 0x6F9D0000,
    DLLBASE_BNCLIENT = 0x6FF20000,
    DLLBASE_D2NET = 0x6FBF0000, 
    DLLBASE_STORM = 0x6FFB0000,//6FBF0000  , ��D2NET��ͻ���޸�ֵ
    DLLBASE_FOG = 0x6FF50000,
    DLLBASE_D2GAME = 0x6FC20000,
    DLLBASE_D2LAUNCH = 0x6FA40000,
	DLLBASE_D2MCPCLIENT = 0x6FA20000
  };

  enum DllNo {DLLNO_D2CLIENT, DLLNO_D2COMMON, DLLNO_D2GFX, DLLNO_D2WIN, DLLNO_D2LANG, DLLNO_D2CMP, DLLNO_D2MULTI, DLLNO_BNCLIENT, DLLNO_D2NET, DLLNO_STORM, DLLNO_FOG, DLLNO_D2GAME , DLLNO_D2LAUNCH,DLLNO_D2MCPCLIENT};
  #define DLLOFFSET(a1,b1) ((DLLNO_##a1)|(( ((b1)<0)?(b1):((b1)-DLLBASE_##a1) )<<8))

  #define D2FUNCPTR(d1,o1,v1,t1,t2) typedef t1 D2##v1##_t t2; extern D2##v1##_t *D2##v1;
  #define D2VARPTR(d1,o1,v1,t1)     typedef t1 p_D2##v1##_t;    extern p_D2##v1##_t *p_D2##v1;
  #define D2ASMPTR(d1,o1,v1)        extern DWORD vD2##v1;
  
  #define D2_PTR_H

#else

  #define D2FUNCPTR(d1,o1,v1,t1,t2) D2##v1##_t *D2##v1 = (D2##v1##_t *)DLLOFFSET(d1,o1);
  #define D2VARPTR(d1,o1,v1,t1)     p_D2##v1##_t *p_D2##v1 = (p_D2##v1##_t *)DLLOFFSET(d1,o1);
  #define D2ASMPTR(d1,o1,v1)        DWORD vD2##v1 = DLLOFFSET(d1,o1);
	
#endif

//���ļ���Ҫ������cpp���ظ�����һ��

D2ASMPTR(D2CLIENT,  0xEEEEEE00, ERR)
D2ASMPTR(D2CLIENT,  0xEEEEEE00, StartOfPtr)




D2FUNCPTR(D2CLIENT, 0x6FAC6780, ShowGameMessage,    void __stdcall, (wchar_t* text, int nColor) )
D2FUNCPTR(D2CLIENT, 0x6FAC6540, ShowPartyMessage,   void __stdcall, (wchar_t* text, int nColor))

D2FUNCPTR(D2CLIENT, 0x6FB19BC0, ShowMap,            void __fastcall, ())
D2FUNCPTR(D2CLIENT, 0x6FB02A20, RevealAutomapRoom,  void __stdcall, (DrlgRoom1 *room1, DWORD clipflag, AutomapLayer *layer))
D2FUNCPTR(D2CLIENT, 0x6FB6D6C0, RecvCommand07,      void __fastcall, (BYTE *cmdbuf))
D2FUNCPTR(D2CLIENT, 0x6FB6D650, RecvCommand08,      void __fastcall, (BYTE *cmdbuf))
D2FUNCPTR(D2CLIENT, 0x6FAFFB10, NewAutomapCell,     AutomapCell * __fastcall, ())
D2FUNCPTR(D2CLIENT, 0x6FB015F0, AddAutomapCell,     void __fastcall, (AutomapCell *cell, AutomapCell **node))

D2FUNCPTR(D2CLIENT, 0x6FACBBE0, GetPlayerXOffset,   long __stdcall, ())
D2FUNCPTR(D2CLIENT, 0x6FACBBF0, GetPlayerYOffset,   long __stdcall, ())

D2FUNCPTR(D2CLIENT, 0x6FB15690, SetUiStatus,        DWORD __fastcall, (DWORD dwUiNo, DWORD howset, DWORD unknown1))

D2FUNCPTR(D2CLIENT, 0x6FB43300, CalcShake,          void __stdcall, (DWORD *pPosX, DWORD *pPosY))
D2FUNCPTR(D2CLIENT, 0x6FB06390, GetMonsterOwner,    DWORD __fastcall, (DWORD dwUnitId))
D2FUNCPTR(D2CLIENT, 0x6FAFC060, GetUnitFromId,      UnitAny * __fastcall, (DWORD dwUnitId, DWORD dwUnitType)) //���ݱ�ź����ͻ�ȡ����,monster and palyer
D2FUNCPTR(D2CLIENT, 0x6FADF950, GetSelectedUnit,    UnitAny * __stdcall, ())


D2FUNCPTR(D2CLIENT, 0x6FB02BB0, InitAutomapLayerStub,   AutomapLayer* __fastcall, (DWORD nLayerNo)) //nLayerNo==>eax ���õ�ǰLayerָ��,�����ӦnLayerNoδ����,�����һ�������ڿͻ���
D2FUNCPTR(D2CLIENT, 0x6FB11380, CheckUiStatusStub,      DWORD __fastcall, (DWORD dwUiNo) )//dwUiNo ==> eax
D2FUNCPTR(D2CLIENT, 0x6FAFFD30, SetAutomapPartyStub	,   void __fastcall, (DWORD flag) )    //parm = flag  ==> esi 
D2FUNCPTR(D2CLIENT, 0x6FAFFD00, SetAutomapNamesStub ,   void __fastcall, (DWORD flag) )    //parm = flag  ==> esi 
D2FUNCPTR(D2CLIENT, 0x6FB41D75, ChatInputStub ,         void __stdcall, (D2MSG *pmsg) )  //�����ƫ����5������,ʹ���Զ����eax


D2FUNCPTR(D2CLIENT, 0x6FB3F5E0, ExitGame,			void __fastcall, ()) //ƫ��2λ��ʹ���Լ���eax
D2FUNCPTR(D2CLIENT, 0x6FADBCA0, ItemProtect,		void __stdcall, (UnitAny *pUnit, DWORD dwType))
D2FUNCPTR(D2CLIENT, 0x6FB67920, DrawClient,         void __fastcall, ())
D2FUNCPTR(D2CLIENT, 0x6FABBD92, Storm511,           void __stdcall, (D2MSG *pMsg) )


D2VARPTR(D2CLIENT,  0x6FBCC150, AutomapLayerList,   AutomapLayer *) //����AutomapLayer�б�
D2VARPTR(D2CLIENT,  0x6FBCC154, AutomapLayer,       AutomapLayer *) //��ǰ���ڵ�AutomapLayer

D2VARPTR(D2CLIENT,  0x6FBCC1E0, PlayerUnit,         UnitAny *)
D2VARPTR(D2CLIENT,  0x6FBCC33C, RosterUnitList,     RosterUnit *) //����б�
D2VARPTR(D2CLIENT,  0x6FBCC128, PetUnitList,        PetUnit * ) //����ٻ����б�

D2VARPTR(D2CLIENT,  0x6FBCC2D0, DrlgAct,            DrlgAct *)
D2VARPTR(D2CLIENT,  0x6FBCA2F4, Expansion,          DWORD ) // 1����Ƭ 0 ������Ƭ
D2VARPTR(D2CLIENT,  0x6FBCC2A8, Difficulty,         BYTE) //��ǰ�Ѷ� 0 1 2
D2VARPTR(D2CLIENT,  0x6FBBD618, GameInfo,           GameStructInfo *)
D2VARPTR(D2CLIENT,  0x6FBCC1EC, Fps,                DWORD )
D2VARPTR(D2CLIENT,  0x6FBCA2A4, Ping,               DWORD )
D2VARPTR(D2CLIENT,  0x6FBA18C0, ExitAppFlag,        DWORD)
D2VARPTR(D2CLIENT,  0x6FBCC2B8, InGame,             BOOL ) //�Ƿ�����Ϸ��

D2VARPTR(D2CLIENT,  0x6FBB40E8, AutomapOn,          DWORD) //С��ͼ�Ƿ��
D2VARPTR(D2CLIENT,  0x6FBA13F0, Divisor,            long)
D2VARPTR(D2CLIENT,  0x6FBCC188, Offset,             POINT)
D2VARPTR(D2CLIENT,  0x6FBCC178, AutomapPos,         POINT)
D2VARPTR(D2CLIENT,  0x6FBCC1C0, AutoMapSize,        POINT) //��ͼ��С
D2VARPTR(D2CLIENT,  0x6FBCC140, MinmapType,         DWORD) // 1С��ͼ 0 ���ͼ
D2VARPTR(D2CLIENT,  0x6FBCC1B8, MinimapOffset,      POINT) //С��ͼ��Ե��ַ �����ͼΪ -16*-16
D2VARPTR(D2CLIENT,  0x6FBA13FC,	MapNameOn,          DWORD) //

D2VARPTR(D2CLIENT,  0x6FBCBAF8, IsMapShakeOn,       BOOL)
D2VARPTR(D2CLIENT,  0x6FBAD944, MapShakeY,          long)
D2VARPTR(D2CLIENT,  0x6FBCBAFC, MapShakeX,          long)
D2VARPTR(D2CLIENT,  0x6FBB40E4, MovingVariable,     DWORD)

D2VARPTR(D2CLIENT,  0x6FBA4FC4, ScreenSizeX,        int ) //��Ļ���X 800*600   640*480
D2VARPTR(D2CLIENT,  0x6FBA4FC8, ScreenSizeY,        int ) //��Ļ���Y 800*600   640*480
D2VARPTR(D2CLIENT,  0x6FBA4FC4, ScreenSize,         POINT)  //��Ļ���X 800*600   640*480
D2VARPTR(D2CLIENT,  0x6FBCBEF8, DrawOffset,         POINT )//��ʾ��ƫ����
D2VARPTR(D2CLIENT,  0x6FBD3394, InfoPositionX,      int) //��Ϸ��Ϣ��ʾX����
D2VARPTR(D2CLIENT,  0x6FBCC1AC, InfoPositionY,      int) //��Ϸ��Ϣ��ʾY����

D2VARPTR(D2CLIENT,  0x6FBB4243, QuestData,          void *) //���������Ϣ��
D2VARPTR(D2CLIENT,  0x6FBB4247, GameQuestData,      void *) //����������Ϣ��
D2VARPTR(D2CLIENT,  0x6FBCD535, QuestPage,          int)

D2VARPTR(D2CLIENT,  0x6FBCC2B8, MButton,            BOOL )
D2VARPTR(D2CLIENT,  0x6FBCD590, LastChatMessage,    wchar_t)  
D2VARPTR(D2CLIENT,  0x6FBCBB30, ChatTextLength,         int)

D2VARPTR(D2CLIENT,  0x6FBCB414, MousePos,           POINT )//���λ��
D2VARPTR(D2CLIENT,  0x6FB9D8D4, LastMousePos,		POINT )//�������λ��
D2VARPTR(D2CLIENT,  0x6FB9CD14, CursorInvGridX,     DWORD)//������Ʒ��λ��
D2VARPTR(D2CLIENT,  0x6FB9CD18, CursorInvGridY,     DWORD)//������Ʒ��λ��
D2VARPTR(D2CLIENT,  0x6FBCBBDC, CurrentViewItem,    UnitAny*) //ѡ����ʾ����Ʒ

D2VARPTR(D2CLIENT,  0x6FBCC108, GoldInTranBox,         int)

D2ASMPTR(D2CLIENT,  0x6FBB8870, AutomapCellListBaseAddr)
D2ASMPTR(D2CLIENT,  0x6FB59070, LoadUiImageFunc)

D2FUNCPTR(D2COMMON, -0x2AA4,   GetObjectTxt,         ObjectTxt * __stdcall, (DWORD objno))
D2FUNCPTR(D2COMMON, -0x2991,   GetLevelDefTxt,       LevelDefTxt* __fastcall, (DWORD levelno))
D2FUNCPTR(D2COMMON, -0x28CD,   GetLevelTxt,          LevelTxt * __stdcall, (DWORD levelno))
D2FUNCPTR(D2COMMON, -0x2816,   GetItemTxt,           ItemTxt * __stdcall, (DWORD itemno))
D2FUNCPTR(D2COMMON, -0x28A2,   GetTreasureClasses,   TreasureClass * __stdcall, (WORD tcno, DWORD lvlno))
D2FUNCPTR(D2COMMON, -0x2AC9,   GetSuperUniqueTxt,    SuperUniqueTxt * __stdcall, (DWORD dwUniqueNo))

D2FUNCPTR(D2COMMON, -0x29BD,   GetItemFileIndex,     DWORD __stdcall, (UnitAny *pItem) ) //pItem->pItemData->dwFileIndex

D2FUNCPTR(D2COMMON, -0x2B5F,   GetStatFromStatList,  BOOL __stdcall, (StatList *pStatList, DWORD dwStatNo, StatEx *pStatVal ,DWORD dwMask ) ) //�Ƿ��������,����õ�����ֵ
D2FUNCPTR(D2COMMON, -0x2AC8,   GetStatListWithFlag,  StatList *  __stdcall, (UnitAny *pUnit, DWORD dwStatNo, DWORD dwListFlag) )//
D2FUNCPTR(D2COMMON, -0x274D,   GetUnitStat,          int __stdcall, (UnitAny *pUnit, DWORD dwStatNo, WORD dwLayerNo))
D2FUNCPTR(D2COMMON, -0x2936,   GetUnitBaseStat,      int __stdcall, (UnitAny *pUnit, DWORD dwStatNo, WORD dwLayerNo))//ֻ���ѯ��һ��statlist,����Ҵ󲿷������ܲ鵽
D2FUNCPTR(D2COMMON, -0x29B5,   GetMonsterHpPercent,  int __stdcall, (UnitAny *pUnit) )//�������Ч

D2FUNCPTR(D2COMMON, -0x296C,   CheckUnitState,       BOOL __stdcall, (UnitAny *pUnit, DWORD dwStateNo))
D2FUNCPTR(D2COMMON, -0x2A01,   CheckQuestFlag,       BOOL __stdcall, ( void *pQuestData, DWORD dwQuestNo, DWORD dwCheckFlag ))
D2FUNCPTR(D2COMMON, -0x283F,   CheckItemFlag,        BOOL __stdcall, (UnitAny *pItem, DWORD dwFlagMask, DWORD dwLineno, char *filename) )
D2FUNCPTR(D2COMMON, -0x2AAC,   CheckCorpseCanUse,    BOOL __stdcall, (UnitAny *pMon,DWORD flag))

D2FUNCPTR(D2COMMON, -0x290F,   GetItemValue,         int __stdcall, (UnitAny * pPlayer, UnitAny * pItem, DWORD dwDifficulty, void* questinfo, int value, DWORD dwFlag))
D2FUNCPTR(D2COMMON, -0x2AA2,   GetCursorItem,        UnitAny * __stdcall, (UnitInventory * ptInventory))//pUnit->pInventory->pCursorItem
D2FUNCPTR(D2COMMON, -0x2927,   GetFirstItemInInv,    UnitAny * __stdcall, (UnitInventory* ptInventory)) // pUnit->pInventory->pFirstItem
D2FUNCPTR(D2COMMON, -0x2B84,   GetNextItemInInv,     UnitAny * __stdcall, (UnitAny *pItem))
D2FUNCPTR(D2COMMON, -0x283D,   GetBoxType,           DWORD __stdcall, (UnitAny * pUnit, BYTE invType, DWORD dwExpansion));//��������
D2FUNCPTR(D2COMMON, -0x28D0,   CheckInvLocation,     int __stdcall, (UnitInventory* pInventory, UnitAny *pItem, DWORD dwCursorGridX, DWORD dwCursorGridY, DWORD dwBoxType, int* GridCount, int* ItemCount, BYTE invType))

D2FUNCPTR(D2COMMON, -0x2B32,   GetDrlgLevel,         DrlgLevel * __fastcall, (DrlgMisc *drlgmisc, DWORD levelno))//����һ���µ�DrlgLevel�ṹ,���ڷ����
D2FUNCPTR(D2COMMON, -0x29F5,   InitDrlgLevel,        void __stdcall, (DrlgLevel *drlglevel))
D2FUNCPTR(D2COMMON, -0x2B0D,   GetLevelIdFromRoom,   DWORD __stdcall, (DrlgRoom1 *pDrlgRoom1))

D2FUNCPTR(D2COMMON, -0x29D8,   GetUnitPosX,          DWORD __stdcall, (DynamicPath *pPath) ) //(Players, Monsters, Missiles) 
D2FUNCPTR(D2COMMON, -0x2B49,   GetUnitPosY,          DWORD __stdcall, (DynamicPath *pPath) ) //(Players, Monsters, Missiles) 

D2FUNCPTR(D2COMMON, -0x27A8,   GetMinExpToLevel,     int __stdcall, (DWORD dwCharClass, DWORD dwLevel))

D2VARPTR(D2COMMON,  0x6FDEFB1C, WeaponsTxts,         int)
D2VARPTR(D2COMMON,  0x6FDEFB24, ArmorTxts,           int)
D2VARPTR(D2COMMON,  0x6FDEEE8C, DataTables,        DWORD)
D2VARPTR(D2COMMON,  0x6FDEFB50, RuneWords,         DWORD)
D2VARPTR(D2COMMON,  0x6FDEFB54, RuneWordTxt,	   DWORD)

D2FUNCPTR(D2GFX,  -0x2726,   GetHwnd,                HWND __stdcall, ())
D2FUNCPTR(D2GFX,  -0x2710,   DrawRectangle,          void __stdcall, (long dwXstart, long dwYstart, long dwXend, long dwYend, DWORD dwPal, DWORD dwTransLvl))
D2FUNCPTR(D2GFX,  -0x2711,   DrawLine,               void __stdcall, (long x1, long y1, long x2, long y2, DWORD dwColor, DWORD dwTransLvl))
D2FUNCPTR(D2GFX,  -0x273C,   DrawCellFile,           void __stdcall, (CellContext *context, DWORD xPos, DWORD yPos, DWORD dw1, DWORD dwTransLvl, BYTE *coltab))
D2FUNCPTR(D2GFX,  -0x2715,   DrawAutomapCell,        void __stdcall, (CellContext *context, DWORD xpos, DWORD ypos, RECT *cliprect, DWORD dwTransLvl))

D2VARPTR(D2GFX,  0x6FA9D65C, WinState,			DWORD)


D2FUNCPTR(D2WIN,  -0x2750,   DrawText,               void __fastcall, (wchar_t *wStr, long xPos, long yPos, DWORD dwColor, DWORD dwAlign))
D2FUNCPTR(D2WIN,  -0x2737,   DrawHoverText,          void __fastcall, (wchar_t *wStr, long xPos, long yPos, DWORD dwTran, DWORD dwColor))
D2FUNCPTR(D2WIN,  -0x272F,   DrawUnitLifeBar,        DWORD __fastcall, (wchar_t *wStr ,long xPos, long yPos, DWORD dwColor, DWORD dwUnk1 ,DWORD dwUnk2) )
D2FUNCPTR(D2WIN,  -0x2735,   DrawHover,              void __fastcall, ()) //������ʾ�ַ���ĵط�������3��ֻ�������˱���,��ʾ���ȼ��ǳ���

D2FUNCPTR(D2WIN,  -0x27C7,   GetTextAreaSize,        DWORD __fastcall, (wchar_t *wStr, DWORD* pWidth, DWORD* pHeight))
D2FUNCPTR(D2WIN,  -0x27BA,   SetTextFont,            DWORD __fastcall, (DWORD dwFont))
D2FUNCPTR(D2WIN,  -0x2790,   GetTextPixelLen,        DWORD __fastcall, (wchar_t *wStr) )//����������ֱܷ���ɫ���룬ֻ��������ɫ�ַ���

D2FUNCPTR(D2WIN,  -0x2747,   GetEditBoxText,         wchar_t* __fastcall, (D2EditBox* box))
D2FUNCPTR(D2WIN,  -0x273F,   SelectEditBoxText,      void __fastcall,  (D2EditBox* box))
D2FUNCPTR(D2WIN,  -0x2764,   AddEditBoxChar,         DWORD __fastcall, (D2EditBox* box, BYTE keycode))
D2FUNCPTR(D2WIN,  -0x2765,   DestroyEditBox,         DWORD __fastcall, (D2EditBox* box))
D2FUNCPTR(D2WIN,  -0x2724,   DestroyListBox,         void __stdcall,   (D2EditBox* box))

D2FUNCPTR(D2WIN,  -0x2780,   CreateEditBox,          D2EditBox* __fastcall, (DWORD dwPosX, DWORD dwPosY, DWORD dwSizeX, DWORD dwSizeY, DWORD dwOffsetX, DWORD dwOffsetY, CellFile *pCellFile, DWORD dwReturnHandler, DWORD arg9, DWORD dwIsCloaked, void* buf))
D2FUNCPTR(D2WIN,  -0x27A5,   SetEditBoxText,         void* __fastcall, (D2EditBox* box, wchar_t* wcszTxt))
D2FUNCPTR(D2WIN,  -0x27C3,   SetEditBoxProc,         void __fastcall, (D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,DWORD,char*)))

D2VARPTR(D2WIN,   0x6F900498, FocusedControl,        D2EditBox*)

D2FUNCPTR(D2CMP,  -0x271E,   DeleteCellFile,         void __stdcall, (CellFile *cellfile))
D2FUNCPTR(D2CMP,  -0x2734,   InitCellFile,           void __stdcall, (void *cellfile, CellFile **outptr, char *srcfile, DWORD lineno, DWORD filever, char *filename))

D2FUNCPTR(D2LANG, -0x2710,   GetLocaleText,          wchar_t* __fastcall, (DWORD dwLocaleTxtNo))

D2VARPTR(D2NET,  0x6FBFB248, UnkNetFlag,	   DWORD)
D2FUNCPTR(D2NET,  -0x2724,   SendPacket,             void __stdcall, (size_t len, DWORD arg1, BYTE* buf))

D2VARPTR(BNCLIENT,  0x6FF3D854, BnChatMessage,     LPDWORD )

D2ASMPTR(D2CLIENT,  0xEEEEEEEE, EndOfPtr)

D2ASMPTR(D2CLIENT,  0xEEEEEE00, StartOfPtr2)

D2VARPTR(D2MULTI,  0x6FA09CC0, GameListControl,       D2EditBox *)
D2VARPTR(D2MULTI,  0x6F9E9C60, EditboxPreferences,    void *)  //6F9E9C5C+4

D2VARPTR(D2CLIENT,  0x6FBCC3CC, TestVariable,     DWORD)


D2ASMPTR(D2CLIENT,  0xEEEEEEEE, EndOfPtr2)

#undef D2FUNCPTR
#undef D2VARPTR
#undef D2ASMPTR




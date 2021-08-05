
#ifdef FUNCTION_DECLARE
	#define MODULE_UNICODESUPPORT
	LPCSTR __fastcall D2Lang_Unicode2WinPatch(LPSTR lpWinStr, LPWSTR lpUnicodeStr, DWORD dwBufSize);
	LPWSTR __fastcall D2Lang_Win2UnicodePatch(LPWSTR lpUnicodeStr, LPCSTR lpWinStr, DWORD dwBufSize);
	DWORD __fastcall ChannelEnterCharPatch(D2EditBox *hWnd, BYTE bKeyCode);
	void	MultiByteFixPatch_ASM();
	void	IsPritableCharacterPatch_ASM();
	
#endif

#ifdef VARIABLE_DEFINE
 
 
#endif

#ifdef PATH_INSTALL

  {PatchJMP,    DLLOFFSET(D2LANG, 0x6FC08C40),      (DWORD)D2Lang_Unicode2WinPatch,          5 ,   &fLocalizationSupport},
  {PatchJMP,    DLLOFFSET(D2LANG, 0x6FC08C70),      (DWORD)D2Lang_Win2UnicodePatch,          5 ,   &fLocalizationSupport},
  {PatchCALL,   DLLOFFSET(D2WIN,  0x6F8F38E0),      (DWORD)ChannelEnterCharPatch,            5 ,   &fLocalizationSupport}, //ע��InputLinePatch1_ASM�������������Ȼ�����𲿷ֶ�ջ����(��Ȼ��Ӱ��ʹ��)
  {PatchCALL,   DLLOFFSET(BNCLIENT,0x6FF2B2EC),     (DWORD)MultiByteFixPatch_ASM,            6 ,   &fLocalizationSupport}, // for /w *acc msg text
  {PatchCALL,   DLLOFFSET(D2WIN , 0x6F8EDDC0),      (DWORD)IsPritableCharacterPatch_ASM,     8 ,   &fLocalizationSupport}, //����

  {PatchFILL,   DLLOFFSET(D2WIN,  0x6F8EF629),		INST_NOP,							     2,	   &fLocalizationSupport},//ǿ��tbl������ʽ
  {PatchFILL,   DLLOFFSET(D2WIN,  0x6F8EF638),		INST_JMPR,							     1,	   &fLocalizationSupport},//ǿ��tbl������ʽ

#endif

#ifdef CONFIG_LOAD


#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif

#ifdef FUNCTION_DECLARE
	#define MODULE_TRANSGOLDHELP
	void SetGoldPatch_ASM();
	void SetDefaultGoldPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

 
#endif

#ifdef PATH_INSTALL

{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB12AC6),      (DWORD)SetGoldPatch_ASM,		6 , &fDefault},//����ת�ƵĽ��ֵ
{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB163DB),      (DWORD)SetDefaultGoldPatch_ASM, 5 , &fDefault},//����Ĭ��ֵ
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

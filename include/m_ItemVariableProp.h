#ifdef FUNCTION_DECLARE
	#define MODULE_ITEMVARIABLEPROP
	void GetItemPropStringPatch_ASM();
	void StrcatItemPropStringPatch_ASM();
	void StrcatSocketStringPatch_ASM();
	void StrcatDefenseStringPatch_ASM();
	void StrcatDamageStringPatch_ASM1();
	void StrcatDamageStringPatch_ASM2();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tShowItemVariableProp,	  1,	0,	-1,	1 , "Item Variable Prop")
 
#endif

#ifdef PATH_INSTALL

    {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAD248A),    (DWORD)GetItemPropStringPatch_ASM,      5 ,   &fDefault},//��ͨ����
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAD0D38),    (DWORD)StrcatItemPropStringPatch_ASM,   6 ,   &fDefault},//��ǿ�˺�����������
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB23485),    (DWORD)StrcatSocketStringPatch_ASM,     6 ,   &fDefault},//ƴ������ETH�ȵײ��ַ�������������Ϊ����
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2283D),    (DWORD)StrcatDefenseStringPatch_ASM,    6 ,   &fDefault},//ƴ����ֵ�ַ���
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB28B0A),    (DWORD)StrcatDamageStringPatch_ASM1,    6 ,   &fDefault},//ƴ�����ַ���,һ������
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB27674),    (DWORD)StrcatDamageStringPatch_ASM2,    9 ,   &fDefault},//ƴ�����ַ���,��ɫ����
	
#endif

#ifdef CONFIG_LOAD
{1, "ShowItemVariablePropToggle",					&tShowItemVariableProp         },

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

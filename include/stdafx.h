// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#define _CRT_SECURE_NO_DEPRECATE        // ȥ���������������ȫ���
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "HelpFunc.h"
#include "d2vars.h"
#include "d2structs.h"
#include "MyStructs.h"

#include "d2ptrs.h"
#include "d2callstub.h"
#include "d2helpfunc.h"

#define FUNCTION_DECLARE
#include "Module.h"
#undef FUNCTION_DECLARE


#define VARIABLE_DEFINE
#include "Module.h"
#undef VARIABLE_DEFINE


#include "Install.h"
#include "Define.h"
#define RET_VOID_NAKE void __declspec(naked)
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�



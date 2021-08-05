#ifndef CONFIGSTRUCT_H
#define CONFIGSTRUCT_H

	//����ṹ
    struct ToggleVar {
        BYTE  type ;    // 1  �����л�����(�ɴ����¼�)  2 ���������¼����������� 3��0  ���������¼� ������ 
        BYTE  isOn;	    //�Ƿ���
        BYTE  key;	    //��������
        BYTE  value;	//����ֵ
        char* desc;     //�¼�����
        union{
            void *func; //���õĺ���
            void (*funcVoid)();
            void (*funcParam)(int);
        };
        int param;     //func2��������
		BOOL  isLoad;  //�Ƿ��������м��ص�
    };

    //�����ļ�����
	/*
	1  ���������¼�
	2  ��ֵ ���ȿ�Ϊ 1  2  4  
	3  �ַ��� ���ֽ�
	4  �ַ��� ˫�ֽ�,����ɫ
	5  ����
	6  ����1
	7  ����2
	*/

    struct ConfigVar {
        int		type ;			//��������
        char	*szCmdName;	    //������
        void	*pVar;			//��������Ķ���
        BYTE	size;			//����ֵ�ĳ���,������int��������
        short	anArrayMax[4];	//��Ӧ����ĸ�ά����
    };

    //��������VCB�ļ���
    struct TreeNode {
        char   *key;
        char   *str;
        TreeNode *left, *right;
    };
    
    //��·��ṹ
    struct Patch_t{
        void (*func)(DWORD, DWORD, DWORD);
        DWORD addr;
        DWORD param;
        DWORD len;
        BOOL *fEnable;
        BYTE *oldcode;
        BOOL fInit ;

    };

	//��ͼָ�������ļ�
	struct MinimapConfig{
		int  nPoints  ;		//ָ������
		struct {
			WORD wPointNo ;	//ָ����
			BYTE fFlag;		//�Ƿ���Ч
			BYTE nColour;	//��ɫ
		} aPoint[30];
	};
	
	//��ָ��ĵ�ͼ��
	struct MinimapCell{
		short	cellno;
		short	xpos;
		short	ypos;
	};

	//ָ��Ŀ��
	struct MinimapPoint{
		int  nPoints  ;		//ָ������
		struct {
			short	xpos;
			short	ypos;
			BYTE	nColour;	//��ɫ
		} aPoint[30];
	};
	
	struct D2ScreenHookStruct
	{
		BYTE *show;
		int xpos;
		int ypos;
		wchar_t wszMsg[512];
		BYTE color;
	};

	struct InventoryType {
		BYTE invType;
		short left;
		short bottom;
		BYTE nGridXs;
		BYTE nGridYs;
		BYTE nGridWidth;
		BYTE nGridHeight;
	};
	
	struct BugQuestInfo{
		DWORD nQuestNo; //������
		DWORD nStatus ; //����״̬
		DWORD nType ;   //����ģʽ
		BYTE *fEnable ; //�Ƿ�ʼ
		char szMsg[10]; //����
	} ;

	struct MonTC
	{
		WORD wGroup;
		WORD wLevel;
		int nTc;
		int nRtc;
		BOOL fInit;	
	};
	
	struct ViewUnitInfo {
		DWORD dwUiNo;
		DWORD dwUnitId;
		DWORD dwUnitType;
		UnitAny *pUnit;
	};

	struct PlayerStat {
		DWORD dwStatNo;
		char* szDesc;
		char* szSuffix;
	};

	struct LevelInfo{
		DrlgLevel* pDrlgLevel;
		BOOL fReady;
		BOOL fRevealed;
	};

	struct StatMonitor {
		wchar_t wszDesc[2][30];
		DWORD	dwStatNo;
		DWORD	dwTimer;
		DWORD   dwColor;
		BOOL	fEnable;
	};
	
	struct MyTimer {
		DWORD dwValue;
		DWORD dwTimer;
		BOOL  fEnable;
	};

	struct ScrollDis {
	double dis;
	double maxdis;
	double todis;
	double newx;
	double newy;
	double newdis;
	double R;
};

#endif

/**********************************�ļ�ͷ��ע��************************************/
//
//
//						Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// �ļ�����		cryptoe2.c
//
// �����ߣ�		lz
//
// ����ʱ�䣺	2005.07.08
//
// �ļ�������
//
// �޸ļ�¼��	��		 �� 	 �� 	 �� 	  �汾		�޶�
//					   ---------		 ---------		  ----- 	   -----
//
/*****************************************************************************************/

/************************************�ļ�����****************************************/
// FOR ST INTEGRATED ENVIORNMENT
#include "cm_lib.h"
#include "cm_i2c.h"
#include "cm_i2c_l.h"
#include "cm_gpa.h"

#include "cryptoe2.h"
#include "des.h"
/************************************�궨��*******************************************/
#define E2DEBUG(x)
#define E2ERROR(x)
#define E2OK(x)


/***********************************************************************
	��������:	E2PROM_WriteConfigZone

	����˵��:	����������

	   �޸ļ�¼:	��		 �� 	 �� 	 �� 	  �޶�
					   ---------		 ---------		   -----

************************************************************************/
sint	E2PROM_WriteConfigZone( uint			Addr,
							uchar			*Buffer,
							uint 		NumberToWrite,
							bool		bAntiTearing)
{
	sint			NVMError = 0;
	sint			CallError = 0;


	cm_InitI2c();

	CallError = cm_WriteConfigZone( Addr,Buffer,NumberToWrite,bAntiTearing);
	cm_TermI2c();

	return NVMError;

}

/***********************************************************************
	��������:	E2PROM_ReadConfigZone

	����˵��:	��ȡ������������

	   �޸ļ�¼:	��		 �� 	 �� 	 �� 	  �޶�
					   ---------		 ---------		   -----

************************************************************************/
sint	E2PROM_ReadConfigZone(uchar Addr,
												uchar	*Buffer,
												uchar	NumberToWrite )
{
	sint			NVMError = 0;
	sint			CallError = 0;

	cm_InitI2c();

	CallError = cm_ReadConfigZone( Addr,Buffer,NumberToWrite);
	cm_TermI2c();

	return NVMError;

}


/***********************************************************************
	��������:	E2PROM_ReadChecksum

	����˵��:	��ȡ��������У���

	   �޸ļ�¼:	��		 �� 	 �� 	 �� 	  �޶�
					   ---------		 ---------		   -----

************************************************************************/
sint	E2PROM_ReadChecksum(uchar *pucCheckSum)
{
	sint			NVMError = 0;
	sint			CallError = 0;

	cm_InitI2c();

	CallError = cm_ReadChecksum( pucCheckSum);
	cm_TermI2c();

	return NVMError;

}


/***********************************************************************
	��������:	E2PROM_VerifyPwd

	����˵��:	������֤

	   �޸ļ�¼:	��		 �� 	 �� 	 �� 	  �޶�
					   ---------		 ---------		   -----

************************************************************************/
sint	E2PROM_VerifyPwd( uchar ucPwdSet, uchar aucPwd[3], bool WritePwd )
{
	sint	CallError;

	cm_InitI2c();

	if (WritePwd)
	{
		CallError = cm_VerifyPassword(aucPwd,ucPwdSet,CM_PWWRITE);
	}
	else
	{
		CallError = cm_VerifyPassword(aucPwd,ucPwdSet,CM_PWREAD);
	}

	cm_TermI2c();

	return CallError;

}

//#define WriteDebug(x)  printf(x)
#define WriteDebug(x)

/***********************************************************************
	��������:	IDENT_E2_ReadSTBID
	����˵��:	Read Ident ID (part of Mac Address) from E2
				(return TRUE : OK)
				(return FALSE: FAILED)
	�޸ļ�¼:	��		 �� 	 �� 	 �� 	  �޶�
					   ---------		 ---------		   -----

************************************************************************/
bool	IDENT_E2_ReadSTBID( uchar *pucData )
{
	sint	YWError = 0;
	//uchar	ucData[16];
	bool	iRet;

#if 0
	// Unlock Config Zone
	WriteDebug("\nUnlock Config Zone:");
	ucData[0] = 0xad;
	ucData[1] = 0x42;
	ucData[2] = 0x97;
	YWError = E2PROM_VerifyPwd(7, ucData, TRUE);
	if ( YWError == 0 )
	{
		WriteDebug("Success!!\n");
	}
	else
	{
		WriteDebug("Failed!\n");
	}
#endif
	// Read back MAC Addr
	WriteDebug("\nRead back Ident ID:");
	YWError = E2PROM_ReadConfigZone(0x19, pucData, 7);
	if ( YWError != 0 )
	{
		WriteDebug("Data Wrong!!\n");
		iRet = FALSE;
	}
	else
	{
		WriteDebug("Success!!\n");
		iRet = TRUE;
	}
#if 0
	// Lock Config Zone
	WriteDebug("\nLock Config Zone:");
	ucData[0] = 0x00;
	ucData[1] = 0x00;
	ucData[2] = 0x00;
	YWError = E2PROM_VerifyPwd(7, ucData, TRUE);
	if ( YWError == 0 )
	{
		WriteDebug("Success!!\n");
	}
	else
	{
		WriteDebug("Failed!\n");
	}
#endif
	return iRet;

}


/***********************************************************************
	��������:	IDENT_E2_IsCryptoE2Exist

	����˵��:	check whether cryptoe2 exist or not.
					(return TRUE : exist)
					(return FALSE: not exist)

	   �޸ļ�¼:	��		 �� 	 �� 	 �� 	  �޶�
					   ---------		 ---------		   -----

************************************************************************/
bool	IDENT_E2_IsCryptoE2Exist( void )
{
	uchar ucData[16];
	sint	YWError = 0;

	// Test write to MTZ
/*	ucData[0] = 0xF8;
	ucData[1] = 0xF6;
	YWError = E2PROM_WriteConfigZone(0x0A, ucData, 2, FALSE);
	if ( YWError != 0 )
	{
		return FALSE;
	}*/

	// Test Read back MTZ
	ucData[0] = 0;
	ucData[1] = 0;
	YWError = E2PROM_ReadConfigZone(0x0A, ucData, 2);
	if ( YWError != 0 )
	{
		return FALSE;
	}

	if (ucData[0] != 0xF8 || ucData[1] != 0xF6)
	{
		return FALSE;
	}

	return TRUE;

}


/***********************************************************************
	��������:	IDENT_E2_Init

	����˵��:	just need a i2c handle for pio simulating.

	   �޸ļ�¼:	��		 �� 	 �� 	 �� 	  �޶�
					   ---------		 ---------		   -----

************************************************************************/
sint	IDENT_E2_Init( void )
{
	cm_PowerOn();
	return 0;
}

sint	IDENT_E2_Term( void )
{
	cm_PowerOff();
	return 0;
}



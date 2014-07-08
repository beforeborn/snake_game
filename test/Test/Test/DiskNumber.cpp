#include "stdafx.h"
#include <windows.h>

#define  FILE_DEVICE_SCSI              0x0000001b
#define  IOCTL_SCSI_MINIPORT_IDENTIFY  ( ( FILE_DEVICE_SCSI << 16 ) + 0x0501 )

#define  IOCTL_SCSI_MINIPORT 0x0004D008  //  see NTDDSCSI.H for definition

#define  IDENTIFY_BUFFER_SIZE  512
#define  SENDIDLENGTH  ( sizeof( SENDCMDOUTPARAMS ) + IDENTIFY_BUFFER_SIZE )

#define  IDE_ATAPI_IDENTIFY  0xA1  //  Returns ID sector for ATAPI.
#define  IDE_ATA_IDENTIFY    0xEC  //  Returns ID sector for ATA.
#define  DFP_RECEIVE_DRIVE_DATA   0x0007c088



typedef struct _SRB_IO_CONTROL
{
	ULONG HeaderLength;
	UCHAR Signature[8];
	ULONG Timeout;
	ULONG ControlCode;
	ULONG ReturnCode;
	ULONG Length;
} SRB_IO_CONTROL, *PSRB_IO_CONTROL;

typedef struct _IDSECTOR
{
	USHORT  wGenConfig;
	USHORT  wNumCyls;
	USHORT  wReserved;
	USHORT  wNumHeads;
	USHORT  wBytesPerTrack;
	USHORT  wBytesPerSector;
	USHORT  wSectorsPerTrack;
	USHORT  wVendorUnique[3];
	CHAR    sSerialNumber[20];
	USHORT  wBufferType;
	USHORT  wBufferSize;
	USHORT  wECCSize;
	CHAR    sFirmwareRev[8];
	CHAR    sModelNumber[40];
	USHORT  wMoreVendorUnique;
	USHORT  wDoubleWordIO;
	USHORT  wCapabilities;
	USHORT  wReserved1;
	USHORT  wPIOTiming;
	USHORT  wDMATiming;
	USHORT  wBS;
	USHORT  wNumCurrentCyls;
	USHORT  wNumCurrentHeads;
	USHORT  wNumCurrentSectorsPerTrack;
	ULONG   ulCurrentSectorCapacity;
	USHORT  wMultSectorStuff;
	ULONG   ulTotalAddressableSectors;
	USHORT  wSingleWordDMA;
	USHORT  wMultiWordDMA;
	BYTE    bReserved[128];
} IDSECTOR, *PIDSECTOR;
typedef struct _GETVERSIONOUTPARAMS
{
	BYTE bVersion;      // Binary driver version.
	BYTE bRevision;     // Binary driver revision.
	BYTE bReserved;     // Not used.
	BYTE bIDEDeviceMap; // Bit map of IDE devices.
	DWORD fCapabilities; // Bit mask of driver capabilities.
	DWORD dwReserved[4]; // For future use.
} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;



BYTE szSystemInfo[4096]; // 在程序执行完毕后，此处存储取得的系统特征码
UINT uSystemInfoLen = 0; // 在程序执行完毕后，此处存储取得的系统特征码的长度


BOOL DoIdentify(HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
	PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
	PDWORD lpcbBytesReturned)
{
	// Set up data structures for IDENTIFY command.
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
	pSCIP->irDriveRegs.bFeaturesReg = 0;
	pSCIP->irDriveRegs.bSectorCountReg = 1;
	pSCIP->irDriveRegs.bSectorNumberReg = 1;
	pSCIP->irDriveRegs.bCylLowReg = 0;
	pSCIP->irDriveRegs.bCylHighReg = 0;

	// calc the drive number.
	pSCIP->irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);

	// The command can either be IDE identify or ATAPI identify.
	pSCIP->irDriveRegs.bCommandReg = bIDCmd;
	pSCIP->bDriveNumber = bDriveNum;
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;

	return DeviceIoControl(hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
		(LPVOID)pSCIP,
		sizeof(SENDCMDINPARAMS)-1,
		(LPVOID)pSCOP,
		sizeof(SENDCMDOUTPARAMS)+IDENTIFY_BUFFER_SIZE - 1,
		lpcbBytesReturned, NULL);
}

BOOL WinNTHDSerialNumAsScsiRead(BYTE* dwSerial, UINT* puSerialLen, UINT uMaxSerialLen)
{
	BOOL bInfoLoaded = FALSE;

	for (int iController = 0; iController < 2; ++iController)
	{
		HANDLE hScsiDriveIOCTL = 0;
		char   szDriveName[256];

		//  Try to get a handle to PhysicalDrive IOCTL, report failure
		//  and exit if can't.
		sprintf(szDriveName, "\\\\.\\Scsi%d:", iController);

		//  Windows NT, Windows 2000, any rights should do
		hScsiDriveIOCTL = CreateFileA(szDriveName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL);

		// if (hScsiDriveIOCTL == INVALID_HANDLE_VALUE)
		//    printf ("Unable to open SCSI controller %d, error code: 0x%lX\n",
		//            controller, GetLastError ());

		if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
		{
			int iDrive = 0;
			for (iDrive = 0; iDrive < 2; ++iDrive)
			{
				char szBuffer[sizeof(SRB_IO_CONTROL)+SENDIDLENGTH] = { 0 };

				SRB_IO_CONTROL* p = (SRB_IO_CONTROL*)szBuffer;
				SENDCMDINPARAMS* pin = (SENDCMDINPARAMS*)(szBuffer + sizeof(SRB_IO_CONTROL));
				DWORD dwResult;

				p->HeaderLength = sizeof(SRB_IO_CONTROL);
				p->Timeout = 10000;
				p->Length = SENDIDLENGTH;
				p->ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
				strncpy((char*)p->Signature, "SCSIDISK", 8);

				pin->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
				pin->bDriveNumber = iDrive;

				if (DeviceIoControl(hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT,
					szBuffer,
					sizeof(SRB_IO_CONTROL)+sizeof(SENDCMDINPARAMS)-1,
					szBuffer,
					sizeof(SRB_IO_CONTROL)+SENDIDLENGTH,
					&dwResult, NULL))
				{
					SENDCMDOUTPARAMS* pOut = (SENDCMDOUTPARAMS*)(szBuffer + sizeof(SRB_IO_CONTROL));
					IDSECTOR* pId = (IDSECTOR*)(pOut->bBuffer);
					if (pId->sModelNumber[0])
					{
						if (*puSerialLen + 20U <= uMaxSerialLen)
						{
							// 序列号
							CopyMemory(dwSerial + *puSerialLen, ((USHORT*)pId) + 10, 20);
							UINT i = 0;
							// Cut off the trailing blanks
							for (i= 20; i != 0U && ' ' == dwSerial[*puSerialLen + i - 1]; --i)
							{
							}
							*puSerialLen += i;

							// 型号
							CopyMemory(dwSerial + *puSerialLen, ((USHORT*)pId) + 27, 40);
							// Cut off the trailing blanks
							for (i= 40; i != 0U && ' ' == dwSerial[*puSerialLen + i - 1]; --i)
							{
							}
							*puSerialLen += i;

							bInfoLoaded = TRUE;
						}
						else
						{
							::CloseHandle(hScsiDriveIOCTL);
							return bInfoLoaded;
						}
					}
				}
			}
			::CloseHandle(hScsiDriveIOCTL);
		}
	}
	return bInfoLoaded;
}

BOOL WinNTHDSerialNumAsPhysicalRead(BYTE* dwSerial, UINT* puSerialLen, UINT uMaxSerialLen)
{
#define  DFP_GET_VERSION          0x00074080
	BOOL bInfoLoaded = FALSE;

	for (UINT uDrive = 0; uDrive < 4; ++uDrive)
	{
		HANDLE hPhysicalDriveIOCTL = 0;

		//  Try to get a handle to PhysicalDrive IOCTL, report failure
		//  and exit if can't.
		TCHAR szDriveName[256];
		
		_stprintf(szDriveName, _T("\\\\.\\PhysicalDrive%d"), uDrive);

		//  Windows NT, Windows 2000, must have admin rights
		hPhysicalDriveIOCTL = CreateFile(szDriveName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL);

		if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
		{
			GETVERSIONOUTPARAMS VersionParams = { 0 };
			DWORD               cbBytesReturned = 0;

			// Get the version, etc of PhysicalDrive IOCTL
			if (DeviceIoControl(hPhysicalDriveIOCTL, DFP_GET_VERSION,
				NULL,
				0,
				&VersionParams,
				sizeof(GETVERSIONOUTPARAMS),
				&cbBytesReturned, NULL))
			{
				// If there is a IDE device at number "i" issue commands
				// to the device
				if (VersionParams.bIDEDeviceMap != 0)
				{
					BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
					SENDCMDINPARAMS  scip = { 0 };

					// Now, get the ID sector for all IDE devices in the system.
					// If the device is ATAPI use the IDE_ATAPI_IDENTIFY command,
					// otherwise use the IDE_ATA_IDENTIFY command
					bIDCmd = (VersionParams.bIDEDeviceMap >> uDrive & 0x10) ? IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;
					BYTE IdOutCmd[sizeof(SENDCMDOUTPARAMS)+IDENTIFY_BUFFER_SIZE - 1] = { 0 };

					if (DoIdentify(hPhysicalDriveIOCTL,
						&scip,
						(PSENDCMDOUTPARAMS)&IdOutCmd,
						(BYTE)bIDCmd,
						(BYTE)uDrive,
						&cbBytesReturned))
					{
						if (*puSerialLen + 20U <= uMaxSerialLen)
						{
							CopyMemory(dwSerial + *puSerialLen, ((USHORT*)(((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer)) + 10, 20);  // 序列号

							// Cut off the trailing blanks
							for (UINT i = 20; i != 0U && ' ' == dwSerial[*puSerialLen + i - 1]; --i)
							{
								*puSerialLen += i;
							}

							CopyMemory(dwSerial + *puSerialLen, ((USHORT*)(((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer)) + 27, 40); // 型号

							// Cut off the trailing blanks
							for (UINT i = 40; i != 0U && ' ' == dwSerial[*puSerialLen + i - 1]; --i)
							{
								*puSerialLen += i;
							}

							bInfoLoaded = TRUE;
						}
						else
						{
							::CloseHandle(hPhysicalDriveIOCTL);
							return bInfoLoaded;
						}
					}
				}
			}
			CloseHandle(hPhysicalDriveIOCTL);
		}
	}
	return bInfoLoaded;
}



int GetDiskNumer()
{
	// 硬盘序列号，注意：有的硬盘没有序列号
	{
		OSVERSIONINFO ovi = { 0 };
		ovi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&ovi);

		if (ovi.dwPlatformId != VER_PLATFORM_WIN32_NT)
		{
			// Only Windows 2000, Windows XP, Windows Server 2003...
			return FALSE;
		}
		else
		{
			if (!WinNTHDSerialNumAsPhysicalRead(szSystemInfo, &uSystemInfoLen, 1024))
			{
				WinNTHDSerialNumAsScsiRead(szSystemInfo, &uSystemInfoLen, 1024);
			}
		}
	}
}
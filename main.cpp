//#include <iostream>
//
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}



// DiskInfo.cpp : Defines the entry point for the console application.
//


#include <tchar.h>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <winioctl.h>
#include <cstddef>
#include <memory.h>

#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _IDENTIFY_DEVICE {
    WORD GeneralConfiguration;                    //0
    WORD LogicalCylinders;                        //1	Obsolete
    WORD SpecificConfiguration;                    //2
    WORD LogicalHeads;                            //3 Obsolete
    WORD Retired1[2];                            //4-5
    WORD LogicalSectors;                            //6 Obsolete
    DWORD ReservedForCompactFlash;                //7-8
    WORD Retired2;                                //9
    CHAR SerialNumber[20];                        //10-19
    WORD Retired3;                                //20
    WORD BufferSize;                                //21 Obsolete
//		WORD		Obsolute4;								//22
    CHAR FirmwareRev[8];                            //23-26
    CHAR Model[40];                                //27-46
    WORD MaxNumPerInterupt;                        //47
    WORD Reserved1;                                //48
    WORD Capabilities1;                            //49
    WORD Capabilities2;                            //50
    DWORD Obsolute5;                                //51-52
    WORD Field88and7064;                            //53
    WORD Obsolute6[5];                            //54-58
    WORD MultSectorStuff;                        //59
    DWORD TotalAddressableSectors;                //60-61
    WORD Obsolute7;                                //62
    WORD MultiWordDma;                            //63
    WORD PioMode;                                //64
    WORD MinMultiwordDmaCycleTime;                //65
    WORD RecommendedMultiwordDmaCycleTime;        //66
    WORD MinPioCycleTimewoFlowCtrl;                //67
    WORD MinPioCycleTimeWithFlowCtrl;            //68
    WORD Reserved2[6];                            //69-74
    WORD QueueDepth;                                //75
    WORD SerialAtaCapabilities;                    //76
    WORD SerialAtaAdditionalCapabilities;        //77
    WORD SerialAtaFeaturesSupported;                //78
    WORD SerialAtaFeaturesEnabled;                //79
    WORD MajorVersion;                            //80
    WORD MinorVersion;                            //81
    WORD CommandSetSupported1;                    //82
    WORD CommandSetSupported2;                    //83
    WORD CommandSetSupported3;                    //84
    WORD CommandSetEnabled1;                        //85
    WORD CommandSetEnabled2;                        //86
    WORD CommandSetDefault;                        //87
    WORD UltraDmaMode;                            //88
    WORD TimeReqForSecurityErase;                //89
    WORD TimeReqForEnhancedSecure;                //90
    WORD CurrentPowerManagement;                    //91
    WORD MasterPasswordRevision;                    //92
    WORD HardwareResetResult;                    //93
    WORD AcoustricManagement;                    //94
    WORD StreamMinRequestSize;                    //95
    WORD StreamingTimeDma;                        //96
    WORD StreamingAccessLatency;                    //97
    DWORD StreamingPerformance;                    //98-99
    ULONGLONG MaxUserLba;                                //100-103
    WORD StremingTimePio;                        //104
    WORD Reserved3;                                //105
    WORD SectorSize;                                //106
    WORD InterSeekDelay;                            //107
    WORD IeeeOui;                                //108
    WORD UniqueId3;                                //109
    WORD UniqueId2;                                //110
    WORD UniqueId1;                                //111
    WORD Reserved4[4];                            //112-115
    WORD Reserved5;                                //116
    DWORD WordsPerLogicalSector;                    //117-118
    WORD Reserved6[8];                            //119-126
    WORD RemovableMediaStatus;                    //127
    WORD SecurityStatus;                            //128
    WORD VendorSpecific[31];                        //129-159
    WORD CfaPowerMode1;                            //160
    WORD ReservedForCompactFlashAssociation[7];    //161-167
    WORD DeviceNominalFormFactor;                //168
    WORD DataSetManagement;                        //169
    WORD AdditionalProductIdentifier[4];            //170-173
    WORD Reserved7[2];                            //174-175
    CHAR CurrentMediaSerialNo[60];                //176-205
    WORD SctCommandTransport;                    //206
    WORD ReservedForCeAta1[2];                    //207-208
    WORD AlignmentOfLogicalBlocks;                //209
    DWORD WriteReadVerifySectorCountMode3;        //210-211
    DWORD WriteReadVerifySectorCountMode2;        //212-213
    WORD NvCacheCapabilities;                    //214
    DWORD NvCacheSizeLogicalBlocks;                //215-216
    WORD NominalMediaRotationRate;                //217
    WORD Reserved8;                                //218
    WORD NvCacheOptions1;                        //219
    WORD NvCacheOptions2;                        //220
    WORD Reserved9;                                //221
    WORD TransportMajorVersionNumber;            //222
    WORD TransportMinorVersionNumber;            //223
    WORD ReservedForCeAta2[10];                    //224-233
    WORD MinimumBlocksPerDownloadMicrocode;        //234
    WORD MaximumBlocksPerDownloadMicrocode;        //235
    WORD Reserved10[19];                            //236-254
    WORD IntegrityWord;                            //255
} IDENTIFY_DEVICE;

typedef enum _COMMAND_TYPE {
    CMD_TYPE_PHYSICAL_DRIVE = 0,
    CMD_TYPE_SCSI_MINIPORT,
    CMD_TYPE_SILICON_IMAGE,
    CMD_TYPE_SAT,                // SAT = SCSI_ATA_TRANSLATION
    CMD_TYPE_SUNPLUS,
    CMD_TYPE_IO_DATA,
    CMD_TYPE_LOGITEC,
    CMD_TYPE_JMICRON,
    CMD_TYPE_CYPRESS,
    CMD_TYPE_PROLIFIC,            // Not imprement
    CMD_TYPE_CSMI,                // CSMI = Common Storage Management Interface
    CMD_TYPE_CSMI_PHYSICAL_DRIVE, // CSMI = Common Storage Management Interface
    CMD_TYPE_WMI,
    CMD_TYPE_DEBUG
} COMMAND_TYPE;

// retrieve the properties of a storage device or adapter.
/*
typedef enum _STORAGE_QUERY_TYPE {
  PropertyStandardQuery = 0,
  PropertyExistsQuery,
  PropertyMaskQuery,
  PropertyQueryMaxDefined
} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;


// retrieve the properties of a storage device or adapter.

typedef struct _STORAGE_PROPERTY_QUERY {
  STORAGE_PROPERTY_ID  PropertyId;
  STORAGE_QUERY_TYPE  QueryType;
  UCHAR  AdditionalParameters[1];
} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;

*/
#define    FILE_DEVICE_SCSI                            0x0000001b
#define    IOCTL_SCSI_MINIPORT_IDENTIFY                ((FILE_DEVICE_SCSI << 16) + 0x0501)
#define    IOCTL_SCSI_MINIPORT_READ_SMART_ATTRIBS        ((FILE_DEVICE_SCSI << 16) + 0x0502)
#define IOCTL_SCSI_MINIPORT_READ_SMART_THRESHOLDS    ((FILE_DEVICE_SCSI << 16) + 0x0503)
#define IOCTL_SCSI_MINIPORT_ENABLE_SMART            ((FILE_DEVICE_SCSI << 16) + 0x0504)
#define IOCTL_SCSI_MINIPORT_DISABLE_SMART            ((FILE_DEVICE_SCSI << 16) + 0x0505)

#define IOCTL_SCSI_BASE                 FILE_DEVICE_CONTROLLER
#define IOCTL_SCSI_PASS_THROUGH         CTL_CODE(IOCTL_SCSI_BASE, 0x0401, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

//
// Define values for pass-through DataIn field.
//
#define SCSI_IOCTL_DATA_OUT          0
#define SCSI_IOCTL_DATA_IN           1
#define SCSI_IOCTL_DATA_UNSPECIFIED  2

//
// Define the SCSI pass through structure.
//
typedef struct _SCSI_PASS_THROUGH {
    USHORT Length;
    UCHAR ScsiStatus;
    UCHAR PathId;
    UCHAR TargetId;
    UCHAR Lun;
    UCHAR CdbLength;
    UCHAR SenseInfoLength;
    UCHAR DataIn;
    ULONG DataTransferLength;
    ULONG TimeOutValue;
    ULONG_PTR DataBufferOffset;
    ULONG SenseInfoOffset;
    UCHAR Cdb[16];
} SCSI_PASS_THROUGH, *PSCSI_PASS_THROUGH;

typedef struct _SCSI_PASS_THROUGH_WITH_BUFFERS {
    SCSI_PASS_THROUGH Spt;
    ULONG Filler;      // realign buffers to double word boundary
    UCHAR SenseBuf[32];
    UCHAR DataBuf[512];
} SCSI_PASS_THROUGH_WITH_BUFFERS, *PSCSI_PASS_THROUGH_WITH_BUFFERS;

static void dump_buffer(const char *title, const unsigned char *buffer, int len) {
    int i = 0;
    int j;

    printf("\n-- %s --\n", title);
    if (len > 0) {
        printf("%8.8s ", " ");
        for (j = 0; j < 16; ++j) {
            printf(" %2X", j);
        }
        printf("  ");
        for (j = 0; j < 16; ++j) {
            printf("%1X", j);
        }
        printf("\n");
    }
    while (i < len) {
        printf("%08x ", i);
        for (j = 0; j < 16; ++j) {
            if ((i + j) < len)
                printf(" %02x", (int) buffer[i + j]);
            else
                printf("   ");
        }
        printf("  ");
        for (j = 0; j < 16; ++j) {
            if ((i + j) < len)
                printf("%c", isprint(buffer[i + j]) ? buffer[i + j] : '.');
            else
                printf(" ");
        }
        printf("\n");
        i += 16;
    }
    printf("-- DONE --\n");
}

void ChangeByteOrder(PCHAR szString, USHORT uscStrSize) {
    USHORT i;
    CHAR temp;

    for (i = 0; i < uscStrSize; i += 2) {
        temp = szString[i];
        szString[i] = szString[i + 1];
        szString[i + 1] = temp;
    }
}

BOOL DoIdentifyDeviceSat(HANDLE physicalDriveId, BYTE target, IDENTIFY_DEVICE *data, COMMAND_TYPE type) {
    BOOL bRet;
    HANDLE hIoCtrl;
    DWORD dwReturned;
    DWORD length;

    SCSI_PASS_THROUGH_WITH_BUFFERS sptwb;

    if (data == NULL) {
        printf("Data\n");
        return FALSE;
    }

    ZeroMemory(data, sizeof(IDENTIFY_DEVICE));

    hIoCtrl = physicalDriveId;
    if (hIoCtrl == INVALID_HANDLE_VALUE) {
        printf("Handle\n");
        return FALSE;
    }

    ZeroMemory(&sptwb, sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS));

    sptwb.Spt.Length = sizeof(SCSI_PASS_THROUGH);
    sptwb.Spt.PathId = 0;
    sptwb.Spt.TargetId = 0;
    sptwb.Spt.Lun = 0;
    sptwb.Spt.SenseInfoLength = 24;
    sptwb.Spt.DataIn = SCSI_IOCTL_DATA_IN;
    sptwb.Spt.DataTransferLength = IDENTIFY_BUFFER_SIZE;
    sptwb.Spt.TimeOutValue = 2;
    sptwb.Spt.DataBufferOffset = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS, DataBuf);
    sptwb.Spt.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS, SenseBuf);

    if (type == CMD_TYPE_SAT) {
        sptwb.Spt.CdbLength = 12;
        sptwb.Spt.Cdb[0] = 0xA1;//ATA PASS THROUGH(12) OPERATION CODE(A1h)
        sptwb.Spt.Cdb[1] = (4 << 1) | 0; //MULTIPLE_COUNT=0,PROTOCOL=4(PIO Data-In),Reserved
        sptwb.Spt.Cdb[2] =
                (1 << 3) | (1 << 2) | 2;//OFF_LINE=0,CK_COND=0,Reserved=0,T_DIR=1(ToDevice),BYTE_BLOCK=1,T_LENGTH=2
        sptwb.Spt.Cdb[3] = 0;//FEATURES (7:0)
        sptwb.Spt.Cdb[4] = 1;//SECTOR_COUNT (7:0)
        sptwb.Spt.Cdb[5] = 0;//LBA_LOW (7:0)
        sptwb.Spt.Cdb[6] = 0;//LBA_MID (7:0)
        sptwb.Spt.Cdb[7] = 0;//LBA_HIGH (7:0)
        sptwb.Spt.Cdb[8] = target;
        sptwb.Spt.Cdb[9] = 0xEC;//COMMAND
    } else if (type == CMD_TYPE_SUNPLUS) {
        sptwb.Spt.CdbLength = 12;
        sptwb.Spt.Cdb[0] = 0xF8;
        sptwb.Spt.Cdb[1] = 0x00;
        sptwb.Spt.Cdb[2] = 0x22;
        sptwb.Spt.Cdb[3] = 0x10;
        sptwb.Spt.Cdb[4] = 0x01;
        sptwb.Spt.Cdb[5] = 0x00;
        sptwb.Spt.Cdb[6] = 0x01;
        sptwb.Spt.Cdb[7] = 0x00;
        sptwb.Spt.Cdb[8] = 0x00;
        sptwb.Spt.Cdb[9] = 0x00;
        sptwb.Spt.Cdb[10] = target;
        sptwb.Spt.Cdb[11] = 0xEC; // ID_CMD
    } else if (type == CMD_TYPE_IO_DATA) {
        sptwb.Spt.CdbLength = 12;
        sptwb.Spt.Cdb[0] = 0xE3;
        sptwb.Spt.Cdb[1] = 0x00;
        sptwb.Spt.Cdb[2] = 0x00;
        sptwb.Spt.Cdb[3] = 0x01;
        sptwb.Spt.Cdb[4] = 0x01;
        sptwb.Spt.Cdb[5] = 0x00;
        sptwb.Spt.Cdb[6] = 0x00;
        sptwb.Spt.Cdb[7] = target;
        sptwb.Spt.Cdb[8] = 0xEC;  // ID_CMD
        sptwb.Spt.Cdb[9] = 0x00;
        sptwb.Spt.Cdb[10] = 0x00;
        sptwb.Spt.Cdb[11] = 0x00;
    } else if (type == CMD_TYPE_LOGITEC) {
        sptwb.Spt.CdbLength = 10;
        sptwb.Spt.Cdb[0] = 0xE0;
        sptwb.Spt.Cdb[1] = 0x00;
        sptwb.Spt.Cdb[2] = 0x00;
        sptwb.Spt.Cdb[3] = 0x00;
        sptwb.Spt.Cdb[4] = 0x00;
        sptwb.Spt.Cdb[5] = 0x00;
        sptwb.Spt.Cdb[6] = 0x00;
        sptwb.Spt.Cdb[7] = target;
        sptwb.Spt.Cdb[8] = 0xEC;  // ID_CMD
        sptwb.Spt.Cdb[9] = 0x4C;
    } else if (type == CMD_TYPE_JMICRON) {
        sptwb.Spt.CdbLength = 12;
        sptwb.Spt.Cdb[0] = 0xDF;
        sptwb.Spt.Cdb[1] = 0x10;
        sptwb.Spt.Cdb[2] = 0x00;
        sptwb.Spt.Cdb[3] = 0x02;
        sptwb.Spt.Cdb[4] = 0x00;
        sptwb.Spt.Cdb[5] = 0x00;
        sptwb.Spt.Cdb[6] = 0x01;
        sptwb.Spt.Cdb[7] = 0x00;
        sptwb.Spt.Cdb[8] = 0x00;
        sptwb.Spt.Cdb[9] = 0x00;
        sptwb.Spt.Cdb[10] = target;
        sptwb.Spt.Cdb[11] = 0xEC; // ID_CMD
    } else if (type == CMD_TYPE_CYPRESS) {
        sptwb.Spt.CdbLength = 16;
        sptwb.Spt.Cdb[0] = 0x24;
        sptwb.Spt.Cdb[1] = 0x24;
        sptwb.Spt.Cdb[2] = 0x00;
        sptwb.Spt.Cdb[3] = 0xBE;
        sptwb.Spt.Cdb[4] = 0x01;
        sptwb.Spt.Cdb[5] = 0x00;
        sptwb.Spt.Cdb[6] = 0x00;
        sptwb.Spt.Cdb[7] = 0x01;
        sptwb.Spt.Cdb[8] = 0x00;
        sptwb.Spt.Cdb[9] = 0x00;
        sptwb.Spt.Cdb[10] = 0x00;
        sptwb.Spt.Cdb[11] = target;
        sptwb.Spt.Cdb[12] = 0xEC; // ID_CMD
        sptwb.Spt.Cdb[13] = 0x00;
        sptwb.Spt.Cdb[14] = 0x00;
        sptwb.Spt.Cdb[15] = 0x00;
    } else {
        return FALSE;
    }

    length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS, DataBuf) + sptwb.Spt.DataTransferLength;

    bRet = DeviceIoControl(hIoCtrl, IOCTL_SCSI_PASS_THROUGH,
                           &sptwb, sizeof(SCSI_PASS_THROUGH),
                           &sptwb, length, &dwReturned, NULL);

    CloseHandle(hIoCtrl);

    if (bRet == FALSE || dwReturned != length) {
        return FALSE;
    }

    memcpy(data, sptwb.DataBuf, sizeof(IDENTIFY_DEVICE));

    return TRUE;
}


int main(int argc, char *argv[]) {
    HANDLE hDevice = NULL;
    STORAGE_PROPERTY_QUERY sQuery;
    STORAGE_DEVICE_DESCRIPTOR *pDescriptor;
    char *model, *firmware, *serialnumber;
    char usb_hdd_model[41], usb_hdd_firmware[9], usb_hdd_Serialnumber[21];
    IDENTIFY_DEVICE identify = {0};
    char pcbData[4096];
    int dwLen = 4096;
    DWORD dwRet;
    BOOL bRet;
    char baseDeviceName[100];
    // 空判
    if (argv[1] == NULL) {
        return -1;
    };
    // copy 到变量
    strcpy(baseDeviceName, argv[1]);
    if (baseDeviceName == NULL) {
        return -1;
    };
    char deviceName[100] = "\\\\.\\PhysicalDrive";
    // 连接string
    strcat(deviceName, baseDeviceName);
    hDevice = CreateFileA(deviceName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                          OPEN_EXISTING, 0, NULL);
    // 如果没有管理员权限会抱错 2020.1
    if (hDevice == INVALID_HANDLE_VALUE) {
        printf("NEED SUPER ADMIN");
//		fprintf(stderr, "CreateFile()\n");
        exit(1);
    }

    memset(pcbData, 0, 4096);
    sQuery.PropertyId = StorageDeviceProperty;
    sQuery.QueryType = PropertyStandardQuery;

    bRet = DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY, &sQuery, sizeof(STORAGE_PROPERTY_QUERY), pcbData,
                           dwLen, &dwRet, NULL);
    if (bRet) {
        pDescriptor = (STORAGE_DEVICE_DESCRIPTOR *) pcbData;
        if (pDescriptor->BusType == BusTypeUsb) {
            printf("USB-Type\n");
        }

        if (pDescriptor->ProductIdOffset) {
            model = (char *) pDescriptor + pDescriptor->ProductIdOffset;
            printf("Model: %s\n", model);
        }
        if (pDescriptor->ProductRevisionOffset) {
            firmware = (char *) pDescriptor + pDescriptor->ProductRevisionOffset;
            printf("Firmware: %s\n", firmware);
        }
        if (pDescriptor->SerialNumberOffset) {
            serialnumber = (char *) pDescriptor + pDescriptor->SerialNumberOffset;
            printf("Serial number: %s\n", serialnumber);
        }
    }
/*
		CMD_TYPE_SAT,				// SAT = SCSI_ATA_TRANSLATION
		CMD_TYPE_SUNPLUS,
		CMD_TYPE_IO_DATA,
		CMD_TYPE_LOGITEC,
		CMD_TYPE_JMICRON,
		CMD_TYPE_CYPRESS,
*/
    if (DoIdentifyDeviceSat(hDevice, 0xa0, &identify, CMD_TYPE_SAT)) {
        printf("0xA0-CMD_TYPE_SAT-Return ok");
    } else if (DoIdentifyDeviceSat(hDevice, 0xa0, &identify, CMD_TYPE_SUNPLUS)) {
        printf("0xA0-CMD_TYPE_SUNPLUS-Return ok");
    } else if (DoIdentifyDeviceSat(hDevice, 0xa0, &identify, CMD_TYPE_IO_DATA)) {
        printf("0xA0-CMD_TYPE_IO_DATA-Return ok");
    } else if (DoIdentifyDeviceSat(hDevice, 0xa0, &identify, CMD_TYPE_LOGITEC)) {
        printf("0xA0-CMD_TYPE_LOGITEC-Return ok");
    } else if (DoIdentifyDeviceSat(hDevice, 0xa0, &identify, CMD_TYPE_JMICRON)) {
        printf("0xA0-CMD_TYPE_JMICRON-Return ok");
    } else if (DoIdentifyDeviceSat(hDevice, 0xb0, &identify, CMD_TYPE_SAT)) {
        printf("0xB0-CMD_TYPE_SAT-Return ok");
    } else if (DoIdentifyDeviceSat(hDevice, 0xb0, &identify, CMD_TYPE_SUNPLUS)) {
        printf("0xB0-CMD_TYPE_SUNPLUS-Return ok");
    } else if (DoIdentifyDeviceSat(hDevice, 0xb0, &identify, CMD_TYPE_IO_DATA)) {
        printf("0xB0-CMD_TYPE_IO_DATA-Return ok");
    } else if (DoIdentifyDeviceSat(hDevice, 0xb0, &identify, CMD_TYPE_LOGITEC)) {
        printf("0xB0-CMD_TYPE_LOGITEC-Return ok");
    } else if (DoIdentifyDeviceSat(hDevice, 0xb0, &identify, CMD_TYPE_JMICRON)) {
        printf("0xB0-CMD_TYPE_JMICRON-Return ok");
    } else {
        printf("Return ng\n");
    }

#define debug 0
#if debug
    dump_buffer("data", (const unsigned char *)&identify, sizeof(IDENTIFY_DEVICE));
#endif

    memcpy(usb_hdd_model, identify.Model, 40);
    ChangeByteOrder(usb_hdd_model, 40);
    usb_hdd_model[40] = '\0';

    memcpy(usb_hdd_firmware, identify.FirmwareRev, 8);
    ChangeByteOrder(usb_hdd_firmware, 8);
    usb_hdd_firmware[8] = '\0';

    memcpy(usb_hdd_Serialnumber, identify.SerialNumber, 20);
    ChangeByteOrder(usb_hdd_Serialnumber, 20);
    usb_hdd_Serialnumber[20] = '\0';

    printf("\nUSB-HDD   Model  name: %s", usb_hdd_model);
    printf("\nUSB-HDD Firmware  Rev: %s", usb_hdd_firmware);
    printf("\nUSB-HDD Serial number: %s", usb_hdd_Serialnumber);
    return 0;
}

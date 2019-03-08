#include <cstdarg>
#include <cstdint>
#include <cstdlib>

static const uint64_t IdStore_DT_DIR = 4;

static const uint64_t IdStore_DT_REG = 1;

static const uint32_t NX_FATDRIVE_ERR_DRIVE_DISCONNECTED = 1786;

static const uint32_t NX_FATDRIVE_ERR_DRIVE_NOT_FOUND = 1018;

static const uint32_t NX_FATDRIVE_ERR_FS_PREFIX = 262144;

static const uint32_t NX_FATDRIVE_ERR_MBR_PREFIX = 393216;

static const uint32_t NX_FATDRIVE_ERR_MODULE = 250;

static const uint32_t NX_FATDRIVE_ERR_NOT_IMPLEMENTED = 506;

static const uint32_t NX_FATDRIVE_ERR_NOT_INITIALIZED = 762;

static const uint32_t NX_FATDRIVE_ERR_POISSENED_MUTEX = 1274;

static const uint32_t NX_FATDRIVE_ERR_SCSI_PREFIX = 327680;

static const uint32_t NX_FATDRIVE_ERR_STDIO_PREFIX = 131072;

static const uint32_t SUCCESS = 0;

extern "C" {

uint32_t usbFsCloseDir(uint64_t dirid);

uint32_t usbFsCloseFile(uint64_t fileid);

uint32_t usbFsCreateDir(const uint8_t *dirpath);

uint32_t usbFsDeleteDir(const uint8_t *dirpath);

uint32_t usbFsDeleteFile(const uint8_t *filepath);

uint32_t usbFsDeviceGetMountStatus();

void usbFsDeviceRegister();

uint32_t usbFsDeviceUpdate();

void usbFsExit();

uint32_t usbFsGetMountStatus(uint64_t *status);

uint32_t usbFsInitialize();

uint32_t usbFsIsInitialized();

uint32_t usbFsIsReady();

uint32_t usbFsOpenDir(uint64_t *dirid, const uint8_t *dirpath);

uint32_t usbFsOpenFile(uint64_t *fileid, const uint8_t *filepath, uint64_t _mode);

uint32_t usbFsReadDir(uint64_t dirid,
                      uint64_t *type_ptr,
                      uint64_t *size,
                      uint8_t *name,
                      uintptr_t namemax);

uint32_t usbFsReadFile(uint64_t fileid, uint8_t *buffer, uintptr_t size, uintptr_t *retsize);

uint32_t usbFsReadRaw(uint64_t sector, uint64_t sectorcount, const uint8_t *buffer);

uint32_t usbFsSeekFile(uint64_t fileid, uint64_t pos, uint64_t whence, uint64_t *retpos);

uint32_t usbFsStatFile(uint64_t fileid, uint64_t *size, uint64_t *mode);

uint32_t usbFsStatFilesystem(uint64_t *totalsize, uint64_t *freesize);

uint32_t usbFsStatPath(const uint8_t *path_ptr, uint64_t *size, uint64_t *mode);

uint32_t usbFsSyncFile(uint64_t fileid);

uint32_t usbFsTruncateFile(uint64_t fileid, uint64_t _size);

uint32_t usbFsWriteFile(uint64_t fileid, uint8_t *buffer, uintptr_t size, uintptr_t *retsize);

} // extern "C"

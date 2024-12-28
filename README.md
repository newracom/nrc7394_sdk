# NRC7394 Standalone SDK Package

## Notice

> [!NOTE]
> The NRC7394 software package v1.0 includes an upgraded data structure for calibration and sysconfig. Therefore, to calibrate NRC7394 EVK, the v3.3.0 (Test Version 3.2) calibration tool (MFGT) should be used, and the EVK should be run on the NRC7394 software package v1.0 after it has been calibrated with the v3.3.0 (Test Version 3.2) calibration tool (MFGT). You can download this tool from the partner's FTP site.

> [!CAUTION]
> The software package released here is specifically designed for the NRC7394 EVK, and the accompanying board data file in https://github.com/newracom/nrc7394_sdk/tree/master/package/bdf/nrc7394 is intended solely for this model.
> If users plan to use this software package with other devices that incorporate the NRC7394 chip, they should utilize the board data file supplied by the device's vendor.

### Release roadmap
- v1.3.2 (2024.12.27) (hotfix)
- v1.3.1 (2024.12.13) (hotfix)
- v1.3 (2024.11.22)
- v1.2.2 (2024.06.21) (hotfix)
- v1.2.1 (2024.04.30) (hotfix)
- v1.2 (2023.11.30)
- v1.1 (2023.08.17)
- v1.0 (2023.08.07)

### Latest release
- [NRC7394_Standalone_SDK_v1.3.2](https://github.com/newracom/nrc7394_sdk/releases/tag/v1.3.2)
  - WPA3-SAE H2E is enabled by default.
  - Please refer to the [UG-7394-008-Memory_Map.pdf](https://github.com/newracom/nrc7394_sdk/blob/master/package/doc/UG-7394-008-Memory_Map.pdf) for the latest memory map updates.
  - The default build configuration is designed for 4MB flash memory. If you are using a 2MB flash memory module, please include the ALIAS "+2m" option. 
    - (ex) make select target=nrc7394.sdk.release+2m APP_NAME=ATCMD_UART  
  - When using 2MB flash memory, some applications may not support certain features. For instance, in ATCMD, the following features are not available: WPS, CONT_TX, IPV6 and FOTA with HTTPS.

### Release package contents
- NRC7394 standalone SDK package for global regulatory domains

## NRC7394 Standalone SDK User Guide
### Get NRC7394 Standalone SDK Package
NRC7394 Standalone SDK package is provided in this repository. Please use the following git command to get it.
```
cd ~/
git clone https://github.com/newracom/nrc7394_sdk.git
```

### Get the detailed user guide
Please refer to [UG-7394-004-Standalone SDK.pdf](https://github.com/newracom/nrc7394_sdk/blob/master/package/doc/UG-7394-004-Standalone%20SDK.pdf) in doc directory. 

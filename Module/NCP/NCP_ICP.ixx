//==========================================================================================================
// @file	:	NCP_ICP
// @author	:	NAGISA
// @data	:	2023/1/14 20:35:05
// @brief	:	
//==========================================================================================================
module;

#include "NCP/NCP_Defined_Macro.h"
#include "Nagisa/NGF_Base.h"

export module NCP_ICP;
import NGF_Defined;
import NCP_IHardware;
import "Nagisa/NGF_Object.h";

NCP_BEGIN
USE_NGF_TYPE
USE_NGF

export
class ICP :/*virtual*/ public NGF_Object{
public:
    /*virtual ~ICP() {
        _pHardWare = nullptr;
    }*/

    virtual VOID WriteBytes(PCBYTE pByte, SIZE_T32 size) = 0;
    virtual PBYTE ReadBytes(SIZE_T32 size) = 0;

    virtual VOID WriteByte(BYTE byte) = 0;
    virtual BYTE ReadByte() = 0;
};

NCP_END

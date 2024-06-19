//==========================================================================================================
// @file	:	NCP_SPI
// @author	:	NAGISA
// @data	:	2023/1/14 20:54:19
// @brief	:	
//==========================================================================================================
module;

#include "NCP/NCP_Defined_Macro.h"
#include "Nagisa/NGS_Macro.h"

export module NCP_SPI;
import NGS_Defined;
import NCP_Concepts;
import "Nagisa/NGS_Object.h";

NCP_BEGIN
USE_NGS_TYPE
USE_NGS

export
class SPI final:public NGS_Object {
public:
    virtual ~SPI() = 0;

    template<NCP_SUP_SPI IHW_SUP_SPI>
    static VOID WriteBytes(IHW_SUP_SPI* pHardware, PCBYTE pByte, SIZE_T32 size);
    template<NCP_SUP_SPI IHW_SUP_SPI>
    static PBYTE ReadBytes(IHW_SUP_SPI* pHardware, SIZE_T32 size);

    template<NCP_SUP_SPI IHW_SUP_SPI>
    inline static VOID WriteByte(IHW_SUP_SPI* pHardware, BYTE byte);
    template<NCP_SUP_SPI IHW_SUP_SPI>
    inline static BYTE ReadByte(IHW_SUP_SPI* pHardware);
};

template<NCP_SUP_SPI IHW_SUP_SPI>
VOID SPI::WriteBytes(IHW_SUP_SPI* pHardware, PCBYTE pByte, SIZE_T32 size)
{

    return VOID();
}
template<NCP_SUP_SPI IHW_SUP_SPI>
PBYTE SPI::ReadBytes(IHW_SUP_SPI* pHardware, SIZE_T32 size)
{
    return PBYTE();
}
template<NCP_SUP_SPI IHW_SUP_SPI>
inline VOID SPI::WriteByte(IHW_SUP_SPI* pHardware, BYTE byte)
{
    return VOID();
}
template<NCP_SUP_SPI IHW_SUP_SPI>
inline BYTE SPI::ReadByte(IHW_SUP_SPI* pHardware)
{
    return 0;
}

NCP_END



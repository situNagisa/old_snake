//==========================================================================================================
// @file	:	NCP_IIC
// @author	:	NAGISA
// @data	:	2023/1/14 22:33:12
// @brief	:	
//==========================================================================================================
module;
#include "NCP/NCP_Defined_Macro.h"
#include "Nagisa/NGS_Macro.h"

export module NCP_IIC;
import NCP_Concepts;
import NGS_Defined;
import "Nagisa/NGS_Object.h";

NCP_BEGIN
USE_NGS_TYPE
USE_NGS

export
class IIC final :public NGS_Object {
public:
    virtual ~IIC() = 0;

    template<NCP_SUP_SPI IHW_SUP_IIC>
    static VOID WriteBytes(IHW_SUP_IIC* pHardware, PCBYTE pByte, SIZE_T32 size);
    template<NCP_SUP_SPI IHW_SUP_IIC>
    static PBYTE ReadBytes(IHW_SUP_IIC* pHardware, SIZE_T32 size);

    template<NCP_SUP_SPI IHW_SUP_IIC>
    inline static VOID WriteByte(IHW_SUP_IIC* pHardware, BYTE byte);
    template<NCP_SUP_SPI IHW_SUP_IIC>
    inline static BYTE ReadByte(IHW_SUP_IIC* pHardware);
};
template<NCP_SUP_SPI IHW_SUP_IIC>
VOID IIC::WriteBytes(IHW_SUP_IIC* pHardware, PCBYTE pByte, SIZE_T32 size)
{

    return VOID();
}
template<NCP_SUP_SPI IHW_SUP_IIC>
PBYTE IIC::ReadBytes(IHW_SUP_IIC* pHardware, SIZE_T32 size)
{
    return PBYTE();
}

template<NCP_SUP_SPI IHW_SUP_IIC>
inline VOID IIC::WriteByte(IHW_SUP_IIC* pHardware, BYTE byte)
{
    return VOID();
}
template<NCP_SUP_SPI IHW_SUP_IIC>
inline BYTE IIC::ReadByte(IHW_SUP_IIC* pHardware)
{
    return 0;
}

NCP_END

//==========================================================================================================
// @file	:	NCP_Concepts
// @author	:	NAGISA
// @data	:	2023/1/14 22:36:46
// @brief	:	
//==========================================================================================================
module;
#include "NCP/NCP_Defined_Macro.h"
#include "Nagisa/NGS_Macro.h"

export module NCP_Concepts;
import NGS_Import;
import NCP_Defined;

export
NCP_BEGIN
USE_NGS_TYPE
USE_NGS

template<class T>
concept NCP_ICP = requires{
    T::WriteBytes;
    T::ReadBytes;
    T::WriteByte;
    T::ReadByte;
};

template<class T>
concept NCP_SUP_SPI = requires(){
    T::SCLK_High();
    T::SCLK_Low();
    T::SCLK_Get();

    T::MOSI_High();
    T::MOSI_Low();
    T::MOSI_Get;

    T::MISO_High();
    T::MISO_Low();
    T::MISO_Get;

    T::CS_High();
    T::CS_Low();
    T::CS_Get;
};

template<class T>
concept NCP_SUP_IIC = requires{
    T::SCL_High();
    T::SCL_Low();
    T::SCL_Get;

    T::SDA_High();
    T::SDA_Low();
    T::SDA_Get;
};


NCP_END

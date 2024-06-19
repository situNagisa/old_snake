//==========================================================================================================
// @file	:	NCP_Hardware
// @author	:	NAGISA
// @data	:	2023/1/14 22:13:23
// @brief	:	
//==========================================================================================================
module;
#include "NCP/NCP_Defined_Macro.h"
#include "Nagisa/NGF_Base.h"

export module NCP_IHardware;
import NGF_Defined;
import NCP_Concepts;
import "Nagisa/NGF_Object.h";

NCP_BEGIN
USE_NGF_TYPE
USE_NGF

export
typedef
class IHardware :public NGF_Object {
public:
    virtual ~IHardware() = 0;
} *PIHardware,*const PCIHardware;



NCP_END

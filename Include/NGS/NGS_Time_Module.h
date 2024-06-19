//==========================================================================================================
// @file	:	NGS_Time_Module
// @author	:	NAGISA
// @data	:	2023/2/14 14:48:11
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Time_Module
#define __HEAD_NGS_Time_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL_Macro.h"

NGS_BEGIN
using namespace std::literals::chrono_literals;

template<class defaultDuration = std::chrono::microseconds>
class Duration {
public:
    NGS_TYPE_DEFINE(std::chrono::high_resolution_clock, clock);
    NGS_TYPE_DEFINE(defaultDuration, duration);
    NGS_TYPE_DEFINE(std::chrono::time_point<__clock>, point);

    _TYP VOID Update() {
        auto now = __clock::now();
        _dt = std::chrono::duration_cast<__duration>(now - _current);
    }
    _TYP VOID Record() { _current = __clock::now(); }
    _TYP UINT64 DeltaCount()const { return _dt.count(); }
    __duration_ref Delta() { return _dt; }
    __duration_ref_cst Delta()const { return _dt; }

private:
    __point _current{};
    __duration _dt;
};

NGS_END

#endif // !__HEAD_NGS_Time_Module

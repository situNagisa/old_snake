//==========================================================================================================
// @file	:	NGS_Defined
// @author	:	NAGISA
// @data	:	2022/12/24 10:54:33
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Defined_Macro
#define __HEAD_NGS_Defined_Macro

//============================
//√¸√˚ø’º‰
//============================
#define NGS         ngs
#define _NGS        ::NGS::
#define NGS_BEGIN   namespace NGS{
#define NGS_END     };
#define USE_NGS     using namespace ::NGS;

#define _TYP            ::NGS::type::
#define NGS_TYPE        namespace type{
#define USE_NGS_TYPE    using namespace ::NGS::type;

#define _TYT                ::NGS::typetrait::
#define NGS_TYPE_TRAIT      namespace typetrait{
#define USE_NGS_TYTR        using namespace ::NGS::typetrait;

#define _CPT            ::NGS::concepts::
#define NGS_CONCEPT     namespace concepts{
#define USE_NGS_CONCEPT using namespace ::NGS::concepts;

#define NGS_INTERNAL        nagisa_internal
#define NGS_INTERNAL_BEGIN  namespace nagisa_internal{
#define NGS_USE_INTERNAL    using namespace ::NGS::nagisa_internal;


#define NGS_TYPE_DEFINE(type,id)        \
using __##id    = type;                 \
using __##id##_cst = const type;        \
using __##id##_ref = type&;             \
using __##id##_ref_cst = const type&;   \
using __##id##_ptr = type*;             \
using __##id##_ptr_cst = const type*;

#define _NGS_TYPE_DEFINE(type,id)   \
using id    = type;                 \
using P##id = type*;                \
using PC##id = const type*;

//#define _NGS_TYPE_DEFINE(type,id)   \
//using id    = type;                 \
//using C##id = const type;           \
//using R##id = type&;                \
//using RC##id = const type&;         \
//using P##id = type*;                \
//using PC##id = const type*;

#define NGS_DEFAULT_TYPE              \
NGS_TYPE_DEFINE(int,sign);              \
NGS_TYPE_DEFINE(unsigned int,unsign)    \
NGS_TYPE_DEFINE(size_t,size)

#define NGS_GET(functionName,prop)\
auto functionName(){return prop;}

#define NGS_SET(functionName,prop,type)\
_TYP VOID functionName(type v){prop = v;}

#define NGS_GET_REF(functionName,prop)\
auto& functionName(){return prop;}\
auto& functionName()const {return prop;}

#define NGS_FLAG_GET(functionName,flagName,bit)\
_TYP BOOL functionName()const{return Bits(flagName,bit);}

#define NGS_FLAG_SET(functionName,flagName,bit)\
_TYP VOID functionName(_TYP BOOL v){Bits(flagName,bit,v);}

#define NGS_FLAG(functionName,flagName,bit)\
_TYP BOOL functionName()const{return Bits(flagName,bit);}   \
_TYP VOID functionName(_TYP BOOL v){Bits(flagName,bit,v);}  

//============================
//…Ë÷√
//============================
#ifdef __cplusplus

#define NGS_C       extern "C"
#define NGS_C_BEGIN extern "C" {
#define NGS_C_END   };

#else

#define NGS_C       
#define NGS_C_BEGIN 
#define NGS_C_END   

#endif
//============================
//≤π≥‰
//============================
#define TRUE true
#define FALSE false

#endif // !__HEAD_NGS_Defined

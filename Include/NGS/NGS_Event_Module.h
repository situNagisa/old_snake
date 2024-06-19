//==========================================================================================================
// @file	:	NGS_Event_Module
// @author	:	NAGISA
// @data	:	2023/2/13 0:17:44
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Event_Module
#define __HEAD_NGS_Event_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL_Macro.h"
#include "NGS/NGS_Object.h"
#include "NGS/NGS_Bases.h"
#include "NGS/NGS_Function.h"

NGS_BEGIN
class Event : public Object, public TypeDefined<Event> {
public:
    NGS_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(std::wstring, string);
    NGS_TYPE_DEFINE(std::wstring_view, view);
    NGS_TYPE_DEFINE(_TYP PVOID, target);
    /*union _type {
        __string string;
        __sign id;

        _type(__string_ref_cst str):
            string(str)
        {}
        _type(__sign id) :
            id(id)
        {}
        _type(const _type& other){
            MemoryCopy(this, &other, sizeof(_type));
        }
        ~_type() noexcept {}

        _type& operator=(__string_ref_cst str) { string = str; }
        _type& operator=(__sign id) { this->id = id; }

        _TYP BOOL operator==(const _type& other) { return string == other.string || id == other.id; }
        _TYP BOOL operator==(__string_ref_cst str) { return string == str; }
        friend _TYP BOOL operator==(__string_ref_cst str,const _type& self) { return self == str; }
        _TYP BOOL operator==(__sign id) { return this->id == id; }
        friend _TYP BOOL operator==(__sign id, const _type& self) { return self == id; }

    };*/
    NGS_TYPE_DEFINE(__string, type);

public:
    NGS_CONSTEXPR Event(__string_ref_cst type):
        type(type)
    {}
    NGS_CONSTEXPR Event():
        type(L"")
    {}

    template<class T>
    T& CurrentTarget() { return *reinterpret_cast<T*>(currentTarget); }

    __type_cst type;
    __target target = nullptr;
    __target currentTarget = nullptr;
    _TYP PVOID param = nullptr;
};

class EventQueue : public Object, public TypeDefined<EventQueue> {
public:
    friend class EventDispatcher;

    NGS_TYPE_DEFINE(Event, evt);
    NGS_TYPE_DEFINE(_TYP SIZE_T32, size);
    NGS_TYPE_DEFINE(std::queue<__evt>, cache);

public:
    _TYP VOID Dispatch(__evt_ref event) {
        _queue.push(event);
    }
    __evt PopEvent() {
        auto e = _queue.front();
        _queue.pop();
        return e;

    }

    __size Length()const { return _queue.size(); }
private:
    __cache _queue;
};

struct EventListener : public Object{
    NGS_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(EventListener, this);
    NGS_TYPE_DEFINE(_TYP PVOID, target);
    NGS_TYPE_DEFINE(Event, evt);
    using callback = _TYP VOID(__evt_ref);
    using callback_ptr = _TYP VOID(*)(__evt_ref);
    NGS_TYPE_DEFINE(std::function<callback>, handler);

    __target currentTarget = nullptr;
    __handler handler;
    __sign priority = 0;

    EventListener( __handler_ref_cst handler, __target target = nullptr, __sign priority = 0) :
        currentTarget(target),
        handler(handler),
        priority(priority)
    {}

    auto operator<=>(__this_ref_cst other)const {
        return priority - other.priority;
    }
    _TYP BOOL operator==(__this_ref_cst other)const {
        return handler == other.handler;
    }
};

class EventDispatcher : public Object ,public TypeDefined<EventDispatcher>{
public:
    NGS_DEFAULT_TYPE;

    NGS_TYPE_DEFINE(std::wstring, string);
    NGS_TYPE_DEFINE(std::wstring_view, string_v);
    NGS_TYPE_DEFINE(Event, evt);
    NGS_TYPE_DEFINE(EventQueue, queue);

    using callback = _TYP VOID(__evt_ref);
    using callback_ptr = _TYP VOID(*)(__evt_ref);
    NGS_TYPE_DEFINE(std::function<callback>, handler);
    NGS_TYPE_DEFINE(EventListener, listener);
    NGS_TYPE_DEFINE(std::vector<__listener>, listeners);
    using __cache = std::map<__string, __listeners>;
    NGS_TYPE_DEFINE(__cache, cache);

public:
    /**
    * @brief ʹ�� EventDispatcher ����ע���¼�������������ʹ�������ܹ������¼�֪ͨ������Ϊ�ض����͵��¼����׶κ����ȼ�����ʾ�б��е����нڵ���ע���¼��������� 
    * 
    * @note �ɹ�ע��һ���¼����������޷�ͨ��������� addEventListener() �����������ȼ���Ҫ���������������ȼ����������ȵ��� removeListener()��Ȼ�󣬿���ʹ���µ����ȼ��ٴ�ע����������� 
    * @note ���ס��ע���������������������þ��в�ͬ type �� useCapture ֵ�� addEventListener()����ᴴ��������������ע�ᡣ���磬�������ע�� useCapture ����Ϊ true �������������������ֻ�ڲ���׶ν���������
    * @note ���ʹ��ͬһ�������������ٴε��� addEventListener()������ useCapture ����Ϊ false����ô���ӵ��������������������һ���ڲ���׶ν�����������һ����Ŀ���ð�ݽ׶ν��������� 
    * @note ����ֻΪĿ��׶λ�ð�ݽ׶�ע���¼�����������Щ�׶���ע���ڼ��ǳɶԳ��ֵģ���Ϊð�ݽ׶�ֻ������Ŀ��ڵ�������
    * @note ���������Ҫĳ���¼����������ɵ��� removeEventListener() ɾ���������������ڴ����⡣�¼������������Զ����ڴ���ɾ������ΪֻҪ���ȶ�����ڣ������������Ͳ���ɾ�������������� useWeakReference ��������Ϊ true����
    * @note ���� EventDispatcher ʵ��ʱ�����������и��ӵ��¼���������������½������Ľڵ���Ҫһ���¼��������������ڴ����ýڵ�󸽼Ӹ��������������ǣ�����ƶ� EventDispatcher ʵ���������и��ӵ��¼�������Ҳ����֮�ƶ���
    * @note ��������ڴ����¼��Ľڵ���ע���¼����������򲻻��ڵ�ǰ�׶δ����¼����������������¼������Ժ�׶δ�������ð�ݽ׶Ρ�
    * @note ��������ڴ����¼��Ľڵ���ɾ���¼�������������¼����������ɵ�ǰ����������ɾ���¼��������󣬾������ٴε��ø��¼��������������ٴ�ע���Ա����������� 
    * 
    * @param type:String �� �¼������͡�  
    * @param listener:Function �� �����¼����������������˺���������� Event ������Ϊ��Ψһ�Ĳ��������Ҳ��ܷ����κν������ʾ����ʾ��function(evt:Event):void 
    * @param useCapture:Boolean (default = false) �� ȷ���������������ڲ���׶λ���������Ŀ���ð�ݽ׶Ρ������ useCapture ����Ϊ true����������ֻ�ڲ���׶δ����¼���������Ŀ���ð�ݽ׶δ����¼������ useCapture Ϊ false����������ֻ��Ŀ���ð�ݽ׶δ����¼���Ҫ�����������׶ζ������¼�������� addEventListener ���Σ�һ�ν� useCapture ����Ϊ true��һ�ν� useCapture ����Ϊ false��  
    * @param priority:int (default = 0) �� �¼������������ȼ������ȼ���һ�������ŵ� 32 λ����ָ��������Խ�����ȼ�Խ�ߡ����ȼ�Ϊ n �������������������ȼ�Ϊ n -1 ��������֮ǰ�õ������������������������������ͬ�����ȼ����������ǵ����˳����д���Ĭ�����ȼ�Ϊ 0��  
    * 
    */
    _TYP VOID AddEventListener(__string type, __listener_ref_cst listener) {
        auto& listeners = _cache[type];
        listeners.push_back(listener);
        std::sort(listeners.begin(), listeners.end(), std::greater<__listener>());
    }
    /**
    * @brief ���¼����ȵ��¼����С��¼�Ŀ���Ƕ������ dispatchEvent() ������ EventDispatcher ����
    *
    * @param event:Event �� ���ȵ��¼����е� Event ��������������µ����¼�������Զ��������¼���һ����¡���ڵ������¼����� target ���Խ��޷����ģ���������봴�����¼���һ���¸������ܹ����µ��ȡ�
    *
    * @return ����ɹ��������¼�����ֵΪ true��ֵ false ��ʾʧ�ܻ���¼������� preventDefault()��
    */
    _TYP BOOL Dispatch(__evt_ref event) const{
        auto&& search = _cache.find(event.type);
        if (search == _cache.end())return FALSE;
        auto& listeners = search->second;
        for (auto& listener : listeners) {
            event.currentTarget = listener.currentTarget;
            listener.handler(event);
        }
            

        return TRUE;
    }
    _TYP BOOL Dispatch(__evt_ref_cst event) const {
        return Dispatch(const_cast<__evt_ref>(event));
    }
    _TYP VOID Dispatch(__queue_ref queue) const {
        while (queue.Length()) 
            Dispatch(queue.PopEvent());
    }
    /**
    * @brief ��� EventDispatcher �����Ƿ�Ϊ�ض��¼�����ע�����κ������������������Ϳ���ȷ�� EventDispatcher �������¼�����νṹ�е��ĸ�λ�øı��˶��¼����͵Ĵ���Ҫȷ���ض��¼������Ƿ�ȷʵ�������¼�����������ʹ�� willTrigger()�� 
    * @brief hasEventListener() �� willTrigger() �������ǣ�hasEventListener() ֻ����������Ķ��󣬶� willTrigger() ��������¼����Բ����� type ����ָ�����¼��� \
    * 
    * @param type:String �� �¼������͡� 
    * 
    * @return ���ָ�����͵���������ע�ᣬ��ֵΪ true������ֵΪ false�� 
    */
    _TYP BOOL HasEventListener(__string_ref_cst type)const {
        auto&& search = _cache.find(type);
        if (search == _cache.end())return FALSE;
        return FALSE;
    }
    /**
    * @brief �� EventDispatcher ������ɾ�������������û���� EventDispatcher ����ע���κ�ƥ�������������Դ˷����ĵ���û���κ�Ч���� 
    * 
    * @param type:String �� �¼������͡�  
    * @param listener:Function �� Ҫɾ��������������  
    * @param useCapture:Boolean (default = false) �� ָ����Ϊ����׶λ���ΪĿ���ð�ݽ׶�ע���������������Ϊ����׶��Լ�Ŀ���ð�ݽ׶�ע����������������Ҫ�� removeEventListener() �������ε��ò��ܽ�������������ɾ����һ�ε��ý� useCapture() ����Ϊ true����һ�ε��ý� useCapture() ����Ϊ false��  
    * 
    * 
    */
    _TYP VOID RemoveEventListener(__string_ref_cst type, __handler_ref_cst listener, _TYP BOOL useCapture = FALSE) {
        auto&& search = _cache.find(type);
        if (search == _cache.end())return;
        auto& listeners = search->second;
        __size i = 0;
        for (;i  < listeners.size();i ++)
            if (listeners[i].handler == listener)break;
        
        if (i >= listeners.size())return;
        listeners.erase(listeners.begin() + i);
    }
    _TYP BOOL WillTrigger(__string_ref_cst type) const;

private:
    __cache _cache;
};

NGS_END

#endif // !__HEAD_NGS_Event_Module

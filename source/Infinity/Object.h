#pragma once

#if 0	//compile error vs2012.
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#endif

#include <string>
#include <mutex>
#include <unordered_map>
#include <boost/type_traits/is_same.hpp>
#include <stdio.h>

namespace Infinity
{
	class Object
	{
	public:
		enum TICKGROUP {
			TICKGROUP_PARALLEL,
			TICKGROUP_SINGLE,
			TICKGROUP_MAX
		};

	private:
		static std::unordered_map<Object *,Object *> mObjects;
		std::string mName;
		TICKGROUP mTickGroup;
		std::mutex mMutex;

	protected:
		static void RegisterObjects(Object *obj);
		static void UnRegisterObjects(Object *obj);

	public:
		Object();
		~Object();

		virtual void Construct() = 0;
		virtual void Destruct() = 0;

	public:
		typedef Object Super;
		static int GetUUID() { return 0;}

		template<class Target,class ThisType, class Super>
		Target* CastBase( int id )
		{
			if( Super::GetID() == id ) {
				return (Target*)this;
			}
			if( boost::is_same<ThisType, typename ThisType::Super>::value ) {
				return nullptr;
			}
			return CastBase<Target, ThisType::Super, Target::Super>(id);
		}

		virtual void Create(const std::string &name, TICKGROUP group);
		virtual bool IsCreate();
		std::string GetName() const { return mName; }
		TICKGROUP GetTickGroup() const { return mTickGroup; }
		virtual void Tick() {}

		void* operator new ( size_t size )
		{
			return 0;
		}

		template<class T>
		static T *Allocate()
		{
			std::lock_guard<std::mutex> lock(TaskManager::getTaskMutex());
			T *mem = ::new(malloc(sizeof(T))) T;
			TaskManager::RegistTask(mem);
			return mem;
		}
	};

#define OBJECT_DECLARE_DECLARE(MyType, ParentType, TickGroup) \
public:											\
	typedef MyType ThisType;					\
	typedef ParentType Super;					\
	static int GetUUID() {return 1;}			\
	MyType() {									\
		Create(#MyType,TickGroup);				\
		Construct();							\
	} \
	virtual ~MyType() { \
		Destruct(); \
	} \
private:

	template<class Target>						\
		Target* Cast( ) { return CastBase<Target,ThisType,Super>(Target::GetID()); } \
}

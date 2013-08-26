#pragma once

#if 0	//compile error vs2012.
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#endif

#include <string>
#include <unordered_map>
#include <boost/type_traits/is_same.hpp>

namespace Infinity
{
	class Object
	{
		static std::unordered_map<Object *,Object *> mObjects;

		static void RegisterObjects(Object *obj);
		static void UnRegisterObjects(Object *obj);
		std::string mName;

	public:
		Object();
		~Object();

	public:
		typedef Object Super;
#if 0
		static boost::uuids::uuid GetUUID() { boost::uuids::string_generator()("InfinityObject"); }
#else
		static int GetUUID() { return 0;}
#endif

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

		void SetName( const std::string &name ) { mName = name; }
	};
#if 0	//compile error vs2012.
	#define OBJECT_DECLARE(MyType, ParentType)		\
	public:	\
		typedef MyType ThisType;	\
		typedef ParentType Super;	\
		static boost::uuids::uuid GetID() { \
			boost::uuids::name_generator gen(Object::GetUUID()); return gen("Infinity"###MyType);}	\
		template<class Target>				\
		Target* Cast( ) { return CastBase<Target,ThisType,Super>(T::GetID()); }	\
	private:
#else

#define OBJECT_DECLARE_DECLARE(MyType, ParentType, TickGroup) \
public:											\
	typedef MyType ThisType;					\
	typedef ParentType Super;					\
	static int GetID() {return 1;}				\
	template<class Target>						\
	Target* Cast( ) { return CastBase<Target,ThisType,Super>(Target::GetID()); } \
	MyType() { \
		SetName(#MyType); \
	} \
private:
#endif
}

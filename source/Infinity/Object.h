#pragma once

#if 0	//compile error vs2012.
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#endif

namespace Infinity
{
	class Object
	{
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
				return (T*)this;
			}
			if( boost::is_same<ThisType, ThisType::Super>::value ) {
				return nullptr;
			}
			return CastBase<Target, ThisType::Super, Target::Super>(id);
		}
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

#define OBJECT_DECLARE_BEGIN(MyType, ParentType)		\
	class MyType : public ParentType {			\
public:											\
	typedef MyType ThisType;					\
	typedef ParentType Super;					\
	static int GetID() {return 1;}				\
	template<class Target>						\
	Target* Cast( ) { return CastBase<Target,ThisType,Super>(T::GetID()); } \
private:
#endif
#define OBJECT_DECLARE_END() }
}

/* Auto-generated by genmsg_cpp for file /home/hubo/maestro/hubomsg/msg/HuboCmd.msg */
#ifndef HUBOMSG_BOOST_SERIALIZATION_HUBOCMD_H
#define HUBOMSG_BOOST_SERIALIZATION_HUBOCMD_H

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <hubomsg/HuboCmd.h>

namespace boost
{
namespace serialization
{

template<class Archive, class ContainerAllocator>
void serialize(Archive& a,  ::hubomsg::HuboCmd_<ContainerAllocator>  & m, unsigned int)
{
    a & make_nvp("joint",m.joint);
    a & make_nvp("angle",m.angle);
    a & make_nvp("msg",m.msg);
}

} // namespace serialization
} // namespace boost

#endif // HUBOMSG_BOOST_SERIALIZATION_HUBOCMD_H

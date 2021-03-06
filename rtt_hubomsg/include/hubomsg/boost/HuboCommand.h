/* Auto-generated by genmsg_cpp for file /opt/ros/fuerte/stacks/maestro/hubomsg/msg/HuboCommand.msg */
#ifndef HUBOMSG_BOOST_SERIALIZATION_HUBOCOMMAND_H
#define HUBOMSG_BOOST_SERIALIZATION_HUBOCOMMAND_H

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <hubomsg/HuboCommand.h>
#include "hubomsg/boost/HuboJointCommand.h"

namespace boost
{
namespace serialization
{

template<class Archive, class ContainerAllocator>
void serialize(Archive& a,  ::hubomsg::HuboCommand_<ContainerAllocator>  & m, unsigned int)
{
    a & make_nvp("joints",m.joints);
    a & make_nvp("num_joints",m.num_joints);
}

} // namespace serialization
} // namespace boost

#endif // HUBOMSG_BOOST_SERIALIZATION_HUBOCOMMAND_H


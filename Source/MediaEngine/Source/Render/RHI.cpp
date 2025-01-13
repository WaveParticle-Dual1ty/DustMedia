#include "MediaEngine/Include/Render/RHI.h"
#include "Vulkan/VulkanRHI.h"

namespace ME
{
std::shared_ptr<RHI> RHI::CreateRHI(API api)
{
    std::shared_ptr<RHI> res;
    switch (api)
    {
        case ME::RHI::API::Vulkan:
            res = std::make_shared<VulkanRHI>();
            break;
        default:
            break;
    }

    return res;
}
}  //namespace ME
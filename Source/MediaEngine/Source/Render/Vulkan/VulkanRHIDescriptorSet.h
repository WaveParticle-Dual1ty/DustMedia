#include "MediaEngine/Include/Render/RHIDescriptorSet.h"
#include <vector>
#include "vulkan/vulkan.h"

namespace ME
{
struct VulkanRHIDescriptorSet : RHIDescriptorSet
{
    std::vector<VkDescriptorSetLayoutBinding> DescriptorSetLayoutBindings;
    VkDescriptorSetLayout DescriptorSetLayout = VK_NULL_HANDLE;
    VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;
};
}  //namespace ME
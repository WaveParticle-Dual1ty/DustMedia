#pragma once
#include <cstdint>
#include <vector>
#include "MediaEngine/Include/Core/Ptr.h"
#include "RHIEnums.h"
#include "RHITexture.h"
#include "RHIResources.h"

namespace ME
{
struct RHIDescriptorSetBindingDesc
{
    uint32_t Binding = 0;
    ERHIDescriptorType DescriptorType = ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_SAMPLER;
    uint32_t DescriptorCount = 1;
    RHIShaderStageFlags ShaderStage = 0;

    RHIDescriptorSetBindingDesc() = default;

    RHIDescriptorSetBindingDesc(
        uint32_t binding,
        ERHIDescriptorType descriptorType,
        uint32_t descriptorCount,
        RHIShaderStageFlags shaderStage)
        : Binding(binding)
        , DescriptorType(descriptorType)
        , DescriptorCount(descriptorCount)
        , ShaderStage(shaderStage)
    {
    }
};

struct RHIDescriptorSetCreateInfo
{
    std::vector<RHIDescriptorSetBindingDesc> BindingDescs;

    RHIDescriptorSetCreateInfo() = default;

    RHIDescriptorSetCreateInfo(const std::initializer_list<RHIDescriptorSetBindingDesc>& bindingDescs)
        : BindingDescs(bindingDescs)
    {
    }
};

struct RHIDescriptorSet
{
    virtual ~RHIDescriptorSet() = default;

    std::vector<RHIDescriptorSetBindingDesc> BindingDescs;
};

struct RHIWriteDescriptorSet
{
    ERHIDescriptorType DescriptorType = ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_SAMPLER;
    uint32_t DstBinding = 0;
    uint32_t DstArrayElement = 0;
    Ref<RHITexture2D> Texture;
    Ref<RHISampler> Sampler;

    RHIWriteDescriptorSet() = default;

    RHIWriteDescriptorSet(
        ERHIDescriptorType descriptorType,
        uint32_t dstBinding,
        uint32_t dstArrayElement,
        Ref<RHITexture2D> texture)
        : DescriptorType(descriptorType)
        , DstBinding(dstBinding)
        , DstArrayElement(dstArrayElement)
        , Texture(texture)
    {
    }

    RHIWriteDescriptorSet(
        ERHIDescriptorType descriptorType,
        uint32_t dstBinding,
        uint32_t dstArrayElement,
        Ref<RHISampler> sampler)
        : DescriptorType(descriptorType)
        , DstBinding(dstBinding)
        , DstArrayElement(dstArrayElement)
        , Sampler(sampler)
    {
    }
};

}  //namespace ME
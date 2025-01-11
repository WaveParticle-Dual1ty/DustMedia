#include "LayerStack.h"

namespace ME
{
LayerStack::~LayerStack()
{
    for (auto& layer : m_Layers)
    {
        layer->OnDetach();
    }
}

void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
    layer->OnAttach();
}

void LayerStack::PushOverlay(std::shared_ptr<Layer> layer)
{
    m_Layers.emplace_back(layer);
    layer->OnAttach();
}

void LayerStack::PopLayer(std::shared_ptr<Layer> layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
    if (it != m_Layers.begin() + m_LayerInsertIndex)
    {
        layer->OnDetach();
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}

void LayerStack::PopOverlay(std::shared_ptr<Layer> layer)
{
    auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), layer);
    if (it != m_Layers.end())
    {
        layer->OnDetach();
        m_Layers.erase(it);
    }
}

const LayerStack::LayerList& LayerStack::GetLayers()
{
    return m_Layers;
}

}  //namespace ME
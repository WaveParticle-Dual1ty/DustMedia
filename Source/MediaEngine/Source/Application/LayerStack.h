#pragma once
#include <memory>
#include <vector>
#include "MediaEngine/Include/Application/Layer.h"

namespace ME
{
class LayerStack
{
public:
    ~LayerStack();

public:
    using LayerList = std::vector<std::shared_ptr<Layer>>;

    void PushLayer(std::shared_ptr<Layer> layer);
    void PushOverlay(std::shared_ptr<Layer> layer);
    void PopLayer(std::shared_ptr<Layer> layer);
    void PopOverlay(std::shared_ptr<Layer> layer);
    const LayerList& GetLayers();

private:
    LayerList m_Layers;
    std::size_t m_LayerInsertIndex = 0;
};
}  //namespace ME
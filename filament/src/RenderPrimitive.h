/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_FILAMENT_DETAILS_RENDERPRIMITIVE_H
#define TNT_FILAMENT_DETAILS_RENDERPRIMITIVE_H

#include "components/RenderableManager.h"

#include "details/MaterialInstance.h"

#include <backend/Handle.h>

#include <utils/compiler.h>

namespace filament {

class FEngine;
class FVertexBuffer;
class FIndexBuffer;
class FRenderer;
class HwRenderPrimitiveFactory;

class FRenderPrimitive {
public:
    FRenderPrimitive() noexcept = default;

    void init(HwRenderPrimitiveFactory& factory, backend::DriverApi& driver,
            const RenderableManager::Builder::Entry& entry) noexcept;

    void set(HwRenderPrimitiveFactory& factory, backend::DriverApi& driver,
            RenderableManager::PrimitiveType type,
            FVertexBuffer* vertices, FIndexBuffer* indices, size_t offset,
            size_t minIndex, size_t maxIndex, size_t count) noexcept;

    // frees driver resources, object becomes invalid
    void terminate(HwRenderPrimitiveFactory& factory, backend::DriverApi& driver);

    const FMaterialInstance* getMaterialInstance() const noexcept { return mMaterialInstance; }
    backend::Handle<backend::HwRenderPrimitive> getHwHandle() const noexcept { return mHandle; }
    backend::PrimitiveType getPrimitiveType() const noexcept { return mPrimitiveType; }
    AttributeBitset getEnabledAttributes() const noexcept { return mEnabledAttributes; }
    uint16_t getBlendOrder() const noexcept { return mBlendOrder; }
    bool isGlobalBlendOrderEnabled() const noexcept { return mGlobalBlendOrderEnabled; }
    const FVertexBuffer* getVertexBuffer() const noexcept { return mVertexBuffer; }
    const FIndexBuffer* getIndexBuffer() const noexcept { return mIndexBuffer; }

    void setMaterialInstance(FMaterialInstance const* mi) noexcept { mMaterialInstance = mi; }

    void setBlendOrder(uint16_t order) noexcept {
        mBlendOrder = static_cast<uint16_t>(order & 0x7FFF);
    }

    void setGlobalBlendOrderEnabled(bool enabled) noexcept {
        mGlobalBlendOrderEnabled = enabled;
    }

private:
    FMaterialInstance const* mMaterialInstance = nullptr;
    backend::Handle<backend::HwRenderPrimitive> mHandle = {};
    AttributeBitset mEnabledAttributes = {};
    uint16_t mBlendOrder = 0;
    bool mGlobalBlendOrderEnabled = false;
    backend::PrimitiveType mPrimitiveType = backend::PrimitiveType::TRIANGLES;
    FVertexBuffer *mVertexBuffer = nullptr;
    FIndexBuffer *mIndexBuffer = nullptr;
    UTILS_UNUSED uint8_t reserved[4] = {};
};

} // namespace filament

#endif // TNT_FILAMENT_DETAILS_RENDERPRIMITIVE_H

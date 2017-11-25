/******************************************************************************
* Spine Runtimes Software License v2.5
*
* Copyright (c) 2013-2016, Esoteric Software
* All rights reserved.
*
* You are granted a perpetual, non-exclusive, non-sublicensable, and
* non-transferable license to use, install, execute, and perform the Spine
* Runtimes software and derivative works solely for personal or internal
* use. Without the written permission of Esoteric Software (see Section 2 of
* the Spine Software License Agreement), you may not (a) modify, translate,
* adapt, or develop new applications using the Spine Runtimes or otherwise
* create derivative works or improvements of the Spine Runtimes or (b) remove,
* delete, alter, or obscure any trademarks or any copyright, trademark, patent,
* or other intellectual property or proprietary rights notices on or in the
* Software, including any copy thereof. Redistributions in binary or source
* form must include this license and terms.
*
* THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
* USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

#include <spine/DrawOrderTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Animation.h>
#include <spine/TimelineType.h>
#include <spine/Slot.h>
#include <spine/SlotData.h>

namespace Spine
{
    SPINE_RTTI_IMPL(DrawOrderTimeline, Timeline);
    
    DrawOrderTimeline::DrawOrderTimeline(int frameCount) : Timeline()
    {
        _frames.reserve(frameCount);
        _drawOrders.reserve(frameCount);
    }
    
    void DrawOrderTimeline::apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>& events, float alpha, MixPose pose, MixDirection direction)
    {
        Vector<Slot*>& drawOrder = skeleton._drawOrder;
        Vector<Slot*>& slots = skeleton._slots;
        if (direction == MixDirection_Out && pose == MixPose_Setup)
        {
            drawOrder.clear();
            drawOrder.reserve(slots.size());
            for (int i = 0, n = static_cast<int>(slots.size()); i < n; ++i)
            {
                drawOrder.push_back(slots[i]);
            }
            return;
        }
        
        if (time < _frames[0])
        {
            if (pose == MixPose_Setup)
            {
                drawOrder.clear();
                drawOrder.reserve(slots.size());
                for (int i = 0, n = static_cast<int>(slots.size()); i < n; ++i)
                {
                    drawOrder.push_back(slots[i]);
                }
            }
            return;
        }
        
        int frame;
        if (time >= _frames[_frames.size() - 1])
        {
            // Time is after last frame.
            frame = static_cast<int>(_frames.size()) - 1;
        }
        else
        {
            frame = Animation::binarySearch(_frames, time) - 1;
        }
        
        Vector<int>& drawOrderToSetupIndex = _drawOrders[frame];
        if (drawOrderToSetupIndex.size() == 0)
        {
            drawOrder.clear();
            for (int i = 0, n = static_cast<int>(slots.size()); i < n; ++i)
            {
                drawOrder.push_back(slots[i]);
            }
        }
        else
        {
            for (int i = 0, n = static_cast<int>(drawOrderToSetupIndex.size()); i < n; ++i)
            {
                drawOrder[i] = slots[drawOrderToSetupIndex[i]];
            }
        }
    }
    
    int DrawOrderTimeline::getPropertyId()
    {
        return ((int)TimelineType_DrawOrder << 24);
    }
    
    void DrawOrderTimeline::setFrame(int frameIndex, float time, Vector<int>& drawOrder)
    {
        _frames[frameIndex] = time;
        _drawOrders[frameIndex] = drawOrder;
    }
    
    Vector<float>& DrawOrderTimeline::getFrames()
    {
        return _frames;
    }
    
    void DrawOrderTimeline::setFrames(Vector<float>& inValue)
    {
        _frames = inValue;
    }
    
    Vector< Vector<int> >& DrawOrderTimeline::getDrawOrders()
    {
        return _drawOrders;
    }
    
    void DrawOrderTimeline::setDrawOrders(Vector< Vector<int> >& inValue)
    {
        _drawOrders = inValue;
    }
    
    int DrawOrderTimeline::getFrameCount()
    {
        return static_cast<int>(_frames.size());
    }
}

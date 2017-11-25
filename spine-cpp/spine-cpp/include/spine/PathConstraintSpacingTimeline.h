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

#ifndef Spine_PathConstraintSpacingTimeline_h
#define Spine_PathConstraintSpacingTimeline_h

#include <spine/PathConstraintPositionTimeline.h>

namespace Spine
{
    class PathConstraintSpacingTimeline : public PathConstraintPositionTimeline
    {
        SPINE_RTTI_DECL;
        
    public:
        PathConstraintSpacingTimeline(int frameCount);
        
        virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>& events, float alpha, MixPose pose, MixDirection direction);
        
        virtual int getPropertyId();
        
//        override public void Apply (Skeleton skeleton, float lastTime, float time, Vector<Event> firedEvents, float alpha, MixPose pose, MixDirection direction) {
//            PathConstraint constraint = skeleton.pathConstraints.Items[pathConstraintIndex];
//            float[] frames = _frames;
//            if (time < frames[0]) {
//                switch (pose) {
//                    case MixPose_Setup:
//                        constraint.spacing = constraint.data.spacing;
//                        return;
//                    case MixPose_Current:
//                        constraint.spacing += (constraint.data.spacing - constraint.spacing) * alpha;
//                        return;
//                }
//                return;
//            }
//
//            float spacing;
//            if (time >= frames[frames.Length - ENTRIES]) // Time is after last frame.
//                spacing = frames[frames.Length + PREV_VALUE];
//            else {
//                // Interpolate between the previous frame and the current frame.
//                int frame = Animation::binarySearch(frames, time, ENTRIES);
//                spacing = frames[frame + PREV_VALUE];
//                float frameTime = frames[frame];
//                float percent = GetCurvePercent(frame / ENTRIES - 1,
//                                                1 - (time - frameTime) / (frames[frame + PREV_TIME] - frameTime));
//
//                spacing += (frames[frame + VALUE] - spacing) * percent;
//            }
//
//            if (pose == MixPose_Setup)
//                constraint.spacing = constraint.data.spacing + (spacing - constraint.data.spacing) * alpha;
//            else
//                constraint.spacing += (spacing - constraint.spacing) * alpha;
//        }
    };
}

#endif /* Spine_PathConstraintSpacingTimeline_h */

#pragma once
/*
 *          ::::::::  :::       :::     :::     :::::::::  :::::::::   ::::::::
 *         :+:    :+: :+:       :+:   :+: :+:   :+:    :+: :+:    :+: :+:    :+:
 *         +:+    +:+ +:+       +:+  +:+   +:+  +:+    +:+ +:+    +:+ +:+    +:+
 *         +#+    +:+ +#+  +:+  +#+ +#++:++#++: +#+    +:+ +#++:++#:  +#+    +:+
 *         +#+  # +#+ +#+ +#+#+ +#+ +#+     +#+ +#+    +#+ +#+    +#+ +#+    +#+
 *         #+#   +#+   #+#+# #+#+#  #+#     #+# #+#    #+# #+#    #+# #+#    #+#
 *          ###### ###  ###   ###   ###     ### #########  ###    ###  ########
 *
 *                  Q W A D R O   E X E C U T I O N   E C O S Y S T E M
 *
 *                                   Public Test Build
 *                               (c) 2017 SIGMA FEDERATION
 *                             <https://sigmaco.org/qwadro/>
 */

/// Qwadro armazena anima��es em partes baseadas em qu�o muitos modelos est�o envolvidos numa anima��o.
/// Assim sendo, uma afxAnimation � a mo��o de um conjunto de afxModel's animando sobre tempo.
/// A afxAnimation cont�m um ou mais afxMotion's, cada do qual correspondendo � mo��o de um modelo espec�fico (desde que uma anima��o pode envolver m�ltiplos modelos, se o autor assim escolher).
/// O afxMotion � constitu�do de curvas, cada da qual especifica a transla��o, rota��o e escala de uma junta no akxSkeleton do correspondente afxModel.

#ifndef ASX_ANIMATION_H
#define ASX_ANIMATION_H

#include "qwadro/inc/sim/afxSimDefs.h"
#include "qwadro/inc/sim/io/afxCurve.h"
#include "qwadro/inc/math/afxTransform.h"
#include "qwadro/inc/base/afxFixedString.h"
#include "qwadro/inc/sim/io/afxMotion.h"
#include "qwadro/inc/sim/body/afxPose.h"

typedef enum afxAnimationFlag
{
    afxAnimationFlag_NONE
} afxAnimationFlags;

AFX_DEFINE_STRUCT(afxAnimationBlueprint)
{
    afxReal         dur;
    afxReal         timeStep;
    afxReal         oversampling;
    afxUnit         motSlotCnt;
    afxMotion*      motions;
    // TODO make motions' names a animation property to ease portability of motions.
    afxString32     id;
};

ASX afxBool     AfxGetAnimationUrn(afxAnimation ani, afxString* id);

ASX afxBool     AfxFindMotion(afxAnimation ani, afxString const* id, afxUnit *motIdx);

ASX afxError    AfxGetMotions(afxAnimation ani, afxUnit first, afxUnit cnt, afxMotion motions[]);

ASX afxError    AfxRelinkMotions(afxAnimation ani, afxUnit baseSlot, afxUnit slotCnt, afxMotion motions[]);

ASX afxUnit     AfxPerformAnimation(afxAnimation ani, afxReal startTime, afxUnit iterCnt, afxUnit cnt, afxBody bodies[]);

//ASX afxUnit    AfxPerformAnimationBinding(afxAnimation ani, afxReal startTime, afxUnit iterCnt, struct asxInstancedAnimation *binding, afxUnit cnt, afxBody bodies[]);

ASX afxError    AfxArchiveAnimation(afxAnimation ani, afxUri const* uri);

////////////////////////////////////////////////////////////////////////////////

ASX afxError    AfxLoadAnimation(afxSimulation sim, afxString const* urn, afxUri const* uri, afxAnimation* animation);

ASX afxError    AfxAssembleAnimations(afxSimulation sim, afxUnit cnt, afxAnimationBlueprint const blueprints[], afxAnimation animations[]);

ASX void        AfxTransformAnimations(afxM3d const ltm, afxM3d const iltm, afxReal linearTol, afxV4d const atv, afxReal affineTol, afxFlags flags, afxUnit cnt, afxAnimation animations[]);

#endif//ASX_ANIMATION_H

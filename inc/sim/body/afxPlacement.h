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

// O objeto afxPlacement � um buffer usado para manter o estado de um afxSkeleton de afxModel como expressado no "world space". 

#ifndef ASX_PLACEMENT_H
#define ASX_PLACEMENT_H

#include "qwadro/inc/sim/afxSimDefs.h"

ASX afxUnit     AfxGetPlacementCapacity(afxPlacement plce);

ASX afxM4d*     AfxGetPlacementMatrices(afxPlacement plce, afxUnit baseArtIdx);

ASX afxM4d*     AfxGetPlacementDeltas(afxPlacement plce, afxUnit baseArtIdx);

/// A afxM4d composta est� no mesmo layout como aquela retornada de GetPosture4x4. 
/// � igual ao "world space" --- afxM4d espacial para a articula��o (como dada por GetPosture4x4) multiplicada pelo transforme inverso de repouso no world-space --- para a articula��o (como alojada no afxSkeleton). 
/// Portanto, esta representa a diferen�a entre a atual posi��o no world-space da articula��o e sua posi��o de repouso no world-space.

/// As afxM4d de transforma��o no world-space e compostas s�o garantida a estarem cont�guas, assim sendo, voc� pode tamb�m obter o ponteiro para o in�cio da array e us�-lo para manualmente acessar articula��es individuais. 

// Pass NIL as @pose to AfxBuildPlacement() to compute the rest placement.
// Pass TRUE as composite to AfxBuildPlacement() to compute the placement's composite buffer.
ASX void        AfxBuildPlacement(afxPlacement plce, afxPose pose, afxModel skl, afxUnit baseJntIdx, afxUnit jntCnt, afxUnit baseReqJnt, afxUnit reqJntCnt, afxM4d const displace, afxBool skipDeltas);

// extract the pose
ASX void        AfxRebuildPose(afxPlacement plce, afxModel skl, afxUnit baseJntIdx, afxUnit jntCnt, afxM4d const displace, afxBool rigid, afxPose pose);

ASX void        AfxBuildCompositeMatrices(afxPlacement plce, afxModel skl, afxUnit baseJnt, afxUnit cnt, afxBool /*3x4*/transposed, afxM4d matrices[]);
ASX void        AfxBuildIndexedCompositeMatrices(afxPlacement plce, afxModel skl, afxUnit cnt, afxUnit const jntMap[], afxBool /*3x4*/transposed, afxM4d matrices[]);

////////////////////////////////////////////////////////////////////////////////

ASX afxError    AfxAcquirePlacements(afxSimulation sim, afxUnit cnt, afxUnit const artCnt[], afxBool const excludeDeltas[], afxPlacement placements[]);

#endif//ASX_PLACEMENT_H

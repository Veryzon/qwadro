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

#ifndef AMX_PLACEMENT_H
#define AMX_PLACEMENT_H

#include "qwadro/inc/sim/afxSimDefs.h"

AMX afxError    AfxAcquirePlacements(afxSimulation sim, afxUnit cnt, afxUnit const artCnt[], afxBool const excludeComposite[], afxPlacement placements[]);

AMX afxUnit     AfxGetPlacementCapacity(afxPlacement const plce);

AMX afxM4d*     AfxGetPlacementMatrices(afxPlacement const plce, afxUnit baseArtIdx);

AMX afxM4d*     AfxGetPlacementDeltas(afxPlacement const plce, afxUnit baseArtIdx);

/// A afxM4d composta est� no mesmo layout como aquela retornada de GetPosture4x4. 
/// � igual ao "world space" --- afxM4d espacial para a articula��o (como dada por GetPosture4x4) multiplicada pelo transforme inverso de repouso no world-space --- para a articula��o (como alojada no afxSkeleton). 
/// Portanto, esta representa a diferen�a entre a atual posi��o no world-space da articula��o e sua posi��o de repouso no world-space.

/// As afxM4d de transforma��o no world-space e compostas s�o garantida a estarem cont�guas, assim sendo, voc� pode tamb�m obter o ponteiro para o in�cio da array e us�-lo para manualmente acessar articula��es individuais. 

AMX afxM4d*     AfxPostureGetWorldMatrixArray(afxPlacement const plce);
AMX afxM4d*     AfxPostureGetCompositeMatrixArray(afxPlacement const plce);

#endif//AMX_PLACEMENT_H

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

/// O objeto afxSkeleton � uma cole��o hier�rquica de articula��es que descrevem a estrutura articular interna de um afxModel, e auxilia no manejo e na anima��o do mesmo. 

/// Cada articula��o no arranjo do afxSkeleton aloja o transforme para aquela articula��o em dois meios diferentes. 
/// Primeiro, afxTransform "local" � o transforme decomposto da articula��o relativa a seu parente imediato (dado pelo �ndice do parente).
/// Se esta n�o houver parente (isto �, o �ndex do parente � igual a AFX_INVALID_INDEX), ent�o esta � relativa a origem do afxSkeleton.

/// Segundo, "iw" � uma afxM4d que � o transforme invertido no world-space para a articula��o na postura padr�o do afxSkeleton (isto �, a postura na qual o afxSkeleton foi originalmente modelado).

/// O afxTransform "local" � usado primariamente na composi��o de anima��es, e a afxM4d "iw" � usada primariamente para deforma��o de malha, raz�o pela qual esta informa��o � alojada em dois diferentes formatos.

/// Cada articula��o tamb�m opcionalmente cont�m dados definidos pelo usu�rio "UDD".
/// Este campo aponta para algum dado, estranho � l�gica do Qwadro, associado com a articula��o, se houver qualquer.

/// Skinning is a technique for deforming geometry by linearly weighting vertices to a set of transformations, represented by nodes.
/// Nodes that affect a particular geometry are usually organized into a single hierarchy called a 'skeleton', although the influencing nodes may come from unrelated parts of the hierarchy.
/// The nodes of such a hierarchy represents the 'joints' of the skeleton, which should not be confused with the 'bones', which are the imaginary line segments connecting two joints.

#ifndef AMX_SKELETON_H
#define AMX_SKELETON_H

#include "qwadro/inc/cad/afxPose.h"
#include "qwadro/inc/cad/afxPoseBuffer.h"
#include "qwadro/inc/io/afxUri.h"
#include "qwadro/inc/math/afxMatrix.h"
#include "qwadro/inc/base/afxFixedString.h"

AFX_DEFINE_STRUCT(akxSkeletonBlueprint)
{
    afxString32         urn;
    afxNat              lodType;
    afxBool             scalable;
    afxBool             deformable;
    afxNat              jointCnt;
    afxString const*    joints;
    afxNat const*       parents;
    afxTransform const* transforms; // local
    afxM4d const*       matrices; // inverse world
    afxReal const*      lodErrors;
};

AMX afxBool             AfxGetSkeletonUrn(afxSkeleton skl, afxString* id);

AMX afxNat              AfxCountSkeletonJoints(afxSkeleton skl, afxReal allowedErr);

AMX afxNat              AfxFindSkeletonJoints(afxSkeleton skl, afxNat cnt, afxString const ids[], afxNat indices[]);

AMX afxString*          AfxGetSkeletonJoints(afxSkeleton skl, afxNat jntIdx);

AMXINL afxTransform*    AfxGetSkeletonTransform(afxSkeleton skl, afxNat jntIdx);
AMX afxM4d*             AfxGetSkeletonMatrices(afxSkeleton skl, afxNat baseJntIdx);
AMXINL afxNat*          AfxGetSkeletonParentIndexes(afxSkeleton skl, afxNat baseJntIdx);

AMX afxError            AfxResetSkeletonMatrices(afxSkeleton skl, afxNat baseJntIdx, afxNat cnt, afxM4d const matrices[], afxNat stride);
AMX afxError            AfxResetSkeletonLodErrors(afxSkeleton skl, afxNat baseJntIdx, afxNat cnt, afxReal const lodErrors[]);
AMX afxError            AfxReparentSkeletonJoints(afxSkeleton skl, afxNat baseJntIdx, afxNat cnt, afxNat const indices[], afxNat stride);
AMX afxError            AfxResetSkeletonTransforms(afxSkeleton skl, afxNat baseJntIdx, afxNat cnt, afxTransform const transforms[]);

AMX void                AfxQuerySkeletonErrorTolerance(afxSkeleton skl, afxReal allowedErr, afxReal* allowedErrEnd, afxReal* allowedErrScaler);

AMX void                AfxLocalPoseFromPoseBuffer(afxSkeleton skl, afxPose lp, afxPoseBuffer const wp, afxM4d const offset, afxNat firstBone, afxNat boneCnt);
AMX void                AfxLocalPoseFromPoseBufferNoScale(afxSkeleton skl, afxPose lp, afxPoseBuffer const wp, afxM4d const offset, afxNat firstBone, afxNat boneCnt);
AMX void                AfxGetWorldMatrixFromLocalPose(afxSkeleton skl, afxNat jntIdx, afxPose const lp, afxM4d const offset, afxM4d m, afxNat const* sparseBoneArray, afxNat const* sparseBoneArrayReverse);
AMX void                AfxGetSkeletonAttachmentOffset(afxSkeleton skl, afxNat jntIdx, afxPose const lp, afxM4d const offset, afxM4d m, afxNat const* sparseArtArray, afxNat const* sparseArtArrayReverse);

AMX void                AfxBuildIndexedCompositeBuffer(afxSkeleton skl, afxPoseBuffer const wp, afxNat const* indices, afxNat idxCnt, afxM4d buffer[]);
AMX void                AfxBuildIndexedCompositeBufferTransposed(afxSkeleton skl, afxPoseBuffer const wp, afxNat const* indices, afxNat idxCnt, afxReal buffer[][3][4]);

AMX void                AfxComputeRestLocalPose(afxSkeleton skl, afxNat baseJnt, afxNat jntCnt, afxPose lp);
AMX void                AfxComputeRestPoseBuffer(afxSkeleton skl, afxNat baseJnt, afxNat jntCnt, afxM4d const offset, afxPoseBuffer wp);

AMX void                AfxComputePoseBuffer(afxSkeleton skl, afxNat baseJnt, afxNat jntCnt, afxPose const lp, afxM4d const offset, afxPoseBuffer wp);
AMX void                AfxComputePoseBufferLod(afxSkeleton skl, afxNat baseJnt, afxNat jntCnt, afxNat firstValidLocalArt, afxNat validLocalArtCnt, afxPose const lp, afxM4d const offset, afxPoseBuffer wp);
AMX void                AfxComputePoseBufferNoCompositeLod(afxSkeleton skl, afxNat baseJnt, afxNat jntCnt, afxNat firstValidLocalArt, afxNat validLocalArtCnt, afxPose const lp, afxM4d const offset, afxPoseBuffer wp);

////////////////////////////////////////////////////////////////////////////////

AMX afxError            AfxAssembleSkeletons(afxSimulation sim, afxNat cnt, akxSkeletonBlueprint const sklb[], afxSkeleton skeletons[]);

AMX afxNat              AfxEnumerateSkeletons(afxSimulation sim, afxNat base, afxNat cnt, afxSkeleton skeletons[]);

AMX void                AfxTransformSkeletons(afxM3d const ltm, afxM3d const iltm, afxReal linearTol, afxV4d const atv, afxReal affineTol, afxNat cnt, afxSkeleton skeletons[]);

#endif//AMX_SKELETON_H

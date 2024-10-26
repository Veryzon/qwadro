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

/// O objeto afxBody aloja o estado de um afxModel no tempo de execu��o.
/// O afxModel � apenas dados estruturados para um modelo particular --- isto �, este n�o h� qualquer conceito de onde este est�, qual estado este est� em, ou quais anima��es est�o interagindo em si.
/// O afxBody mant�m rastreio disto e prov�m um n�mero de fun��es �teis para facilitar o trabalho com estados de modelo. 

/// Enquanto todas as suas entidades id�nticas deveriam compartilhar o mesmo afxModel, desde que seus dados de malha e esqueleto sejam id�nticos, cada um deveria ainda haver seu pr�prio afxBody.
/// Dito isto porque os dados do afxBody s�o todos din�micos, e n�o s�o compartilhados atrav�s de m�ltiplos modelos, mesmo se estes foram feitos do mesmo afxModel.
/// Assim, enquanto � comum colocar a hierarquia de estruturas do afxModel no cache e instanci�-las m�ltiplas vezes, voc� nunca deveria colocar objetos afxBody no cache e reus�-los.
/// Eles deveriam sempre ser instanciados e liberados ao longo da exist�ncia das entidades que eles representam na sua aplica��o.

/// Note, no entanto, que estes s�o simplesmente ponteiros para os dados originais que voc� passou durante a instancia��o.
/// O afxBody n�o mant�m c�pias dos dados (para minimizar uso de mem�ria), ent�o voc� n�o pode liberar os dados originais do modelo e esperar obter ponteiros v�lidos de volta aqui.
/// Para aquilo que importa, se voc� liberar os dados originais do modelo, nenhuma das chamadas para afxBody funcionar�o, desde que elas todas dependem daqueles dados, como voc� esperaria.

#ifndef AMX_BODY_H
#define AMX_BODY_H

#include "qwadro/inc/cad/afxModel.h"
#include "qwadro/inc/sim/afxMotor.h"

AMX afxBool     AfxGetBodyModel(afxBody bod, afxModel* model);
AMX afxBool     AfxGetBodySkeleton(afxBody bod, afxSkeleton* skeleton);
    
AMX void        AkxResetBodyClock(afxBody bod);
AMX void        AfxUpdateBodyMatrix(afxBody bod, afxReal secsElapsed, afxBool inverse, afxM4d const mm, afxM4d m);

AMX void        AfxRecenterBodyMotiveClocks(afxBody bod, afxReal currClock);

/// Update all the motors affecting a particular puppet.
AMX void        AfxUpdateBodyMotives(afxBody bod, afxReal newClock);

AMX void        AfxPurgeTerminatedMotives(afxBody bod);

AMX void        AfxGetBodyRootMotionVectors(afxBody bod, afxReal secsElapsed, afxBool inverse, afxV3d translation, afxV3d rotation);

AFX_DEFINE_STRUCT(afxAnimSampleContext)
{
    afxBool         accelerated;
    afxUnit          firstPivot;
    afxUnit          pivotCnt;
    afxMotor        moto;
    afxPose         pose;
    afxPoseBuffer   posb;
    afxReal         allowedErr;
    afxM4d const    displacement;
    afxUnit const*   sparseBoneArray;
};

AMX afxBool     AfxSampleBodyAnimations(afxBody bod, afxAnimSampleContext const* ctx);

AMX void        AfxSampleBodyAnimationsLODSparse(afxBody bod, afxUnit basePivotIdx, afxUnit pivotCnt, afxPose rslt, afxReal allowedErr, afxUnit const* sparseBoneArray);
AMX void        AfxSampleBodyAnimationsAcceleratedLOD(afxBody bod, afxUnit pivotCnt, afxM4d const offset, afxPose scratch, afxPoseBuffer rslt, afxReal allowedErr);
AMX afxBool     AfxSampleSingleBodyAnimationLODSparse(afxBody bod, afxMotor moto, afxUnit basePivotIdx, afxUnit pivotCnt, afxPose rslt, afxReal allowedErr, afxUnit const* sparseBoneArray);
AMX void        AfxAccumulateBodyAnimationsLODSparse(afxBody bod, afxUnit basePivotIdx, afxUnit pivotCnt, afxPose rslt, afxReal allowedErr, afxUnit const* sparseBoneArray);

AMX void        AkxCmdBindPose(avxCmdb cmdb, afxPose pose);
AMX void        AkxCmdBindPoseBuffer(avxCmdb cmdb, afxPoseBuffer wp);
AMX void        AkxCmdBindSparsePivotMap(avxCmdb cmdb, afxUnit const* sparseBoneArray);
AMX void        AkxCmdSetAllowedSamplingError(avxCmdb cmdb, afxReal allowedErr);
AMX void        AkxCmdSampleBodyMotions(avxCmdb cmdb, afxBody bod, afxUnit basePivot, afxUnit pivotCnt);

AMX void        AfxSetBodyMass(afxBody bod, afxV3d mass);

////////////////////////////////////////////////////////////////////////////////

AMX afxError    AfxSpawnBodies(afxModel proto, afxUnit cnt, afxBody bod[]);

AMX afxError    AfxAcquireBodies(afxSimulation sim, afxModel mdl, afxUnit cnt, afxBody bodies[]);

AMX afxUnit      AfxPerformManipulatedPose(afxPose pose, afxReal startTime, afxReal duration, afxUnit iterCnt, akxTrackMask* modelMask, afxUnit cnt, afxBody bodies[]);

#endif//AMX_BODY_H

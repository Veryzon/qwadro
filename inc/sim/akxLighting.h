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

#ifndef AMX_LIGHT_H
#define AMX_LIGHT_H

#include "qwadro/inc/sim/afxNode.h"
#include "qwadro/inc/mem/afxArray.h"
#include "qwadro/inc/math/afxColor.h"

#define AFX_LIT_ALIGN AFX_SIMD_ALIGNMENT

// light rigs as in Doom

typedef enum
{
    /// A light placed infinitely far away. It affects everything in the scene.
    akxLightType_DIRECTIONAL,

    /// A light that shines equally in all directions from its location, affecting all objects within its Range.
    akxLightType_OMNI,

    /// A light that shines everywhere within a cone defined by Spot Angle and Range. Only objects within this region are affected by the light.
    akxLightType_SPOT,

    /// A light that shines in all directions to one side of a rectangular area of a plane. The rectangle is defined by the Width and Height properties.
    /// Area lights are only available during lightmap baking and have no effect on objects at runtime.
    akxLightType_AREA
} akxLightType;

typedef enum akxLightFlag
{
    akxLightFlag_FADE_ENABLED   = AFX_BIT(0), // false
    akxLightFlag_NEGATIVE       = AFX_BIT(1), // false
    akxLightFlag_SHADOW_ENABLED = AFX_BIT(2), // false
    akxLightFlag_REV_CULL_FACE  = AFX_BIT(3), // false
} akxLightFlags;

#ifdef _AMX_LIGHT_C
AFX_OBJECT(akxLight)
{
    afxReal     distFadeBegin; // 40.f
    /// A luz ser� suavemente esvanecida afora quando longe da c�mera ativa iniciando de distFadeBegin.
    /// Isto atua como uma forma de LOD. A luz ser� esmaecida afora sobre distFadeBegin + distFadeLen, ap�s a qual ser� coligida e n�o enviada a shader.

    afxReal     distFadeLen; // 10.f
    /// Dist�ncia sobre a qual a luz e sua sombra esmaecem. A energia da luz e a opacidade da sombra s�o progressivamente reduzidas sobre esta dist�ncia e � completamente invis�vel ao fim.
    
    afxReal     distFadeShadow; // 50.f
    /// A dist�ncia da c�mera na qual a sombra da luz corta (em unidades 3D).

    afxReal     angularDist; // 0.f
    
    afxUnit32    bakeMode; // 2
    afxColor    color; // [1, 1, 1, 1]
    afxMask     cullMask; // 0xFFFFFFFF
    afxReal     energy; // 1.f
    afxReal     indirectEnergy; // 1.f
    afxReal     intensLumens;
    afxReal     intensLux;
    afxRaster  projector;
    afxReal     size; // 0.f
    afxReal     specular; // 0.5f
    afxReal     temperature;
    afxReal     volFogEnergy; // 1.f
    afxReal     shadowBias; // 0.1f
    afxReal     shadowBlur; // 1.f
    afxReal     shadowNormalBias; // 2.f
    afxReal     shadowOpacity; // 1.f
    afxReal     shadowTransBias; // 0.05f

    akxLightType            type;
    union
    {
        struct
        {
            afxReal attenuation; // 1.f
            afxReal range; // 5.f
            // shadow mode
            afxReal shadowNormalBias; // 1.0
        } omni;
        struct
        {
            afxReal shadowBias; // 0.03f
            afxReal shadowNormalBias; // 1.f
            afxReal angle; // 45.f
            afxReal angleAttenuation; // 1.f
            afxReal range; // 5.f
        } spot;
        struct
        {
            afxBool shadowBlendSplits; // false
            afxReal shadowFadeStart; // 0.8
            afxReal shadowMaxDist; // 100.f
            // shadow mode
            afxReal shadowPancakeSiz; // 20.f
            afxReal shadowSplit1; // 0.1f
            afxReal shadowSplit2; // 0.2f
            afxReal shadowSplit3; // 0.5f
            // sky mode
        } dir;
    };
};
#endif//_AMX_LIGHT_C

////////////////////////////////////////////////////////////////////////////////
// MASSIVE OPERATIONS                                                         //
////////////////////////////////////////////////////////////////////////////////

AMX afxError    AfxAcquireDirectionalLights(afxSimulation sim, afxUnit cnt, afxUnit uid[]);
AMX afxError    AfxAcquireOmniLights(afxSimulation sim, afxUnit cnt, afxUnit uid[]);
AMX afxError    AfxAcquireSpotLights(afxSimulation sim, afxUnit cnt, afxUnit uid[]);

#endif//AMX_LIGHT_H

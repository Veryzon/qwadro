/*
 *          ::::::::  :::       :::     :::     :::::::::  :::::::::   ::::::::
 *         :+:    :+: :+:       :+:   :+: :+:   :+:    :+: :+:    :+: :+:    :+:
 *         +:+    +:+ +:+       +:+  +:+   +:+  +:+    +:+ +:+    +:+ +:+    +:+
 *         +#+    +:+ +#+  +:+  +#+ +#++:++#++: +#+    +:+ +#++:++#:  +#+    +:+
 *         +#+  # +#+ +#+ +#+#+ +#+ +#+     +#+ +#+    +#+ +#+    +#+ +#+    +#+
 *         #+#   +#+   #+#+# #+#+#  #+#     #+# #+#    #+# #+#    #+# #+#    #+#
 *          ###### ###  ###   ###   ###     ### #########  ###    ###  ########
 *
 *        Q W A D R O   V I D E O   G R A P H I C S   I N F R A S T R U C T U R E
 *
 *                                   Public Test Build
 *                               (c) 2017 SIGMA FEDERATION
 *                             <https://sigmaco.org/qwadro/>
 */

// This code is part of SIGMA GL/2 <https://sigmaco.org/gl>

#ifndef AVX_BUFFERIZER_H
#define AVX_BUFFERIZER_H

#include "qwadro/inc/draw/io/afxBuffer.h"
#include "qwadro/inc/draw/pipe/avxVertexDecl.h"

AFX_DEFINE_HANDLE(afxBufferizer);

#ifdef _AVX_DRAW_C
#ifdef _AVX_VERTEX_BUFFER_C

#endif//_AVX_VERTEX_BUFFER_C
#endif//_AVX_DRAW_C

AFX_DEFINE_STRUCT(afxBufferizerInfo)
{
    afxUnit         bufCap;
    afxBufferFlags  access;
    afxBufferUsage  usage;
};

AVX afxError        AfxAcquireBufferizer(afxDrawInput din, afxBufferizerInfo const* info, afxBufferizer* bufferizer);

AVX afxBuffer       AfxGetVertexBufferStorage(afxVertexBuffer vbuf);
AVX afxUnit         AfxGetVertexBufferUsage(afxVertexBuffer vbuf);
AVX avxVertexDecl  AfxGetVertexBufferLayout(afxVertexBuffer vbuf);
AVX afxUnit         AfxGetVertexBufferCapacity(afxVertexBuffer vbuf);

#endif//AVX_BUFFERIZER_H

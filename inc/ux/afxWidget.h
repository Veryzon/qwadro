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

// Advanced User Experience Extensions for Qwadro

#ifndef AUX_WIDGET_H
#define AUX_WIDGET_H

#include "qwadro/inc/ux/afxUxDefs.h"
#include "qwadro/inc/math/afxColor.h"
#include "qwadro/inc/base/afxChain.h"
#include "qwadro/inc/base/afxObject.h"
#include "qwadro/inc/io/afxUri.h"
#include "qwadro/inc/math/afxTransform.h"
//#include "afxViewport.h"
//#include "qwadro/inc/draw/dev/afxDrawInput.h"

typedef enum afxWidgetType
{
    //NIL
    AFX_WIDG_PANEL          = AFX_MAKE_FCC('w', 'p', 'a', 'n'),
    AFX_WIDG_LABEL          = AFX_MAKE_FCC('w', 'l', 'a', 'b'),
    AFX_WIDG_BUTTON         = AFX_MAKE_FCC('w', 'b', 'u', 't'),
    AFX_WIDG_CHECKBOX       = AFX_MAKE_FCC('w', 'c', 'h', 'k'),
    AFX_WIDG_EDITBOX        = AFX_MAKE_FCC('w', 'e', 'd', 't'),
    AFX_WIDG_SLIDER         = AFX_MAKE_FCC('w', 's', 'l', 'd'),
    AFX_WIDG_DROPDOWN       = AFX_MAKE_FCC('w', 'd', 'r', 'p'),
    AFX_WIDG_PROGRESSBAR    = AFX_MAKE_FCC('w', 'p', 'r', 'o'),
    AFX_WIDG_PICTURE        = AFX_MAKE_FCC('w', 'p', 'i', 'c'),
    AFX_WIDG_VIDEO          = AFX_MAKE_FCC('w', 'v', 'i', 'd'),
    AFX_WIDG_GROUP          = AFX_MAKE_FCC('w', 'g', 'r', 'p'),

    AFX_WIDG_TYPE_TOTAL
} afxWidgetType;

AFX_DEFINE_STRUCT(afxWidgetStyle)
{
    afxRect     rect;
};

// screen overlay is a draw input device that has been idealized to be an widget layer.

AFX_DEFINE_STRUCT(afxWidgetVertex)
{
    afxV2d      xy, uv;
};

AFX_DECLARE_STRUCT(afxWidgetImplementation);
AFX_DECLARE_STRUCT(afxWidgetImplementationData);

AFX_DEFINE_STRUCT(afxWidgetConfig)
{
    afxString const *name;
    afxWidget parent;
    afxUri const *uri;
    afxResult(*f)(afxWidget, afxUri const*, void *data);
};

AUX afxError    AfxAcquireWidgets(afxSession ses, afxNat cnt, afxWidgetConfig cfg[], afxWidget widgets[]);

#endif//AUX_WIDGET_H
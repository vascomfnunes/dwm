/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 0;     /* 0 means no systray */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 4;        /* horizontal padding for statusbar */
static const int vertpadbar         = 12;        /* vertical padding for statusbar */
static const int rmaster            = 0;        /* 1 means master-area is initially on the right */

static const char buttonbar[]       = "";
static const char *fonts[]          = { "Hack Nerd Font Mono:size=9" };
static const char col_bg[]          = "#073642";
static const char col_fg_norm[]     = "#ffaf00";
static const char col_fg_sel[]      = "#859900";
static const char col_border[]      = "black";

static const char *colors[][3]      = {
    /*                fg          bg      border     */
    [SchemeNorm]  = { "white",    col_bg, col_border },
    [SchemeSel]   = { col_fg_sel, col_bg, col_border },
    [SchemeTitle] = { col_bg,     col_bg, col_border },
};

/* static const char *tags[] = { "", "", "", "", "", "", "", "", "" }; */
/* static const char *tagsalt[] = { "", "", "", "", "", "", "", "", "" }; */

/* tagging */
static const char *tags[] = { "", "", "", "", "" };
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { NULL,       NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol   arrange function */
    { "",      tile },
    { "",      deck },
    { "",      monocle },
    { "",      NULL }, /* no layout function means floating behavior *1/ */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* mbp-mappings */
#define XF86MonBrightnessDown	0x1008ff03
#define XF86MonBrightnessUp		0x1008ff02
#define XF86KbdBrightnessDown	0x1008ff06
#define XF86KbdBrightnessUp		0x1008ff05
#define XF86AudioPrev			0x1008ff16
#define XF86AudioPlay			0x1008ff14
#define XF86AudioNext			0x1008ff17
#define XF86AudioMute			0x1008ff12
#define XF86AudioLowerVolume	0x1008ff11
#define XF86AudioRaiseVolume	0x1008ff13

/* commands */
static const char dmenufont[] = "Hack Nerd Font Mono:size=9";
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "#073642", "-nf", "#859900", "-sb", "#073642", "-sf", "#ffaf00", NULL };
static const char *termcmd[] = { "st", NULL, NULL, NULL };
static const char *brightnessup[] = { "light", "-A", "1", NULL };
static const char *brightnessdown[] = { "light", "-U", "1", NULL };
static const char *keyboardbrightnessup[] = { "light", "-s", "sysfs/leds/smc::kbd_backlight", "-A", "1", NULL };
static const char *keyboardbrightnessdown[] = { "light", "-s", "sysfs/leds/smc::kbd_backlight", "-U", "1", NULL };
static const char *volumeup[] = { "/home/vasco/scripts/volume", "up", NULL };
static const char *volumedown[] = { "/home/vasco/scripts/volume", "down", NULL };
static const char *volumemute[] = { "/home/vasco/scripts/volume", "mute", NULL };

#include "zoomswap.c"
static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Down,   pushdown,       {0} },
    { MODKEY|ShiftMask,             XK_Up,     pushup,         {0} },
    { MODKEY,                       XK_l,      switchcol,      {0} },

    { MODKEY,                       XK_j,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_k,      incnmaster,     {.i = -1 } },

    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_w,      killclient,     {0} },
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_t,      togglermaster,  {0} },

    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_d,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

    { 0,                            XF86MonBrightnessUp, spawn,{.v = brightnessup } },
    { 0,                            XF86MonBrightnessDown, spawn,{.v = brightnessdown } },
    { 0,                            XF86KbdBrightnessUp, spawn,{.v = keyboardbrightnessup } },
    { 0,                            XF86KbdBrightnessDown, spawn,{.v = keyboardbrightnessdown } },
    { 0,                            XF86AudioRaiseVolume, spawn,{.v = volumeup } },
    { 0,                            XF86AudioLowerVolume, spawn,{.v = volumedown } },
    { 0,                            XF86AudioMute, spawn,{.v = volumemute } },
    { MODKEY,						XK_Right,					focusstack,			{.i = +1 } },
    { MODKEY,						XK_Left,					focusstack,			{.i = -1 } },
    { MODKEY,						XK_i,						incnmaster,			{.i = +1 } },
    { MODKEY,						XK_d,						incnmaster,			{.i = -1 } },
    { MODKEY|ShiftMask,				XK_Left,					setmfact,			{.f = -0.05} },
    { MODKEY|ShiftMask,				XK_Right,					setmfact,			{.f = +0.05} },
    { MODKEY,						XK_Down,					pushdown,			{0} },
    { MODKEY,						XK_Up,						pushup,				{0} },
    { MODKEY,				        XK_z,					    zoom,				{0} },
    { MODKEY,						XK_Tab,						view,				{0} },

    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkButton,            0,              Button1,        spawn,          {.v = dmenucmd } },

    { ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[2]} },
    { ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[0]} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },

    { ClkWinTitle,          0,              Button1,        focusstack,     {.i = -1 } },
    { ClkWinTitle,          0,              Button3,        focusstack,     {.i = +1 } },
    { ClkWinTitle,          0,              Button2,        killclient,     {0} },

    { ClkStatusText,        0,              Button1,        zoom,           {0} },

    { ClkClientWin,         0,              Button2,        togglebar,      {0} },
    { ClkRootWin,           0,              Button2,        togglebar,      {0} },

    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },

    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

#define NUMCOLORS       13
#define MODKEY          Mod1Mask
#include "X11/XF86keysym.h"
#define MONKEY          Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

static const unsigned int tagspacing = 2;       /* space between tags */
static const unsigned int tagpadding = 6;      /* inner padding of tags */
static const unsigned int taglinepx = 2;        /* height of tag underline */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool showsystray = True;           /* false means no systray */
static const unsigned int gappx = 8;            /* gaps between windows */
static const unsigned int borderpx = 1;         /* border pixel of windows */
static const unsigned int snap = 32;            /* snap pixel */
static const Bool showbar = True;               /* false means no bar */
static const Bool topbar = False;                /* false means bottom bar */
static const float mfact = 0.50;                /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;                   /* number of clients in master area */
static const Bool resizehints = False;          /* true means respect size hints in tiled resizals */
//static const char font[] = "-*-ohsnap.icons-medium-r-*-*-14-*-*-*-*-*-*-*";
static const char font[] = "-*-ohsnap.icons-medium-r-*-*-14-*-*-*-*-*-*-*";
static const char colors[NUMCOLORS][ColLast][13] = {
    /* border fg bg */
    { "#2D2D2D", "#FFFFFF", "#2D2D2D" }, /* 01 - regular */
    { "#4A8DC3", "#FFFFFF", "#2D2D2D" }, /* 02 - selected */
    { "#2D2D2D", "#FF0000", "#2D2D2D" }, /* 03 - urgent */
    { "#2D2D2D", "#666666", "#2D2D2D" }, /* 04 - occupied */
    { "#2D2D2D", "#A82222", "#2D2D2D" }, /* 05 - red */
    { "#2D2D2D", "#1F7B94", "#2D2D2D" }, /* 06 - blue */
    { "#2D2D2D", "#349147", "#2D2D2D" }, /* 07 - green */
    { "#2D2D2D", "#666666", "#2D2D2D" }, /* 08 - dark grey */
    { "#2D2D2D", "#DCDCDC", "#2D2D2D" }, /* 09 - light grey */
    { "#2D2D2D", "#4A8DC3", "#2D2D2D" }, /* 0A - orange */
    { "#2D2D2D", "#B86A6A", "#2D2D2D" }, /* 0B - pink */
    { "#2D2D2D", "#FFFFFF", "#2D2D2D" }, /* 0C - white */
    { "#2D2D2D", "#000000", "#2D2D2D" }, /* 0D - black */
};

static const Layout layouts[] = {
    /* symbol gaps arrange */
    { "t", True, tile },
    { "b", True, bstack },
    { "m", False, monocle },
    { "N", False, NULL },
};


static const Tag tags[] = {
    /* name layout mfact nmaster */
    { "I", &layouts[0], -1, -1 },
    { "II", &layouts[0], -1, -1 },
    { "III", &layouts[0], -1, -1 },
    { "IV", &layouts[0], -1, -1 },
    { "V", &layouts[0], -1, -1 },
    { "VI", &layouts[0], -1, -1 },
};
static const Rule rules[] = {
    /* class                instance    title       tags mask       isfloating      iscentred       monitor */
    { "Firefox",            NULL,       NULL,       1 << 0,         False,          False,          -1 },
    { "Skype",              NULL,       NULL,       1 << 1,         False,          False,          -1 },
    { "URxvt",              NULL,       NULL,       1 << 2,         False,          False,          -1 },
    { "Rhythmbox",          NULL,       NULL,       1 << 4,         False,          False,          -1 },
    { "Banshee",            NULL,       NULL,       1 << 4,         False,          False,          -1 },
    { "Vlc",                NULL,       NULL,       1 << 4,         False,          False,          -1 },
    { "Geany",              NULL,       NULL,       1 << 3,         False,          False,          -1 },
    { "Transmission-gtk",   NULL,       NULL,       1 << 5,         False,          False,          -1 },
};

static const char *menu[] = { "dmenu_run", "-i", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *webb[] = { "firefox", NULL, "firefox" };
static const char *chat[] = { "skype", NULL, "Skype" };
static const char *term[] = { "urxvt", NULL, "URxvt" };
static const char *edit[] = { "leafad", NULL, "Geany" };
static const char *mdia[] = { "vlc", NULL, "Vlc" };
static const char *prts[] = { "scrot", NULL };
static const char *volumedown[] = { "amixer", "-q", "set", "Master", "2%-", "unmute", NULL };
static const char *volumeup[]   = { "amixer", "-q", "set", "Master", "2%+", "unmute", NULL };
static const char *mute[]       = { "amixer", "-q", "set", "Master", "toggle", NULL };

static Key keys[] = {
    { MODKEY,           XK_p,       spawn,          {.v = menu } },
    { MONKEY,           XK_w,       runorraise,     {.v = webb } },
    { MONKEY,           XK_s,       runorraise,     {.v = chat } },
    { MODKEY|ShiftMask, XK_Return,  runorraise,     {.v = term } },
    { MONKEY,           XK_e,       runorraise,     {.v = edit } },
    { MONKEY,           XK_m,       runorraise,     {.v = mdia } },
    { MONKEY,           XK_Print,   spawn,          {.v = prts } },
    { MODKEY|ShiftMask, XK_q,       quit,           {0} },
    { MODKEY,		XK_b,       togglebar,      {0} },
    { MODKEY|ShiftMask, XK_c,       killclient,     {0} },
    { MODKEY,           XK_Return,  zoom,           {0} },
    { MODKEY,           XK_Tab,     view,           {0} },
    { MODKEY|ShiftMask, XK_f,       togglefloating, {0} },
    { MODKEY,           XK_space,   setlayout,      {0} },
    { MODKEY,           XK_t,       setlayout,      {.v = &layouts[0] } },
    { MODKEY,           XK_b,       setlayout,      {.v = &layouts[1] } },
    { MODKEY,           XK_m,       setlayout,      {.v = &layouts[2] } },
    { MODKEY,           XK_f,       setlayout,      {.v = &layouts[3] } },
    { MODKEY,           XK_Right,   focusstack,     {.i = +1 } },
    { MODKEY,           XK_Left,    focusstack,     {.i = -1 } },
    { MODKEY,           XK_h,       setmfact,       {.f = -0.05 } },
    { MODKEY,           XK_l,       setmfact,       {.f = +0.05 } },
    { MODKEY,           XK_equal,   incnmaster,     {.i = +1 } },
    { MODKEY,           XK_equal,   incnmaster,     {.i = +1 } },
    { MODKEY,           XK_Down,    focusstack,     {.i = +1 } },
    { MODKEY,           XK_Up,      focusstack,     {.i = -1 } },
    { MODKEY,           XK_0,       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask, XK_0,       tag,            {.ui = ~0 } },
    { MODKEY,           XK_comma,   focusmon,       {.i = -1 } },
    { MODKEY,           XK_period,  focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask, XK_comma,   tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask, XK_period,  tagmon,         {.i = +1 } },
    { 0, XF86XK_AudioLowerVolume,   spawn,        { .v = volumedown } },
    { 0, XF86XK_AudioRaiseVolume,   spawn,        { .v = volumeup } }, 
    { 0, XF86XK_AudioMute,          spawn,        { .v = mute } }, 
    TAGKEYS(            XK_1,       0)
    TAGKEYS(            XK_2,       1)
    TAGKEYS(            XK_3,       2)
    TAGKEYS(            XK_4,       3)
    TAGKEYS(            XK_5,       4)
    TAGKEYS(            XK_6,       5)
};

static Button buttons[] = {
    { ClkLtSymbol,      0,          Button1,        setlayout,      {0} },
    { ClkClientWin,     MODKEY,     Button1,        movemouse,      {0} },
    { ClkClientWin,     MODKEY,     Button2,        togglefloating, {0} },
    { ClkClientWin,     MODKEY,     Button3,        resizemouse,    {0} },
    { ClkTagBar,        0,          Button1,        view,           {0} },
    { ClkTagBar,        0,          Button3,        toggleview,     {0} },
    { ClkTagBar,        MODKEY,     Button1,        tag,            {0} },
    { ClkTagBar,        MODKEY,     Button3,        toggletag,      {0} },
};

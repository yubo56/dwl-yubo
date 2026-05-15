/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "Baekmuk Batang Bold 16";
/* static const char font[]            = "Terminus Medium 13"; */
/* static const char font[]            = "Source Code Pro 14"; */
static const char normbordercolor[] = "#000000";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#49e20e";
static const char selbordercolor[]  = "#49e20e";
static const char selbgcolor[]      = "#555555";
static const char selfgcolor[]      = "#49e20e";

/* static const char normbordercolor[] = "#444444"; */
/* static const char normbgcolor[]     = "#222222"; */
/* static const char normfgcolor[]     = "#bbbbbb"; */
/* static const char selbordercolor[]  = "#005577"; */
/* static const char selbgcolor[]      = "#005577"; */
/* static const char selfgcolor[]      = "#eeeeee"; */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool statusmarkup      = True;     /* True means use pango markup in status message */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
   /* class      instance    title       tags mask     isfloating   monitor */
   { "Pidgin",      NULL,       NULL,       1 << 7,            False,       -1 },
   /* { "chromium",    NULL,       NULL,       1 << 8,            False,       -1 }, */
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol       arrange function    new_nmaster */
    { "(0/1)",      tile,               1 },    /* first entry is default */
    { "~",          NULL,               1 },    /* no layout function means floating behavior */
    { "[0/0]",      monocle,            0 },
};

/* key definitions */
#define MODKEY Mod4Mask
/* #define MODKEY Mod1Mask */
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", "-*-terminus-medium-*-*-*-*-180-*-*-*-*-*-*", "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *browser[] = { "dwm_browser_launch", NULL };
static const char *ibus[] = { "ibus-daemon", "-drx", NULL };
static const char *toggle_transp[] = { "dwm_set_transp", NULL };
static const char *brightup[] = { "dwm_brightup", NULL };
static const char *brightdown[] = { "dwm_brightdown", NULL };
static const char *changekeys[] = { "dwm_changekeys", NULL };
static const char *toggleInt[] = { "dwm_toggle_keybd", NULL };
static const char *togglecompact[] = { "dwm_toggle_compact", NULL };
static const char *tptoggle[] = { "dwm_tptoggle", NULL };
static const char *paste_x[] = { "dwm_paste_x", NULL };
static const char *paste_c[] = { "dwm_paste_x", "-c", NULL };
static const char *quick_type[] = { "dwm_quick_type", "_run", NULL };
static const char *killibus[] = { "dwm_re_ibus", NULL };
static const char *usbconnect[] = { "dwm_usbconnect", NULL };

static const char *xscreensaver_custom[] = { "dwm_xscreensaver_error", "-lock", NULL };
static const char *xscreensaver_blank[] = { "dwm_xscreensaver_blank", "-lock", NULL };
static const char *rebg[] = { "dwm_rebg", NULL };
static const char *volup[] = { "dwm_revol", "up", NULL };
static const char *voldown[] = { "dwm_revol", "down", NULL };
static const char *voltoggle[] = { "dwm_revol", "toggle", NULL };

static Key keys[] = {
    /* modifier                     key                         function        argument */
    { MODKEY,                       XK_F1,                      spawn,          {.v = changekeys } },
    { MODKEY|ShiftMask,             XK_F1,                      spawn,          {.v = toggleInt } },
    { MODKEY,                       XK_F2,                      spawn,          {.v = brightdown } },
    { MODKEY|ShiftMask,             XK_F2,                      spawn,          {.v = togglecompact } },
    { MODKEY,                       XK_F3,                      spawn,          {.v = brightup } },
    { MODKEY,                       XK_F5,                      spawn,          {.v = rebg } },
    { MODKEY,                       XK_F9,                      spawn,          {.v = voldown } },
    { MODKEY,                       XK_F10,                     spawn,          {.v = volup} },
    { MODKEY,                       XK_F11,                     spawn,          {.v = voltoggle } },
    { MODKEY,                       XK_F9,                      spawn,          {.v = voldown } },
    { MODKEY,                       XK_F10,                     spawn,          {.v = volup} },
    { 0,                            XF86XK_AudioMute,           spawn,          {.v = voltoggle } },
    { 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = voldown } },
    { 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = volup} },
    { MODKEY,                       XK_F12,                     spawn,          {.v = tptoggle } },
    { MODKEY,                       XK_period,                  spawn,          {.v = termcmd } },
    { MODKEY,                       XK_comma,                   spawn,          {.v = browser } },
    { MODKEY,                       XK_p,                       spawn,          {.v = ibus } },
    { MODKEY,                       XK_b,                       togglebar,      {0} },
    { MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,                       incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,                       incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,                       setmfact,       {.f = -0.02} },
    { MODKEY,                       XK_l,                       setmfact,       {.f = +0.02} },
    { MODKEY|ShiftMask,             XK_h,                       zoom,           {0} },
    { MODKEY,                       XK_Tab,                     view,           {0} },
    { MODKEY|ShiftMask,             XK_q,                       killclient,     {0} },
    { MODKEY,                       XK_t,                       setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,                       setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,                       setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,                   setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
    { MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
    { MODKEY,                       XK_c,                       focusmon,       {.i = +1 } },
    { MODKEY,                       XK_r,                       focusmon,       {.i = -1 } },
    { MODKEY|ShiftMask,             XK_c,                       tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask,             XK_r,                       tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_x,                       quit,           {0} },
    { MODKEY|ShiftMask,             XK_l,                       spawn,          {.v = xscreensaver_custom } },
    { MODKEY|ShiftMask,             XK_n,                       spawn,          {.v = xscreensaver_blank } },
    { MODKEY,                       XK_n,                       spawn,          {.v = toggle_transp } },
    { MODKEY,                       XK_Return,                  spawn,          {.v = paste_x } },
    { MODKEY|ShiftMask,             XK_Return,                  spawn,          {.v = paste_c } },
    { MODKEY,                       XK_apostrophe,              spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_s,                       spawn,          {.v = quick_type } },
    { MODKEY|ShiftMask,             XK_i,                       spawn,          {.v = killibus } },
    { MODKEY|ShiftMask,             XK_F5,                      spawn,          {.v = usbconnect } },

    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


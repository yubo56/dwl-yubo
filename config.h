/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[]                 = {"Source Code Pro Medium:size=14"};
static const float rootcolor[]             = COLOR(0x000000ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0x49e20eff, 0x000000ff, 0x000000ff },
	[SchemeSel]  = { 0x49e20eff, 0x555555ff, 0x49e20eff },
	[SchemeUrg]  = { 0x49e20eff, 0x000000ff, 0xff0000ff },
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   monitor */
	{ "Pidgin",           NULL,       1 << 7,       0,           -1 },
	/* { "chromium",      NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "(0/1)",    tile },
	{ "~",        NULL },    /* no layout function means floating behavior */
	{ "[0/0]",    monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients due to
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899 */
static const MonitorRule monrules[] = {
   /* name        mfact  nmaster scale layout       rotate/reflect                x    y
    * example of a HiDPI laptop monitor:
    { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 }, */
	{ NULL,       0.5f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	/* default monitor rule: can be changed but cannot be eliminated; at least one monitor rule must exist */
};

/* keyboard */
static const char *xkb_config_path = ".config/xkb";
static const char *xkb_status_file = "/tmp/dwl_xkb_suffix";
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.layout = "custom",
	.variant = "dvorak_caps_nav",
	.options = NULL,
};

static const struct xkb_rule_names xkb_custom_layouts[][2] = {
	{
		{ .layout = "custom", .variant = "dvorak_caps_nav", .options = NULL },
		{ .layout = "custom", .variant = "dvorak_caps_nav_grave", .options = NULL },
	},
	{
		{ .layout = "custom", .variant = "dvorak_caps_nav_intl", .options = NULL },
		{ .layout = "custom", .variant = "dvorak_caps_nav_intl_grave", .options = NULL },
	},
};
static const char *xkb_custom_suffixes[][2] = {
	{ "D", "D" },
	{ "DI", "DI" },
};

static const struct xkb_rule_names xkb_layouts[] = {
	{ .layout = "custom", .variant = "dvorak_caps_nav", .options = NULL },
	{ .layout = "us", .variant = NULL,     .options = NULL },
	{ .layout = "us", .variant = "dvorak-l", .options = NULL },
};
static const char *xkb_layout_suffixes[] = { "D", "U", "L" };
static size_t xkb_layout_idx = 0;
static int xkb_intl = 0;
static int xkb_compact = 0;

static const int repeat_rate = 60;
static const int repeat_delay = 150;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the Alt key for MODKEY, use WLR_MODIFIER_ALT */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* commands */
static const char normbgcolor[] = "#000000";
static const char normfgcolor[] = "#49e20e";
static const char selbgcolor[] = "#555555";
static const char selfgcolor[] = "#49e20e";
static const char wmenufont[] = "Source Code Pro Medium 14";
static const char wmenunormbgcolor[] = "000000";
static const char wmenunormfgcolor[] = "49e20e";
static const char wmenuselbgcolor[] = "555555";
static const char wmenuselfgcolor[] = "49e20e";

static const char *termcmd[] = { "foot", NULL };
static const char *wmenucmd[] = {
	"wmenu-run",
	"-f", wmenufont,
	"-N", wmenunormbgcolor,
	"-n", wmenunormfgcolor,
	"-M", wmenuselbgcolor,
	"-m", wmenuselfgcolor,
	"-S", wmenuselbgcolor,
	"-s", wmenuselfgcolor,
	NULL
};

static const char *browser[] = { "dwm_browser_launch", NULL };
static const char *ibus[] = { "dwl_ibus", NULL };
static const char *brightup[] = { "dwm_brightup", NULL };
static const char *brightdown[] = { "dwm_brightdown", NULL };
static const char *tptoggle[] = { "dwm_tptoggle", NULL };
static const char *paste_x[] = { "dwl_paste_x", NULL };
static const char *paste_c[] = { "dwl_paste_x", "-c", NULL };
static const char *screenshot[] = {
	"sh", "-c",
	"mkdir -p \"$HOME/screenshots\" && grim \"$HOME/screenshots/$(date +%y-%m-%d_%H_%M_%S).png\"",
	NULL
};
static const char *killibus[] = { "dwl_ibus", "restart", NULL };

static const char *lock_custom[] = { "dwl_lock", "custom", NULL };
static const char *lock_blank[] = { "dwl_lock", "blank", NULL };
static const char *rebg[] = { "dwl_rebg", NULL };
static const char *volup[] = { "dwm_revol", "up", NULL };
static const char *voldown[] = { "dwm_revol", "down", NULL };
static const char *voltoggle[] = { "dwm_revol", "toggle", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: 2 -> at, etc. */
	/* modifier                  key                  function          argument */
	{ MODKEY,                    XKB_KEY_F1,          cyclexkblayout,   {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F1,          togglexkbintl,    {0} },
	{ MODKEY,                    XKB_KEY_F2,          spawn,            {.v = brightdown} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F2,          togglexkbcompact, {0} },
	{ MODKEY,                    XKB_KEY_F3,          spawn,            {.v = brightup} },
	{ MODKEY,                    XKB_KEY_F5,          spawn,            {.v = rebg} },
	{ MODKEY,                    XKB_KEY_F9,          spawn,            {.v = voldown} },
	{ MODKEY,                    XKB_KEY_F10,         spawn,            {.v = volup} },
	{ MODKEY,                    XKB_KEY_F11,         spawn,            {.v = voltoggle} },
	{ 0,                         XKB_KEY_XF86AudioMute, spawn,          {.v = voltoggle} },
	{ 0,                         XKB_KEY_XF86AudioLowerVolume, spawn,   {.v = voldown} },
	{ 0,                         XKB_KEY_XF86AudioRaiseVolume, spawn,   {.v = volup} },
	{ MODKEY,                    XKB_KEY_F12,         spawn,            {.v = tptoggle} },
	{ MODKEY,                    XKB_KEY_period,      spawn,            {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_comma,       spawn,            {.v = browser} },
	{ MODKEY,                    XKB_KEY_p,           spawn,            {.v = ibus} },
	{ MODKEY,                    XKB_KEY_b,           togglebar,        {0} },
	{ MODKEY,                    XKB_KEY_j,           focusstack,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,           focusstack,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_i,           incnmaster,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_d,           incnmaster,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,           setmfact,         {.f = -0.02f} },
	{ MODKEY,                    XKB_KEY_l,           setmfact,         {.f = +0.02f} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_h,           zoom,             {0} },
	{ MODKEY,                    XKB_KEY_Tab,         view,             {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_q,           killclient,       {0} },
	{ MODKEY,                    XKB_KEY_t,           setlayout,        {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,           setlayout,        {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,           setlayout,        {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_space,       setlayout,        {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,       togglefloating,   {0} },
	{ MODKEY,                    XKB_KEY_e,           togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,           view,             {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,  tag,              {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_c,           focusmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY,                    XKB_KEY_r,           focusmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_c,           tagmon,           {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_r,           tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_x,           quit,             {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_l,           spawn,            {.v = lock_custom} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_n,           spawn,            {.v = lock_blank} },
	{ MODKEY,                    XKB_KEY_n,           toggleopacity,    {.f = 0.80f} },
	{ MODKEY,                    XKB_KEY_Return,      spawn,            {.v = paste_x} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,      spawn,            {.v = paste_c} },
	{ MODKEY,                    XKB_KEY_apostrophe,  spawn,            {.v = wmenucmd} },
	{ MODKEY,                    XKB_KEY_s,           spawn,            {.v = screenshot} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_i,           spawn,            {.v = killibus} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                        0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                            1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                    2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                        3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                       4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                   5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                     6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                      7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                     8),

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};

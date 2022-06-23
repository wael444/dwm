/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2;
static const unsigned int snap     = 16;
static const unsigned int gappx    = 16;

/* swallow, systray */
static const int swallowfloating         = 0;
static const unsigned int systraypinning = 1; /* pin on mon f+1 */
static const unsigned int systrayspacing = 2;
static const int systraypinningfailfirst = 1;
static int showsystray                   = 0;

/* bar */
static const int showbar     = 1;
static const int topbar      = 0;
static const int horizpadbar = 4;
static const int vertpadbar  = 6;
static const char *fonts[]   = { "monospace:size=9:Medium" };

/* colors */
static char col_bg[]     = "#000000";
static char col_bl[]     = "#404040";
static char col_gr[]     = "#606060";
static char col_ac[]     = "#005577";
static char col_fg[]     = "#dfdfdf";
static char *colors[][3] = {
	/*                 fg      bg      border   */
	[SchemeNorm]    = { col_fg, col_bg, col_bg },
	[SchemeTitle]   = { col_fg, col_bg, NULL   },
	[SchemeSel]     = { col_ac, col_bg, col_gr },
	[SchemeTagNorm] = { col_gr, col_bg, NULL },
	[SchemeTagSel]  = { col_fg, col_bg, NULL },
};

static char *scolor[] = { col_bg, col_bl, col_gr, col_ac, col_fg };

/* xresources */
ResourcePref resources[] = {
		{ "background",  STRING,  &col_bg },
		{ "color0",      STRING,  &col_bl },
		{ "color8",      STRING,  &col_gr },
		{ "foreground",  STRING,  &col_fg },
		{ "color4",      STRING,  &col_ac },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* rules */
static const Rule rules[] = {
	/* class         inst  title            tags mask  rsh  fl  tr  !sw  mon */
	{ "Firefox",     NULL, NULL,            1 << 8,   -1,   0,  0, -1,  -1 },
	{ "st-256color", NULL, NULL,            0,         0,   0,  1,  0,  -1 },
	{ "st-256color", NULL, "run",           0,         0,   1,  1,  1,  -1 },
	{ NULL,          NULL, "Event Tester",  0,        -1,   0,  0,  1,  -1 }, // xev
};

static const MonitorRule monrules[] = {
	/* mon  tag  lt  mfact  nmaster  sbar tbar */
	{  0,  -1,   0, -1,    -1,      -1,  -1 }, // primary monitor
	{  1,  -1,   0, -1,     0,      -1,  -1 }, // vertical secondary monitor
};

/* layout(s) */
static const float mfact        = 0.55;
static const int nmaster        = 1;
static const int resizehints    = 1;
static const int lockfullscreen = 1;
static const Layout layouts[]   = {
	{ "[]=", tile },
	{ "><>", NULL },
	{ "[M]", monocle },
};

/* internal keyboard keybindings */
static Key keys[] = {
	/* key mask         key           function              args */
	{ 0,XF86XK_AudioRaiseVolume,      spawn,                LAUNCHARG("volctl", "+10%") },
	{ 0,XF86XK_AudioLowerVolume,      spawn,                LAUNCHARG("volctl", "-10%") },
	{ MODKEY,           XK_space,     spawn,                LAUNCHARG("m", "run") },
	{ MODKEY,           XK_Return,    spawn,                LAUNCH("st") },
	{ MODKEY,           XK_a,         focusstack,           {.i = +1 } },
	{ MODKEY,           XK_d,         focusstack,           {.i = -1 } },
	{ MODKEY,           XK_w,         incnmaster,           {.i = +1 } },
	{ MODKEY,           XK_s,         incnmaster,           {.i = -1 } },
	{ MODKEY,           XK_f,         togglefloating,       {0} },
	{ MODKEY,           XK_g,         togglefakefullscreen, {0} },
	{ MODKEY,           XK_BackSpace, zoom,                 {0} },
	{ MODKEY,           XK_v,         focusmon,             {.i = +1 } },
	{ MODKEY,           XK_c,         tagmon,               {.i = +1 } },
	{ MODKEY|ShiftMask, XK_a,         setmfact,             {.f = -0.05} },
	{ MODKEY|ShiftMask, XK_d,         setmfact,             {.f = +0.05} },
	{ MODKEY|ShiftMask, XK_s,         setcfact,             {.f = +0.25} },
	{ MODKEY|ShiftMask, XK_w,         setcfact,             {.f = -0.25} },
	{ MODKEY,           XK_b,         togglebar,            {0} },
	{ MODKEY,           XK_z,         togglesystray,        {0} },
	{ MODKEY,           XK_x,         reload_xresources,    {0} },
	{ MODKEY|ShiftMask, XK_c,         killclient,           {0} },
	{ MODKEY|ShiftMask, XK_q,         quit,                 {0} },
	{ MODKEY|ShiftMask, XK_r,         quit,                 {1} }, 
	{ MODKEY,           XK_Tab,       view,                 {0} },
	{ MODKEY,           XK_0,         view,                 {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,         tag,                  {.ui = ~0 } },
	TAGKEYS(XK_1,0) TAGKEYS(XK_2,1) TAGKEYS(XK_3,2) TAGKEYS(XK_4,3)
	TAGKEYS(XK_5,4) TAGKEYS(XK_6,5) TAGKEYS(XK_7,6) TAGKEYS(XK_8,7)
	TAGKEYS(XK_9,8)

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, 
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click mask   key mask  bt  function        args */
	{ ClkLtSymbol,  0,        1,  setlayout,      {0} },
	{ ClkLtSymbol,  0,        3,  setlayout,      {.v = &layouts[2]} },
	{ ClkClientWin, MODKEY,   1,  moveorplace,    {.i = 0} },
	{ ClkClientWin, MODKEY,   2,  togglefloating, {0} },
	{ ClkClientWin, MODKEY,   3,  resizemouse,    {0} },
	{ ClkTagBar,    0,        1,  view,           {0} },
	{ ClkTagBar,    0,        3,  toggleview,     {0} },
	{ ClkTagBar,    MODKEY,   1,  tag,            {0} },
	{ ClkTagBar,    MODKEY,   3,  toggletag,      {0} },
};


/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;
static const unsigned int snap      = 16;
static const unsigned int gappx     = 16;

/* swallow, systray */
static const int swallowfloating    = 0;
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, 0: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */

/* bar */
static const int showbar            = 1;
static const int topbar             = 0;
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=9:Medium" };

/* colors */
static const char col_bg[]          = "#000000";
static const char col_gr[]          = "#202020";
static const char col_fg[]          = "#dfdfdf";
static const char *colors[][3]      = {
	/*                 fg      bg      border   */
	[SchemeNorm]   = { col_fg, col_bg, col_bg },
	[SchemeSel]    = { col_fg, col_gr, col_gr },
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
	{ MODKEY,           XK_space,     spawn,                LAUNCHARG("m", "run") },
	{ MODKEY,           XK_Return,    spawn,                LAUNCH("st") },
	{ MODKEY,           XK_a,         focusstack,           {.i = +1 } },
	{ MODKEY,           XK_d,         focusstack,           {.i = -1 } },
	{ MODKEY,           XK_w,         incnmaster,           {.i = +1 } },
	{ MODKEY,           XK_s,         incnmaster,           {.i = -1 } },
	{ MODKEY,           XK_f,         togglefloating,       {0} },
	{ MODKEY|ShiftMask, XK_f,         togglefakefullscreen, {0} },
	{ MODKEY,           XK_BackSpace, zoom,                 {0} },
	{ MODKEY,           XK_v,         focusmon,             {.i = +1 } },
	{ MODKEY,           XK_c,         tagmon,               {.i = +1 } },
	{ MODKEY|ShiftMask, XK_a,         setmfact,             {.f = -0.05} },
	{ MODKEY|ShiftMask, XK_d,         setmfact,             {.f = +0.05} },
	{ MODKEY|ShiftMask, XK_s,         setcfact,             {.f = +0.25} },
	{ MODKEY|ShiftMask, XK_w,         setcfact,             {.f = -0.25} },
	{ MODKEY,           XK_b,         togglebar,            {0} },
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


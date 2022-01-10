/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=9:Medium" };
static const char col_bg[]          = "#1d2021";
static const char col_gr[]          = "#3c3836";
static const char col_fg[]          = "#ebdbb2";
static const char *colors[][3]      = {
	/*                 fg      bg      border   */
	[SchemeNorm]   = { col_fg, col_bg, col_bg },
	[SchemeSel]    = { col_fg, col_gr, col_gr },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance  title            tags mask  rsh  isfloating  isterminal  noswallow  monitor */
	{ "Firefox",     NULL,     NULL,            1 << 8,   -1,   0,          0,          -1,        -1 },
	{ "st-256color", NULL,     NULL,            0,         0,   0,          1,           0,        -1 },
	{ "st-256color", NULL,     "run",           0,         0,   1,          1,           1,        -1 },
	{ NULL,          NULL,     "Event Tester",  0,        -1,   0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

static Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY,                       XK_space,     spawn,          LAUNCHARG("m", "run") },
	{ MODKEY,                       XK_Return,    spawn,          LAUNCH("st") },
	{ MODKEY,                       XK_b,         togglebar,      {0} },
	{ MODKEY,                       XK_a,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_d,         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_w,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_s,         incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_a,         setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_d,         setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_BackSpace, zoom,           {0} },
	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,         killclient,     {0} },
	{ MODKEY,                       XK_f,         togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,         togglefakefullscreen, {0} },
	{ MODKEY,                       XK_v,         focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_c,         tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                         0)
	TAGKEYS(                        XK_2,                         1)
	TAGKEYS(                        XK_3,                         2)
	TAGKEYS(                        XK_4,                         3)
	TAGKEYS(                        XK_5,                         4)
	TAGKEYS(                        XK_6,                         5)
	TAGKEYS(                        XK_7,                         6)
	TAGKEYS(                        XK_8,                         7)
	TAGKEYS(                        XK_9,                         8)
	{ MODKEY|ShiftMask,             XK_q,         quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,         quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


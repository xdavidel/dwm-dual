/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char statussep         = ';';      /* separator between status bars */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static const unsigned int baralpha = 0xc0;
static const unsigned int borderalpha = OPAQUE;
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
 };
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

/* #include "fibonacci.c" */
/* #include "grid.c" */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",    tile },    /* first entry is default */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
 	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "HHH",	grid },		/* Master in middle, slaves on sides */
	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define CTLKEY ControlMask
#define SFTKEY ShiftMask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include "shiftview.c"
#include "movestack.c"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, */
	/* { MODKEY|SFTKEY,             XK_Return, spawn,          {.v = termcmd } }, */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	/* { MODKEY|SFTKEY,                XK_Down,   incnmaster,     {.i = +1 } }, */
	/* { MODKEY|SFTKEY,                XK_Up,     incnmaster,     {.i = -1 } }, */
	{ MODKEY|SFTKEY,                XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|SFTKEY,                XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|SFTKEY,                XK_Down,   movestack,      {.i = +1 } },
	{ MODKEY|SFTKEY,                XK_Up,     movestack,      {.i = -1 } },
	{ MODKEY|CTLKEY,                XK_Left,   shiftview,      {.i = -1 } },
	{ MODKEY|CTLKEY,                XK_Right,  shiftview,      {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ALTKEY,                XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ALTKEY,                XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ALTKEY,                XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY|ALTKEY,                XK_k,      setcfact,       {.f = +0.20} },
	{ MODKEY|ALTKEY,                XK_j,      setcfact,       {.f = -0.20} },
	{ MODKEY|ALTKEY,                XK_Up,     setcfact,       {.f = +0.20} },
	{ MODKEY|ALTKEY,                XK_Down,   setcfact,       {.f = -0.20} },
	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	{ MODKEY|ALTKEY,                XK_0,      togglegaps,     {0} },
	{ MODKEY|ALTKEY|SFTKEY,         XK_0,      defaultgaps,    {0} },
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */
	/* { MODKEY,                       XK_Return, zoom,           {0} }, */
	/* { MODKEY,                       XK_Tab,    view,           {0} }, */
	/* { MODKEY|SFTKEY,             XK_c,      killclient,     {0} }, */
	{ MODKEY|CTLKEY,	        	XK_k,      cyclelayout,    {.i = -1 } },
	{ MODKEY|CTLKEY,                XK_j,      cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|SFTKEY,                XK_t,      setlayout,      {.v = &layouts[1]} },
	/* { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, */
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|SFTKEY,                XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|SFTKEY,                XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|SFTKEY,                XK_g,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|SFTKEY,                XK_f,      togglefloating, {0} },
	/* { MODKEY|SFTKEY,                XK_f,      setlayout,      {.v = &layouts[8]} }, */
	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|SFTKEY,                XK_0,      tag,            {.ui = ~0 } },
	/* { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
	/* { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, */
	/* { MODKEY|SFTKEY,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { MODKEY|SFTKEY,             XK_period, tagmon,         {.i = +1 } }, */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	/* { MODKEY|SFTKEY,             XK_q,      quit,           {0} }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1} },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1} },
	{ ClkLtSymbol,          0,              Button4,        cyclelayout,    {.i = +1} },
	{ ClkLtSymbol,          0,              Button5,        cyclelayout,    {.i = -1} },
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

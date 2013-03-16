/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-stlarch-medium-r-*-*-10-*-*-*-*-*-*-*"
                                      ","
                                      "-*-termsyn-medium-*-*-*-14-*-*-*-*-*-*-*";
#define NUMCOLORS 11
static const char colors[NUMCOLORS][ColLast][8] = {
/*   border     foreground background    */
   { "#002b36", "#839496", "#002b36" },  // 0 = normal
   { "#073642", "#fdf6e3", "#002b36" },  // 1 = selected
   { "#cb4b16", "#eee8d5", "#cb4b16" },  // 2 = urgent/warning
   { "#002b36", "#0087ff", "#002b36" },  // 3 = blue
   { "#002b36", "#d75f00", "#002b36" },  // 4 = orange
   { "#002b36", "#d33682", "#002b36" },  // 5 = magneta
   { "#002b36", "#5f8700", "#002b36" },  // 6 = green
   { "#002b36", "#dc322f", "#002b36" },  // 7 = red
   { "#002b36", "#5f5faf", "#002b36" },  // 8 = purple
   { "#000000", "#000000", "#000000" },  // unusable
   { "#002b36", "#00afaf", "#002b36" },  // 9 = cyan
};
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gap pixel between windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
/* tagging */
static const char *tags[] = { "web", "dev", "misc", "chat" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium", NULL,       NULL,       1 << 0,       False,       -1 },
	{ "Skype",    NULL,       NULL,       1 << 3,       True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False;/* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MOD4   Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font,
                                  "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],
                                  "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *volume_increase[] = { "amixer", "set", "Master", "3%+", "unmute", NULL };
static const char *volume_decrease[] = { "amixer", "set", "Master", "3%-", "unmute", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_F1,                     0)
	TAGKEYS(                        XK_F2,                     1)
	TAGKEYS(                        XK_F3,                     2)
	TAGKEYS(                        XK_F4,                     3)
/*
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
*/
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
  {  MOD4,                        XK_Up,     spawn,          {.v = volume_increase}},
  {  MOD4,                        XK_Down,   spawn,          {.v = volume_decrease}},
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

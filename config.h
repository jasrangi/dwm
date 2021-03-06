/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Ubuntu Mono:style=Bold:size=16:antialias=true:autohint=true", "Font Awesome 5 Free Solid:style=Solid:size=16:antialias=true" };
static const char dmenufont[]       = "Ubuntu Mono::style=Bold:size=16:antialias=true:autohint=true";
/* background of top bar */
static const char col_gray1[]       = "#222222";
/* inactive window border */
static const char col_gray2[]       = "#140202";
/* font */
static const char col_gray3[]       = "#eeeeee";
/* current tag and window name text*/
static const char col_gray4[]       = "#eeeeee";
/* active window border */
static const char col_gray5[]       = "#444444";
/* top bar second */
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray5 },
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
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "| ???",      tile },    /* first entry is default */
	{ "| ???",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
/* custom cmds */
static const char *firefox[]  = { "firefox", NULL };
static const char *browser[] = { "librewolf", NULL };
static const char *galc[] = { "galculator", NULL };
static const char *volmute[]  = { "pamixer", "-t", NULL };
static const char *voldown[]  = { "pamixer", "-d", "5", NULL };
static const char *volup[]    = { "pamixer", "-i", "5", NULL };
static const char *play_pause[] = { "playerctl", "play-pause", NULL };
static const char *play_prev[] = { "playerctl", "previous", NULL };
static const char *play_next[] = { "playerctl", "next", NULL };
static const char *screenshot[] = { "scrot", "-s", "/home/jas/Pictures/screenshots/%m-%d-%Y-%T.png", NULL };
static const char *slock[]    = { "slock", NULL };
static const char *sleep_mode[]    = { "systemctl", "suspend", NULL };
static const char *power_down[] = { "shutdown", "now", NULL };
static const char *init_audio[] = { "alsactl", "init", NULL };


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
	{ Mod1Mask,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* start custom */
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,		XK_f,	   spawn,          {.v = firefox } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = browser } },
	{ 0,                    XF86XK_Calculator, spawn,          {.v = galc } },
	{ 0,                     XF86XK_AudioMute, spawn,          {.v = volmute } },
	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = voldown } },
	{ 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = volup } },
	{ 0,                     XF86XK_AudioPlay, spawn,          {.v = play_pause } },
	{ 0,                     XF86XK_AudioPrev, spawn,          {.v = play_prev } },
	{ 0,                     XF86XK_AudioNext, spawn,          {.v = play_next } },
	{ 0,                            XK_Print,  spawn,          {.v = screenshot } },
	{ MODKEY|ShiftMask,		XK_l,	   spawn,          {.v = slock } },
	{ MODKEY|ShiftMask,		XK_s,	   spawn,          {.v = sleep_mode } },
	{ MODKEY|ShiftMask,		XK_p,	   spawn,          {.v = power_down } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = init_audio } },
	/* end custom */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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


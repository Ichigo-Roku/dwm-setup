/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
#define NUMCOLORS 6 /* need at least 3 */

static const char colors[NUMCOLORS][ColLast][8] = {
	/* border   foreground  background */
	{ "#262729", "#FAFAFA", "#262729" },  /* 0 = normal */
	{ "#262729", "#1793D1", "#262729" },  /* 1 = selected */
	{ "#262729", "#0066ff", "#262729" },  /* 2 = urgent/warning */
	{ "#262729", "#ffffff", "#262729" },  /* 3 = error */
	{ "#262729", "#E04614", "#262729" },  /* 4 = orange */
	{ "#262729", "#6D9EAC", "#262729" },  /* 5 = blue */
	/* add more here */
};

static const char font[]            = "-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 20;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const unsigned int titlemaxw = 600; 	/* maximum title width in pixel */

/* layout(s) 1st part */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "><>",      NULL },
	{ "[]=",      tile },
	{ "[M]",      monocle },
};

/* tagging */
static const Tag tags[] = {
  /* name		layout		mfact	nmaster */
  { "dev",      	&layouts[2],	-1,	-1 },
  { "web",		&layouts[2],	-1,	-1 },
  { "irc",      	&layouts[2],    -1,    	-1 },
  { "torrent",      	&layouts[2],    -1,    	-1 },
  { "anime",      	&layouts[2],    -1,     -1 },
  { "misc",      	&layouts[2],    -1,     -1 },
};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) 2nd part */
static const float mfact      = 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;     /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ WINKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] =	{ "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *halt[]  = { "sh", ".scripts/halt.sh", NULL };
static const char *reboot[]  = { "sh", ".scripts/reboot.sh", NULL };
static const char *scrot[]  = { "sh", ".scripts/scrot.sh", NULL };
static const char *volup[]  = { "sh", ".scripts/volup.sh", NULL };
static const char *voldown[]  =	{ "sh", ".scripts/voldown.sh", NULL };
static const char *mute[]  = { "sh", ".scripts/mute.sh", NULL };
static const char *brightup[] = { "sh", ".scripts/brightup.sh", NULL };
static const char *brightdown[] = { "sh", ".scripts/brightdown.sh", NULL };
static const char *kbdlightup[] = { "sh", ".scripts/kbdlightup.sh", NULL };
static const char *kbdlightdown[] = { "sh", ".scripts/kbdlightdown.sh", NULL };
static const char *lock[] = { "xtrlock", NULL };

static Key keys[] = {
	/* modifier                     key				function        argument */
	{ MODKEY,                       XK_p,				spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_h,				spawn,          {.v = halt } },
	{ MODKEY|ShiftMask,             XK_r,				spawn,          {.v = reboot } },
	{ 0,				XF86XK_LaunchB,			spawn,          {.v = scrot } },
	{ 0,				XF86XK_AudioRaiseVolume,	spawn,          {.v = volup } },
	{ 0,				XF86XK_AudioLowerVolume,	spawn,          {.v = voldown } },
	{ 0,				XF86XK_AudioMute,		spawn,          {.v = mute } },
	{ 0,				XF86XK_MonBrightnessUp,		spawn,          {.v = brightup } },
	{ 0,				XF86XK_MonBrightnessDown,	spawn,          {.v = brightdown } },
	{ 0,				XF86XK_KbdBrightnessUp,		spawn,          {.v = kbdlightup } },
	{ 0,				XF86XK_KbdBrightnessDown,	spawn,          {.v = kbdlightdown } },
	{ WINKEY,                       XK_l,      			spawn,          {.v = lock } },
	{ MODKEY,                       XK_b,      			togglebar,      {0} },
	{ MODKEY,                       XK_j,      			focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      			focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      			setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      			setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 			zoom,           {0} },
	{ MODKEY,                       XK_Tab,    			view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      			killclient,     {0} },
	{ MODKEY,                       XK_t,      			setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      			setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  			togglefloating, {0} },
	{ MODKEY,                       XK_agrave,			view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave,			tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  			focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  			tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon,			tagmon,      	{.i = +1 } },
	TAGKEYS(                        XK_1,                     	0)
	TAGKEYS(                        XK_2,                        	1)
	TAGKEYS(                        XK_3,                      	2)
	TAGKEYS(                        XK_4,                    	3)
	TAGKEYS(                        XK_5,                     	4)
	TAGKEYS(                        XK_6,                         	5)
	TAGKEYS(                        XK_7,                        	6)
	TAGKEYS(                        XK_8,                    	7)
	TAGKEYS(                        XK_9,                      	8)
	{ MODKEY|ShiftMask,             XK_q,				quit,		{0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

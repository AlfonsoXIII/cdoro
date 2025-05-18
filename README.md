# C pomoDORO

A pure C based *pomodoro studying technique* in-terminal app, with a subtle yet sweet client-server architecture flavour.

<img src="logo.png" alt="cdoro logo image" style="max-width: 300px;">

## Roadmap 
So far, a compact yet functional path is foreseen in the near future.

- ~~A logo~~
- A daemon-based pomodoro manager.
- A pipeline-based client to interface pomodoro actions.
- Dynamic focusing and break timers.
- Pomodoro stacking and/or activities planner.
- Notifications customization.

## Dependencies 󱧘

- Pretty much any not so outdated C compiler, [gcc](https://gcc.gnu.org/) or [icx](https://www.intel.com/content/www/us/en/developer/tools/oneapi/dpc-compiler-download.html) being recommended
- A suitable notification daemon for your distribution, with an emphasis on [mako](https://github.com/emersion/mako) and [dunst](https://github.com/dunst-project/dunst)
- [notify-send](https://man.archlinux.org/man/notify-send.1.en) to manage and push notifications, alternatively check the [improved reimplementation](https://github.com/jefvel/notify-send-improved) by @jefvel


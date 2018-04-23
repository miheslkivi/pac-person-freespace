# pac-person-freespace

Pac-person freespace continuum undiscreted ( PPFCU )

Driving and shooting game that gets some inspiration from Pac-man. 

It is undiscreted / de-discreted Pacman in the sense that moving-angle, velocity and both coordinates can be decimal numbers, not just whole-numbers / integers, and not just 90 degree turns.

The big 10 megabyte file "pac-island-overlay.png" is not absolutely necessary, but it makes the game look nicer.

Keeping view rotation on may be too CPU heavy, depending on your computer and other things. Many will prefer fixed view-angle anyway. Higher zoom and smaller window helps speed.

F9 switches view rotation. F10 switches follow. Then it is good to look around the arena by pointing with mouse and pressing "c".

F5 reloads configuration file, if it is altered in a text editor during game.

F7 makes ghosts escape, instead of attacking, if that button is enabled in configuration file.

There are 3 types of terrain: meadow, hill and water. Pac-Person and ghosts can move only in meadow. They can see over water / sea / lake if their line of sight is not blocked by hill terrain and distance is not too much ( that length can be adjusted on configuration file ). Pac-person can also shoot missiles over water. 

Press m to lay one mine. If a yellow light is on a mine center, it can not explode. Mines have a safety feature that deactivates them near Pac-person. 

Default mode has all ghosts visible all the time, but this game is better if ghosts can be seen only in line of sight. Use --ghostshide command line option or "ghinv" config file setting for this more advanced mode.

Mines turn color if they hear or see ghosts. If they see a ghost, i.e. their line of sight is not blocked by a hill and distance is close enough, they report it's precise location. Mines can hear ghosts over hills but can not report precise location just by hearing. Pac-person has some information about distance of the closest ghost, if not too far.

VLC media player can be controlled from inside the game:

Key_6 = play / pause media

Key_7 = skip_back_media 4 seconds

It just works or not, without needing anything else from user. If it works, it uses MPRIS and dbus inter process communication. Especially useful if listening to audiobooks while playing.

This game has no sound of it's own, at least yet.

This can be 2 person game so that one drives with keyboard and other shoots with mouse, especially if used on a computer connected to a big TV in front of a sofa / couch.

This game is better if used with a second TV / display / monitor where the optional controller/info program window is placed. See:

https://github.com/miheslkivi/PPFCU-controller

The buttons might work with a touch screen. 

One thing that can be done only from that extra software is automatic mine laying with chosen separations.

Any image editor ( like GIMP ) can be used for editing arenas and for making new arenas. The color values have to be precise. Turn off anti-aliasing. Derive optional overlay image from it's arena picture by blurring, adding pixel noise and using any artistic ideas that preserve distinctions between the 3 terrain types.

Currently no configuration file where keys / buttons could be set. If compiling from source, the file "toplevel.cpp" has keys. Search for string "actions.insert" and setting up keys is as easy as any config file could be.

Default data file directory is now:

../pac-person-freespace-0.9.2/filesforbin/

It is near beginning of main.cpp, if it needs to be altered. May be easiest to rename directory if there is a problem.

---------------------------------------

With further developments, probably lots can be done with performance. OpenGL use is unclear. Might be better to try Vulkan?

This could be turned into a geography lesson by converting some actual map to arena.
Maybe switch water and meadow so movement happens in water.

The collected things could be a list of something that needs to be learned, for example, chemical elements.

Derived from Qt4 example software "ported asteroids". Small remnants of it are still there.

Most was done with Qt4 and ported to Qt5 on last stages.

BSD license





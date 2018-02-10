# pac-person-freespace

Pac-person freespace continuum undiscreted ( PPFCU )

Driving and shooting game that gets some inspiration from Pac-man. 

It is undiscreted Pacman in the sense that moving-angle, velocity and both coordinates can be decimal numbers, not just whole-numbers / integers, and not just 90 degree turns.

Copy the data files and configuration files to the same directory where the binary is.

The big 10 megabyte file "pac-island-overlay.png" is not absolutely necessary, but it makes the game look nicer.

Keeping view rotation on may be too CPU heavy, depending on your computer and other things. Many will prefer fixed view-angle anyway. Higher zoom and smaller window helps speed.

There are 3 types of terrain: meadow, hill and water. Pac-Person and ghosts can move only in meadow. They can see over water / sea / lake if their line of sight is not blocked by hill terrain and distance is not too much ( that length can be adjusted on configuration file ). Pac-person can also shoot missiles over water. 

Press m to lay a mine. If a yellow light is on a mine, it can not explode. Mines have a safety feature that makes them stand down near Pac-person. Press w to make all mines stand down. 

Default mode has all ghosts visible all the time, but this game is better if ghosts can be seen only in line of sight. Use --ghostshide command line option for this more advanced mode.

Mines turn color if they hear or see ghosts. If they see a ghost, i.e. their line of sight is not blocked by a hill and distance is close enough, they report it's precise location. Mines can hear ghosts over hills but can not report precise location just by hearing. Pac-person has some information about the closest ghost.

VLC media player can be controlled from inside the game:

Key_6 = play / pause media
Key_7 = skip_back_media 4 seconds

It uses MPRIS and dbus inter process communication. 

This can be 2 person game so that one drives with keyboard and other shoots with mouse, especially if used on a computer connected to a big TV in front of a sofa / couch.

This game is better if used with a second TV / display / monitor where the optional controller/info program window is placed. See:

https://github.com/miheslkivi/PPFCU-controller

The buttons might work with a touch screen. 

Any image editor ( like GIMP ) can be used for editing arenas and for making new arenas. The color values have to be precise. Turn off anti-aliasing. Derive optional overlay image from it's arena picture by blurring, adding pixel noise and using any artistic ideas.

Currently no configuration file where keys / buttons could be set. If compiling from source, the file "toplevel.cpp" has keys. Search for string "actions.insert" and setting up keys is as easy as any config file could be.

---------------------------------------

With further developments, probably lots can be done with performance. OpenGL use is unclear. Might be better to try Vulkan?

Derived from Qt4 example software "ported asteroids". Small remnants of it are still there.

Most was done with Qt4 and ported to Qt5 on last stages.

Version 0.9 or alpha.

BSD license





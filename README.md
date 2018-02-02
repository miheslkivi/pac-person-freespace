# pac-person-freespace

Pac-person freespace continuum undiscreted ( PPFCU )

Driving and shooting game that gets some inspiration from Pac-man.

It is undiscreted Pacman in the sense that moving-angle, velocity and both coordinates can be decimal numbers, 
not just whole-numbers / integers, and not just 90 degree turns.

Copy the data files and configuration files to the same directory where the binary is.

The big 10 megabyte file "pac-island-overlay.png" is not absolutely necessary, but it makes the game look nicer.

Keeping view rotation on may be too CPU heavy, depending on your computer and other things. Many will prefer fixed view angle anyway. Higher zoom and smaller window helps speed.

With further developments, probably lots can be done with performance. OpenGL use is unclear. Might be better to try Vulkan?



Derived from Qt4 example software "ported asteroids". Small remnants of it are still there.

Most was done with Qt4 and ported to Qt5 on last stages.

Version 0.9

BSD license





# Pyramid
## A Free UI

C++ has a few different UIs to choose from, there is WxWidgets, Qt, GTK+ and probably more I don't know about. The issue I've had with all of them is licensing. Can I statically link and not have the gestapo banging on my door? Do I need to give my source code away to everyone? Do I need to pay a bunch of money to do whatever I want? The goal of this project is answer, all those questions. You can basically do whatever you want.

I do no have a Mac, so Apple support will be limited. The UI is drawn using SDL2, so these are non-native widgets.

This is just designed to be a widget tool kit. It interacts with simplexsdl (a SDL2 wrapper) to draw widgets on the screen. The drawing is actually all done with the SDL2 library. All the backend file handling, string functions, singleton handling is done by simplextk.

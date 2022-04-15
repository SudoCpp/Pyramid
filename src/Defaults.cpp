#include "Theme.hpp"

#define PYRAMID_THEME_DOTNET 1
#define PYRAMID_THEME_GNOME 2
#define PYRAMID_THEME_QT 3

#ifndef PYRAMID_THEME
#error "Pyramid UI requires a style"
#elif PYRAMID_THEME == PYRAMID_THEME_DOTNET
#include "DefaultsDotNet.cpp"
#elif PYRAMID_THEME == PYRAMID_THEME_GNOME
#include "DefaultsGnome.cpp"
#elif PYRAMID_THEME == PYRAMID_THEME_QT
#include "DefaultsQt.cpp"
#else
#error "Pyramid UI requires a valid style"
#endif
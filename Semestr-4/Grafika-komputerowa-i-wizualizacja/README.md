
# Grafika komputerowa i wizualizacja

<br>

## About 

This document provides instructions for running programs using the library [GLFW](https://www.glfw.org/). \
GLFW is a library that allows you to create windows, handle input and events in applications using OpenGL, Vulkan, and other graphics APIs.


## Project setup in Visual Studio


### Dodaj Ścieżki do Nagłówków GLFW
> Właściwosi projektu -> “Konfiguracja właściwości” > “C/C++” > “Dodatkowe katalogi plików nagłówkowych" \
> Edytuj i dodaj `C:\ścieżka_do_glfw\include`

### Dodaj Ścieżki do Bibliotek GLFW
> “Konfiguracja właściwości” > “Linker” > “Ogólne” > “Dodatkowe katalogi bibliotek” \
> Edytuj i dodaj `C:\ścieżka_do_glfw\lib-vc2022`

### Linkowanie z Biblioteką GLFW
> “Linker” > “Dane wejściowe” > “Dodatkowe zależności” \
> Edytuj i dodaj `glfw3.lib  opengl32.lib`

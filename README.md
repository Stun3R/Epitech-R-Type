# RTYPE DOCUMENTATION

by Maxime Barbier
<p>&nbsp;</p>

## Summary
1. [Remotes](#REMOTES)
2. [Introduction](#INTRO)
3. [Dependencies](#DEPENDENCIES)
4. [Create Conan build folder](#create-conan-build-folder)
5. [.gitignore](#.gitignore)
<p>&nbsp;</p>

## INTRO

R-type is a 3rd years project at EPITECH. You need to recreate the r-type game but with multiplayer and with ECS.

## REMOTES

to add remotes to conan you need to do :
conan remote add <NAME> <URL>

and the only remote to add is :
https://api.bintray.com/conan/conan-community/conan
https://api.bintray.com/conan/conan-center
https://api.bintray.com/conan/bincrafters/public-conan

name it randomly ;)
<p>&nbsp;</p>

## DEPENDENCIES

You will need somes package to install all libs. There is all of them :

sudo dnf install libfontenc-devel libXaw-devel libXcomposite-devel libXdmcp-devel libXtst-devel libXres-devel xorg-x11-xkb-utils-devel libXScrnSaver-devel libXvMC-devel xorg-x11-xtrans-devel xcb-util-wm-devel xcb-util-keysyms-devel xcb-util-renderutil-devel libXdamage-devel xkeyboard-config-devel libXcursor-devel libXinerama-devel libXrandr-devel libXv-devel
<p>&nbsp;</p>

## CREATE CONAN BUILD FOLDER

In order to create conan build architecture, you may need this command:

>mkdir build && cd build && conan install .. --build missing && cmake .. -G “UnixMakefiles” && cmake –build

This command will download and install all the libs contain in "conanfile.txt".
Two files will be created "conanbuildinfo.cmake" and "conanbuildinfo.txt" and they are necessary to compile so copy them to the root of the repo.
<p>&nbsp;</p>

## .gitignore

Some files are undesirable on github ! Don't forget to add all of these files to your ```.gitignore``` file.

- CMakeFiles
- build
- cmake_install.cmake
- CMakeCache.txt
- conanbuildinfo.cmake
- conanbuildinfo.txt
- conaninfo.txt
- rtype_server
- rtype_client
Game of Life
-----------------
Conway's Game of Life is a simple cellular automaton based on a few rules:

1. Any live cell with two or three live neighbours survives.
2. Any dead cell with three live neighbours becomes a live cell.
3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.

What this project aims to do is simulate it using the *Simple Directmedia Layer*(SDL) library for video rendering.

How to build the project
----------------------
To build this project, you must have:
- CMake and a C compiler;
- You also must have the SDL2 library installed.
Check out [the libsdl wiki guide](https://wiki.libsdl.org/Installation) to learn how to install it on your machine;
- Finally, you should have git, so that you can clone the repository(though with GitHub you can download the source in your browser)

After downloading the project or cloning the repository, follow these steps(on Linux):

```shell script
user@user-desktop:~/GameOfLife$ cmake .
user@user-desktop:~/GameOfLife$ make
```

And you're done! Your binary/executable file will be in the `GameOfLife/bin` directory.
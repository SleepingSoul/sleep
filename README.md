# sleep
2D game engine written in modern C++. **Currently in development**, no stable builds here. But we have many things already done :3

The architectural model now is component system, but will be changed in future to [ECS](https://www.youtube.com/watch?v=NTWSeQtHZ9M&t=174s).

Now uses [OpenGL](https://www.opengl.org/) for rendering, but will be changed to [Vulkan](https://www.khronos.org/vulkan/) soon.

This engine stands for __simplicity, good architecture, fast and smooth runtime__.

## Compatibility
Currently engine works only on Windows and Visual Studio IDE.\
We have some crossplatform plans on future. Since we use crosspltform libraries it can work on anything. Also some day we will migrate to cmake and it will be possible to use any of IDEs.

## How to install and run the example scene?
This is quite easy to do. You should do the following things:
- Clone this repository and it's submodules. You can do it with running this command in Git Bash:\
`git clone --recursive https://github.com/SleepingSoul/sleep`\
If you already cloned it without submodules, you should run\
`git submodule update --init --recursive`
- Go to *scripts* and run *install_dependencies.bat*. It will install all project dependencies and create a package. To read more what do we use for it, read [this page](https://github.com/SleepingSoul/sleep/wiki/How-install-dependencies-works) in our Wiki.
- In the end of this script there will be this instruction:\
`Install-Package sleep_dependencies -Source "..."`\
  with your native path output in console. You should copy it, go to\
*Visual Studio -> Tools -> Nuget -> Management Console*\
and run this command there.
- PROFIT. Thats all, pretty easy in my opinion. Now just compile end run example scene :)

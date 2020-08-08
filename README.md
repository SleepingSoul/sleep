# sleep game engine
This is what happens when 2 lazy programmers decide to create engine

| Platform / configuration      | Build status (master) |
|-------------------------------|-----------------------|
| Windows x86 Debug (VS 2017)   |     [![Build status](https://ci.appveyor.com/api/projects/status/6q5iwq0663gqc14m?svg=true)](https://ci.appveyor.com/project/SleepingSoul/sleep)    |
| Windows x86 Release (VS 2017) |     [![Build status](https://ci.appveyor.com/api/projects/status/6ico441n2483p30i?svg=true)](https://ci.appveyor.com/project/SleepingSoul/sleep-isewm)    |
| Windows x64 Debug (VS 2017)   |     [![Build status](https://ci.appveyor.com/api/projects/status/cr8ingqk399vsywd?svg=true)](https://ci.appveyor.com/project/SleepingSoul/sleep-md0ar)    |
| Windows x64 Release (VS 2017) |     [![Build status](https://ci.appveyor.com/api/projects/status/ea3sbufiingdu2ip?svg=true)](https://ci.appveyor.com/project/SleepingSoul/sleep-a0y8m)    |

**Currently in development**, no stable builds here. But we have many things already done :3

The architectural model now is component system, but will be changed in future to [ECS](https://www.youtube.com/watch?v=NTWSeQtHZ9M&t=174s).

Uses [OpenGL](https://www.opengl.org/) for rendering.

This engine stands for:
- simplicity
- clear code
- good architecture
- fast and smooth runtime

## Compatibility
Engine works on Windows under either x86 or x64.
It required Visual Studio IDE to work with.

## How to install and run the example scene?
This is quite easy to do. You should follow these steps:
- Clone this repository and it's submodules. Run:\
`git clone --recursive https://github.com/SleepingSoul/sleep`\
If you already cloned it without submodules, you should then run:\
`git submodule update --init --recursive`
- Go to *scripts* and run *install_dependencies.bat*. It will install all project dependencies and create a package. To read more what do we use for it, read [this page](https://github.com/SleepingSoul/sleep/wiki/How-install-dependencies-works) in our Wiki.
- In the end of this script there will be this instruction:\
`Install-Package sleep_dependencies -Source "..."`\
  with your native path output in console. You should copy it, go to\
*Visual Studio -> Tools -> Nuget -> Management Console*\
and run this command there.
- Thats all Now, just compile end run example scene :)

@echo Project dependencies will be installed with vcpkg.

cd ..\vcpkg

FOR %%P IN (opengl glfw3 glm glad stb spdlog nlohmann-json) DO vcpkg.exe install %%P

cd ..\scripts

@echo Done.
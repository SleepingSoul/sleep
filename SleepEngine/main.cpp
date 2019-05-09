#include <stdafx.h>
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Engine/Utils/unit_utils.h>
#include <Engine/object_shortcuts.h>
#include <Demos/Bubbles/bubbles_demo.h>
#include <Demos/test_relative_transform.h>
#include <Engine/Jobs/JobSystem.h>
#include <Engine/Render/UpdateRenderBridge.h>

// settings
namespace
{
    // todo move to config
	size_t const WindowWidth = 1920;
	size_t const WindowHeight = 1080;
}

int main()
{
    EASY_PROFILER_ENABLE;

    slp::Game game(WindowWidth, WindowHeight);

    game.getClock().setFPS(60.f);
    //game.getClock().setRestrictFPS(true);

    game.getResourceManager().preload();
    game.addScene(initBubbleDemoScene);
	game.run();

    profiler::dumpBlocksToFile("../profiles/last_session_profile.prof");
    return 0;
}

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <sol/sol.hpp>


int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	{
		printf("SDL Initialization failed: %s\n", SDL_GetError());
		return -1;
	}

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("print('Hello from Lua!')");

	glm::vec2 velocity = glm::vec2(2.0, -1.0);

	std::cout << "Hello, world! \n";

	// Your SDL code here...

	SDL_Quit(); // Clean up before exiting
	return 0;
}

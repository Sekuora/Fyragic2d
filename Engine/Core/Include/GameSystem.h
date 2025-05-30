#pragma once

class SDL_Window;
class SDL_Renderer;


const float FYR_milliseconds = 1000.0f;
const int FYR_fps = 1000;
const int FYR_millisecondsPerFrame = FYR_milliseconds / FYR_fps;

class Game
{

public:
	Game();
	~Game();

	// Entry Point
	void Start();

	// Runtime game process
	void Run();

	// End
	void End();

	// Pre Process Setup
	void Setup();

	// Process Functions
	void ProcessInput();
	void Update();
	void Render();


	unsigned int windowWidth;
	unsigned int windowHeight;

private:
	/**
	* @brief SDL Window for Fyragic Engine Games
	**/
	SDL_Window* window;

	/**
	* @brief SDL Renderer for Window
	**/
	SDL_Renderer* renderer;

	/**
	* @brief Check Is Running
	**/
	bool isRunning;

	/*
	* @brief Track previous frame milliseconds for constant framerate implementation
	*/
	int previousFrameMilliseconds;

	/*
	* @brief The difference in ticks since the last frame in terms of seconds
	*/
	double deltaTime;

};

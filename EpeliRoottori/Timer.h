#ifndef TIMER_H
#define TIMER_H

// GLEW
#include "GL\glew.h"

// GLFW
#include "GLFW\glfw3.h"

class Timer
{
public:
	Timer();
	~Timer();

	static GLfloat GetGlobalTime(); // Palauttaa globaalin ajan millisekunneissa
	void SetTimer();
	GLfloat GetLocalTime(); // Palauttaa paikallisen ajan millisekunneissa
	GLfloat Start(); // Aloittaa ajan laskemisen
	GLfloat Pause(); // Pys‰ytt‰‰ ja jatkaa ajan laskemista
	GLfloat Stop(); // Pys‰ytt‰‰ ajastimen
	bool IsStarted(); // Palauttaa arvon, joka kertoo onko ajastin k‰ynniss‰ vai ei
	bool IsPaused(); // Palauttaa arvon, joka kertoo onko ajastin pys‰ytetty vai ei

private:
	GLfloat startTime;
	GLfloat stopTime;
	GLfloat pauseTime;
	GLfloat localTime;
	bool started;
	bool paused;
};

#endif
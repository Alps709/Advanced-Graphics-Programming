
// Library Includes
#include <chrono>

// Local Includes

// This Includes
#include "clock.h"


// Implementation
//****************************************************
// CClock: CClock Class Constructor
// @author: 
// @parameter: No parameters
//
// @return: none
//*****************************************************
CClock::CClock()
	: m_fTimeElapsed(0.0f)
	, m_fDeltaTime(0.0f)
{

}

//****************************************************
// ~CClock: CClock Class Destructor
// @author: 
// @parameter: No parameters
//
// @return: none
//*****************************************************
CClock::~CClock()
{

}

//****************************************************
// Initialise: CClock Class Initialiser - sets the first time values
// @author: 
// @parameter: No parameters
//
// @return: true if initialisation is successful, false if not
//*****************************************************
bool CClock::Initialise()
{
	m_fCurrentTime = std::chrono::high_resolution_clock::now();
	return (true);
}

//****************************************************
// Process: processes the change in time since it was last called
// @author:
// @parameter: No parameters
//
// @return: void
//*****************************************************
void
CClock::Process()
{
	m_fLastTime = m_fCurrentTime;

	m_fCurrentTime = std::chrono::high_resolution_clock::now();

	//Get change in time as microseconds so that level of precision is stored after the decimal place when converted to milliseconds
	m_fDeltaTime = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(m_fCurrentTime - m_fLastTime).count());

	//Convert to milliseconds
	m_fDeltaTime /= 1000.0;
	
	m_fTimeElapsed += m_fDeltaTime;
}

//****************************************************
// GetDeltaTick: gets the current delta tick value
// @author: 
// @parameter: No parameters
//
// @return: the current delta tick value
//*****************************************************
double CClock::GetDeltaTick() const
{
	return (m_fDeltaTime);
}

//Get time elapsed in milliseconds
double CClock::GetTimeElapsedMS() const
{
	return (m_fTimeElapsed);
}

//Get time elapsed in seconds
double CClock::GetTimeElapsedS() const
{
	return (m_fTimeElapsed / 1000.0);
}

double CClock::GetCurrentTime() const
{
	auto current_time = std::chrono::system_clock::now();
	auto duration_in_seconds = std::chrono::duration<double>(current_time.time_since_epoch());
	return duration_in_seconds.count();
}

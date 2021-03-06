/**
 * @file Input_Manager.hpp
 * @author Pablo Rodriguez Zurro (przuro@gmail.com)
 * @brief Class that checks and saves the state of the input
 * @version 0.1
 * @date 08-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_INPUT_MANAGER_H_
#define OPENGL_SCENE_INPUT_MANAGER_H_

#include <Declarations.hpp>

#include <SFML/System.hpp>

using namespace sf;

namespace prz
{
	
	/**
 	 * @brief Class that checks and saves the state of the input
	 * 
	 */
	class Input_Manager
	{
	public:

		/**
		 * @brief Get an static instance object of this class
		 *
		 * @return InputManager&
		 */
		static Input_Manager& instance()
		{
			static Input_Manager instance;
			return instance;
		}

	public:

		/**
		 * @brief Update the keyboard state with the input event
		 *
		 * @param event
		 */
		void update(Event& event)
		{
			switch (event.type)
			{
			case Event::KeyPressed:

				keysPressed_[event.key.code] = true;

				break;

			case Event::KeyReleased:

				keysPressed_[event.key.code] = false;

				break;

			case Event::MouseButtonPressed:

				isMousePressed_ = true;

				break;

			case Event::MouseButtonReleased:

				isMousePressed_ = false;
				break;

			case Event::MouseMoved:

				prevMouseX_ = curMouseX_;
				prevMouseY_ = curMouseY_;

				curMouseX_ = event.mouseMove.x;
				curMouseY_ = event.mouseMove.y;

				break;
			}
		}

	public:

		/**
		 * @brief Get the state of a key
		 *
		 * @param key
		 * @return true
		 * @return false
		 */
		bool is_key_pressed(const PKey& key) const
		{
			return keysPressed_.count(key) == 1 && keysPressed_.at(key) == true;
		}

		/**
		 * @brief return if mouse is pressed
		 * 
		 * @return true 
		 * @return false 
		 */
		bool is_mouse_pressed()
		{
			return isMousePressed_;
		}

	public:
		
		/**
		 * @brief return the current mouse position vector
		 * 
		 * @return PUVec2 
		 */
		PUVec2 current_mouse_position()
		{
			return PVec2(curMouseX_, curMouseY_);
		}

		/**
		 * @brief return the previous mouse position vector
		 * 
		 * @return PUVec2 
		 */
		PUVec2 previous_mouse_position()
		{
			return PVec2(prevMouseX_, prevMouseY_);
		}

	public:

		/**
		 * @brief return the current mouse x position
		 * 
		 * @return const unsigned& curMouseX 
		 */
		const unsigned int& curMouseX()
		{
			return curMouseX_;
		}

		/**
		 * @brief return the current mouse y position
		 * 
		 * @return const unsigned& curMouseY 
		 */
		const unsigned int& curMouseY()
		{
			return curMouseY_;
		}

		/**
		 * @brief return the previous mouse x position
		 * 
		 * @return const unsigned& prevMouseX 
		 */
		const unsigned int& prevMouseX()
		{
			return prevMouseX_;
		}

		/**
		 * @brief return the previous mouse y position
		 * 
		 * @return const unsigned& prevMouseY 
		 */
		const unsigned int& prevMouseY()
		{
			return prevMouseY_;
		}

	private:

		/**
		 * @brief Construct a new Input Manager object, private to avoid undesired instantiation
		 *
		 */
		Input_Manager():
			isMousePressed_(false)
		{
			curMouseX_ = prevMouseX_ = curMouseY_ = prevMouseY_ = 0;
		}

	private:

		PMap< PKey, bool > keysPressed_;

	private:
	
		unsigned int  curMouseX_, prevMouseX_;
		unsigned int  curMouseY_, prevMouseY_;

	private: 

		bool isMousePressed_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_INPUT_MANAGER_H_

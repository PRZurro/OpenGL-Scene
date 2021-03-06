#include <Shader_Program.hpp>

namespace prz
{
	const Shader_Program* Shader_Program::activeShaderProgram_ = nullptr;
	unsigned int Shader_Program::instanceCount_ = 0;

	bool Shader_Program::link()
	{
		glLinkProgram(programObjID_);

		// Check if the link is successful

		GLint linkSucceeded = 0;

		glGetProgramiv(programObjID_, GL_LINK_STATUS, &linkSucceeded);

		if (!linkSucceeded)
		{
			// Register the events in the log
			GLint logLength;

			glGetShaderiv(programObjID_, GL_INFO_LOG_LENGTH, &logLength);

			if (logLength > 0)
			{
				logStr_.resize(logLength);

				glGetShaderInfoLog(programObjID_, logLength, NULL, &logStr_.front());
			}

			cout << name_ + " failed to link.  LOG:" + logStr_ << endl;
			assert(false);
		}

		return (islinkSuccessful_ = (linkSucceeded != 0));
	}
}

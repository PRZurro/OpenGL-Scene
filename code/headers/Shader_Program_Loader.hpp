/**
 * @file Shader_Program_Loader.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief Class to load and store shader programs
 * @version 0.1
 * @date 16-05-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OPENGL_SCENE_SHADER_PROGRAM_LOADER_H_
#define OPENGL_SCENE_SHADER_PROGRAM_LOADER_H_

#include <Shader_Loader.hpp>
#include <Shader_Program.hpp>
#include <Vertex_Shader.hpp>
#include <Fragment_Shader.hpp>

#include <Declarations.hpp>

namespace prz
{

	/**
	 * @brief Class to load and store shader programs
	 * 
	 */
	class Shader_Program_Loader
	{
	public:

		/**
		 * @brief Get an static instance object of this class
		 *
		 * @return Shader_Program_Loader&
		 */
		static Shader_Program_Loader& instance()
		{
			static Shader_Program_Loader instance;
			return instance;
		}

	public:

		/**
		 * @brief Load shader program by:
		 * 
		 * @param pathVertexShader 
		 * @param pathFragmentShader 
		 * @return PSPtr< Shader_Program > 
		 */
		PSPtr< Shader_Program > load_shader_program(const PString& pathVertexShader, const PString& pathFragmentShader)
		{
			PBuffer< PString > shaderPaths = { pathVertexShader , pathFragmentShader };
			return load_shader_program(shaderPaths);
		}

		/**
		 * @brief Load a shader program by: 
		 * 
		 * @param shaderPaths 
		 * @return PSPtr< Shader_Program > 
		 */
		PSPtr< Shader_Program > load_shader_program(PBuffer< PString >& shaderPaths)
		{
			Shader_Loader& loader =  Shader_Loader::instance();
			PBuffer< PSPtr< Shader > > shaders(shaderPaths.size());

			for (size_t i = 0; i < shaderPaths.size(); ++i)
			{
				PSPtr< Shader > shader = loader.load_shader(shaderPaths[i]);

				shaders[i] = shader;
			}

			return load_shader_program(shaders);
		}

		/**
		 * @brief Load a shader program by: 
		 * 
		 * @param vertexShader 
		 * @param fragmentShader 
		 * @return PSPtr< Shader_Program > 
		 */
		PSPtr< Shader_Program > load_shader_program(PSPtr< Vertex_Shader > vertexShader, PSPtr< Fragment_Shader > fragmentShader)
		{
			PBuffer< PSPtr< Shader > > shaders = { vertexShader, fragmentShader };

			return load_shader_program(shaders);
		}

		/**
		 * @brief Load a shader program by:
		 * 
		 * @param shaders 
		 * @return PSPtr< Shader_Program> 
		 */
		PSPtr< Shader_Program> load_shader_program(PBuffer< PSPtr< Shader > >& shaders)
		{
			PString nameFormedByShadersName = Shader_Program::form_shader_program_name(shaders);

			if (nameFormedByShadersName != "A shader is empty")
			{
				if (exists_shader_program_with_name(nameFormedByShadersName))
				{
					return loadedShaderPrograms_[nameFormedByShadersName];
				}

				PSPtr< Shader_Program > shaderProgram(make_shared<Shader_Program>());

				for (size_t i = 0; i < shaders.size(); ++i)
				{
					PSPtr< Shader > shader = shaders[i];

					if (!shaderProgram->attach(shader))  // The shader to attach is either empty, duplicated or failed to compile.
					{
						break;
					}
				}

				if (shaderProgram->get_number_of_attached_shaders() == shaders.size())
				{
					shaderProgram->link();

					if (shaderProgram->is_usable())
					{
						loadedShaderPrograms_[shaderProgram->name()] = shaderProgram;

						return loadedShaderPrograms_[shaderProgram->name()];
					}
				}
			}

			return PSPtr< Shader_Program >();
		}

	public:

		/**
		 * @brief Return if exists a shader program with name
		 * 
		 * @param name 
		 * @return true 
		 * @return false 
		 */
		bool exists_shader_program_with_name(const PString& name)
		{
			return loadedShaderPrograms_.find(name) != loadedShaderPrograms_.end();
		}

		/**
		 * @brief Return if exists a shader program with the input shader names
		 * 
		 * @param shaderNames 
		 * @return true 
		 * @return false 
		 */
		bool exists_shader_program_with_shaders(PBuffer< PString > & shaderNames)
		{
			return exists_shader_program_with_name(Shader_Program::form_shader_program_name(shaderNames));
		}
		
		/**
		 * @brief Return if exists a shader program with the input shaders
		 * 
		 * @param shaders 
		 * @return true 
		 * @return false 
		 */
		bool exists_shader_program_with_shaders(PBuffer< PSPtr< Shader > >& shaders)
		{
			return exists_shader_program_with_name(Shader_Program::form_shader_program_name(shaders));
		}

	private:

		/**
		 * @brief Construct a new Shader_Program_Loader (private)
		 * 
		 */
		Shader_Program_Loader() {}

	private:

		PMap< PString, PSPtr< Shader_Program > > loadedShaderPrograms_;
	};


} // !namespace prz

#endif //! OPENGL_SCENE_SHADER_PROGRAM_LOADER_H_

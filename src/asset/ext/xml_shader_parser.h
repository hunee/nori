/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/shader.h"

#include "renderer/GL/GL_state.h"
#include "renderer/GL/GL_shader.h"
#include "renderer/GL/GL_program.h"

#include "renderer/GL/GL_uniform.h"

namespace ext {

/**
 * @brief 
 * 
 */
class xml_shader_parser {
private:

public:
/**
 * @brief 
 * 
 * @param element 
 * @return std::shared_ptr<asset_> 
 */
std::shared_ptr<asset_> parser(const XMLElement * element)
{
  //__method__

	/**
	 * technique
	 */
	for (auto shader_element = element->FirstChildElement("shader"); shader_element; shader_element = shader_element->NextSiblingElement())
	{
		auto shader_name = shader_element->Attribute("name");
		auto shader_language = shader_element->Attribute("language");

    ///COUT << "shader_name: " << shader_name << ENDL;
    ///COUT << "shader_language: " << shader_language << ENDL;


    ////
    auto shader = std::make_shared<asset<GL::shader>>();
    if (shader == nullptr)
      return nullptr;

    ///
    for (auto program_element = shader_element->FirstChildElement("pass"); program_element; program_element = program_element->NextSiblingElement())
		{
			auto program_name = program_element->Attribute("name");
      //COUT << "program_name: " << program_name << ENDL;

      auto blend_func_element = program_element->FirstChildElement("blend_func");
      if (blend_func_element)
      {
        auto sfactor = blend_func_element->Attribute("sfactor");
        //COUT << "sfactor: " << sfactor << ENDL;

        auto dfactor = blend_func_element->Attribute("dfactor");
        //COUT << "dfactor: " << dfactor << ENDL;        
      }


      ///
      try {
        auto program = std::make_shared<GL::GL_program>();
        if (program == nullptr)
          return nullptr;

        parser_render_state_block(program, program_element);
        parser_shader_program(program, program_element);
        parser_shader_variables(program, program_element);

        program->dump();

        (*shader)[program_name] = program;
        //(*shader)[pass_name]->bind();

        //auto p = shader->find("pass_name").get();
        //p->bind();

      } catch (std::exception& e) {
          COUT << e.what() << ENDL;
      }
    }

    ////
    shader->dump();

    return shader;
  }

  return nullptr;
}

private:
/**
 * @brief 
 * 
 * @param program 
 * @param element 
 * @return int 
 */
int parser_render_state_block(std::shared_ptr<GL::GL_program>& program, const XMLElement* element)
{
  //GLstateblock* stateblock = new GLstateblock;
  //pass->set_stateblock(stateblock);

  /**
   * render_state_block
   */
  auto render_state_block_element = element->FirstChildElement("render_state_block");
  if (render_state_block_element)
  {
    for (auto render_state_element = render_state_block_element->FirstChildElement("render_state"); render_state_element; render_state_element = render_state_element->NextSiblingElement())
    {
      auto render_state_name = render_state_element->Attribute("name");
      if (!strcmp(render_state_name, "GL_BLEND_FUNC"))
      {
        auto render_state_value = render_state_element->Attribute("sfactor");
        auto render_state_dfactor = render_state_element->Attribute("dfactor");

        auto state = GL::GL_make_state(render_state_name, render_state_value, render_state_dfactor);
        if (state != nullptr)
          program->states_[render_state_name] = state;
      }
      else
      {
        auto render_state_value = render_state_element->Attribute("value");
      
        auto state = GL::GL_make_state(render_state_name, render_state_value, "");
        if (state != nullptr)
          program->states_[render_state_name] = state;
      }
    }
  }

  return 1;
}


/**
 * @brief 
 * 
 * @param program 
 * @param element 
 * @return int 
 */
int parser_shader_program(std::shared_ptr<GL::GL_program>& program, const XMLElement* element)
{
  /**
   * shader_program
   */
  for (auto shader_program_element = element->FirstChildElement("shader_program"); shader_program_element != 0; shader_program_element = shader_program_element->NextSiblingElement())
  {
    if (!strcmp(shader_program_element->Value(), "shader_program"))
    {
      auto shader_program_name = shader_program_element->Attribute("name");
      auto shader_program_profile = shader_program_element->Attribute("profile");
      auto shader_program_code = shader_program_element->GetText();

      ///COUT << "shader_program_name: " << shader_program_name << ENDL;
      ///COUT << "profile: " << shader_program_profile << ENDL;
      ///COUT << "shader_code: " << shader_program_code << ENDL;

      try {
        std::unique_ptr<GL::GL_shader> shader_program = nullptr;
        if (!strcmp(shader_program_name, "GL_FRAGMENT_SHADER"))
          shader_program = std::make_unique<GL::GL_shader_<GL_FRAGMENT_SHADER>>(shader_program_code);
        else if (!strcmp(shader_program_name, "GL_VERTEX_SHADER"))
          shader_program = std::make_unique<GL::GL_shader_<GL_VERTEX_SHADER>>(shader_program_code);
      //else if (!strcmp(shader_program_name, "GL_GEOMETRY_SHADER_EXT"))
      //  shader_program = new GLshader<GL_GEOMETRY_SHADER_EXT>(shader_program_code);

        program->push_back(std::move(shader_program));
      } 
      catch (std::exception& e) {
        COUT << e.what() << ENDL;
			}
    }
  }
  
  program->link();

  return 1;
}


/**
 * @brief 
 * 
 * @param program 
 * @param element 
 * @return int 
 */
int parser_shader_variables(std::shared_ptr<GL::GL_program>& program, const XMLElement* element)
{
  //shader_variable
  for (auto variable_element = element->FirstChildElement("shader_variable"); variable_element; variable_element = variable_element->NextSiblingElement())
  {
    auto variable_name = variable_element->Attribute("name");
    auto variable_value = variable_element->Attribute("value");

    //COUT << "shader_variable name: " << variable_name << ENDL;
    //COUT << "value: " << variable_value << ENDL;

    if (!strcmp(variable_name, "sampler2D"))
    {
      auto uniform = std::make_shared<GL::GL_uniform_<unsigned int>>(variable_value, program->handle());
      (*program)[variable_value] = uniform;

      {
        //pass->push_back(uniform);

        
        /**
         * Sampler state
         */
        //GLstateblock* stateblock = new GLstateblock;
        //uniform->setStateblock(stateblock);

        for (auto sampler_state_element = variable_element->FirstChildElement("sampler_state"); sampler_state_element; sampler_state_element = sampler_state_element->NextSiblingElement())
        {
          auto sampler_state_name = sampler_state_element->Attribute("name");
          auto sampler_state_value = sampler_state_element->Attribute("value");

          //TRACEA("->> sampler_state name=%s ", sampler_state_name);
          //TRACELA("value=%s\n", sampler_state_value);

          ///
          //GLIstate* state = stateblock->state(sampler_state_name, sampler_state_value);
          //if (state)
          //	stateblock->push_back(state);
        }
      }
    }
    else if (!strcmp(variable_name, "render_target"))
    {
    }
    else if (!strcmp(variable_name, "float"))
    {
      auto scalar = variable_element->Attribute("scalar");

      auto uniform = std::make_shared<GL::GL_uniform_<float>>(variable_value, program->handle());
      uniform->set(atof(scalar));

      (*program)[variable_value] = uniform;
    }
    else if (!strcmp(variable_name, "vec2"))
    {
      auto x = variable_element->Attribute("x");
      auto y = variable_element->Attribute("y");

      auto uniform = std::make_shared<GL::GL_uniform_<GL::float2>>(variable_value, program->handle());
      uniform->set(GL::float2(atof(x), atof(y)));

      (*program)[variable_value] = uniform;
    }
    else if (!strcmp(variable_name, "vec3"))
    {
      auto x = variable_element->Attribute("x");
      auto y = variable_element->Attribute("y");
      auto z = variable_element->Attribute("z");

      auto uniform = std::make_shared<GL::GL_uniform_<GL::float3>>(variable_value, program->handle());
      uniform->set(GL::float3(atof(x), atof(y), atof(z)));

      (*program)[variable_value] = uniform;
    }
    else if (!strcmp(variable_name, "vec4"))
    {
      auto x = variable_element->Attribute("x");
      auto y = variable_element->Attribute("y");
      auto z = variable_element->Attribute("z");
      auto w = variable_element->Attribute("w");

      auto uniform = std::make_shared<GL::GL_uniform_<GL::float4>>(variable_value, program->handle());
      uniform->set(GL::float4(atof(x), atof(y), atof(z), atof(w)));
      
      (*program)[variable_value] = uniform;
    }
    else if (!strcmp(variable_name, "mat4"))
    {
      auto _11 = variable_element->Attribute("_11");
      auto _12 = variable_element->Attribute("_12");
      auto _13 = variable_element->Attribute("_13");
      auto _14 = variable_element->Attribute("_14");
      auto _21 = variable_element->Attribute("_21");
      auto _22 = variable_element->Attribute("_22");
      auto _23 = variable_element->Attribute("_23");
      auto _24 = variable_element->Attribute("_24");
      auto _31 = variable_element->Attribute("_31");
      auto _32 = variable_element->Attribute("_32");
      auto _33 = variable_element->Attribute("_33");
      auto _34 = variable_element->Attribute("_34");
      auto _41 = variable_element->Attribute("_41");
      auto _42 = variable_element->Attribute("_42");
      auto _43 = variable_element->Attribute("_43");
      auto _44 = variable_element->Attribute("_44");

      auto uniform = std::make_shared<GL::GL_uniform_<GL::float4x4>>(variable_value, program->handle());
      uniform->set(GL::float4x4(atof(_11), atof(_12), atof(_13), atof(_14),
                                atof(_21), atof(_22), atof(_23), atof(_24),
                                atof(_31), atof(_32), atof(_33), atof(_34),
                                atof(_41), atof(_42), atof(_43), atof(_44)));

      (*program)[variable_value] = uniform;
    }
  }

  return 1;
}
};

}; //ext

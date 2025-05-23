/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-07, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Entity.h"
#include "AnimatedEntity.h"
#include "platformer_lib.h"
#include "helper.h"

AnimatedEntity::AnimatedEntity(glm::vec3 init_pos, glm::vec3 init_scale, 
    float width, float height, GLuint tex_id, 
    std::vector<AnimationInfo> anims, int max_frames
    )
    : Entity(init_pos, init_scale,
        width, height, 
        tex_id
      ),
      m_anims(anims), m_anim_cols(max_frames), m_flip_horizontal(false)
{
    m_anim_rows = (int) m_anims.size();
    set_anim(0);
}

AnimatedEntity::AnimatedEntity(glm::vec3 init_pos,
    float width, float height, GLuint tex_id, 
    std::vector<AnimationInfo> anims, int max_frames
    )
    : Entity(init_pos,
        width, height, 
        tex_id
      ),
      m_anims(anims), m_anim_cols(max_frames), m_flip_horizontal(false)
{
    m_anim_rows = (int) m_anims.size();
    set_anim(0);
}

void AnimatedEntity::set_anim(int anim)
{
    if (m_curr_anim != anim)
    {
        m_anim_time = 0.0f;
        m_curr_anim = anim;
        m_anim_index = 0;
    }
}

bool AnimatedEntity::is_anim(int anim)
{
    return m_curr_anim == anim;
}

void AnimatedEntity::update(float delta_time)
{
    AnimationInfo anim = m_anims[m_curr_anim];
    m_anim_time += delta_time;
    
    if (m_anim_time >= anim.time_duration)
    {
        m_anim_time = 0.0f;
        m_anim_index++;

        if (m_anim_index >= anim.total_frames)
        {
            if (anim.loop_index != -1) m_anim_index = anim.loop_index;
            if (anim.next_anim != -1)  set_anim(anim.next_anim);
        }
    }

    Entity::update(delta_time);
}

void AnimatedEntity::render(ShaderProgram* program)
{
    program->set_model_matrix(m_model_mat);
    glBindTexture(GL_TEXTURE_2D, m_texture_id); 

    int anim_index = m_curr_anim * m_anim_cols + m_anim_index;

    float width = 1.0f / (float) m_anim_cols;
    float height = 1.0f / (float) m_anim_rows;

    float u = (float) (anim_index % m_anim_cols) * width;
    float v = (float) (anim_index / m_anim_cols) * height;

    float left = u;
    float right = u + width;

    if (m_flip_horizontal)
    {
        float temp = left;
        left = right;
        right = temp;
    }
        
    float texture_coordinates[] =
    {
        // Triangle 1
        left, v + height,
        right, v + height, 
        right, v,
        // Triangle 2
        left, v + height, 
        right, v, 
        left, v
    };

    glVertexAttribPointer(program->get_position_attribute(),
        2, GL_FLOAT, false, 0, STANDARD_COORDINATES);
    glVertexAttribPointer(program->get_tex_coordinate_attribute(),
        2, GL_FLOAT, false, 0, texture_coordinates);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}


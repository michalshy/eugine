#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP
#include "TypeDef.hpp"
#include <glad/glad.h>
#include <iostream>

class FrameBuffer {
    u32 m_screenWidth, m_screenHeight;
    u32 m_framebuffer;
    u32 m_textureColorbuffer;
    u32 m_rbo;

public:
    FrameBuffer() : m_screenWidth(800), m_screenHeight(600) {};
    FrameBuffer(u32 screenWidth, u32 screenHeight);
    void resize(u32 screenWidth, u32 screenHeight);
    void configure()
    {
        glGenFramebuffers(1, &m_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
        glGenTextures(1, &m_textureColorbuffer);
        glBindTexture(GL_TEXTURE_2D, m_textureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_screenWidth, m_screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorbuffer, 0);
        glGenRenderbuffers(1, &m_rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_screenWidth, m_screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo); // now actually attach it
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void rescale(float width, float height)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorbuffer, 0);
    
        glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    }
    void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    }
    void unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    u32 getTextureColorbuffer() { return m_textureColorbuffer; }
    void setScreenWidth(u32 screenWidth) { m_screenWidth = screenWidth; }
    void setScreenHeight(u32 screenHeight) { m_screenHeight = screenHeight; }
    ~FrameBuffer()
    {
        glDeleteFramebuffers(1, &m_framebuffer);
        glDeleteTextures(1, &m_textureColorbuffer);
        glDeleteRenderbuffers(1, &m_rbo);
    }
};

#endif
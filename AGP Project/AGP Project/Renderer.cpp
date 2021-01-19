#include "Renderer.h"

namespace Spoonity {

    Renderer::Renderer()
        : _Window(nullptr), _Camera(nullptr),
        _DepthMapFBO(0), _DepthMap(0),
        _gBuffer(0), _gPosition(0), _gNormal(0), _gAlbedoSpec(0),
        _CurrentScene(nullptr),
        quadVAO(0), quadVBO(0)
    {
    }

    Renderer::Renderer(const Window* window, const Camera* camera)
        : _Window(window), _Camera(camera)
	{
        _DepthShader = Shader("Data/Shaders/Depth/depth_shader.vs","Data/Shaders/Depth/depth_shader.fs");
        _GeometryShader = Shader("Data/Shaders/Geometry/geometry_shader.vs", "Data/Shaders/Geometry/geometry_shader.fs");
        _LightingShader = Shader("Data/Shaders/Lighting/lighting_shader.vs", "Data/Shaders/Lighting/lighting_shader.fs");

        debugDepthShader = Shader("Data/Shaders/Depth/debug.vs", "Data/Shaders/Depth/debug.fs");

        //_PostProcessShader = Shader("Data/Shaders/PostProcessing/default_shader.vs", "Data/Shaders/PostProcessing/default_shader.fs");

		//Tell stb_image.h to flip loaded texture's on the y-axis (before loading model)
		//stbi_set_flip_vertically_on_load(true);

		//Configure global opengl state
		glEnable(GL_DEPTH_TEST);

        //Set the light data
        _LightDirection = glm::vec3(1.0f, -1.0f, 1.0f);
        _LightColor = glm::vec3(0.5f);
		
        //Initialise the shaders
		genBuffers();

        //Shader Config
        _LightingShader.use();
        _LightingShader.setInt("gPosition", 0);
        _LightingShader.setInt("gNormal", 1);
        _LightingShader.setInt("gAlbedoSpec", 2);
	}

    //Destructor
    Renderer::~Renderer()
    {
        _Window = nullptr;
        _Camera = nullptr;
    }

	//Function for configuring buffers
	void Renderer::genBuffers()
	{
        //Shadow map
        glGenFramebuffers(1, &_DepthMapFBO);
        glGenTextures(1, &_DepthMap);
        glBindTexture(GL_TEXTURE_2D, _DepthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glBindFramebuffer(GL_FRAMEBUFFER, _DepthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _DepthMap, 0);
        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, _DepthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        //Configure geometry framebuffer
        glGenFramebuffers(1, &_gBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);

        unsigned int width = _Window->getWidth();
        unsigned int height = _Window->getHeight();

        //Position color buffer
        glGenTextures(1, &_gPosition);
        glBindTexture(GL_TEXTURE_2D, _gPosition);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _gPosition, 0);

        //Normal color buffer
        glGenTextures(1, &_gNormal);
        glBindTexture(GL_TEXTURE_2D, _gNormal);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _gNormal, 0);

        //Color + specular color buffer
        glGenTextures(1, &_gAlbedoSpec);
        glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _gAlbedoSpec, 0);

        //Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2/*, GL_DEPTH_ATTACHMENT*/};
        glDrawBuffers(3, attachments);

        //Create and attach depth buffer (renderbuffer)
        unsigned int rboDepth;
        glGenRenderbuffers(1, &rboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

        //Finally check if framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            throw "Framebuffer not complete!";
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	void Renderer::renderScene()
	{
        //Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);

        //For shadow depth map debug?
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        unsigned int width = _Window->getWidth();
        unsigned int height = _Window->getHeight();

        glm::mat4 projection = glm::perspective(glm::radians(_Camera->_FOV), (float)width / (float)height, 0.1f, 500.0f);
        glm::mat4 view = _Camera->GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        
        // 0. depth pass: render scene from the lights perspective to get shadows
        float near_plane = 1.0f, far_plane = 16.0f;
        //glm::vec3 lightOffset = glm::vec3(-10.0f, 10.0f, -10.0f);
        glm::vec3 lightPos = glm::vec3(-50.0f, 20.0f, -50.0f/*_Camera->_Position + lightOffset*/);
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(lightPos /*liftOffset*/, glm::vec3(0.0f) /*lightOffset, lightOffset + _LightDirection*/, _Camera->_WorldUp);
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        _DepthShader.use();
        _DepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, _DepthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        _Skybox->disable();
        
        _CurrentScene->draw(_DepthShader, lightProjection, lightView, model);

        _Skybox->enable();
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1. geometry pass: render scene's geometry/color data into gbuffer
        glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        _CurrentScene->draw(_GeometryShader, projection, view, model);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _LightingShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, _DepthMap);
        //Send light relevant uniforms
        //_LightingShader.setVec3("light.Position", _LightPosition); //position not used for directional lighting
        _LightingShader.setVec3("light.Color", _LightColor);
        _LightingShader.setVec3("light.Direction", _LightDirection);
        // update attenuation parameters and calculate radius
        //const float constant = 1.0f;
        //const float linear = 0.7f;
        //const float quadratic = 1.8f;
        //_LightingShader.setFloat("light.constant", constant);
        //_LightingShader.setFloat("light.Linear", linear);
        //_LightingShader.setFloat("light.Quadratic", quadratic);
        //
        //// then calculate radius of light volume/sphere
        //const float maxBrightness = 1.0f;
        //float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
        //_LightingShader.setFloat("light.Radius", radius);

        _LightingShader.setVec3("viewPos", _Camera->_Position);
        _LightingShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        // finally render quad
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);

        // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, _gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // TODO: 3. Post processing
        //------------------------
        
        
        //debugDepthShader.use();
        //debugDepthShader.setFloat("near_plane", near_plane);
        //debugDepthShader.setFloat("far_plane", far_plane);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, _DepthMap);
        

        //------------------------

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(_Window->getInstance());
	}
}
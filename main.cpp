#include <iostream>
#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./dependencies/imgui/imgui.h"
#include "./dependencies/imgui/imgui_internal.h"
#include "./dependencies/imgui/backends/imgui_impl_glfw.h"
#include "./dependencies/imgui/backends/imgui_impl_opengl3.h"

#include "shader.cpp"

static void glfw_error_callback( int error, const char* description )
{
  fprintf( stderr, "GLFW Error %d: %s\n", error, description );
}

int main( int argc, char **argv )
{

  glfwSetErrorCallback( glfw_error_callback );

  if( !glfwInit() ) {
    return 1;
  }

  const char* glsl_version = "#version 330";
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );

  GLFWwindow* window = glfwCreateWindow( 1280, 720, "Satisfactory Scheme", NULL, NULL );
  if( window == NULL ) {
    return 1;
  }

  glfwMakeContextCurrent( window );
  glfwSwapInterval( 1 ); // vsync

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL( window, true );
  ImGui_ImplOpenGL3_Init( glsl_version );

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  Shader current_shader( "shaders/shaders.vert", "shaders/shaders.frag" );

  while( !glfwWindowShouldClose( window ) ) {

    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell
    // if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
    //   your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data
    //   to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from
    // your application based on those two flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize( window, &display_w, &display_h );
    glViewport( 0, 0, display_w, display_h );

    glClearColor( clear_color.x * clear_color.w,
		  clear_color.y * clear_color.w,
		  clear_color.z * clear_color.w,
		  clear_color.w );
    
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
  
}
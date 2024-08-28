#include "include/gui.h"
#include "include/bpm_analyzer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of files the user can input
#define MAX_FILES 100

// Function to render a simple button
void draw_button(Button *button) {
    glColor3f(0.7f, 0.7f, 0.7f);  // Button color
    glBegin(GL_QUADS);
        glVertex2f(button->x, button->y);
        glVertex2f(button->x + button->width, button->y);
        glVertex2f(button->x + button->width, button->y + button->height);
        glVertex2f(button->x, button->y + button->height);
    glEnd();

    // Rendering the button label is omitted here for simplicity.
}

// Function to check if the button was clicked
int is_button_clicked(Button *button, double mouse_x, double mouse_y) {
    return mouse_x >= button->x && mouse_x <= button->x + button->width &&
           mouse_y >= button->y && mouse_y <= button->y + button->height;
}

void create_gui() {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }

    // Set up OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "BPM Analyzer", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }

    // Define buttons
    Button calculate_button = { 300.0f, 200.0f, 200.0f, 50.0f, "Calculate" };
    Button clear_button = { 300.0f, 300.0f, 200.0f, 50.0f, "Clear List" };

    // File list and count
    char *file_list[MAX_FILES];
    int file_count = 0;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Get mouse position
        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        // Convert mouse coordinates to OpenGL coordinates
        int window_width, window_height;
        glfwGetWindowSize(window, &window_width, &window_height);
        mouse_x = (mouse_x / window_width) * 2.0 - 1.0;
        mouse_y = (mouse_y / window_height) * -2.0 + 1.0;

        // Check for button clicks
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (is_button_clicked(&calculate_button, mouse_x, mouse_y)) {
                // Calculate BPM for all files in the list
                for (int i = 0; i < file_count; i++) {
                    double bpm = calculate_bpm(file_list[i]);
                    printf("File: %s, Calculated BPM: %.1f\n", file_list[i], bpm);
                }
            }
            if (is_button_clicked(&clear_button, mouse_x, mouse_y)) {
                // Clear the list of files
                for (int i = 0; i < file_count; i++) {
                    free(file_list[i]);
                }
                file_count = 0;
                printf("Cleared the list.\n");
            }
        }

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw buttons
        draw_button(&calculate_button);
        draw_button(&clear_button);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up file list
    for (int i = 0; i < file_count; i++) {
        free(file_list[i]);
    }

    glfwTerminate();
}

// Resize the viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

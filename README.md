# Aquarium Simulation – Computer Graphics Mini Project

This is a mini project developed in C using **OpenGL** and **GLUT** to simulate an animated **Aquarium**. The program visually represents an underwater environment with animated fishes, background elements, and user-interactive features.

---

## Objective

To simulate a real-time aquarium using 2D/3D computer graphics techniques, demonstrating the use of OpenGL primitives, animation, transformations, and basic user interaction.

---

## Features

- Real-time animated fishes swimming across the screen.
- Visual elements including aquarium borders, bubbles, and static decorations.
- Use of color blending, line drawing, and polygonal shapes to simulate environment.
- Simulated motion using translation transformations.
- Timer-based animation using GLUT's `glutTimerFunc`.

---

## How Computer Graphics Concepts Were Used

This project utilizes key principles of computer graphics, including:

- **2D Graphics Primitives**: Lines, polygons, circles to represent fish, tank, and other elements.
- **Transformations**: Translation is applied to animate fish movement.
- **Double Buffering**: Ensures flicker-free animation.
- **Color and Lighting**: Custom color fills for different objects using RGB color codes.
- **Animation Loop**: GLUT's `glutTimerFunc()` enables smooth frame updates.
- **Event Handling**: Basic keyboard or timer-based control logic.

---

## Technologies Used

- **Language**: C
- **Graphics API**: OpenGL (GLUT)
- **Development Environment**: Linux (GCC) or Windows (Code::Blocks/Dev-C++)

---

## Compilation Instructions

### Linux

Ensure OpenGL and GLUT are installed:

#compile and run 
gcc aquarium.c -o aquarium -lGL -lGLU -lglut -lm
./aquarium


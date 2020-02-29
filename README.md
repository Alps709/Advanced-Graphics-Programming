# OpenGL Graphics Programming
This is a repository for the code I'm writing, in the Graphics Programming component for my 'Software Engineering in Game Programming Bachelors degree' at Media Design School.

This is the first rendering of a triangle I did to start with, in OpenGL:
![My First Triangle](https://github.com/Alps709/OpenGL-Graphics-Programming/blob/master/OpenGL%20Graphics%20Programming/Resources/Textures/Triangle.png)

Next I made 4 quads using two triangles for each one, and made the fragment shader change the colour of each vertex based off the current time. So now each corner of a quad has a different colour, and those colours fade in and out.
(The quality of the gif is terrible in this example, the colour is uniform when the program is run)
![Coloured quads](https://github.com/Alps709/OpenGL-Graphics-Programming/blob/master/OpenGL%20Graphics%20Programming/Resources/Textures/colouredQuads1.gif)

After being able to render quads I set up the rendering of textures onto those 4 quads. I also added an Index Buffer Object (IBO), before now if two triangles had a vertex in the same place, it would store a unique one for each triangle. Using an IBO they can now share the same vertex and save memory.
(I found a better gif compression format that allows for more colours, although it still has some strange artifacting)
![Textures](https://github.com/Alps709/OpenGL-Graphics-Programming/blob/master/OpenGL%20Graphics%20Programming/Resources/Textures/Textures.gif)

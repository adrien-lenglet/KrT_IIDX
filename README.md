# KrT_IIDX
DRIIIIIFT

## Added context by Adrien LENGLET on the 31st of August, 2023

This repository is basically the "gone horribly wrong" game engine in mentionned as a plot in https://adrien-lenglet.fr/project/rosee  
By the way, I just made the successor "Rosee" renderer public: https://github.com/FMC64/Rosee  

Rosee has been designed with the lessons (written in blood) of Krt_IIDX in mind. Aside from the main which is openly-admitted to be a messy application playground, I'm pretty happy with the rest of the code. At the time of writing this, the last commit of Rosee is almost 2 years and a half old. I acquired further experience since and even better practices on recent projects, which are mostly closed-source private IP unfortunately.

To get back to KrT_IIDX, it really is a prime example of overengineering, overthinking, overdesigning everything. I think there is something quite remarkable in the actual execution of this project. I never backed down on anything at the time. At the end it was actually capable of doing some screen-space global illumination, with a bunch of custom shader scripts and preprocessing to attempt to make the rendering pipeline more of a single-object entity inheriting from independent modules. This system had some design flaws and the underlying entire attempt at abstracting Vulkan behind the scenes further motivated me to start on solid (and much more simple) foundations for Rosee.

This was instrumental for me to get to the bottom of the limits of C++, my intent at the time always required me to dig further and be more and more creative. It was also a lesson in how important simple systems based on well-defined and publicly known conventions are, especially where these are used as a fundamental building block.

Ultimately KrT_IIDX had a tremendous value in education and experience for me. I think it may provide a comical value to a lot of seasoned C++/system programmers :)  
So enjoy!

## Original public release commentary (20th of January, 2021)

# Giant overengineed clusterfuck. The most blatant I have ever done and probably will ever do. Template wizardry, obscure constexpr at my finest level. Features a custom shading language and a render pass one. Even includes a C++17 generator. That's right, you can generate C++ from C++. Boom. You've been warned.

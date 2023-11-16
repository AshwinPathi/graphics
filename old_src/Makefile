CXX=clang++
CXXVERSION=c++2a
CXXFLAGS=-std=$(CXXVERSION) -O2 -I$(CURDIR)/..

# Find makefile dependencies with:
# clang++ -MM -I$(CURDIR)/.. <file> 
# Consider doing: https://stackoverflow.com/questions/313778/generate-dependencies-for-a-makefile-for-a-project-in-c-c


########################################################################
#       															   #
#						   Image Test								   #
#																	   #
########################################################################
image_test_objects = image_test.o ppm_image.o

# Binary
image_test : $(image_test_objects)
	$(CXX) $(CXXFLAGS) -o image_test.out $(image_test_objects)

# Object files
image_test.o : core/ppm_image.h core/color.h
	$(CXX) $(CXXFLAGS) -c image_test.cpp


########################################################################
#       															   #
#						     Raytracer								   #
#																	   #
########################################################################
raytracer_objects = raytracer.o renderer.o sphere.o plane.o ppm_image.o scene_parser.o world.o

## Binary
raytracer : $(raytracer_objects)
	$(CXX) $(CXXFLAGS) -o raytracer.out $(raytracer_objects)

## Main
raytracer.o : core/ppm_image.h raytracer/renderer/renderer.h raytracer/utils/scene_parser.h
	$(CXX) $(CXXFLAGS) -c raytracer.cpp

## Utils
scene_parser.o : raytracer/renderer/renderer_utils.h raytracer/shapes/intersectable.h raytracer/shapes/sphere.h raytracer/shapes/plane.h raytracer/renderer/world.h
	$(CXX) $(CXXFLAGS) -c raytracer/utils/scene_parser.cpp

## Renderer
renderer.o : math/vector3.h core/color.h core/ppm_image.h raytracer/common/material.h raytracer/renderer/renderer_utils.h raytracer/renderer/world.h
	$(CXX) $(CXXFLAGS) -c raytracer/renderer/renderer.cpp

world.o : raytracer/shapes/intersectable.h math/vector3.h
	$(CXX) $(CXXFLAGS) -c raytracer/renderer/world.cpp

## Shapes
sphere.o : raytracer/shapes/intersectable.h math/vector3.h math/fast_math.h raytracer/common/material.h
	$(CXX) $(CXXFLAGS) -c raytracer/shapes/sphere.cpp

plane.o : raytracer/shapes/intersectable.h math/vector3.h math/fast_math.h raytracer/common/material.h
	$(CXX) $(CXXFLAGS) -c raytracer/shapes/plane.cpp


########################################################################
#       															   #
#						       Core								       #
#																	   #
######################################################################## 

ppm_image.o : core/ppm_image.h core/color.h
	$(CXX) $(CXXFLAGS) -c core/ppm_image.cpp


########################################################################
#       															   #
#						       Math								       #
#																	   #
######################################################################## 

# Nothing here


.PHONY: clean

clean: 
	rm -f *.out *.o

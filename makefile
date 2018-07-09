all :  ov2640_capture ov5642_capture ov5640_capture ov2640_4cams_capture ov5640_4cams_capture ov5642_4cams_capture
VPATH= ../../../ArduCAM
INCLUDE1 = -I../../../ArduCAM -I./
INCLUDE2 =-I./ -I../../../ArduCAM
CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
objects = ArduCAM.o arducam_arch_raspberrypi.o


ov2640_capture : $(objects) arducam_ov2640_capture.o transmit.cpp capture.cpp compress.cpp
	g++ $(CFLAGS) $(LIBS) -o ov2640_capture $(objects) arducam_ov2640_capture.o transmit.cpp capture.cpp compress.cpp -l pthread -lturbojpeg -lwiringPi -Wall


ArduCAM.o : ArduCAM.cpp
	g++ $(INCLUDE1) -c $(VPATH)/ArduCAM.cpp
arducam_arch_raspberrypi.o : arducam_arch_raspberrypi.c
	g++ $(INCLUDE2) -c arducam_arch_raspberrypi.c


arducam_ov2640_capture.o : arducam_ov2640_capture.cpp
	g++ $(INCLUDE2) -c arducam_ov2640_capture.cpp

clean :
	rm -f  ov2640_capture $(objects) *.o

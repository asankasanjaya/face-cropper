# face-cropper
This is a simple c++ program which reads image files from a directory and crops human faces. It detects the largest human face from the input image, crop the face and save the face in the disk. So you can input bunch of images in order to detect the face.

One of the use case of this program is, in cascade classifiers training, we should input thousands of images. So if it is related to face or facial expressions etc, we can use this program to crop the faces from bunch of images easily.

The program uses the opencv image processing library.

#Setting up the program.

This is a c++ project which uses the opencv. So the IDE should be properly configured to run c++ opecv programs.

#Running the program

All the input images should be placed in images folder.
Output folder should be empty before run the program.
The output faces will be saved in the output folder.

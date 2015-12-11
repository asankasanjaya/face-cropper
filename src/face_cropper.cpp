#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>
#include "dirent.h"
#include <string>

using namespace std;
using namespace cv;

void crop_and_save(std::string image_name);

CascadeClassifier face_cascade;
string face_cascade_name = "raw/haarcascade_frontalface_alt.xml";
int face_id;


void main(){

	//load cascade xml file
	if (!face_cascade.load(face_cascade_name)){
		printf("--(!)Error loading face cascade\n");
		exit;
	}

	//read all the images in the folder
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("images//")) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			std::string dirName = ent->d_name;
			if(dirName.at(0)!='.'){
				crop_and_save(dirName);
			}
		}
	}
	closedir (dir);
}

void crop_and_save(std::string image_name){

	std::cout<<"cropping image: "<<image_name<<std::endl;
	Mat image = imread("images/"+image_name,CV_LOAD_IMAGE_COLOR);

	//detect face

	vector<Rect> faces;
	Mat crop;
	Mat res;
	string text;
	stringstream sstm;
	Mat frame_gray;

	cvtColor(image, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	// Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 10, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	// Set Region of Interest
	Rect roi_b;
	Rect roi_c;

	size_t ic = 0; // ic is index of current element
	int ac = 0; // ac is area of current element

	size_t ib = 0; // ib is index of biggest element
	int ab = 0; // ab is area of biggest element

	Rect face;

	for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
	{
		roi_c.x = faces[ic].x;
		roi_c.y = faces[ic].y;
		roi_c.width = (faces[ic].width);
		roi_c.height = (faces[ic].height);

		ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

		roi_b.x = faces[ib].x;
		roi_b.y = faces[ib].y;
		roi_b.width = (faces[ib].width);
		roi_b.height = (faces[ib].height);

		ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

		if (ac > ab)
		{
			ib = ic;
			roi_b.x = faces[ib].x;
			roi_b.y = faces[ib].y;
			roi_b.width = (faces[ib].width);
			roi_b.height = (faces[ib].height);
		}

		face = roi_b;

		//Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window
		//Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
		//rectangle(image, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
	}
	if(faces.size()>0){
		face_id++;
		Mat faceROI = image( face );
		imwrite("output/"+image_name,faceROI);
	}
}


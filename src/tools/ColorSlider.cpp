
#include <opencv2\opencv.hpp>


IplImage* getThresholdedImage(IplImage* inputImage, int minHue, int maxHue, int minSaturation, int maxSaturation, int minValue, int maxValue){

	IplImage* hsvImage = cvCreateImage(cvGetSize(inputImage), 8, 3);
	cvCvtColor(inputImage, hsvImage, CV_BGR2HSV);

	IplImage* thresholdedImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	cvInRangeS(hsvImage, cvScalar(minHue, minSaturation, minValue), cvScalar(maxHue, maxSaturation, maxValue), thresholdedImage);
	cvReleaseImage(&hsvImage);
	return thresholdedImage;
}



int main(){

	CvCapture* capture;
	capture = cvCaptureFromCAM(0);

	if (!capture){
		printf("Camera capture failed\n");
		return -1;
	}

	const char* inputWindow = "Feed";
	const char* outputWindow = "Filtered";

	const char* minHueSlider = "Hue min";
	const char* maxHueSlider = "Hue max";
	const char* minSatSlider = "Sat min";
	const char* maxSatSlider = "Sat max";
	const char* minValueSlider = "Value min";
	const char* maxValueSlider = "Value max";

	

	cvNamedWindow(inputWindow);
	cvNamedWindow(outputWindow);

	int minHue = 0;
	int maxHue = 0;
	int minSaturation = 0;
	int maxSaturation = 0;
	int minValue = 0;
	int maxValue = 0;

	cvCreateTrackbar(minHueSlider, inputWindow, &minHue, 180, NULL);
	cvCreateTrackbar(maxHueSlider, inputWindow, &maxHue, 180, NULL);
	cvCreateTrackbar(minSatSlider, inputWindow, &minSaturation, 255, NULL);
	cvCreateTrackbar(maxSatSlider, inputWindow, &maxSaturation, 255, NULL);
	cvCreateTrackbar(minValueSlider, inputWindow, &minValue, 255, NULL);
	cvCreateTrackbar(maxValueSlider, inputWindow, &maxValue, 255, NULL);


	for(;;){
		IplImage* frame = 0;
		frame = cvQueryFrame(capture);

		if(!frame){
			break;
		}

		IplImage* thresholdImage = getThresholdedImage(frame, minHue, maxHue, minSaturation, maxSaturation, minValue, maxValue);

		cvShowImage(inputWindow, frame);
		cvShowImage(outputWindow, thresholdImage);
		

		int c = cvWaitKey(10);
		if(c!=-1)
		{
			cvReleaseImage(&thresholdImage);
            break;
		}
		
		cvReleaseImage(&thresholdImage);
	}
	cvReleaseCapture(&capture);
	return 0;
	
	
}


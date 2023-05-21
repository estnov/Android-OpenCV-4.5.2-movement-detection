#include <jni.h>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/video.hpp>
#include "android/bitmap.h"



cv::Mat anterior;
cv::Mat resta;


extern "C" JNIEXPORT void JNICALL
Java_ec_com_ups_practica2visionporcomputador_MainActivity_imageProcessing(
        JNIEnv* env,
        jobject instance, jlong matAddr) {
    cv::Mat& image = *(cv::Mat*)matAddr;

    cv::cvtColor(image, image, cv::COLOR_RGBA2GRAY);

    //Eq Histogram
    //cv::equalizeHist(image, image);

    //CLAHE
    //cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    //clahe->setClipLimit(4.0);
    //clahe->apply(image, image);

    //Unsharp Mask filter
    cv::addWeighted(image, 1.5, image, -0.5, 0, image);

    if(anterior.empty()){
        anterior = image.clone();
    }

    absdiff(image, anterior, resta);

    anterior = image.clone();

    image = resta.clone();


}

#include "head/FaceImage.h"

#include <ros/console.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class FaceImageImpl : public FaceImage {

public:
    FaceImageImpl(const string& face_dir) {
        load_images(face_dir);
    }

    Mat with_eyeballs_vertically(int y) override {

        /* parameters same to both eyes */

        static const Size eye_size(50, 87);
        static const int eye_top_y = 165;

        static const int start_row = eye_top_y + eye_size.height / 2 - eyeball.size().height / 2;
        static const int end_row   = eye_top_y + eye_size.height / 2 + eyeball.size().height / 2;
        ROS_ERROR_COND(end_row - start_row != eyeball.size().height, "end_row - start_row != eyeball.size().height");

        /* add left and right eyeballs */

        Mat face = face_without_eyeball.clone();
        int start_col, end_col;

        // add left eyeball
        static const int left_eye_left_x = 369;
        start_col = left_eye_left_x + eye_size.width / 2 - eyeball.size().width / 2;
        end_col   = left_eye_left_x + eye_size.width / 2 + eyeball.size().width / 2;
        ROS_ERROR_COND(end_col - start_col != eyeball.size().width, "end_col - start_col != eyeball.size().width");
        eyeball.copyTo(face.rowRange(start_row + y, end_row + y).colRange(start_col, end_col));

        // add right eyeball
        static const int right_eye_left_x = 606;
        start_col = right_eye_left_x + eye_size.width / 2 - eyeball.size().width / 2;
        end_col   = right_eye_left_x + eye_size.width / 2 + eyeball.size().width / 2;
        ROS_ERROR_COND(end_col - start_col != eyeball.size().width, "end_col - start_col != eyeball.size().width");
        eyeball.copyTo(face.rowRange(start_row + y, end_row + y).colRange(start_col, end_col));

        return face;
    }

private:
    Mat face_without_eyeball, eyeball;

    void load_images(const string& face_dir) {
        static const string BACKGROUND = face_dir + "/face_without_eyeballs_smile.png";
        static const string EYEBALL = face_dir + "/eyeball-big.png";

        face_without_eyeball = imread(BACKGROUND);
        if (face_without_eyeball.empty()) {
            ROS_ERROR_STREAM(BACKGROUND << " doesn't exist");
            exit(1);
        }

        Mat eyeball = imread(EYEBALL);
        if (eyeball.empty()) {
            ROS_ERROR_STREAM(EYEBALL << " doesn't exist");
            exit(1);
        }
        cv::resize(eyeball, this->eyeball, cv::Size(20, 40), 0, 0, INTER_AREA);
    }
};

FaceImage::Ptr FaceImage::create(const string& face_dir) {
    return FaceImage::Ptr(new FaceImageImpl(face_dir));
}

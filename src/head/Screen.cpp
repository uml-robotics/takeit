#include "head/Screen.h"

#include <ros/callback_queue.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <boost/thread.hpp>

class ScreenImpl : public Screen {
private:

    ros::NodeHandle nh;
    ros::CallbackQueue callback_queue;

    image_transport::Publisher pub;
    cv_bridge::CvImage bridged_cv_image;

    boost::thread* dedicated_thread;
    bool stop_thread;
    boost::mutex image_mutex;

public:
    ScreenImpl() : dedicated_thread(nullptr), stop_thread(false) {
        nh.setCallbackQueue(&callback_queue);

        // publisher
        image_transport::ImageTransport image_transport(nh);
        pub = image_transport.advertise("/robot/xdisplay", 1);

        bridged_cv_image.encoding = "bgr8";
    }

    ~ScreenImpl() {
        stop_thread = true;
        dedicated_thread->join();
        delete dedicated_thread;
    }

    void display(std::string filepath) override {
        this->display(cv::imread(filepath));
    }

    void display(cv::Mat image) override {
        image_mutex.lock();
        bridged_cv_image.image = image;
        image_mutex.unlock();

        if (bridged_cv_image.image.empty())
            ROS_WARN("img does not exist");

        if (dedicated_thread == nullptr)
            dedicated_thread = new boost::thread(boost::bind(&ScreenImpl::spin, this));
    }

private:
    void spin() {
        auto timeout = ros::WallDuration(0.05);

        sensor_msgs::ImagePtr image_msg;
        while (ros::ok() && ! stop_thread) {
            image_mutex.lock();
            image_msg = bridged_cv_image.toImageMsg();
            image_mutex.unlock();

            pub.publish(image_msg);
            callback_queue.callAvailable(timeout);
        }
    }
};

Screen::Ptr Screen::create() {
    return Screen::Ptr(new ScreenImpl);
}

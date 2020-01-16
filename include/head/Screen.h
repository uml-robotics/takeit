#pragma once

#include <string>
#include <opencv2/core/core.hpp>

namespace boost { template<class T> class shared_ptr; }
namespace ros { class NodeHandle; }
namespace cv { class Mat; }


class Screen {

public:
    typedef boost::shared_ptr<Screen> Ptr;
    static Screen::Ptr create();

    // async. the main thread should keep running or wait longer to allow publish consumed
    virtual void display(std::string filepath) = 0;
    virtual void display(cv::Mat image) = 0;
};
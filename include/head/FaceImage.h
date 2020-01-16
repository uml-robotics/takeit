#pragma once

#include <string>

namespace boost { template<class T> class shared_ptr; }
namespace cv { class Mat; }

class FaceImage {

public:
    typedef boost::shared_ptr<FaceImage> Ptr;
    static FaceImage::Ptr create(const std::string& face_dir);

    // y range = [-20, 20]
    virtual cv::Mat with_eyeballs_vertically(int y) = 0;
};
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "base64.h"

namespace opencv_resize {

    std::string encodeImage(cv::Mat img) {
        std::vector<uchar> buf;
        cv::imencode(".jpg", img, buf);
        auto *enc_msg = reinterpret_cast<unsigned char*>(buf.data());
        return base64_encode(enc_msg, buf.size());
    }

    std::string resizeImage(std::string encodedString, int width, int height)
    {
        std::string decoded_string = base64_decode(encodedString);
        std::vector<uchar> data(decoded_string.begin(), decoded_string.end());
        cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);

        cv::Mat resized_down;
        std::cout<<cv::Size(height, width)<<std::endl;
        std::cout<<encodedString<<std::endl;
        cv::resize(image, resized_down, cv::Size(height, width), cv::INTER_LINEAR);
        return encodeImage(resized_down);
    }
}
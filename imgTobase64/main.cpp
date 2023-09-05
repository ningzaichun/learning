#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <sstream>

class ImageToBase64Converter {
public:
    ImageToBase64Converter() = default;
    ~ImageToBase64Converter() = default;

    std::string convertImageToBase64(const std::string& imagePath) {
        cv::Mat image = cv::imread(imagePath);
        if (image.empty()) {
            std::cerr << "Error: Unable to read image." << std::endl;
            return "";
        }

        std::vector<uchar> buffer;
        cv::imencode(".jpg", image, buffer);

        std::stringstream ss;
        ss << "data:image/jpeg;base64,";
        ss << base64_encode(buffer.data(), buffer.size());

        return ss.str();
    }

    std::string convertImageToBase64(const cv::Mat& image) {
        if (image.empty()) {
            std::cerr << "Error: Unable to read image." << std::endl;
            return "";
        }

        std::vector<uchar> buffer;
        cv::imencode(".jpg", image, buffer);

        std::stringstream ss;
        ss << "data:image/jpeg;base64,";
        ss << base64_encode(buffer.data(), buffer.size());
        return ss.str();
    }

private:
    std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::string base64_encode(const unsigned char* bytes_to_encode, size_t in_len) {
        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];

        while (in_len--) {
            char_array_3[i++] = *(bytes_to_encode++);
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for (i = 0; i < 4; i++)
                    ret += base64_chars[char_array_4[i]];

                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 3; j++)
                char_array_3[j] = '\0';

            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

            for (j = 0; j < i + 1; j++)
                ret += base64_chars[char_array_4[j]];

            while (i++ < 3)
                ret += '=';
        }

        return ret;
    }
};

int main() {
    ImageToBase64Converter converter;
    std::string imagePath = "/home/ym/cpp_demo/imgTobase64/3.jpg";
    std::string base64EncodedImage = converter.convertImageToBase64(imagePath);


    const cv::Mat image = cv::imread(imagePath);
    std::string base64EncodedImage2=converter.convertImageToBase64(image);

    //std::cout << base64EncodedImage << std::endl;
    std::cout << base64EncodedImage2 << std::endl;

    return 0;
}

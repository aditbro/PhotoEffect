#include <math.h>
#include <vector>
#include "complex.h"
#include "dft.h"
#include "image.h"
#include "color.h"

#define PI 3.14159265

std::vector< std::vector <Complex> > fft2d(const std::shared_ptr<Image> &img) {
    int height = img->getHeight();
    int width = img->getWidth();

    std::vector< std::vector <Complex> > result(height, std::vector<Complex>(width));

    // get frequency domain
    for (int y_freq = 0; y_freq < height; y_freq++) {
        for (int x_freq = 0; x_freq < width; x_freq++) {
            // iterate space domain (input img)
            for (int y_space = 0; y_space < height; y_space++) {
                for (int x_space = 0; x_space < width; x_space++) {
                    (result[y_freq][x_freq]).r += (img->getColorAt(y_space, x_space).r * cos(2 * PI * ((1.0 * x_freq * x_space / width) + (1.0 * y_freq * y_space / height)))) / sqrt(width * height);

                    (result[y_freq][x_freq]).i -= (img->getColorAt(y_space, x_space).r * sin(2 * PI * ((1.0 * x_freq * x_space / width) + (1.0 * y_freq * y_space / height)))) / sqrt(width * height);
                }
            }

            std::cout << "(" << x_freq << "," << y_freq << ")\n";
            std::cout << (result[y_freq][x_freq]).r << " + " << (result[y_freq][x_freq]).i << "i\n";
            std::cout << "Scalar: " << (result[y_freq][x_freq]).getScalar() << "\n";
            std::cout << "---\n";
        }
    }

    return result;
}

std::shared_ptr<Image> ifft2d(const std::vector<std::vector<Complex>>& frequencies)
{
    int height = frequencies[0].size();
    int width = frequencies.size();

    Complex result[height][width];

    // get space domain
    for (int y_space = 0; y_space < height; y_space++)
    {
        for (int x_space = 0; x_space < width; x_space++)
        {
            // iterate frequency domain (input img)
            for (int y_freq = 0; y_freq < height; y_freq++)
            {
                for (int x_freq = 0; x_freq < width; x_freq++)
                {
                    double theta = 2 * PI * ((1.0 * x_space * x_freq / width) + (1.0 * y_space * y_freq / height));

                    (result[y_space][x_space]).r += ((frequencies[y_freq][x_freq]).r * cos(theta) - (frequencies[y_freq][x_freq]).i * sin(theta));

                    (result[y_space][x_space]).i += ((frequencies[y_freq][x_freq]).i * cos(theta) + (frequencies[y_freq][x_freq]).r * sin(theta));
                }
            }
        }
    }

    std::shared_ptr<Image> fft_result(new Image('a', width, height));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float scalar_value = (result[i][j]).getScalar();
            if (scalar_value > 255) {
                scalar_value = 255;
            }
            unsigned char color = (unsigned char) scalar_value;
            fft_result->setColorAt(i, j, Color(color, color, color));
        }
    }

    return fft_result;
}
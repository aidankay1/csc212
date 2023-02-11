/*
Image binarization
*/

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<double>> Image;

void ReadFile(std::string file_name, Image *image_data);
void WriteFile(std::string file_name, Image const *image_data);
void DoGlobalThresholding(Image *image_data);
double CalculateGlobalThreshold(Image const *image_data);
void DoLocalThresholding(Image *image_data, long neighborhood_size);
double CalculateLocalThreshold(std::vector<double> const local_pixels, double max_intensity, double min_intensity);

int main(int argc, char *argv[]) {
    std::string binarization_type = argv[1];
    std::string input_filename = argv[2];
    std::string output_filename = argv[3];
    long neighborhood_size = 0;

    if (argc == 5) {
        neighborhood_size = strtol(argv[4], NULL, 10);
    }

    Image img;
    ReadFile(input_filename, &img);

    if (binarization_type == "global") {
        DoGlobalThresholding(&img);
    } else {
        DoLocalThresholding(&img, neighborhood_size);
    }

    WriteFile(output_filename, &img);
}

void ReadFile(std::string file_name, Image *image_data) {
    // Opens the file for reading
    std::ifstream file(file_name);

    // Creates a string to hold each line in temporarily
    std::string line;

    // Iterates over the file, storing one line at a time into `line`
    while (std::getline(file, line)) {
        // Create a temporary 1D Vector of doubles
        std::vector<double> new_row;

        // Create a stringstream object with our line of integers from the file
        std::istringstream iss(line);

        // Create a double that will hold our extracted value from the string
        double token;

        // While there are still numbers in this string, extract them as doubles
        while (iss >> token) {
            // Push these doubles into our temp vector
            new_row.push_back(token);
        }

        // The line is empty, push our completed row into our 2D vector
        image_data->push_back(new_row);
    }
}

void WriteFile(std::string file_name, Image const *image_data) {
    // Open our file with write permissions
    std::ofstream output_file(file_name);

    // Use an iterator to traverse the outer dimension
    for (Image::const_iterator i = (*image_data).begin(); i != (*image_data).end(); ++i) {
        // Use an interator to traverse the inner dimention
        for (std::vector<double>::const_iterator j = i->begin(); j != i->end(); ++j) {
            // Output each element to the file with a space at the end
            output_file << *j << " ";
        }
        // Output a newline symbol to the file
        output_file << "\n";
    }
}

void DoGlobalThresholding(Image *image_data) {
    double global_threshold = CalculateGlobalThreshold(image_data);

    for (auto &row : *image_data) {
        for (auto &pixel : row) {
            if (pixel < global_threshold) {
                pixel = 0;
            } else {
                pixel = 255;
            }
        }
    }
}

double CalculateGlobalThreshold(Image const *image_data) {
    std::vector<double> pixels;

    for (const auto &row : *image_data) {
        for (const auto &pixel : row) {
            pixels.push_back(pixel);
        }
    }

    std::sort(pixels.begin(), pixels.end());

    if (pixels.size() % 2 == 1) {
        return pixels[pixels.size() / 2 - 1];
    } else {
        double left_median = pixels[pixels.size() / 2 - 1];
        double right_median = pixels[pixels.size() / 2];
        return (left_median + right_median) / 2;
    }
}

void DoLocalThresholding(Image *image_data, long neighborhood_size) {
    // Copy image data
    Image image_data_old = *image_data;

    // Get image dimensions
    size_t height = image_data_old.size();
    size_t width = image_data_old.front().size();

    double max_intensity = 0;
    double min_intensity = 255;

    // Find global max and min intensity of image
    for (const auto &row : image_data_old) {
        for (const auto &pixel : row) {
            if (pixel > max_intensity) {
                max_intensity = pixel;
            }

            if (pixel < min_intensity) {
                min_intensity = pixel;
            }
        }
    }

    // Loop over each pixel
    for (long y = 0; y < height; y++) {
        for (long x = 0; x < width; x++) {
            // Keep track of all neighborhood pixels in a vector
            std::vector<double> local_pixels;

            // Loop over local neighborhood
            for (long y_offset = -(neighborhood_size / 2); y_offset <= neighborhood_size / 2; y_offset++) {
                for (long x_offset = -(neighborhood_size / 2); x_offset <= neighborhood_size / 2; x_offset++) {
                    // Skip pixel if out of image bounds
                    if (y + y_offset < 0 ||
                        y + y_offset >= height ||
                        x + x_offset < 0 ||
                        x + x_offset >= width) {
                        continue;
                    }

                    local_pixels.push_back(image_data_old[y + y_offset][x + x_offset]);
                }
            }

            // Use the ADIB formula to calculate local threshold
            double local_threshold = CalculateLocalThreshold(local_pixels, max_intensity, min_intensity);

            // Update pixel based on threshold
            if (image_data_old[y][x] < local_threshold) {
                (*image_data)[y][x] = 0;
            } else {
                (*image_data)[y][x] = 255;
            }
        }
    }
}

double CalculateLocalThreshold(std::vector<double> const local_pixels, double max_intensity, double min_intensity) {
    // Calculate mean with vectors: https://stackoverflow.com/a/7616783
    double intensity_sum = std::accumulate(local_pixels.begin(), local_pixels.end(), 0.0);
    double mean_intensity = intensity_sum / local_pixels.size();

    // Calculate standard deviation with vectors: https://stackoverflow.com/a/7616783
    std::vector<double> diff(local_pixels.size());
    // Prevents overflows/underflows with very large/very small values
    std::transform(local_pixels.begin(), local_pixels.end(), diff.begin(), [mean_intensity](double x) { return x - mean_intensity; });
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev_intensity = sqrt(sq_sum / local_pixels.size());

    double k = 0.2;
    double R = 0.5 * (max_intensity - min_intensity);
    
    return mean_intensity * (1 + k * ((stdev_intensity / R) - 1));
}

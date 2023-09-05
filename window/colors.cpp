#include <better_fractol.h>

glm::vec4 find_ranges(std::vector<float> &data)
{
    std::sort(data.begin(), data.end());
    int lowest = 0;
    while (data[lowest] == 0.0f)
    {
        ++lowest;
    }
 
    int size = data.size();
    int length = size - lowest;
    glm::vec4 ranges = glm::vec4( data[lowest], data[lowest + length * 3 / 4 - 1], data[lowest + length * 7 / 8 - 1], data[size - 1] );
    return ranges;
}
#include <iostream>
#include <iomanip>

#include <opencv2/core.hpp>

void print_point(const cv::Point2f &pt)
{
    std::cout << std::setprecision(7);
    std::cout << pt.x << "\t" << pt.y << std::endl;
}

void print_point(const cv::Point2d &pt)
{
    std::cout << std::setprecision(15);
    std::cout << pt.x << "\t" << pt.y << std::endl;
}

cv::RotatedRect RotatedRect_2f(const cv::Point2f &_point1, const cv::Point2f &_point2, const cv::Point2f &_point3)
{
    cv::Point2f _center = 0.5f * (_point1 + _point3);
    cv::Vec2f vecs[2];
    vecs[0] = cv::Vec2f(_point1 - _point2);
    vecs[1] = cv::Vec2f(_point2 - _point3);
    // print
    print_point(_point1);
    print_point(_point2);
    print_point(_point3);
    std::cout << cv::norm(vecs[0]) << std::endl;
    std::cout << cv::norm(vecs[1]) << std::endl;
    std::cout << std::abs(vecs[0].dot(vecs[1])) / (cv::norm(vecs[0]) * cv::norm(vecs[1])) << std::endl;
    // check that given sides are perpendicular
    CV_Assert(std::abs(vecs[0].dot(vecs[1])) / (cv::norm(vecs[0]) * cv::norm(vecs[1])) <= FLT_EPSILON);

    // wd_i stores which vector (0,1) or (1,2) will make the width
    // One of them will definitely have slope within -1 to 1
    int wd_i = 0;
    if (std::abs(vecs[1][1]) < std::abs(vecs[1][0]))
        wd_i = 1;
    int ht_i = (wd_i + 1) % 2;

    double _angle = std::atan(vecs[wd_i][1] / vecs[wd_i][0]) * 180.0f / (double)CV_PI;
    double _width = (double)cv::norm(vecs[wd_i]);
    double _height = (double)cv::norm(vecs[ht_i]);

    return cv::RotatedRect(_center, cv::Size2d(_width, _height), _angle);
}

cv::RotatedRect RotatedRect_2d(const cv::Point2d &_point1, const cv::Point2d &_point2, const cv::Point2d &_point3)
{
    cv::Point2d _center = 0.5f * (_point1 + _point3);
    cv::Vec2d vecs[2];
    vecs[0] = cv::Vec2d(_point1 - _point2);
    vecs[1] = cv::Vec2d(_point2 - _point3);
    // print
    print_point(_point1);
    print_point(_point2);
    print_point(_point3);
    std::cout << cv::norm(vecs[0]) << std::endl;
    std::cout << cv::norm(vecs[1]) << std::endl;
    std::cout << std::abs(vecs[0].dot(vecs[1])) / (cv::norm(vecs[0]) * cv::norm(vecs[1])) << std::endl;
    // check that given sides are perpendicular
    CV_Assert(std::abs(vecs[0].dot(vecs[1])) / (cv::norm(vecs[0]) * cv::norm(vecs[1])) <= FLT_EPSILON);

    // wd_i stores which vector (0,1) or (1,2) will make the width
    // One of them will definitely have slope within -1 to 1
    int wd_i = 0;
    if (std::abs(vecs[1][1]) < std::abs(vecs[1][0]))
        wd_i = 1;
    int ht_i = (wd_i + 1) % 2;

    double _angle = std::atan(vecs[wd_i][1] / vecs[wd_i][0]) * 180.0f / (double)CV_PI;
    double _width = (double)cv::norm(vecs[wd_i]);
    double _height = (double)cv::norm(vecs[ht_i]);

    return cv::RotatedRect(_center, cv::Size2d(_width, _height), _angle);
}

int main(int argc, char *argv[])
{
    cv::Mat points = (cv::Mat_<double>(10, 2) <<
                    1357., 1337.,
                    1362., 1407.,
                    1367., 1474.,
                    1372., 1543.,
                    1375., 1625.,
                    1375., 1696.,
                    1377., 1734.,
                    1378., 1742.,
                    1382., 1801.,
                    1372., 1990.);

    cv::PCA pca_points(points, cv::Mat(), CV_PCA_DATA_AS_ROW, 2);

    cv::Point2d p1(564.45, 339.8819), p2, p3;
    p2 = p1 - 1999 * cv::Point2d(pca_points.eigenvectors.row(0));
    p3 = p2 - 1498.5295 * cv::Point2d(pca_points.eigenvectors.row(1));

    RotatedRect_2d(p1, p2, p3);
    RotatedRect_2f(p1, p2, p3);
    cv::RotatedRect(p1, p2, p3);

    return 0;
}

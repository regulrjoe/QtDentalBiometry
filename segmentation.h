#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>

using namespace std;

class Segmentation
{
public:
    // Empty constructor
    Segmentation() : _lineprofile_column_spacing(5), _lineprofile_derivative_distance(5) {
        cout << "Create instance of Segmentation." << endl;
    }

    // Destructor
    ~Segmentation() {
        cout << "Destroying instance of Segmentation." << endl;
    }

    // Run algorithm
    cv::Mat Process(const cv::Mat&);


    //// SETTERS AND GETTERS ////
    // Set line profiles column spacing
    bool setLineProfileColumnSpacing(const int& cs) {
        if (cs < 1 || cs > 100)
            return false;
        _lineprofile_column_spacing = cs;
        return true;
    }
    // Get line profiles column spacing
    int getLineProfileColumnSpacing() {
        return _lineprofile_column_spacing;
    }
    // Set line profiles derivative distance
    bool setLineProfileDerivativeDistance(const int& dd) {
        if (dd < 1 || dd > 100)
            return false;
        _lineprofile_derivative_distance = dd;
        return true;
    }
    // Get line profiles derivative distance
    int getLineProfileDerivativeDistance() {
        return _lineprofile_derivative_distance;
    }

private:
    //// ATTRIBUTES ////
    // Local copy of input image
    cv::Mat _image;
    // Local copy of _image for drawing and displaying
    cv::Mat _display_image;
    // Column spacing between line profiles
    int _lineprofile_column_spacing;
    // Distance between values in line profile to derive
    int _lineprofile_derivative_distance;
    // Pair of vectors with crown points <upper crowns, lower crowns>
    pair< vector<cv::Point>, vector<cv::Point> > _crowns;


    //// METHODS ////
    // Obtain derivatives of the vertical line profiles of image
    vector< pair< int, vector<int> > > DerivativeLineProfiles(const cv::Mat&, const int&, const int&);

    // Define upper and lower crown points
    void DefineCrownPoints();

    // Remove crown points too far from avg row to be valid
    void RemoveAfarCrownPoints();

    //// HELPFUL VISUALIZATION METHODS ////
    // Mark an X at input point
    cv::Mat DrawXAtPoints(const cv::Mat&, const vector<cv::Point>&, const cv::Vec3b&, const int& = 2);

    // Draw an image-length horizontal line at input row
    cv::Mat DrawRow(const cv::Mat&, const int&, const cv::Vec3b&);

    // Show display image
    void ShowDisplayImage();


};

#endif // SEGMENTATION_H

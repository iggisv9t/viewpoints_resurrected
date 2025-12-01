#pragma once

#include <FL/Fl_Spinner.H>
#include <FL/Fl_Hor_Value_Slider.H>
#include <FL/Fl_Value_Input.H>

// Replace FLEWS widgets with FLTK equivalents
class Fl_Hor_Value_Slider_Input : public Fl_Hor_Value_Slider {
public:
    Fl_Hor_Value_Slider_Input(int X, int Y, int W, int H, const char* L = 0)
        : Fl_Hor_Value_Slider(X, Y, W, H, L) {
        // Initialize any additional settings if needed
    }
};

class Vp_Value_Input_Spin : public Fl_Spinner {
public:
    Vp_Value_Input_Spin(int X, int Y, int W, int H, const char* L = 0)
        : Fl_Spinner(X, Y, W, H, L) {
        // Initialize any additional settings if needed
        type(FL_FLOAT_INPUT);
        range(-1e9, 1e9);
        step(0.1);
    }

    // Add any additional methods that were in the original class
    void value(double v) { Fl_Spinner::value(v); }
    double value() const { return Fl_Spinner::value(); }
};

// Define any missing constants or enums that were in FLEWS
#ifndef FL_WHEN_RELEASE_ALWAYS
#define FL_WHEN_RELEASE_ALWAYS 4
#endif

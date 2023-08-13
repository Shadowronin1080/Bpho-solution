#ifndef _MAIN_H
#define _MAIN_H

#include<iostream>
#include "main.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include<stdio.h>
#include <math.h>
#include"GLFW/glfw3.h"
#include "implot.h"
#include <vector>
#include<string>
#include <sciplot/sciplot.hpp>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_spline.h>
#include<tuple>
#include "gnuplot-iostream.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
namespace plt = sciplot;


//testing
const int screenHeight = 960;
const int screenWidth = 1680;
const ImVec2 size = ImVec2(1000.0f, 900.0f);
bool arr_bool[11] = { false, false, false, false, false, false, false, false, false, true, false };

const double origin = 0;
const double pi = 3.14159265359;
std::vector<double> originvec = { 0.0 };

int Plan_a, centre, Plan_b = 0;
float value = 0;
float spirocolour[3] = { 1.0f, 1.0f, 1.0f };
int orbits = 10;

//horizons
int index = 0;
std::string H_Strt = "2000-01-01", H_End="2005-01-01", H_dt="1 day";
bool old_orbits;


//data
const char* names[9] = { "Mercury", "Venus" ,"Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto" };
const char* IDS[9] = { "199", "299", "399", "499", "599", "699", "799", "899", "999" };

const float arr_a[9] = { 0.387f, 0.723f, 1.000f, 1.524f, 5.204f, 9.573f, 19.165f, 30.178f, 39.236f };
const float arr_b[9] = { 0.370f, 0.722f, 0.999f , 1.517f, 5.191f, 9.547f, 19.123f, 30.175f, 36.892f };//  *10^6
const float arr_e[9] = { 0.2056f, 0.0068f, 0.0167f, 0.0935f, 0.0487f, 0.0520f, 0.0469f, 0.0097f, 0.2444f };
const float arr_beta[9] = { 7.007f, 3.395f, 0.0f, 1.8f, 1.304f, 2.486f, 0.770f, 1.770f, 17.16f };
const float arr_Rv[9] = { 1.6f, 1.17f, 1.0f, 0.81f, 0.44f, 0.33f, 0.23f, 0.18f, 0.16f };

const float arr_T[9] = { 0.241f, 0.615f, 1.000f, 1.881f, 11.862f, 29.457f, 84.011f, 164.79f, 247.94f };

const float a32[9] = { 0.24075f, 0.614763f, 1.000f, 1.88138f, 11.8715f, 29.6191f, 83.9003f, 165.781f, 245.7689f };

//regression calc 
//maths https://alevelmathsrevision.com/downloads/Lesson%20Notes/Year%201/Further%20Stats/PMCC%20Lesson%20Notes.pdf

class  Planet
{
private:

    double  a, b, r, x, y, beta, theta, speed, xx, z;
    double deltatheta = (2.0 * pi) / 1000;
    ImVec4 colour;


public:
    const char* name;
    const char* Nasa_ID;

    std::vector<double> xpoints, ypoints, zpoints, xxpoints; //points to draw orbit
    std::vector<double> H_x, H_y, H_z;
    double xpos, ypos, zpos, xxpos; //Curent posstition relitive to time


    double p, eccent;

    Planet(int index) {
        a = *(arr_a + index);
        b = *(arr_b + index);
        p = *(arr_T + index);
        eccent = *(arr_e + index);
        name = names[index];
        Nasa_ID = IDS[index];
        speed = arr_Rv[index];
        beta = (arr_beta[index] * pi) / 180;
        CalcOrbit();
    }
    void CalcOrbit() {

        for (int i = 0; i <= 1000; i++) {
            theta = deltatheta * i;
            r = (a * (1 - (eccent * eccent)) / (1 - (eccent * cos(theta))));
            x = r * cos(theta);
            y = r * sin(theta);
            z = x * sin(beta);
            xx = x * cos(beta);
            xpoints.push_back(x);
            ypoints.push_back(y);
            zpoints.push_back(z);
            xxpoints.push_back(xx);
        }
        theta = 0;
    }

    void PlotOrbit() {
        ImPlot::PlotLine(name, xpoints.data(), ypoints.data(), 1000);
    }
    void HorizonOrbit() {
        ImPlot::PlotLine(name, H_x.data(), H_y.data(), H_x.size());

    }

    void HorizonsAnimate(int& index) {
        if ((!H_x.empty()) && (index < H_x.size())) {

            ImPlot::PushStyleVar(ImPlotStyleVar_Marker, ImPlotMarker_Circle);
            ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 8.0f);
            ImPlot::PlotScatter(name, &H_x[index], &H_y[index], 1);
            ImPlot::PopStyleVar(2);

        }
        else if((index > H_x.size())) {
            index = H_x.size()-1;
        
        }

        


    }
    void animate(double time) {

        theta = (2 * pi * time) / p;
        r = (a * (1 - (eccent * eccent)) / (1 - (eccent * cos(theta))));
        double xa = r * cos(theta);
        double ya = r * sin(theta);
        ImPlot::PushStyleVar(ImPlotStyleVar_Marker, ImPlotMarker_Circle);
        ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 8.0f);
        ImPlot::PlotScatter(name, &xa, &ya, 1);
        ImPlot::PopStyleVar(2);

    }
    void spiro(double time) {

        theta = (2 * pi * time) / p;
        r = (a * (1 - (eccent * eccent)) / (1 - (eccent * cos(theta))));
        xpos = r * cos(theta);
        ypos = r * sin(theta);

    }
    void plot() {

        ImPlot::PushStyleColor(ImPlotCol_MarkerFill, ImVec4(0.956f, 0.501f, 0.215f, 1));
        ImPlot::PushStyleColor(ImPlotCol_MarkerOutline, ImVec4(0.956f, 0.501f, 0.215f, 1));
        ImPlot::PushStyleVar(ImPlotStyleVar_Marker, ImPlotMarker_Circle);

        ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 8.0f);
        ImPlot::PlotScatter(name, &origin, &origin, 1);

        ImPlot::PopStyleColor(2);
        ImPlot::PopStyleVar(2);
    }
    auto OrbitData3D() {
        return std::make_tuple(xxpoints, ypoints, zpoints);


    }
    auto animate3d(double time) {

        std::vector<std::pair<std::pair<double, double>, double>> points;

        //points.push_back({ {1.0, 2.0}, 3.0 });

        theta = (2 * pi * time) / p;
        r = (a * (1 - (eccent * eccent)) / (1 - (eccent * cos(theta))));
        double x = r * cos(theta);
        double y = r * sin(theta);
        double xx = x * cos(beta); //xx
        double z = x * sin(beta);
        points.push_back({ {xx, y}, z });
        return points;

    }
    void Horizons(std::string StartDate, std::string EndDate, std::string dt, std::string centre) {

        //make sure the vectors(arrays) are empty
        H_x.clear();
        H_y.clear();
        H_z.clear();
        std::string command;

        command = "/api/horizons.api?format=text&COMMAND='" + std::string{ Nasa_ID } + "'&OBJ_DATA='NO'&MAKE_EPHEM='YES'&EPHEM_TYPE='VECTORS'&VEC_TABLE='1'&VEC_LABELS='NO'&OUT_UNITS='AU-D'&CSV_FORMAT='YES'";
        command = command + "&CENTER='500@" + centre + "'&START_TIME='" + StartDate + "'&STOP_TIME='" + EndDate + "'&STEP_SIZE='" + dt + "'";


        httplib::SSLClient cli("ssd.jpl.nasa.gov");


        auto res = cli.Get(command);
        std::cout << res->status << "\n";


        std::string body = res->body;
        std::vector<std::string> data;

        const char* strt = "$$SOE";
        const char* end = "$$EOE";


        size_t START = (body).find(strt) + 6;
        size_t END = ((body).find(end));
        size_t LEN = END - START;

        body = body.substr(START, LEN);


        for (int i = 0; i < (body.length() / (123)); i++) {

            std::string temp_body = body;

            size_t TEMP_START = ((i * 123) + 50);
            size_t TEMP_LEN = 72;

            std::string temp_data = temp_body.substr(TEMP_START, TEMP_LEN);
            std::cout << temp_data << "\n";
            //split up into x y and z
            std::string x = temp_data.substr(0, 24);
            std::string y = temp_data.substr(24, 24);
            std::string z = temp_data.substr(48, 24);


            //data.push_back(temp_data);
            //string to long double
            H_x.push_back(std::stod(x));
            H_y.push_back(std::stod(y));
            H_z.push_back(std::stod(z));

            std::cout << std::stod(x) << std::stod(y) << "\n";

            temp_body = body;
        }





    }



};

void spirograph(Planet a, Planet b);
void ptolomey(Planet origin, Planet a);
void gnuplot3d();


long double simpsons(Planet P, double a, double b, int N) {

    long double h = (b - a) / N;

    int c;
    long double fx, sum = 0.0;
    long double x;
    for (int i = 0; i < N; i++) {
        x = a + (h * i);
        if ((i == 0) || (i == N)) { c = 1; }
        else if ((i % 2) != 0)
        {
            c = 4;
        }
        else { c = 2; }
        fx = pow(((1 - P.eccent) * cos(x)), -2);
        sum += (fx * c);

    }
    return ((sum * h) / 3.0);




}
double interpolate(std::vector<double> tt, std::vector<double> theta, double t) {

    // Create spline-interpolated curve
    gsl_interp_accel* acc = gsl_interp_accel_alloc();
    gsl_spline* spline = gsl_spline_alloc(gsl_interp_cspline, tt.size());
    gsl_spline_init(spline, tt.data(), theta.data(), tt.size());

    // Evaluate spline at desired time points t
    double theta_interpolated;

    theta_interpolated = gsl_spline_eval(spline, t, acc);


    // Cleanup
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);

    // Return the interpolated polar angles
    return theta_interpolated;

}
void integrate(Planet a, int O) {


    long double dtheta = (2 * pi * O) / 1234;
    std::vector<double> angles;
    std::vector<double> times;
    std::vector<double> t_vec, a_vec, theta;


    long double t = 0, sum = 0;


    for (double theta = 0;theta < (2 * pi) * O;theta += dtheta) {
        sum += simpsons(a, theta, (theta + dtheta), O);
        t = ((a.p) * pow((1 - pow(a.eccent, 2)), 1.5)) * pow((2 * pi), -1) * (sum);

        angles.push_back((theta));
        times.push_back((t / 1000));

    }
    for (int time = 0, tmax = a.p * O, dt = tmax / 100; time < tmax; time += dt)
    {
        theta.push_back((2 * pi * time) / a.p);
        t_vec.push_back(time);

    }

    ImPlot::PlotLine(a.name, times.data(), angles.data(), times.size());
    ImPlot::PlotLine("circular", t_vec.data(), theta.data(), theta.size());



}






#endif












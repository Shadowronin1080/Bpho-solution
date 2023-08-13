#include<iostream>
#include "main.h"
#include "imgui.h"
#include"imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include<stdio.h>
#include <math.h>
#include"GLFW/glfw3.h"
#include "implot.h"
#include <vector>
#include<string>
#include<thread>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_spline.h>
#include"gnuplot-iostream.h"
#include<tuple>
#include"imgui-knobs.h"




//namespace plt = matplot;
Planet Mercury(0), Venus(1), Earth(2), Mars(3), Jupiter(4), Saturn(5), Uranus(6), Neptune(7), Pluto(8);

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}




int main(int, char**) {

    bool my_tool_active = false;
    float colour = 0xeb4034;
    float* my_color = &colour;


    double max_time = Mercury.p;
    double time = 0;




    glfwSetErrorCallback(glfw_error_callback);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    if (!glfwInit()) {
        return 1;
    }

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only


    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Bpho Solution Rayan Fahad", nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);



    while (!glfwWindowShouldClose(window)) {
        if (arr_bool[8]) {
            max_time = Pluto.p;
        }
        else {
            if (arr_bool[7]) {
                max_time = Neptune.p;
            }
            else {
                if (arr_bool[6]) {
                    max_time = Uranus.p;
                }
                else {
                    if (arr_bool[5]) {
                        max_time = Saturn.p;
                    }
                    else {
                        if (arr_bool[4]) {
                            max_time = Jupiter.p;
                        }
                        else {
                            if (arr_bool[3]) {
                                max_time = Mars.p;
                            }
                            else {
                                if (arr_bool[2]) {
                                    max_time = Earth.p;
                                }
                                else {
                                    if (arr_bool[1]) {
                                        max_time = Venus.p;
                                    }
                                    else {
                                        max_time = Mercury.p;
                                    }
                                }
                            }


                        }

                    }

                }
            }
        }
        float deltatime = max_time / 1000;
        if (!(arr_bool[10])) {
            time = 0;
        }
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Window", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);


        if (ImGui::BeginTabBar("my tab bar", ImGuiTabItemFlags_Trailing)) {


            if (ImGui::BeginTabItem("   Keplars 3rd Law   ")) {

                ImGui::Columns(2, nullptr, true);
                ImGui::SetColumnOffset(1, 1009.5);

                ImGui::Text("Task 1");

                if (ImPlot::BeginPlot("Keplar's 3rd Law Proof", size, ImPlotSubplotFlags_NoResize)) {

                    ImPlot::SetupAxes("(a/AU)^3", "(T/Yr)^2");
                    ImPlot::SetupAxesLimits(0, 300, 0, 300);

                    ImPlot::PushStyleVar(ImPlotStyleVar_Marker, ImPlotMarker_Cross);
                    ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 10.0f);

                    ImPlot::PlotLine("my line plot", a32, arr_T, 9);
                    ImPlot::PopStyleVar(2);

                    ImPlot::EndPlot();
                }
                ImGui::NextColumn();

                ImGui::Text("""Proof of keplars third law : \nKeplars third law states that the square of the period is directly proportional to the cube \nof the semi-major axis, when plotted againt each other these result in a near straight line""");


                ImGui::Columns(1);
              

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("   Orbits   ")) {

                ImGui::Columns(2, nullptr, true);
                ImGui::SetColumnOffset(1, 1009.5);
                ImGui::Text("Task 2");
                if (arr_bool[9]) { ImPlot::SetNextAxesToFit(); }
                if (ImPlot::BeginPlot("Plot of The Planets", size)) {


                    ImPlot::SetupAxes("X/AU", "Y/AU");

                    ImPlot::PushStyleColor(ImPlotCol_MarkerFill, ImVec4(0.956f, 0.501f, 0.215f, 1));
                    ImPlot::PushStyleColor(ImPlotCol_MarkerOutline, ImVec4(0.956f, 0.501f, 0.215f, 1));
                    ImPlot::PushStyleVar(ImPlotStyleVar_Marker, ImPlotMarker_Circle);

                    ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 8.0f);
                    ImPlot::PlotScatter("Sun", &origin, &origin, 1);

                    ImPlot::PopStyleColor(2);
                    ImPlot::PopStyleVar(2);
                    //multiplyed by 10* the orbital velocity aprox ratio https://nssdc.gsfc.nasa.gov/planetary/factsheet/planet_table_ratio.html


                    if (arr_bool[0]) { Mercury.PlotOrbit();if (arr_bool[10]) { Mercury.animate(time);max_time = Mercury.p; } }
                    if (arr_bool[1]) { Venus.PlotOrbit();if (arr_bool[10]) { Venus.animate(time);max_time = Venus.p; } }
                    if (arr_bool[2]) { Earth.PlotOrbit();if (arr_bool[10]) { Earth.animate(time);max_time = Earth.p; } }
                    if (arr_bool[3]) { Mars.PlotOrbit();if (arr_bool[10]) { Mars.animate(time);max_time = Mars.p; } }
                    if (arr_bool[4]) { Jupiter.PlotOrbit();if (arr_bool[10]) { Jupiter.animate(time);max_time = Jupiter.p; } }
                    if (arr_bool[5]) { Saturn.PlotOrbit();if (arr_bool[10]) { Saturn.animate(time);max_time = Saturn.p; } }
                    if (arr_bool[6]) { Uranus.PlotOrbit();if (arr_bool[10]) { Uranus.animate(time);max_time = Uranus.p; } }
                    if (arr_bool[7]) { Neptune.PlotOrbit();if (arr_bool[10]) { Neptune.animate(time);max_time = Neptune.p; } }
                    if (arr_bool[8]) { Pluto.PlotOrbit();if (arr_bool[10]) { Pluto.animate(time);max_time = Pluto.p; } }

                    ImPlot::EndPlot();
                }
                ImGui::NextColumn();

                ImGui::SliderFloat("Time Step", &deltatime, 0.000241f, 0.248f);
                //ImGui::InputDouble("Delta T", &deltat);

                ImGui::Checkbox("Mercury", &arr_bool[0]);
                ImGui::SameLine();
                ImGui::Checkbox("AutoFit", &arr_bool[9]);
                ImGui::SameLine();
                ImGui::Checkbox("Animate", &arr_bool[10]);
                ImGui::Checkbox("venus", &arr_bool[1]);
                ImGui::Checkbox("earth", &arr_bool[2]);
                ImGui::Checkbox("mars", &arr_bool[3]);
                ImGui::Checkbox("jupiter", &arr_bool[4]);
                ImGui::Checkbox("saturn", &arr_bool[5]);
                ImGui::Checkbox("uranus", &arr_bool[6]);
                ImGui::Checkbox("neptune", &arr_bool[7]);
                ImGui::Checkbox("pluto", &arr_bool[8]);


                if (ImGui::Button("Plot 3D orbits")) {

                    std::thread graph(gnuplot3d);
                    graph.detach();

                }


                ImGui::Columns(1);

                ImGui::EndTabItem();

            }
            if (ImGui::BeginTabItem("   Eccentricity   ")) {


                ImGui::Text("Task 3");
                ImGui::Columns(2, nullptr, true);
                ImGui::SetColumnOffset(1, 1009.5);

                if (ImPlot::BeginPlot("Spirograph of the planets ", size)) {


                    ImPlot::SetupAxes("TIME", "ANGLE");

                    integrate(Pluto, orbits);



                    ImPlot::EndPlot();
                }
                ImGui::NextColumn();
                ImGuiKnobs::KnobInt("orbits of planet", &orbits, 2, 200);

                ImGui::Columns(1);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("   Spirographs   ")) {
                Planet a(Plan_a), b(Plan_b);


                ImGui::Columns(2, nullptr, true);
                ImGui::SetColumnOffset(1, 1009.5);
                if (arr_bool[9]) { ImPlot::SetNextAxesToFit(); }
                if (ImPlot::BeginPlot("Spirograph of the planets ", size)) {


                    ImPlot::SetupAxes("X/AU", "Y/AU");

                    spirograph(a, b);


                    ImPlot::EndPlot();
                }

                ImGui::NextColumn();

                ImGui::Text("Choose The Further Planet :                  Choose The closer Planet : ");


                ImGui::ListBox("", &Plan_a, names, 9);
                ImGui::SameLine(NULL, 15.0f);
                ImGui::ListBox("##box 2", &Plan_b, names, 9);

                ImGui::Checkbox("AutoFit", &arr_bool[9]);
                ImGui::ColorEdit3("colour", spirocolour);

                //if(ImGui::BeginListBox("Choose Outer Planet"))
                ImGui::Columns(1);
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("   Ptolomey   ")) {
                ImGui::Columns(2, nullptr, true);
                ImGui::SetColumnOffset(1, 1009.5);
                Planet Centre(centre);
                if (arr_bool[9]) { ImPlot::SetNextAxesToFit(); }

                if (ImPlot::BeginPlot("Plot of The Planets", size)) {



                    ImPlot::SetupAxes("X/AU", "Y/AU");
                    Centre.plot();
                    if (arr_bool[0]) { ptolomey(centre, Mercury); }
                    if (arr_bool[1]) { ptolomey(centre, Venus); }
                    if (arr_bool[2]) { ptolomey(centre, Earth); }
                    if (arr_bool[3]) { ptolomey(centre, Mars); }
                    if (arr_bool[4]) { ptolomey(centre, Jupiter); }
                    if (arr_bool[5]) { ptolomey(centre, Saturn); }
                    if (arr_bool[6]) { ptolomey(centre, Uranus); }
                    if (arr_bool[7]) { ptolomey(centre, Neptune); }
                    if (arr_bool[8]) { ptolomey(centre, Pluto); }


                    ImPlot::EndPlot();
                }
                ImGui::NextColumn();
                ImGui::Combo("##combo", &centre, names, 9, 9);
                ImGui::SameLine();
                ImGui::Checkbox("AutoFit", &arr_bool[9]);

                ImGui::Checkbox("Mercury", &arr_bool[0]);
                ImGui::SameLine();
                ImGui::Checkbox("venus", &arr_bool[1]);
                ImGui::SameLine();
                ImGui::Checkbox("earth", &arr_bool[2]);
                ImGui::SameLine();
                ImGui::Checkbox("mars", &arr_bool[3]);

                ImGui::Checkbox("jupiter", &arr_bool[4]);
                ImGui::SameLine();
                ImGui::Checkbox("saturn", &arr_bool[5]);
                ImGui::SameLine();
                ImGui::Checkbox("uranus", &arr_bool[6]);
                ImGui::SameLine();
                ImGui::Checkbox("neptune", &arr_bool[7]);
                ImGui::SameLine();
                ImGui::Checkbox("pluto", &arr_bool[8]);
                ImGui::SliderInt("Number of orbits for center", &orbits, 10, 100);




                ImGui::Columns(1);


                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Horizons")) {
                ImGui::Columns(2, nullptr, true);
                ImGui::SetColumnOffset(1, 1009.5);
                if (arr_bool[9]) { ImPlot::SetNextAxesToFit(); }
                if (ImPlot::BeginPlot("Plot of The Planets", size)) {
                    ImPlot::SetupAxes("X/AU", "Y/AU");

                    if (arr_bool[0]) {
                        Mercury.HorizonsAnimate(index);
                        if (old_orbits) {
                            Mercury.PlotOrbit();
                        }
                        else { Mercury.HorizonOrbit(); }

                    }
                    if (arr_bool[1]) {
                        Venus.HorizonsAnimate(index);
                        if (old_orbits) {
                            Venus.PlotOrbit();
                        }
                        else { Venus.HorizonOrbit(); }
                    }
                    if (arr_bool[2]) {
                        Earth.HorizonsAnimate(index);
                        if (old_orbits) {
                            Earth.PlotOrbit();
                        }
                        else { Earth.HorizonOrbit(); }
                    }
                    if (arr_bool[3]) {
                        Mars.HorizonsAnimate(index);
                        if (old_orbits) {
                            Mars.PlotOrbit();
                        }
                        else { Mars.HorizonOrbit(); }
                    }
                    if (arr_bool[4]) {
                        Jupiter.HorizonsAnimate(index);
                        if (old_orbits) {
                            Jupiter.PlotOrbit();
                        }
                        else { Jupiter.HorizonOrbit(); }
                    }
                    if (arr_bool[5]) {
                        Saturn.HorizonsAnimate(index);
                        if (old_orbits) {
                            Saturn.PlotOrbit();
                        }
                        else { Saturn.HorizonOrbit(); }
                    }
                    if (arr_bool[6]) {
                        Uranus.HorizonsAnimate(index);
                        if (old_orbits) {
                            Uranus.PlotOrbit();
                        }
                        else { Uranus.HorizonOrbit(); }
                    }
                    if (arr_bool[7]) {
                        Neptune.HorizonsAnimate(index);
                        if (old_orbits) {
                            Neptune.PlotOrbit();
                        }
                        else { Neptune.HorizonOrbit(); }
                    }
                    if (arr_bool[8]) {
                        Pluto.HorizonsAnimate(index);
                        if (old_orbits) {
                            Pluto.PlotOrbit();
                        }
                        else { Pluto.HorizonOrbit(); }
                    }

                    index++;


                    ImPlot::EndPlot();
                }



                ImGui::NextColumn();
                ImGui::InputText("The Start Date ", &H_Strt);
                ImGui::InputText("The End Date ", &H_End);
                ImGui::InputText("The Time Step", &H_dt);
                ImGui::Checkbox("AutoFit", &arr_bool[9]);
                ImGui::SameLine();
                ImGui::Checkbox("Old Orbits", &old_orbits);

                ImGui::Checkbox("Mercury", &arr_bool[0]);
                ImGui::SameLine();
                ImGui::Checkbox("venus", &arr_bool[1]);
                ImGui::SameLine();
                ImGui::Checkbox("earth", &arr_bool[2]);
                ImGui::SameLine();
                ImGui::Checkbox("mars", &arr_bool[3]);

                ImGui::Checkbox("jupiter", &arr_bool[4]);
                ImGui::SameLine();
                ImGui::Checkbox("saturn", &arr_bool[5]);
                ImGui::SameLine();
                ImGui::Checkbox("uranus", &arr_bool[6]);
                ImGui::SameLine();
                ImGui::Checkbox("neptune", &arr_bool[7]);
                ImGui::SameLine();
                ImGui::Checkbox("pluto", &arr_bool[8]);
                ImGui::SliderInt("Number of orbits for center", &orbits, 10, 100);
                if (ImGui::Button("Horizons Data Generate ")) {

                    if (arr_bool[0]) { Mercury.Horizons(H_Strt, H_End, H_dt, "10"); }
                    if (arr_bool[1]) { Venus.Horizons(H_Strt, H_End, H_dt, "10"); }
                    if (arr_bool[2]) { Earth.Horizons(H_Strt, H_End, H_dt, "10"); }
                    if (arr_bool[3]) { Mars.Horizons(H_Strt, H_End, H_dt, "10"); }
                    if (arr_bool[4]) { Jupiter.Horizons(H_Strt, H_End, H_dt, "10"); }
                    if (arr_bool[5]) { Saturn.Horizons(H_Strt, H_End, H_dt, "10"); }
                    if (arr_bool[6]) { Uranus.Horizons(H_Strt, H_End, H_dt, "10"); }
                    if (arr_bool[7]) { Neptune.Horizons(H_Strt, H_End, H_dt, "10"); }
                    if (arr_bool[8]) { Pluto.Horizons(H_Strt, H_End, H_dt, "10"); }
                }
                ImGui::SameLine();
                if (ImGui::Button("Reset Plot")) {
                    index = 0;
                }



                ImGui::Columns(1);
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();

        time = time + deltatime;


        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);





    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;

}
void gnuplot3d() {
    double max_time;
    bool first_done = false;



    Gnuplot gp;
    gp.useTmpFile(true);


    for (double t = 0;;) {
        if (arr_bool[8]) {
            max_time = Pluto.p;
        }
        else {
            if (arr_bool[7]) {
                max_time = Neptune.p;
            }
            else {
                if (arr_bool[6]) {
                    max_time = Uranus.p;
                }
                else {
                    if (arr_bool[5]) {
                        max_time = Saturn.p;
                    }
                    else {
                        if (arr_bool[4]) {
                            max_time = Jupiter.p;
                        }
                        else {
                            if (arr_bool[3]) {
                                max_time = Mars.p;
                            }
                            else {
                                if (arr_bool[2]) {
                                    max_time = Earth.p;
                                }
                                else {
                                    if (arr_bool[1]) {
                                        max_time = Venus.p;
                                    }
                                    else {
                                        max_time = Mercury.p;
                                    }
                                }
                            }


                        }

                    }

                }
            }
        }
        if (t > max_time) { t = 0; }
        double dt = max_time / 1000;

        auto plots = gp.splotGroup();

        if (arr_bool[10]) {

            if (arr_bool[0]) {
                {plots.add_plot1d((Mercury.OrbitData3D()), "with line title 'Mercury' linetype rgb 'gray'");}
                {plots.add_plot1d((Mercury.animate3d(t)), "with points notitle pt 7");}
            }
            if (arr_bool[1]) {
                {plots.add_plot1d((Venus.OrbitData3D()), "with line title 'Venus' linetype rgb 'yellow'");}
                {plots.add_plot1d((Venus.animate3d(t)), "with points notitle pt 7");}
            }
            if (arr_bool[2]) {
                {plots.add_plot1d((Earth.OrbitData3D()), "with line title 'Earth' linetype rgb 'green'");}
                {plots.add_plot1d((Earth.animate3d(t)), "with points notitle pt 7");}
            }
            if (arr_bool[3]) {
                {plots.add_plot1d((Mars.OrbitData3D()), "with line title 'Mars' linetype rgb 'red'");}
                {plots.add_plot1d((Mars.animate3d(t)), "with points notitle pt 7");}
            }
            if (arr_bool[4]) {
                {plots.add_plot1d((Jupiter.OrbitData3D()), "with line title 'Jupiter' linetype rgb 'purple'");}
                {plots.add_plot1d((Jupiter.animate3d(t)), "with points notitle pt 7");}
            }
            if (arr_bool[5]) {
                {plots.add_plot1d((Saturn.OrbitData3D()), "with line title 'Saturn' linetype rgb 'orange'");}
                {plots.add_plot1d((Saturn.animate3d(t)), "with points notitle pt 7");}
            }
            if (arr_bool[6]) {
                {plots.add_plot1d((Uranus.OrbitData3D()), "with line title 'Uranus' linetype rgb 'cyan'");}
                {plots.add_plot1d((Uranus.animate3d(t)), "with points notitle pt 7");}
            }
            if (arr_bool[7]) {
                {plots.add_plot1d((Neptune.OrbitData3D()), "with line title 'Neptune' linetype rgb 'blue'");}
                {plots.add_plot1d((Neptune.animate3d(t)), "with points notitle pt 7");}
            }
            if (arr_bool[8]) {
                {plots.add_plot1d((Pluto.OrbitData3D()), "with line title 'Pluto' linetype rgb 'violet'");}
                {plots.add_plot1d((Pluto.animate3d(t)), "with points notitle pt 7");}
            }


            t += dt;
            gp << plots;

            gp.flush();

        }
        else {


            if (arr_bool[0]) {
                {plots.add_plot1d((Mercury.OrbitData3D()), "with line title 'Mercury' linetype rgb 'gray'");}
                {plots.add_plot1d((Mercury.animate3d(t)), "with points notitle pt 7");}
            }
            if (arr_bool[1]) {
                {plots.add_plot1d((Venus.OrbitData3D()), "with line title 'Venus' linetype rgb 'yellow'");}
            }
            if (arr_bool[2]) {
                {plots.add_plot1d((Earth.OrbitData3D()), "with line title 'Earth' linetype rgb 'green'");}
            }
            if (arr_bool[3]) {
                {plots.add_plot1d((Mars.OrbitData3D()), "with line title 'Mars' linetype rgb 'red'");}
            }
            if (arr_bool[4]) {
                {plots.add_plot1d((Jupiter.OrbitData3D()), "with line title 'Jupiter' linetype rgb 'purple'");}
            }
            if (arr_bool[5]) {
                {plots.add_plot1d((Saturn.OrbitData3D()), "with line title 'Saturn' linetype rgb 'orange'");}
            }
            if (arr_bool[6]) {
                {plots.add_plot1d((Uranus.OrbitData3D()), "with line title 'Uranus' linetype rgb 'cyan'");}
            }
            if (arr_bool[7]) {
                {plots.add_plot1d((Neptune.OrbitData3D()), "with line title 'Neptune' linetype rgb 'blue'");}

            }
            if (arr_bool[8]) {
                {plots.add_plot1d((Pluto.OrbitData3D()), "with line title 'Pluto' linetype rgb 'violet'");}

            }
            gp << plots;

        }
    }


}

void spirograph(Planet a, Planet b) {
    double t, dt, tmax;
    float x[2], y[2];
    if ((a.p) > (b.p)) {
        tmax = (a.p) * 10;
    }
    else { tmax = b.p; }
    dt = tmax / 1234;
    a.PlotOrbit();b.PlotOrbit();
    for (t = 0;t < tmax;t += dt) {
        a.spiro(t);
        b.spiro(t);
        x[0] = a.xpos;x[1] = b.xpos;
        y[0] = a.ypos;y[1] = b.ypos;

        ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(spirocolour[0], spirocolour[1], spirocolour[2], 1.0f));
        ImPlot::PlotLine("", x, y, 2);
        ImPlot::PopStyleColor();

    }


}

void ptolomey(Planet centre, Planet a) {
    double t, dt, tmax;
    tmax = centre.p * orbits;
    dt = tmax / 1000;
    std::vector<double> x, y;


    for (t = 0;t < tmax;t += dt) {
        centre.spiro(t);a.spiro(t);
        x.push_back((a.xpos) - (centre.xpos));
        y.push_back((a.ypos) - (centre.ypos));
    }
    ImPlot::PlotLine(a.name, x.data(), y.data(), 1000);
}















/*
 * Acid Cam v2 - OpenCV Edition
 * written by Jared Bruni ( http://lostsidedead.com / https://github.com/lostjared )
 
 
 GitHub: http://github.com/lostjared
 Website: http://lostsidedead.com
 YouTube: http://youtube.com/LostSideDead
 Instagram: http://instagram.com/jaredbruni
 Twitter: http://twitter.com/jaredbruni
 Facebook: http://facebook.com/LostSideDead0x
 
 You can use this program free of charge and redistrubute as long
 as you do not charge anything for this program. This program is 100%
 Free.
 
 BSD 2-Clause License
 
 Copyright (c) 2017, Jared Bruni
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 */

#ifndef __ACIDCAM__H__
#define __ACIDCAM__H__
#include"ac.h"
#include<iostream>
#include<iomanip>
#include<vector>

namespace cmd {
    
    class AC_Program {
    public:
        AC_Program() = default;
        AC_Program(const AC_Program &) = delete;
        AC_Program(AC_Program &&) = delete;
        AC_Program &operator=(const AC_Program &) = delete;
        AC_Program &operator=(AC_Program &&) = delete;
        
        bool initProgram(bool visible, const std::string &input, const std::string &output, std::vector<int> &filter_list) {
            is_visible = visible;
            input_file = input;
            output_file = output;
            filters = filter_list;
            capture.open(input_file);
            if(!capture.isOpened()) {
                std::cerr << "acidcam: Error could not open file: " << input_file << "\n";
                return false;
            }
            int aw = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
            int ah = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));
            double fps = capture.get(CV_CAP_PROP_FPS);
            writer.open(output_file, CV_FOURCC('m', 'p', '4', 'v'), fps, cv::Size(aw, ah), true);
            if(!writer.isOpened()) {
                std::cerr << "acidcam: Error could not open file for writing: " << output_file << "\n";
                return false;
            }
            std::cout << "acidcam: input[" << input_file << "] output[" << output_file << "] width[" << aw << "] height[" << ah << "] fps[" << fps << "]\n";
            std::cout << "\nFilters to Apply: \n";
            for(unsigned int q = 0; q < filter_list.size(); ++q) {
                std::cout << ac::draw_strings[q] << "\n";
            }
            std::cout << "\n";
            return true;
        }
        
        void run() {
            unsigned long frame_count_len = 0, frame_index = 0;
            frame_count_len = capture.get(CV_CAP_PROP_FRAME_COUNT);
            bool active = true;
            unsigned int percent_now = 0;
            
            if(is_visible)
                cv::namedWindow("acidcam_cli");
            
            while(active == true) {
                cv::Mat frame;
                if(capture.read(frame) == false) {
                    break;
                }
                frame_index ++;
                if(frame_index >= frame_count_len) {
                    break;
                }
                for(unsigned int i = 0; i < filters.size(); ++i) {
                    ac::draw_func[filters[i]](frame);
                }
                writer.write(frame);
                double val = frame_index;
                double size = frame_count_len;
                if(size != 0) {
                    double percent = (val/size)*100;
                    unsigned int percent_trunc = static_cast<unsigned int>(percent);
                    if(percent_trunc > percent_now) {
                        percent_now = percent_trunc;
                        std::cout << "acidcam: Working frame: [" << frame_index << "/" << frame_count_len << "] - " << percent_trunc << "%\n";
                    }
                }
                if(is_visible) {
                    cv::imshow("acidcam_cli", frame);
                    int key = cv::waitKey(25);
                    if(key == 27) break;
                }
            }
            std::cout << "acidcam: 100% Done wrote to file [" << output_file << "]\n";
        }
        
        std::string getInput() const { return input_file; }
        std::string getOutput() const { return output_file; }
    private:
        std::string input_file, output_file;
        cv::VideoCapture capture;
        cv::VideoWriter writer;
        std::vector<int> filters;
        bool is_visible;
    };
}

#endif

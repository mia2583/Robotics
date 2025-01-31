cmake_minimum_required(VERSION 3.10)
project(OpenCVTest)

# OpenCV 경로 설정
find_package(OpenCV REQUIRED)

# 빌드할 실행파일 이름과 소스 파일 목록 설정
add_executable(simple_drawing simple_drawing.cpp)
add_executable(simple_control simple_control.cpp)

# OpenCV 라이브러리 링크
target_link_libraries(simple_drawing PRIVATE ${OpenCV_LIBS})
target_link_libraries(simple_control PRIVATE ${OpenCV_LIBS})

# C++ 표준 설정 (C++11 이상 권장)
set(CMAKE_CXX_STANDARD 11)

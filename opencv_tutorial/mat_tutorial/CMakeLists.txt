cmake_minimum_required(VERSION 3.10)
project(OpenCVTest)

# OpenCV 경로 설정
find_package(OpenCV REQUIRED)

# 빌드할 실행파일 이름과 소스 파일 목록 설정
add_executable(simple_mat simple_mat.cpp)
add_executable(simple_image simple_image.cpp)
add_executable(pixel_access pixel_access.cpp)
add_executable(simple_video simple_video.cpp)

# OpenCV 라이브러리 링크
target_link_libraries(simple_mat PRIVATE ${OpenCV_LIBS})
target_link_libraries(simple_image PRIVATE ${OpenCV_LIBS})
target_link_libraries(pixel_access PRIVATE ${OpenCV_LIBS})
target_link_libraries(simple_video PRIVATE ${OpenCV_LIBS})

# C++ 표준 설정 (C++11 이상 권장)
set(CMAKE_CXX_STANDARD 11)

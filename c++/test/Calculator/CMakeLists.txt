cmake_minimum_required(VERSION 3.10)
project(Calculator)

# 헤더 경로 추가
include_directories(${PROJECT_SOURCE_DIR}/include)

# 실행 파일 생성
add_executable(CalculatorApp
    src/Calculator.cpp
    src/CalculatorTutorial.cpp
)
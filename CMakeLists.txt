#cmake_minimum_required(VERSION 3.10) 
cmake_minimum_required(VERSION 3.31) //현재 cmake버쳔디 3.31 이상 일것. 
project(CppProSFML)

set(CMAKE_CXX_STANDARD 17)
# set(OpenGL_GL_PREFERENCE GLVND)

# 1. 소스 파일들을 리스트로 만들기 (source 폴더 내의 모든 cpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
   
# 2. 패키지 찾기 
# find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

# 3. 실행 파일 생성 (main.cpp가 루트에 있다면 포함, 소스 리스트 추가)
add_executable(CppProSFML main.cpp ${SOURCES}) 

# 4. 핵심: include 폴더 경로를 컴파일러에게 알려주기 
target_include_directories(CppProSFML PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 5. 라이브러리 연결
target_link_libraries(CppProSFML sfml-graphics sfml-window sfml-system)

# file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
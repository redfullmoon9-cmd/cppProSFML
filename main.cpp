// #define _CRTDBG_MAP_ALLOC
#include <cstdlib>

// C++에서 new에 대한 누수 라인까지 찾으려면 아래 정의 추가 (선택 사항이지만 권장)

#include <iostream>
#include <SFML/Graphics.hpp>
#include "DrawTest1.hpp"
#include "DrawTest2.hpp"
#include "DrawTest3.hpp"
#include "DrawTest4.hpp"
#include <random>
#include <filesystem>

int main()
{
    // 메모리 누수 자동 설정. 상단의 #define _CRTDBG_MAP_ALLOC과 함께 사용.
    // 이곳의 설정이 있어야 메모리 누수를 출력 할 수 있음.
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); -- 리눅스에는 없는코드 ...
    int mode = 2;
    // 경로 확인용 디버깅
    // std::cout << "Working dir: " << std::filesystem::current_path() << std::endl;

    // std::cout << "Exists: " << std::filesystem::exists("resources/graphics/fighter.png") << std::endl;

    // 기본적인 shape테스트
    if (mode == 1)
    {
        DrawTest dTest;
        dTest.run();
    }
    // 키보드 이벤트 다루기 별도 수행.
    else if (mode == 2)
    {
        DrawTest2 dTest2;
        dTest2.run();
    }
    // 강의 에서 사용한 코드를 구조안에 넣어서 테스트
    //  -- 키보드 이벤트 다루기, 적들 따라오기
    //  현재 키보드 관련 주석 처리 되어서 별도로 다시 손보아야.
    else if (mode == 3)
    {
        DrawTest3 dTest3;
        dTest3.run();
    }
    // 키보드 이벤트 변경 테스트
    else if (mode == 4)
    {
        DrawTest4 dTest4;
        dTest4.run();
    }

    return 0;
}

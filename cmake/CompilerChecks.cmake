# ============================================
# Файл: cmake/CompilerChecks.cmake
# ============================================

# Проверка минимальной версии компилятора
function(check_compiler_version)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
            message(FATAL_ERROR "Требуется GCC 10.0 или выше. Текущая версия: ${CMAKE_CXX_COMPILER_VERSION}")
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12.0)
            message(FATAL_ERROR "Требуется Clang 12.0 или выше. Текущая версия: ${CMAKE_CXX_COMPILER_VERSION}")
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.29)
            message(FATAL_ERROR "Требуется MSVC 19.29 (Visual Studio 16.11) или выше. Текущая версия: ${CMAKE_CXX_COMPILER_VERSION}")
        endif()
    endif()
    
    message(STATUS "Компилятор ${CMAKE_CXX_COMPILER_ID} версии ${CMAKE_CXX_COMPILER_VERSION} поддерживается")
endfunction()

# Проверка поддержки C++20 функций
function(check_cxx20_features)
    include(CheckCXXSourceCompiles)
    
    # Проверка концептов (C++20)
    set(CMAKE_REQUIRED_FLAGS "-std=c++20")
    check_cxx_source_compiles("
        template<typename T>
        concept Integral = std::is_integral_v<T>;
        
        template<Integral T>
        T add(T a, T b) { return a + b; }
        
        int main() {
            return add(1, 2);
        }
    " HAS_CONCEPTS)
    
    # Проверка корутин (C++20)
    check_cxx_source_compiles("
        #include <coroutine>
        struct task {
            struct promise_type {
                task get_return_object() { return {}; }
                std::suspend_never initial_suspend() { return {}; }
                std::suspend_never final_suspend() noexcept { return {}; }
                void return_void() {}
                void unhandled_exception() {}
            };
        };
        
        task dummy() { co_return; }
        
        int main() {
            dummy();
            return 0;
        }
    " HAS_COROUTINES)
    
    if(NOT HAS_CONCEPTS)
        message(WARNING "Компилятор не поддерживает концепты C++20")
    endif()
    
    if(NOT HAS_COROUTINES)
        message(WARNING "Компилятор не поддерживает корутины C++20")
    endif()
endfunction()
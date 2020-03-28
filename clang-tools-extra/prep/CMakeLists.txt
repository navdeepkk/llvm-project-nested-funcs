include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

set(LLVM_LINK_COMPONENTS support)

add_clang_executable(prep
  Prep.cpp
  )
target_link_libraries(prep
  PRIVATE
  clangTooling
  clangBasic
  clangASTMatchers
  clangAST
	clangLex
  clangRewrite
  clangDynamicASTMatchers
  clangFrontend
  clangSerialization
  LLVMSupport
  )



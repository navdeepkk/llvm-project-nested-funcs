include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

set(LLVM_LINK_COMPONENTS support)

add_clang_executable(hoist
  Hoist.cpp
  )
target_link_libraries(hoist
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



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

set(LLVM_LINK_COMPONENTS support)

add_clang_executable(loop-convert
  LoopConvert.cpp
  )
target_link_libraries(loop-convert
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



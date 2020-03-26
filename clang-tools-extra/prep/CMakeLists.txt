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



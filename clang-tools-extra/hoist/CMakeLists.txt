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



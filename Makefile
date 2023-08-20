help:
	@echo "Available commands:"
	@echo " clang-format\t- formats code"

clang-format:
	@find . -regex '\./\(src\|test\).*\(cpp\|hpp\)' -exec clang-format-15 -i --style=file {} \;


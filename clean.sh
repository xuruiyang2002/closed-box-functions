# Delete all directories with .bc prefix in the current directory and subdirectories
find -L . -type d -name 'klee*' -exec rm -rf {} \; -prune

# Delete all files with .bc extension in the current directory and subdirectories
find . -depth -type f -name '*.bc' -exec rm -rf {} \; -prune

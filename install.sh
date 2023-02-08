curl https://raw.githubusercontent.com/purplevarun/comment-checker-git-hook/main/hook.cc > hook-creator.cc
g++ -std=c++11 hook-creator.cc -o pre-commit
rm -rf .git/hooks/pre-commit
mv pre-commit .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
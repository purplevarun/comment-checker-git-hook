g++ -std=c++11 hook-creator.cc -o pre-commit
rm -rf .git/hooks/pre-commit
mv pre-commit .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
# download the hook-creator
curl https://raw.githubusercontent.com/purplevarun/comment-checker-git-hook/main/hook.cc > hook-creator.cc
echo "downloaded hook-creator"

# compile hook-creator and add hook
g++ -std=c++11 hook-creator.cc -o pre-commit
rm -rf .git/hooks/pre-commit
mv pre-commit .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
echo "added hook in repository"

# cleanup
rm -rf hook-creator.cc
echo "cleaned up"
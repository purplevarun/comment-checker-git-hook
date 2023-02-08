curl https://github.com/purplevarun/comment-checker-git-hook/blob/main/result/comment-checker-hook?raw=true > pre-commit
rm -rf .git/hooks/pre-commit
mv pre-commit .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
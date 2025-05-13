echo "please enter your commit message"
read commit_message
if [ -z "$commit_message" ]
then
    echo "commit message cannot be empty"
    exit 1
fi
git add .
git commit -m "$commit_message"
git push origin main
echo "git push is done"
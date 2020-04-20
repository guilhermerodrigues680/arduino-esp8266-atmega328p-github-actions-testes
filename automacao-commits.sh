#!/bin/bash

# chmod 744 -> Owner Group Public -> -rwxr--r--
# ARRAYS: https://linuxconfig.org/how-to-use-arrays-in-bash-script

files_add=(
    # .gitignore
    anotacoes.txt
    arduino-esp8266.Dockerfile
    automacao-commits.sh
    platformio.Dockerfile
    testes.Dockerfile
)

commit_msg="Update GitHub Workflow $(date)"
branch_name="master"
repo_name="origin-testes"

for file in "${files_add[@]}";
do
    echo "git add $file"
    git add $file
done

echo "git commit -m \"$commit_msg\""
git commit -m "$commit_msg"


echo "git push $repo_name $branch_name"
git remote get-url $repo_name
git push $repo_name $branch_name
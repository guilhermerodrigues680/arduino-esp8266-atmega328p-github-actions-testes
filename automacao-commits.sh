#!/bin/bash

# chmod 744 -> Owner Group Public -> -rwxr--r--
# ARRAYS: https://linuxconfig.org/how-to-use-arrays-in-bash-script

# Captura de erros
red='\e[0;31m'
green='\e[0;32m'
no_color='\e[0m'
err_report() {
    printf "${red}Erro em '$0' na linha $1. Encerrando Script.${no_color}\n"
    exit 1
}
trap 'err_report $LINENO' ERR


files_add=(
    .github/workflows/*
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

git status

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

git status
git log --oneline -n 3 | cat

github_link="https://github.com/guilhermerodrigues680/arduino-esp8266-atmega328p-github-actions-testes"
github_link+="/commit/$(git rev-parse --short HEAD)"
echo "open -a /Applications/Firefox.app -g $github_link"
open -a /Applications/Firefox.app -g "$github_link"

printf "${green}Commits enviados sem erros :) ${no_color}\n"
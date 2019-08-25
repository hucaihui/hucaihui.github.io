#!/bin/zsh
set_color="\e[32m\e[1m"
clear_color="\e[0m"
git add . &&  echo -e "$set_color git add .     done"
echo -e "$clear_color"
if [ $1 ]
then
    git commit -m "$1" && echo "$set_color git commit -m \"$1\"  done"
else
    git commit -m "update" && echo "$set_color git commit -m \"update\"  done"
fi
echo -e "$clear_color"
git push origin master && echo "$set_color git push origin master done" 
echo -e "$clear_color"
